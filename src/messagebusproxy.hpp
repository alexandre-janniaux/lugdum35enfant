#pragma once

#include <functional>
#include <memory>

template <typename MessageType>
class MessageBusProxy {
	public:
		using Callback = std::function<void, const MessageType&>;
		MessageBusProxy(Callback callback);

		bool read();

	private:
		std::shared_ptr<MessageBus<MessageType>> m_bus;
		std::function m_callback;

};

#include "messagebus.hpp"

template <typename MessageType>
MessageBusProxy<MessageType>::MessageBusProxy(Callback callback) :
	m_callback(callback)
{
	m_bus = MessageBus<MessageType>::getBus();
}
