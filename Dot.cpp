#include "Dot.h"

Dot::Dot()
{
	brain.randomize();
	if (!ghost_texture.loadFromFile("images/ghost1.png"))
	{
		system("pause");
	}
	ghost.setTexture(ghost_texture);
	ghost.setPosition(x, y);
}

Dot::Dot(const Dot& a)
{

}

Dot::~Dot()
{
}

void Dot::Init()
{
	brain.randomize();
	if (!ghost_texture.loadFromFile("images/ghost1.png"))
	{
		//std::cout << "Not working";
		system("pause");
	}
	ghost.setTexture(ghost_texture);
	ghost.setPosition(x, y);
}

void Dot::Init_Winner()
{
	if (!ghost_texture.loadFromFile("images/ghost2_winner.png"))
	{
		//std::cout << "Not working";
		system("pause");
	}
	ghost.setTexture(ghost_texture);
	ghost.setPosition(x, y);
}

sf::Sprite Dot::getSprite()
{
	return ghost;
}

void Dot::Restart()
{
	gravity = 2;
	velocity = -12.5;
	jump = -12.5;
	y = 250.0f;
	ghost.setPosition(x, y);
	dead = false;
	k = 0;
	fitness = 0.0f;
}

int Dot::Update(int score, float v)
{
	int ok = 0;
	if (!dead && !reachedPosition) {
		move();
		if (Collision()) {
			dead = true;
			ok = 1;
		}
		if (score == 30) {
			reachedPosition = true;
		}
	}
	else if (dead) {
		ghost.move(-v, 0.0f);
	}
	return ok;
}

int Dot::Collision()
{
	if (y + h >= 500) {
		y = 500 - h;
		ghost.setPosition(x, y);
		return 1;
	}
	return 0;
}

void Dot::move()
{
	if (brain.Press[k] <= 3)
		velocity = jump;
	k++;
	velocity += gravity;
	y += velocity;
	ghost.setPosition(x, y);
}

void Dot::Draw(sf::RenderWindow& window) const
{
	window.draw(ghost);
}

void Dot::calculateFitness(int h)
{
	fitness = (float)((float)((float)(5.0f / k) * 1500.0f) + (float)((float)((abs(y - h) / (abs(y - h) + 1))) / 300.0f));
	
}


