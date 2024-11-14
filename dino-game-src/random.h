#pragma once

#include <random>

class Random {
private:
	std::random_device _rdev;
	std::mt19937 _mt{ _rdev() };
	std::uniform_int_distribution<std::mt19937::result_type> _dist;

public:
	Random(unsigned int low, unsigned int high) : _dist{ low, high } {}

	int operator() () {
		return _dist(_mt);
	}
};