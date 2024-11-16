#pragma once

#include <random>

class Random {
private:
	std::random_device _rdev;
	std::minstd_rand _lcg{ _rdev() };
	std::uniform_int_distribution<std::minstd_rand::result_type> _dist;

public:
	Random(unsigned int low, unsigned int high) : _dist{ low, high } {}

	int operator() () {
		return _dist(_lcg);
	}
};