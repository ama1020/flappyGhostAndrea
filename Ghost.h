#pragma once
#include <SFML/Graphics.hpp>
//#include <iostream>

class Ghost {
public:
	void Init();
	void Restart();
	void Draw(sf::RenderWindow& window) const;
	void Update();
	sf::Sprite getSprite();
	int Collision();
	float gravity = 2, velocity = -12.5, jump = -12.5, y = 250.0f;
private:
	float x = 150.0f;
	const int h = 50, w = 50;
	sf::Sprite ghost;
	sf::Texture ghost_texture;
};
