#include "manager/GameManager.h"


GameManager* GameManager::m_instance = nullptr;
GameManager* GameManager::GetInstance()
{
    if (m_instance == nullptr) {
        m_instance = new GameManager();
    }

    return m_instance;

}

GameManager::~GameManager() {
    if (m_instance != nullptr)
    {
        delete m_instance;
    }
}

bool GameManager::Run(const std::string& _title, const Vec2i& _size)
{
    return true;
}

bool GameManager::LoadResources()
{
    return true;
}