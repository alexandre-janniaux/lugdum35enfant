#pragma once

#include <functional>
#include <memory>

template <typename T>
class MessageBus;

class MessageBusProxyAbstract {
	private:
		friend class MessageStack;
		virtual bool readOne()=0;
};


template <typename MessageType>
class MessageBusProxy : public MessageBusProxyAbstract {
	public:
		using Callback = std::function<void(const MessageType&)>;
		MessageBusProxy(Callback callback);
		~MessageBusProxy();

		void readAll();
		bool readOne() override;

	private:
		std::shared_ptr<MessageBus<MessageType>> m_bus;
		Callback m_callback;
};

#include "messagebus.hpp"

template <typename MessageType>
MessageBusProxy<MessageType>::MessageBusProxy(Callback callback) :
	m_callback(callback)
{
	m_bus = MessageBus<MessageType>::getBus() ;
	m_bus->registerProxy(this);
}

template <typename MessageType>
MessageBusProxy<MessageType>::~MessageBusProxy()
{
	m_bus->unregisterProxy(this);
}

template <typename MessageType>
bool MessageBusProxy<MessageType>::readOne()
{
	auto message = MessageBus<MessageType>::getBus()->next(this);
	if (message != nullptr)
	{
		m_callback(*message);
		return true;
	}
	return false;
}

template <typename MessageType>
void MessageBusProxy<MessageType>::readAll()
{
	while(readOne());
}
