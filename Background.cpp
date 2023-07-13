#include "Background.h"
//#include <iostream>

void Background::Init()
{
	if (!sky_texture.loadFromFile("images/Wall.png"))
	{
		//std::cout << "Not working";
		system("pause");
	}
	sky_texture.setRepeated(true); //Texture to repeat when applied to a sprite larger than the texture.
	sky.setTexture(sky_texture); 
	sky.setTextureRect(sf::IntRect(0, 0, 800, 500)); //left, top, width, height

	if (!grass_texture.loadFromFile("images/Tile.png"))
	{
		//std::cout << "Not working";
		system("pause");
	}
	grass_texture.setRepeated(true);
	grass.setTexture(grass_texture);
	grass.setPosition(0.f, 500.f);
	grass.setTextureRect(sf::IntRect(0, 500, 800, 100));
}

void Background::Draw(sf::RenderWindow& window) const
{
	window.draw(sky);
	window.draw(grass);
}
