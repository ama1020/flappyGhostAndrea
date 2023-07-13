#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

class Obstacle {
public:
	void Random();
	void Init();
	void Add();
	void Restart();
	void Draw(sf::RenderWindow& window);
	void Update();
	bool score(sf::Sprite sp);
	bool score();
	int returnk();
	sf::Sprite getSprite(int i);
	int i = 0;
	float v = 5.0f, h = 100.0f, gap = 150.0f;
	float randomh[100];
	int k = 0;
private:
	const int heightmin = 75, heightmax = 300, w = 50.0f;
	float y = 0.0f, x = 800.0f;
	std::vector<sf::Sprite> spears;
	sf::Texture spear_texture;
	//std::random_device rd;
};
