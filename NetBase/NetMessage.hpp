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
		friend message<T>& operator << (message<T>& m, const PODdata& d)
		{
			static_assert(std::is_pod<PODdata>::value, "Data is not POD");
			
			m.data.resize(m.data.size() + sizeof(d));

			std::memcpy(m.data.data() + m.data.size() - sizeof(d), &d, sizeof(d));

			m.header.size = m.size();

			return m;
		}

		template<typename PODdata>
		friend message<T>& operator >> (message<T>& m, PODdata& d)
		{
			static_assert(std::is_pod<PODdata>::value, "Data is not POD");

			std::memcpy(&d, m.data.data() + m.data.size() - sizeof(d), sizeof(d));

			m.data.resize(m.data.size() - sizeof(d));

			m.header.size = m.size();
						 
			return m;

		}
	};


}