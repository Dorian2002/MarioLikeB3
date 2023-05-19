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
        speedCoefficient = 0.08f;
    }
    else
    {
        speedCoefficient = 1.0f;
    }
    Entity::Update(deltaT);
    if (left)
    {
        SetVelX(-0.05f * speedCoefficient);
        if (velocity.x < 0)
        {
            auto spriteComponent = GetComponent<SpriteComponent>();
            spriteComponent->m_sprite->setOrigin({ spriteComponent->m_sprite->getLocalBounds().width - spriteComponent->m_spriteSize.x, 0 });
            spriteComponent->m_sprite->setScale({ 1, 1 });
        }
        m_isWalking = true;
    }
    if (right)
    {
        SetVelX(0.05f * speedCoefficient);
        if (velocity.x > 0)
        {
            auto sprite = GetComponent<SpriteComponent>()->m_sprite;
            sprite->setOrigin({ sprite->getLocalBounds().width, 0 });
            sprite->setScale({ -1, 1 });
        }

        m_isWalking = true;
    }
    if (!left && !right)
    {
        if (velocity.x > 0)
        {
            SetVelX(-0.05f * speedCoefficient);
        }
        if (velocity.x < 0)
        {
            SetVelX(0.05f * speedCoefficient);
        }
        m_isWalking = false;
    }
    if (velocity.x < 0.05f * speedCoefficient && velocity.x > -0.05f * speedCoefficient) {
        velocity.x = 0;
        m_isWalking = false;
    }
    auto dist = velocity.x * deltaT;

    if (dist > 0)
    {
        Move(dist, 0.99f);
    }
    else
    {
        Move(dist, -0.99f);
    }
}

void Player::Move(float dist, float val)
{
    bool collide = false;
    while (dist < -0.99f)
    {
        collide = EntityManager::GetInstance()->MoveEntity(this, Vec2f(val, 0));
        if (collide)
            break;
        dist -= val;
    }
    if (!collide)
    {
        EntityManager::GetInstance()->MoveEntity(this, Vec2f(dist, 0));
    }
}
void Player::SetVelX(float acceleration)
{
    velocity.x = std::clamp(velocity.x + acceleration, -1.f, 1.f);
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
            t->jumpForce = -.18f;
            t->isGrounded = false;
            t->isJumping = true;
        }
    }
}

void Player::IsWalking(bool val) {
    if ((velocity.x != 0) == val) {
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
