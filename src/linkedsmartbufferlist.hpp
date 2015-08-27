#pragma once

#include <list>
#include <vector>
#include <algorithm>

template <typename T>
class LinkedSmartBufferList {
	public:
		LinkedSmartBufferList(std::size_t buffer_size=100);
		
		void pop_front_buffer();
		
		void push_back(const T& element);
		
		T& operator[](const std::size_t& at);
		const T& operator[](const std::size_t& at) const;
		
		T& at(const std::size_t& at);
		const T& at(const std::size_t& at) const;
		
		std::size_t buffer_size() const;
		
		std::size_t size() const;
		
	private:
		using Buffer = std::vector<T>;
		std::size_t m_bufferSize;
		std::size_t m_size;
		std::list<std::vector<T>*> m_buffers;
		Buffer* m_lastBuffer;
	
};


template <typename T>
LinkedSmartBufferList<T>::LinkedSmartBufferList(std::size_t bufferSize) :
m_bufferSize(bufferSize),
m_size(0)
{
	// TODO: not safe
	auto buffer = new std::vector<T>;
	buffer->reserve(m_bufferSize);
	m_buffers.push_back(buffer);
	m_lastBuffer = buffer;
	
}

template <typename T>
T& LinkedSmartBufferList<T>::operator[](const std::size_t& index)
{
	LinkedSmartBufferList::Buffer* buffer = *std::advance(m_buffers.begin(), index / m_bufferSize);
	return buffer[index%m_bufferSize];
}

// TODO : automatic const version ? 
template <typename T>
const T& LinkedSmartBufferList<T>::operator[](const std::size_t& index) const
{
	LinkedSmartBufferList::Buffer* buffer = *std::advance(m_buffers.begin(), index / m_bufferSize);
	return buffer[index%m_bufferSize];
}

template <typename T>
T& LinkedSmartBufferList<T>::at(const std::size_t& index) 
{
	auto iterator = m_buffers.begin();
	std::advance(iterator, index / m_bufferSize);
	LinkedSmartBufferList::Buffer* buffer = *iterator;
	return buffer->at(index%m_bufferSize);
}

// TODO : automatic const version ?
template <typename T>
const T& LinkedSmartBufferList<T>::at(const std::size_t& index) const
{
	LinkedSmartBufferList::Buffer* buffer = *std::advance(m_buffers.begin(), index / m_bufferSize);
	return buffer->at(index%m_bufferSize);
}

template <typename T>
void LinkedSmartBufferList<T>::push_back(const T& element)
{
	m_lastBuffer->push_back(element);
	if (m_lastBuffer->size() == m_bufferSize)
	{
			m_buffers.push_back(new LinkedSmartBufferList::Buffer);
			m_lastBuffer = m_buffers.back();
			m_lastBuffer->reserve(m_bufferSize);
	}
	m_size += 1;
}

template <typename T>
std::size_t LinkedSmartBufferList<T>::buffer_size() const
{
	return m_bufferSize;
}

template <typename T>
void LinkedSmartBufferList<T>::pop_front_buffer() 
{	
	auto buffer = m_buffers.front();
	m_size -= buffer->size();
	if (m_buffers.size() == 1) {
		buffer->clear();
	}
	else {
		m_buffers.pop_front();
		delete buffer;
	}
}

template <typename T>
std::size_t LinkedSmartBufferList<T>::size() const
{
	return m_size;
}
