#include "models/Player.h"
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
    std::cout << GetClassRttiName() << std::endl;
    Entity::Start();
    auto inputManager = InputManager::GetInstance();
    inputManager->AddKeyBind(sf::Keyboard::Q, new Event::Slot<>(this, &Player::MoveLeft));
    inputManager->AddKeyBind(sf::Keyboard::D, new Event::Slot<>(this, &Player::MoveRight));
    inputManager->AddKeyBind(sf::Keyboard::Space, new Event::Slot<>(this, &Player::jump), onKeyPress);
}

void Player::Update(float deltaT) {
    Entity::Update(deltaT);
    if (velocity.x < 0.02 && velocity.x > -0.02) {
        m_isWalking = false;
    }
}

void Player::MoveRight() {
    float deltaT = GameEngine::GetInstance()->GetDeltaTime();
    std::cout << deltaT << std::endl;
    m_isWalking = true;
    auto t = GetComponent<Transform>();
    auto lastPos = t->GetPosition();
    if (velocity.x < 0.02) {
        velocity.x += 0.02;
    }
    t->Translate(0, velocity.x * deltaT * 10000, 0);


    auto sprite = GetComponent<SpriteComponent>()->m_sprite;
    sprite->setOrigin({ sprite->getLocalBounds().width, 0 });
    sprite->setScale({ -1, 1 });


    if (!EntityManager::GetInstance()->MoveEntity(this))
    {
        t->SetPosition(lastPos);
    }
}

void Player::MoveLeft()
{
    float deltaT = GameEngine::GetInstance()->GetDeltaTime();
    m_isWalking = true;
    auto t = GetComponent<Transform>();
    auto lastPos = t->GetPosition();
    if (velocity.x > -0.02) {
        velocity.x += -0.02;
    }
    t->Translate(0, velocity.x * deltaT * 10000, 0);


    auto spriteComponent = GetComponent<SpriteComponent>();
    spriteComponent->m_sprite->setOrigin({ spriteComponent->m_sprite->getLocalBounds().width - spriteComponent->m_spriteSize.x, 0 });
    spriteComponent->m_sprite->setScale({ 1, 1 });


    if (!EntityManager::GetInstance()->MoveEntity(this))
    {
        t->SetPosition(lastPos);
    }
}

void Player::jump() {
    auto t = GetComponent<PhysicsComponent>();
    if (t->isGrounded) {
        float deltaT = GameEngine::GetInstance()->GetDeltaTime();
        t->isGrounded = false;
        t->jumpForce -= 200000 * deltaT;
    }
}

void Player::IsWalking(bool val) {
    if (m_isWalking == val) {
        GetComponent<Animator>()->m_changeAnim = true;
    }
    return;
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
