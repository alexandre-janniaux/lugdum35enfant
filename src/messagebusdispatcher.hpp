#pragma once

#include <algorithm>
#include <bits/stl_pair.h>
#include "messagebus.hpp"

namespace {
	using ProxyPair = std::pair<void*,void*>;
}

class MessageBusDispatcher
{
	public:
		template<typename MessageType>
		void addProxy(const MessageBusProxy<MessageType>& proxy);

		template<typename MessageType>
		void removeProxy(const MessageBusProxy<MessageType>& proxy);

		void processQueue();

	private:
		std::vector<std::pair<void*, void*>> m_proxys;
};

template<typename MessageType>
void MessageBusDispatcher::addProxy(const MessageBusProxy<MessageType>& proxy)
{
	auto search = std::find_if(m_proxys.begin(), m_proxys.end(),
		[] (const ProxyPair& proxy) { return proxy.first == &proxy; });

	if (search != m_proxys.end()) return;

	m_proxys.push_back(ProxyPair(&proxy, &MessageBus<MessageType>::getBus()));
}

template<typename MessageType>
void MessageBusDispatcher::removeProxy(const MessageBusProxy<MessageType>&proxy)
{
	auto search = std::find_if(m_proxys.begin(), m_proxys.end(),
		[] (const ProxyPair& proxy) { return proxy.first == &proxy; });

	if (search != m_proxys.end()) return;

	m_proxys.erase(search);
}

void MessageBusDispatcher::processQueue()
{
	MessageStack::instance()->dispatch(m_
}
