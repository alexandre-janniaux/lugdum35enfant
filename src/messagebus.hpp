#pragma once

#include <vector>
#include <memory>

class MessageBusProxy;

template <typename MessageType>
class MessageBus {
	public:
		void push(const MessageType& message);


	private:
		MessageBus();

		static std::shared_ptr<MessageBus>&& getBus();

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
	if (m_bus == nullptr)
	{
		auto ptr = std::make_shared<MessageBus<MessageType>>();

	}
}

