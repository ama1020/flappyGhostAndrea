#pragma once
#include <SFML/Graphics.hpp>
class Button {
public:
	void Init();
	void Draw(sf::RenderWindow& window) const;
	sf::Sprite getSprite();
private:
	sf::Sprite button;
	sf::Texture button_texture;
	const int x = 10, y = 10;
};
