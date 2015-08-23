#pragma once

#include <algorithm>
#include <string>
#include <map>
#include <bits/stl_pair.h>
#include "messagebus.hpp"

class MessageBusDispatcher
{
	public:
		template<typename MessageType>
		void listen(const std::string& name, std::function<void(MessageType&)> callback);

		template<typename MessageType>
		void remove(const std::string& name);

		void processQueue();

	private:
		std::map<std::string, std::unique_ptr<MessageBusProxyAbstract>> m_proxys;
};

template<typename MessageType>
void MessageBusDispatcher::listen(const std::string& name, std::function<void(MessageType&)> callback)
{
	auto search = m_proxys.find(name);

	if (search == m_proxys.end())
		m_proxys[name].reset(new MessageBusProxy<MessageType>(callback);

	m_proxys.emplace(name, new MessageBusProxy<MessageType>(callback));
}

template<typename MessageType>
void MessageBusDispatcher::remove(const std::string& name)
{
	auto search = m_proxys.find(name);

	if (search == m_proxys.end()) return;

	m_proxys.erase(search);
}

void MessageBusDispatcher::processQueue()
{
	MessageBusQueue::instance()->dispatch(m_proxys);
}
