#include "Button.h"

void Button::Init()
{
	if (!button_texture.loadFromFile("images/button.png"))
	{
		//std::cout << "Not working";
		system("pause");
	}
	button.setTexture(button_texture);
	button.setPosition(x, y);
	button.setTextureRect(sf::IntRect(x, y, 35, 35));
}

void Button::Draw(sf::RenderWindow& window) const
{
	window.draw(button);
}

sf::Sprite Button::getSprite()
{
	return button;
}
