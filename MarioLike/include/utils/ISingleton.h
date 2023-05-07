#pragma once
template <typename T>
class ISingleton
{
public:
	static T* GetInstance();
private:
	static T* m_instance;
};