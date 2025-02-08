
#include <exception>
#include <iostream>
#include <numbers>

import R3;

using namespace R3;

// entry point
int main()
{
	try
	{
		coordinates<double, cartesian_system> v1{ 1.0, 2.0, 3.0 }, v2{ -1.0, 0.0, 1.0 };
		auto v3 = v1 + v2;
		std::cout << v1 << '\n' << v2 << '\n' << v3 << '\n';
		coordinates<float, cylindrical_system> v4{ 3.f, std::numbers::pi_v<float> / 4.f, -1.f };
		//auto v5 = v1 + v4;
		auto v6 = v4.to_spherical_coordinates();
		auto v7{ v6.to_spherical_coordinates() };
		std::cout << v4 << '\n' << v6 << '\n' << v7 << '\n';

		return 0;
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
}