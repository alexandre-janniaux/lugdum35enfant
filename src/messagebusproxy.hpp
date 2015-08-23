#pragma once

#include <functional>
#include <memory>

template <typename T>
class MessageBus;

class MessageBusProxyAbstract {
	private:
		friend class MessageBusQueue;
		virtual bool readOne()=0;
		virtual void* const getBusAddress() const=0;

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
		void* const getBusAddress() const override;
		MessageBus<MessageType>* m_bus;
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
void* const MessageBusProxy<MessageType>::getBusAddress() const
{
	return static_cast<void*>(m_bus);
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
