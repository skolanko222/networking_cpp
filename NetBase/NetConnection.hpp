#pragma once

#include "NetQueue.hpp"
#include "NetMessage.hpp"

namespace net
{
	template<typename T>
	class connection : public std::enable_shared_from_this<connection<T>>
	{
	public:
		connection()
		{}
		~connection()
		{}

		bool connectToServer() 
		{}
		bool disconnect()
		{}
		bool isConnected() const
		{}
		bool send(const message<T> & m)
		{}
	private:
		asio::ip::tcp::socket socket;

		asio::io_context & context;

		// queue of messages received from server/other client
		queue<message<T>> receivedQueue;

		// queue of messages from remote to be send, that should be provided by the sender
		queue<remote_message<T>> remoteQueue;


	};

}