#pragma once
#include "NetBase.hpp"

namespace net
{
	template <typename T>
	struct header
	{
		uint32_t size = 0; // unsigned int
		T id{}; 
	};

	template <typename T>
	class message
	{
	private:
		header<T> header{};
		std::vector<uint8_t> data; // unsigned char
	public:
		size_t size() const
		{
			return data.size() + sizeof(header);
		}
		friend std::ostream& operator<<(std::ostream& o, const message<T> m)
		{
			return o << "ID: " << m.header.id << " Size:" << m.header.size;
		}
		template<typename PODdata>
		message<T>& operator << (const PODdata& d)
		{
			static_assert(std::is_pod<PODdata>::value, "Data is not POD");
			
			data.resize(data.size() + sizeof(d));

			std::memcpy(data.data() + data.size() - sizeof(d), &d, sizeof(d));

			header.size = size();

			return *this;
		}

		template<typename PODdata>
		message<T>& operator >> (PODdata& d)
		{
			static_assert(std::is_pod<PODdata>::value, "Data is not POD");

			std::memcpy(&d, data.data() + data.size() - sizeof(d), sizeof(d));

			data.resize(data.size() - sizeof(d));

			header.size = size();
						 
			return *this;

		}
	};
	template <typename T>
	class connection;
	// message from remote to be send
	template <typename T>
	class remote_message
	{
		std::shared_ptr<connection<T>> src = nullptr;
		message<T> m;
	};


}