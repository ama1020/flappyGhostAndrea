#pragma once //preprocessor directive, so hedaer file is included only once in  compilation
#include <SFML/Graphics.hpp>

class Background {
public:
	void Init();
	void Draw(sf::RenderWindow& window) const;
private:
	sf::Texture sky_texture;
	sf::Sprite sky;
	sf::Texture grass_texture;
	sf::Sprite grass;
};