#pragma once
#include "Dot.h"

class Population {
public:
	void Init();
	void Draw(sf::RenderWindow& window) const;
	void Update(int score, float v);
	void Dead(int i);
	void calculateFitness(int h);
	void calculateFitnessSum();
	void naturalSelection();
	void mutate();
	void nextgen();
	void modifyscorei();
	bool AllDead();
	void SelectParents();
	void SetBestDot();
	sf::Sprite getSprite(int i);
	const int nrdots = 22;
	int gen = 1, scorei = 0;
private:
	Dot dots[22];
	int bestdot;
	float fitnessSum = 0;
};
