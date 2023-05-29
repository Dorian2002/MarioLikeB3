#include "models/Player.h"
#include "managers/EntityManager.h"
#include "models/Coin.h"
#include "models/Block.h"
#include "models/Boomba.h"

Player::Player() {
    MarioRun* run = new MarioRun(AssetManager::GetInstance()->GetTexture("littleMarioRun"), 3);
    MarioIdle* idle = new MarioIdle(AssetManager::GetInstance()->GetTexture("littleMarioIdle"), 1);
    Components = {
        new Transform(this, {2,0}),
        new SpriteComponent(this, "littleMarioIdle"),
        new PhysicsComponent(this, true),
        new BoxColliderComponent(this, {16,16}, false),
        new Animator(
            this,
            std::vector<Animation*>{
                run,
                idle
             }
        )
    };
    SetUpAnimatorLink(run, idle);
}

void Player::Start() {
    Entity::Start();
    auto inputManager = InputManager::GetInstance();
    inputManager->AddKeyBind(sf::Keyboard::Q, new Event::Slot<>(this, &Player::StartLeft), onKeyPress);
    inputManager->AddKeyBind(sf::Keyboard::D, new Event::Slot<>(this, &Player::StartRight), onKeyPress);
    inputManager->AddKeyBind(sf::Keyboard::Q, new Event::Slot<>(this, &Player::StopLeft), onKeyRelease);
    inputManager->AddKeyBind(sf::Keyboard::D, new Event::Slot<>(this, &Player::StopRight), onKeyRelease);
    inputManager->AddKeyBind(sf::Keyboard::Left, new Event::Slot<>(this, &Player::StartLeft), onKeyPress);
    inputManager->AddKeyBind(sf::Keyboard::Right, new Event::Slot<>(this, &Player::StartRight), onKeyPress);
    inputManager->AddKeyBind(sf::Keyboard::Left, new Event::Slot<>(this, &Player::StopLeft), onKeyRelease);
    inputManager->AddKeyBind(sf::Keyboard::Right, new Event::Slot<>(this, &Player::StopRight), onKeyRelease);
    inputManager->AddKeyBind(sf::Keyboard::Space, new Event::Slot<>(this, &Player::Jump), onKeyHeld);
}

void Player::Update(float deltaT) {
    auto t = GetComponent<PhysicsComponent>();
    if (t->m_isJumping)
    {
        m_speedCoefficient = 2.f;
    }
    else
    {
        m_speedCoefficient = 100.f;
    }
    Entity::Update(deltaT);
    if (m_left)
    {
        SetVelX(-3.f * m_speedCoefficient * deltaT);
        if (t->m_velocity.x < 0)
        {
            auto spriteComponent = GetComponent<SpriteComponent>();
            spriteComponent->m_sprite->setOrigin({ spriteComponent->m_sprite->getLocalBounds().width - spriteComponent->m_spriteSize.x, 0 });
            spriteComponent->m_sprite->setScale({ 1, 1 });
        }
    }
    if (m_right)
    {
        SetVelX(3.f * m_speedCoefficient * deltaT);
        if (t->m_velocity.x > 0) {
            auto sprite = GetComponent<SpriteComponent>()->m_sprite;
            sprite->setOrigin({ sprite->getLocalBounds().width, 0 });
            sprite->setScale({ -1, 1 });
        }
    }
    if (!m_left && !m_right)
    {
        if (t->m_velocity.x > 0)
        {
            SetVelX(-3.f * m_speedCoefficient * deltaT, 0);
        }
        if (t->m_velocity.x < 0)
        {
            SetVelX(3.f * m_speedCoefficient * deltaT, -6.f, 0);
        }
    }
}

void Player::Move(float dist)
{
    float val = 0.99f;
    bool isNegative = dist < 0;
    if (isNegative)
        dist = -dist;
    while (dist > val)
    {
	    if (!EntityManager::GetInstance()->MoveEntity(this, Vec2f(isNegative ? -val : val, 0)))
	    {
	        break;
	    }
	    dist -= val;
    }
    if (isNegative)
    {
        if (-dist < 0 && -dist >= -val)
        {
            EntityManager::GetInstance()->MoveEntity(this, Vec2f(-dist, 0));
        }
    }
    else
    {
        if (dist > 0 && dist <= val)
        {
            EntityManager::GetInstance()->MoveEntity(this, Vec2f(dist, 0));
        }
    }
}
void Player::SetVelX(float acceleration, float min, float max)
{
    GetComponent<PhysicsComponent>()->m_velocity.x = std::clamp(GetComponent<PhysicsComponent>()->m_velocity.x + acceleration, min, max);
}

void Player::StartRight()
{
    m_right = true;
}

void Player::StopRight()
{
    m_right = false;
}

void Player::StopLeft()
{
    m_left = false;
}

void Player::StartLeft()
{
    m_left = true;
}

void Player::Jump() {
    auto t = GetComponent<PhysicsComponent>();
    if (t->m_isGrounded) {
        if (t->m_isGrounded) {
            t->m_velocity.y = -10.f;
            t->m_isGrounded = false;
            t->m_isJumping = true; 
        }
    }
}

bool Player::IsWalking() {
    if (GetComponent<PhysicsComponent>()->m_velocity.x != 0) {
        return true;
    }
    return false;
}

void Player::AnimIsWalking(bool val)
{
    if ((GetComponent<PhysicsComponent>()->m_velocity.x != 0) == val) {
        GetComponent<Animator>()->m_changeAnim = true;
    }
}

void Player::OnCollide(Component* overlapComponent, Entity* overlapEntity)
{
	if(overlapEntity->GetClassRttiName() == Block::GetStaticRName())
	{
        return;
	}
}

void Player::OnOverlap(Component* overlapComponent, Entity* overlapEntity)
{
	if (overlapEntity->GetClassRttiName() == Coin::GetStaticRName())
    {
        m_coins++;
        EntityManager::GetInstance()->DeleteEntity(overlapEntity);
        return;
    }
    if (overlapEntity->GetClassRttiName() == Boomba::GetStaticRName())
    {
        if (GetComponent<Transform>()->GetPosition().y + 0.9f <= overlapEntity->GetComponent<Transform>()->GetPosition().y)
        {
            EntityManager::GetInstance()->DeleteEntity(overlapEntity);
        }
        else
        {
            GameEngine::GetInstance()->BackToMenu();
        }
        
    }
}

int* Player::GetCoinCount()
{
    return &m_coins;
}

//Method that set up links between animations
void Player::SetUpAnimatorLink(Animation* run, Animation* idle)
{
    Animator* animator = GetComponent<Animator>();

    Event::Signal<bool>* sigRunToIdle = new Event::Signal<bool>();
    Event::SlotKey sig1Key = sigRunToIdle->connect(new Event::Slot<bool>(this, &Player::AnimIsWalking));
    animator->CreateLink(run, idle, sigRunToIdle, false, &sig1Key);

    Event::Signal<bool>* sigIdleToRun = new Event::Signal<bool>();
    Event::SlotKey sig2Key = sigIdleToRun->connect(new Event::Slot<bool>(this, &Player::AnimIsWalking));
    animator->CreateLink(idle, run, sigIdleToRun, true, &sig2Key);
}

