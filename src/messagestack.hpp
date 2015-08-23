#pragma once

class MessageProxy
{
	public:
		template <typename T>
		static MessageProxy create();

	private:
		MessageProxy();
		void* m_busAddress;
};


class MessageStack
{
	public:
		

	private:
		MessageStack();
		std::deque<MessageProxy> m_messages;

};
