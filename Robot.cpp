#include "Robot.h"
#include <fstream>
#include<iostream>

void Robot::Init()
{
	if (!ghost_texture.loadFromFile("images/ghost1.png"))
	{
		//std::cout << "Not working";
		system("pause");
	}
	ghost.setTexture(ghost_texture);
	ghost.setPosition(x, y);
	std::ifstream fin("result/copy_in.txt");
	int a;
	fin >> a;
	for (int i = 0; i < 20000; i++) {
		fin >> brain.Press[i];
	}
	fin.close();
}

void Robot::Restart()
{
	gravity = 2;
	velocity = -12.5;
	jump = -12.5;
	y = 250.0f;
	k = 0;
}

void Robot::Draw(sf::RenderWindow& window) const
{
	window.draw(ghost);
}

void Robot::Update()
{
	if (brain.Press[k] <= 3)
		velocity = jump;
	k++;
	velocity += gravity;
	y += velocity;
	ghost.setPosition(x, y);
}

sf::Sprite Robot::getSprite()
{
	return ghost;
}

int Robot::Collision()
{
	if (y + h >= 500) {
		y = 500 - h;
		Update();
		return 1;
	}
	return 0;
}
