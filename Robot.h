#pragma once
#include <SFML/Graphics.hpp>
#include "Brain.h"

class Robot {
public:
	void Init();
	void Restart();
	void Draw(sf::RenderWindow& window) const;
	void Update();
	sf::Sprite getSprite();
	int Collision();
	Brain brain;
	float gravity = 2, velocity = -12.5, jump = -12.5, y = 250.0f;
	int k = 0;
private:
	float x = 150.0f;
	const int h = 50, w = 50;
	sf::Sprite ghost;
	sf::Texture ghost_texture;
};