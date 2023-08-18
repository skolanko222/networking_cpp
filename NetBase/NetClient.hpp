#pragma once

#include "NetQueue.hpp"
#include "NetMessage.hpp"
#include "NetConnection.hpp"

namespace net
{
	template <typename T>
	class client
	{
	public:
		client()
		{}
		~client()
		{}
		bool connect(const char* addres, const uint16_t port)
		{
			try
			{
				// connection = std::make_unique< connection<T>>();

				asio::ip::tcp::resolver resol(context);
				// resol.resolve(addres, std::to_string(port)); 

				// connection->connectToServer();

				thrContext = std::thread([this]() {context.run(); });

			}
			catch (std::exception& e)
			{

			}
			return false;
		}
		bool disconnect()
		{

			if (isConnected())
			{
				connection->disconnect();

			}
			context.stop();

			if (thrContext.joinable())
				thrContext.join();

			return false;

		}
		bool isConnected()
		{
			if (connection)
			{
				return connection->isConnected();
			}
			return false;

		}
		auto& getRQueue()
		{
			return remoteQueue;
		}

	private:
		queue<remote_message<T>> remoteQueue;

		asio::io_context context;
		std::thread thrContext;

		asio::ip::tcp::socket socket;
		std::unique_ptr<connection<T>> connection = nullptr; 
	};


}
