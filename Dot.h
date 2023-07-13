#pragma once

#ifndef _DOT_H_
#define _DOT_H_

//#endif // !_DOT_H_

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Brain.h"

class Dot {
public:
	Dot();
	Dot(const Dot& a);
	~Dot();
	void Init();
	void Init_Winner();
	void Restart();
	int Update(int score, float v);
	int Collision();
	void move();
	sf::Sprite getSprite();
	void Draw(sf::RenderWindow& window) const;
	void calculateFitness(int h);
	bool dead = false;
	float fitness = 0.0f;
	Brain brain;
	bool reachedPosition = false;
	bool isBest = false;
	int k = 0;
private:
	float gravity = 2, velocity = -12.5, jump = -12.5, y = 250.0f;
	float x = 150.0f;
	const int h = 56, w = 45;
	sf::Sprite ghost;
	sf::Texture ghost_texture;
};

#endif
