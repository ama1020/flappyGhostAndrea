#pragma once
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>

class Brain {
public:
	Brain();
	Brain(const Brain& a);
	~Brain();
	void mutate(int i1);
	void randomize();
	short int Press[20000];
private:
	std::random_device rd;
};
