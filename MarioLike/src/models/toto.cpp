#include "models/toto.h"
#include "engine/GameEngine.h"

void toto::MoveRight()
{
    m_isWalking = true;
    auto t = GetComponent<Transform>();
    auto lastPos = t->GetPosition();
    if (velocity.x < 0.1) {
        velocity.x += 0.1;
    }
    t->Translate(0, velocity.x, 0);


    auto sprite = GetComponent<SpriteComponent>()->m_sprite;
    sprite->setOrigin({ sprite->getLocalBounds().width, 0 });
    sprite->setScale({ -1, 1 });


    if (!EntityManager::GetInstance()->MoveEntity(this))
    {
        t->SetPosition(lastPos);
    }
}

void toto::MoveLeft()
{
    m_isWalking = true;

    auto t = GetComponent<Transform>();
    auto lastPos = t->GetPosition();
    if (velocity.x > -0.1) {
        velocity.x += -0.1;
    }
    t->Translate(0, velocity.x, 0);


    auto spriteComponent = GetComponent<SpriteComponent>();
    spriteComponent->m_sprite->setOrigin({ spriteComponent->m_sprite->getLocalBounds().width - spriteComponent->m_spriteSize.x, 0 });
    spriteComponent->m_sprite->setScale({ 1, 1 });


    if (!EntityManager::GetInstance()->MoveEntity(this))
    {
        t->SetPosition(lastPos);
    }
}

void toto::jump()
{
    auto t = GetComponent<PhysicsComponent>();
    if (t->isGrounded) {
        float deltaT = GameEngine::GetInstance()->GetDeltaTime();
        t->isGrounded = false;
        t->jumpForce -= 200000 * deltaT;
    }
}
