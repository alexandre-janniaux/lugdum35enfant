#pragma once

#include <deque>
#include <memory>
#include <vector>
#include <map>

class MessageBusProxyAbstract;

namespace {
	using Cursor = long unsigned int;
}

class MessageProxy
{
	public:
		template <typename T>
		static MessageProxy create();


	private:
		MessageProxy()=default;
		void* m_busAddress;
};


class MessageBusQueue
{
	public:
		static MessageBusQueue* instance();
		template<typename T>
		void push();

		void dispatch(std::vector<MessageBusProxyAbstract*> proxys);

	private:
		using MessageQueue = std::deque<MessageProxy>;

		MessageBusQueue()=default;

		static std::unique_ptr<MessageBusQueue> m_instance;

		MessageQueue m_messages;
		std::map<MessageBusProxyAbstract*, typename MessageQueue::iterator> m_proxys;
};

#include "messagebus.hpp"

template <typename MessageType>
MessageProxy MessageProxy::create()
{
	MessageProxy proxy;
	proxy.m_busAddress = static_cast<void*>(MessageBus<MessageType>::getBus());
	return proxy;
}

template <typename MessageType>
void MessageBusQueue::push()
{
	m_messages.push_back(MessageProxy::create<MessageType>());
}
