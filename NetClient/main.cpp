#include <iostream>

#include <net.hpp>

int main()
{
	net::message<int> m{};

	int x = 90;
	float z = 7.453234;

	m << x << z;

	std::cout << m;
	x = 2;
	z = 4.4;
	m >> z >> x;
	std::cout << std::endl;

	net::queue<int> que;
	que.emplace_back(1);
	que.emplace_back(2);
	que.emplace_back(3);
	que.emplace_front(4);

	std::cout << que;



	return 0;
}
