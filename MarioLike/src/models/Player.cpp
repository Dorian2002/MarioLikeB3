#include "models/Player.h"
#include "managers/EntityManager.h"
Player::Player() {
    MarioRun* run = new MarioRun(AssetManager::GetInstance()->GetTexture("littleMarioRun"), 3);
    MarioIdle* idle = new MarioIdle(AssetManager::GetInstance()->GetTexture("littleMarioIdle"), 1);
    Components = {
        new Transform(this, {2,10}),
        new SpriteComponent(this, "littleMarioIdle"),
        new PhysicsComponent(this, true),
        new BoxColliderComponent(this, new Vec2f{16,16}),
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
    inputManager->AddKeyBind(sf::Keyboard::Space, new Event::Slot<>(this, &Player::jump), onKeyHeld);
}

void Player::Update(float deltaT) {
    auto t = GetComponent<PhysicsComponent>();
    if (t->isJumping)
    {
        speedCoefficient = 5.f;
    }
    else
    {
        speedCoefficient = 100.f;
    }
    Entity::Update(deltaT);
# define multiplier speedCoefficient * deltaT
    if (left)
    {
        SetVelX(-3.f * multiplier);
        auto spriteComponent = GetComponent<SpriteComponent>();
        spriteComponent->m_sprite->setOrigin({ spriteComponent->m_sprite->getLocalBounds().width - spriteComponent->m_spriteSize.x, 0 });
        spriteComponent->m_sprite->setScale({ 1, 1 });
    }
    if (right)
    {
        SetVelX(3.f * multiplier);
        auto sprite = GetComponent<SpriteComponent>()->m_sprite;
        sprite->setOrigin({ sprite->getLocalBounds().width, 0 });
        sprite->setScale({ -1, 1 });
    }
    if (!left && !right)
    {
        if (t->velocity.x > 0)
        {
            SetVelX(-3.f * multiplier);
        }
        if (t->velocity.x < 0)
        {
            SetVelX(3.f * multiplier);
        }
    }
    if (t->velocity.x < 0.5f * speedCoefficient / 100 && t->velocity.x > -0.5f * speedCoefficient / 100) {
        t->velocity.x = 0;
    }
    auto dist = t->velocity.x * deltaT;

    if (dist > 0)
    {
        Move(dist);
    }
    else
    {
        Move(dist);
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
void Player::SetVelX(float acceleration)
{
    GetComponent<PhysicsComponent>()->velocity.x = std::clamp(GetComponent<PhysicsComponent>()->velocity.x + acceleration, -6.f, 6.f);
}

void Player::StartRight()
{
    right = true;
}

void Player::StopRight()
{
    right = false;
}

void Player::StopLeft()
{
    left = false;
}

void Player::StartLeft()
{
    left = true;
}

void Player::jump() {
    auto t = GetComponent<PhysicsComponent>();
    if (t->isGrounded) {
        if (t->isGrounded) {
            t->velocity.y = -10.f;
            t->isGrounded = false;
            t->isJumping = true;
        }
    }
}

void Player::IsWalking(bool val) {
    if ((GetComponent<PhysicsComponent>()->velocity.x != 0) == val) {
        GetComponent<Animator>()->m_changeAnim = true;
    }
}

void Player::SetUpAnimatorLink(Animation* run, Animation* idle) {
    Animator* animator = GetComponent<Animator>();

    Event::Signal<bool>* sigRunToIdle = new Event::Signal<bool>();
    sigRunToIdle->connect(new Event::Slot<bool>(this, &Player::IsWalking));
    animator->CreateLink(run, idle, sigRunToIdle, false);

    Event::Signal<bool>* sigIdleToRun = new Event::Signal<bool>();
    sigIdleToRun->connect(new Event::Slot<bool>(this, &Player::IsWalking));
    animator->CreateLink(idle, run, sigIdleToRun, true);
}
