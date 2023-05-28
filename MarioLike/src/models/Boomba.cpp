#include "models/Boomba.h"
#include "managers/EntityManager.h"

Boomba::Boomba()
{
    BoombaRun* run = new BoombaRun(AssetManager::GetInstance()->GetTexture("boombaRun"), 2);
    BoombaIdle* idle = new BoombaIdle(AssetManager::GetInstance()->GetTexture("boombaIdle"), 1);
    Components = {
        new Transform(this, {2,10}),
        new SpriteComponent(this, "boombaIdle"),
        new PhysicsComponent(this, true),
        new BoxColliderComponent(this, {16,16}, false),
        new Animator(
            this,
            std::vector<Animation*>{
                run,
                idle
            }
        ),
        new BoombaBT(this)
    };
    SetUpAnimatorLink(run, idle);
}

void Boomba::Start()
{
    std::cout << GetClassRttiName() << std::endl;
    Entity::Start();
}

void Boomba::Update(float deltaT)
{
    Entity::Update(deltaT);
    if (velocity.x < 0.02 && velocity.x > -0.02) {
        m_isWalking = false;
    }
}

bool Boomba::MoveRight()
{
    float deltaT = GameEngine::GetInstance()->GetDeltaTime();
    auto t = GetComponent<Transform>();
    m_isWalking = true;
    auto lastPos = t->GetPosition();
    lastPos.x -= 0.05;
    if (velocity.x < 0.02) {
        velocity.x += 0.02;
    }
    t->Translate(0, velocity.x * deltaT * 300, 0);


    auto sprite = GetComponent<SpriteComponent>()->m_sprite;
    sprite->setOrigin({ sprite->getLocalBounds().width, 0 });
    sprite->setScale({ -1, 1 });


    if (!EntityManager::GetInstance()->MoveEntity(this))
    {
        t->SetPosition(lastPos);
        std::cout << "collide right" << std::endl;
        return false;
    }
    return true;
}

bool Boomba::MoveLeft()
{
    float deltaT = GameEngine::GetInstance()->GetDeltaTime();
    m_isWalking = true;
    auto t = GetComponent<Transform>();
    auto lastPos = t->GetPosition();
    lastPos.x += 0.05;
    if (velocity.x > -0.02) {
        velocity.x += -0.02;
    }
    t->Translate(0, velocity.x * deltaT * 300, 0);


    auto spriteComponent = GetComponent<SpriteComponent>();
    spriteComponent->m_sprite->setOrigin({ spriteComponent->m_sprite->getLocalBounds().width - spriteComponent->m_spriteSize.x, 0 });
    spriteComponent->m_sprite->setScale({ 1, 1 });


    if (!EntityManager::GetInstance()->MoveEntity(this))
    {
        t->SetPosition(lastPos);
        std::cout << "collide left : " << lastPos.x << lastPos.y << std::endl;
        return false;
    }
    return true;
}

void Boomba::IsWalking(bool val)
{
    if (m_isWalking == val) {
        GetComponent<Animator>()->m_changeAnim = true;
    }
}

void Boomba::SetUpAnimatorLink(Animation* run, Animation* idle)
{
    Animator* animator = GetComponent<Animator>();

    Event::Signal<bool>* sigRunToIdle = new Event::Signal<bool>();
    Event::SlotKey sig1Key = sigRunToIdle->connect(new Event::Slot<bool>(this, &Boomba::IsWalking));
    animator->CreateLink(run, idle, sigRunToIdle, false, &sig1Key);

    Event::Signal<bool>* sigIdleToRun = new Event::Signal<bool>();
    Event::SlotKey sig2Key = sigIdleToRun->connect(new Event::Slot<bool>(this, &Boomba::IsWalking));
    animator->CreateLink(idle, run, sigIdleToRun, true, &sig2Key);
}
