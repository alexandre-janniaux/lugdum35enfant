#pragma once

#include <deque>
#include <memory>

namespace {
	using Cursor = long unsigned int;
}

class MessageProxy
{
	public:
		template <typename T>
		static MessageProxy create();

	private:
		MessageProxy();
		void* m_busAddress;
		Cursor m_cursor;
};


class MessageStack
{
	public:
		static MessageStack* instance();
		template<typename T>
		Cursor push();

	private:
		MessageStack()=default;
		std::deque<MessageProxy> m_messages;

		static std::unique_ptr<MessageStack> m_instance;

};

template <typename MessageType>
Cursor MessageStack::push()
{

}

