#include "Brain.h"

Brain::Brain()
{
}

Brain::Brain(const Brain& a)
{
}

Brain::~Brain()
{
}

void Brain::mutate(int i1)
{
	float MutationRate = 0.1;
	if (i1 > 20)
		i1 -= 20;
	for (int i = i1; i < 20000; i++) {
		srand(time(NULL));
		std::uniform_real_distribution<float> rand(0.0, 1.0);
		std::mt19937 randomNumbers(rd());
		std::uniform_int_distribution<int> rand1(0, 50);
		float nr = (float)(rand(randomNumbers));
		if (nr <= MutationRate) {
			Press[i] = (float)(rand1(randomNumbers));
		}
	}
}

void Brain::randomize()
{
	srand(time(NULL));
	std::uniform_int_distribution<int> rand(0, 50);
	std::mt19937 randomNumbers(rd());
	for (int i = 0; i < 20000; i++) {
		Press[i] = rand(randomNumbers);
	}
}
