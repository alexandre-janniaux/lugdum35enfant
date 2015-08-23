#pragma once

#include <vector>
#include <memory>
#include <iostream>

template <typename T>
class MessageBusProxy;

template <typename MessageType>
class MessageBus {
	public:
		void push(const MessageType& message);

		static std::shared_ptr<MessageBus>&& getBus();

		
		MessageBus()=default;
	private:
		
		std::vector<MessageType> m_messages;
		std::vector<MessageBusProxy<MessageType>*> m_proxys;

		static std::weak_ptr<MessageBus<MessageType>> m_bus;
};

template <typename MessageType>
void MessageBus<MessageType>::push(const MessageType& message)
{
	if (m_proxys.empty())
		return;
	m_messages.push_back(message);
	// TODO: stack
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
std::weak_ptr<MessageBus<MessageType>> MessageBus<MessageType>::m_bus;
