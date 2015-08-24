#pragma once

#include <deque>
#include <memory>
#include <iostream>
#include <map>
#include <utility>

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

		template<typename ResponseType>
		const std::vector<ResponseType>&& request(const MessageType& message);

		static MessageBus<MessageType>* getBus();

		MessageType* next(MessageBusProxy<MessageType>* proxy);

	private:
		using MessageQueue = std::deque<MessageType>;
		friend class MessageBusProxy<MessageType>;

		void registerProxy(MessageBusProxy<MessageType>* proxy);
		void unregisterProxy(MessageBusProxy<MessageType>* proxy);
		
		MessageQueue m_messages;
		std::map<MessageBusProxy<MessageType>*, typename MessageQueue::iterator> m_proxys;

		static std::unique_ptr<MessageBus<MessageType>> m_bus;
};

#include "messagebusqueue.hpp"
#include "messagebusproxy.hpp"

template <typename MessageType>
void MessageBus<MessageType>::push(const MessageType& message)
{
	if (m_proxys.size() == 0)
		return;
	MessageBusQueue::instance()->push<MessageType>();
	m_messages.push_back(message);
}

template <typename MessageType>
MessageBus<MessageType>* MessageBus<MessageType>::getBus()
{
	if (m_bus == nullptr)
	{
		std::cout << "bus expired"<< std::endl;
		m_bus.reset(new MessageBus<MessageType>());
	}
	return m_bus.get();
}

template <typename MessageType>
void MessageBus<MessageType>::registerProxy(MessageBusProxy<MessageType>* proxy) {
	auto cursor = m_messages.begin();
	if (m_messages.size() > 0)
		std::advance(cursor, m_messages.size()-1);
	m_proxys.emplace(proxy, cursor);
}

template <typename MessageType>
void MessageBus<MessageType>::unregisterProxy(MessageBusProxy<MessageType>* proxy) {
	auto _search = m_proxys.find(proxy);
	if (_search == m_proxys.end())
		return;
	m_proxys.erase(_search);

	if (m_proxys.size() == 0)
		delete m_bus.release();
}

template <typename MessageType>
MessageType* MessageBus<MessageType>::next(MessageBusProxy<MessageType>* proxy) {
	// TODO : implement next function
	auto& iterator = m_proxys.at(proxy);
	if (iterator == m_messages.end())
		return nullptr;
	return &*(iterator++);
}

template <typename MessageType>
std::unique_ptr<MessageBus<MessageType>> MessageBus<MessageType>::m_bus = nullptr;

template <typename MessageType>
void SendMessage(const MessageType& message) {
	MessageBus<MessageType>::getBus()->push(message);
}

template <typename MessageType, typename ResponseType>
const std::vector<ResponseType>&& RequestMessage(const MessageType& message)
{
	MessageBus<MessageType>::getBus()->request(message);
}

template <typename MessageType, typename ResponseType>
const ResponseType& RequestUnique(const MessageType& message)
{
	auto& response = RequestMessage<MessageType, ResponseType>(message);
	if (response.size() != 1) throw std::runtime_error("More than 1 response");
	return response[0];
}

