#pragma once
#include "NetBase.hpp"

namespace net
{
	template<typename T>
	class queue
	{
	public:
		queue() = default;
		queue(const queue<T>& a) = delete;

		const T& front()
		{
			std::lock_guard<std::mutex> lock{mux};
			return deq.front();
		}
		const T& back()
		{
			std::lock_guard<std::mutex> lock{mux};
			return deq.back();
		}
		queue<T>& emplace_back(const T& o)
		{
			std::lock_guard<std::mutex> lock{mux};
			deq.emplace_back(o);
			return *this;
		}
		queue<T>& emplace_front(const T& o)
		{
			std::lock_guard<std::mutex> lock{mux};
			deq.emplace_front(o);
			return *this;
		}
		size_t size()
		{
			std::lock_guard<std::mutex> lock{mux};
			return deq.size();
		}
		auto begin() const // -> mutex mutable
		{
			std::lock_guard<std::mutex> lock{mux}; 
			return deq.begin();
		}
		auto end() const 
		{
			std::lock_guard<std::mutex> lock{mux};
			return deq.end();
		}
		friend std::ostream& operator<<(std::ostream& o, const queue<T>& q)
		{
			for (auto it = q.begin(); it != q.end(); ++it)
				o << *it << " ";
			return o << std::endl;
		}

	private:
		mutable std::mutex mux;
		std::deque<T> deq;
	};
}