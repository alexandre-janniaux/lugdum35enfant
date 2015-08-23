#pragma once

#include <vector>
#include <memory>

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
	m_messages.push_back(message);
	// TODO: stack
}

template <typename MessageType>
std::shared_ptr<MessageBus<MessageType>>&& MessageBus<MessageType>::getBus()
{
	if (m_bus.expired())
	{
		auto ptr = std::make_shared<MessageBus<MessageType>>();

	}
}

template <typename MessageType>
std::weak_ptr<MessageBus<MessageType>> MessageBus<MessageType>::m_bus;