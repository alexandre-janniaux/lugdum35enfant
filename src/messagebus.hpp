#pragma once

#include <deque>
#include <queue>
#include <memory>
#include <iostream>
#include <map>
#include <utility>
#include "messagestack.hpp"

template <typename T>
class MessageBusProxy;

namespace {
	using Cursor = long unsigned int;

}

template <typename MessageType>
class MessageBus {
	public:

		MessageBus()=default;

		void push(const MessageType& message);

		static std::shared_ptr<MessageBus>&& getBus();

		MessageType* next(MessageBusProxy<MessageType>* proxy);

	private:
		using MessageQueue = std::deque<std::pair<Cursor, MessageType>>;
		friend class MessageBusProxy<MessageType>;

		void registerProxy(MessageBusProxy<MessageType>* proxy);
		void unregisterProxy(MessageBusProxy<MessageType>* proxy);
		
		MessageQueue m_messages;
		std::map<MessageBusProxy<MessageType>*, typename MessageQueue::iterator> m_proxys;

		static std::weak_ptr<MessageBus<MessageType>> m_bus;
};

template <typename MessageType>
void MessageBus<MessageType>::push(const MessageType& message)
{
	if (m_proxys.size() == 0)
		return;
	Cursor message_id = MessageStack::instance()->push<MessageType>();
	m_messages.push_back(std::pair<Cursor, MessageType>(message_id, message));
}

template <typename MessageType>
std::shared_ptr<MessageBus<MessageType>>&& MessageBus<MessageType>::getBus()
{
	if (m_bus.expired())
	{
		std::cout << "bus expired"<< std::endl;
		auto ptr = std::make_shared<MessageBus<MessageType>>();
		m_bus = std::weak_ptr<MessageBus<MessageType>>(ptr);
		return std::move(ptr);
	}
	return std::move(m_bus.lock());
}

template <typename MessageType>
void MessageBus<MessageType>::registerProxy(MessageBusProxy<MessageType>* proxy) {
	m_proxys.insert(std::make_pair(proxy, --m_messages.end()));
}

template <typename MessageType>
void MessageBus<MessageType>::unregisterProxy(MessageBusProxy<MessageType>* proxy) {
	auto _search = m_proxys.find(proxy);
	if (_search == m_proxys.end())
		return;
	m_proxys.erase(_search);
}

template <typename MessageType>
MessageType* MessageBus<MessageType>::next(MessageBusProxy<MessageType>* proxy) {
	// TODO : implement next function
}

template <typename MessageType>
std::weak_ptr<MessageBus<MessageType>> MessageBus<MessageType>::m_bus;
