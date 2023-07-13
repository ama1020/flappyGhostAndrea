#include "Ghost.h"

void Ghost::Init()
{
	if (!ghost_texture.loadFromFile("images/ghost1.png"))
	{
		//std::cout << "Not working";
		system("pause");
	}
	ghost.setTexture(ghost_texture);
	ghost.setPosition(x, y);
}

void Ghost::Restart()
{
	gravity = 2;
	velocity = -12.5;
	jump = -12.5;
	y = 250.0f;
	Update();
}

void Ghost::Draw(sf::RenderWindow& window) const
{
	window.draw(ghost);
}

void Ghost::Update()
{
	ghost.setPosition(x, y);
}

sf::Sprite Ghost::getSprite()
{
	return ghost;
}

int Ghost::Collision()
{
	if (y + h >= 500) {
		y = 500 - h;
		Update();
		return 1;
	}
	return 0;
}
