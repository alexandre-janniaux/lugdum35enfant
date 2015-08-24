#pragma once

#include <memory>

template <typename T>
class Singleton
{
	public:
		static T* instance() {
			if (m_instance == nullptr) {
				m_instance.reset(new T);
			}
			return m_instance.get();
		}

	private:
		static std::unique_ptr<T> m_instance;
};

template <typename T>
std::unique_ptr<T> Singleton<T>::m_instance(new T);
