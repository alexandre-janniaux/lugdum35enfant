#include "messagestack.hpp"


MessageStack* MessageStack::instance()
{
	if (m_instance==nullptr)
		m_instance.reset(new MessageStack);
	return m_instance.get();
}

std::unique_ptr<MessageStack> MessageStack::m_instance = nullptr;
