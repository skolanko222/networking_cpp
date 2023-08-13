#include <iostream>
#include <chrono>

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

#ifdef _WIN32
#define _WIN32_WINDOWS = 0x0A00
#endif
#define ASIO_STANDALONE

std::vector<char> vBuffer(20 * 1024);

void GrabSomeData(asio::ip::tcp::socket& socket)
{
	socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()), 
		[&](std::error_code ec, std::size_t len)
		{
			if (!ec)
			{
				std::cout << "\n\nRead" << len << " bytes\n\n";
				for (char c : vBuffer)
					std::cout << c;

				GrabSomeData(socket);
			}
		}
		
		);
}

int main()
{
	asio::error_code ec;

	asio::io_context context;

	asio::io_context::work idleWork(context);

	std::thread thrContext = std::thread([&]() {context.run(); });

	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("2001:41d0:2:7530::1001", ec), 80);;

	asio::ip::tcp::socket socket(context);

	socket.connect(endpoint, ec);

	if (!ec)
	{
		std::cout << "Connected!" << std::endl;
	}
	else
	{
		std::cout << "Failed!" << ec.message() << std::endl;
	}
	if (socket.is_open())
	{
		GrabSomeData(socket);

		std::string sRequest =
			"GET /index.html HTTP/1.1\r\n"
			"Host: example.com\r\n"
			"Connection: close\r\n\r\n";
		socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

	}
	thrContext.join();

	return 0;
}