#include "messagebusqueue.hpp"


MessageBusQueue* MessageBusQueue::instance()
{
	if (m_instance==nullptr)
		m_instance.reset(new MessageBusQueue);
	return m_instance.get();
}

void MessageBusQueue::dispatch(std::vector< MessageBusProxyAbstract* > proxys)
{
	// TODO
}


std::unique_ptr<MessageBusQueue> MessageBusQueue::m_instance = nullptr;
