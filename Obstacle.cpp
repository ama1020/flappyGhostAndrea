#include "Obstacle.h"

void Obstacle::Random()
{
	int randomh1[105] = { 116 , 92 , 109 , 250 , 119 , 274 , 78 , 183 , 262 , 239 , 155 , 95 , 181 , 252 , 136 , 116 , 145 , 92 , 177 , 111 , 291 , 279 , 152 , 228 , 142 , 82 , 171 , 116 , 218 , 170 , 122 , 201 , 221 , 138 , 144 , 187 , 92 , 274 , 235 , 294 , 203 , 261 , 122 , 258 , 198 , 239 , 141 , 136 , 203 , 193 , 197 , 269 , 112 , 207 , 87 , 109 , 248 , 141 , 154 , 178 , 241 , 185 , 215 , 117 , 138 , 256 , 115 , 242 , 214 , 223 , 296 , 255 , 215 , 279 , 145 , 125 , 231 , 126 , 168 , 248 , 129 , 98 , 84 , 229 , 156 , 215 , 91 , 251 , 281 , 283 , 144 , 114 , 176 , 148 , 212 , 238 , 218 , 132 , 279 , 191, 90, 130, 180 };
	for (int i = 0; i < 100; i++)
		randomh[i] = randomh1[i];
}

void Obstacle::Init() {
	sf::Sprite spear, spear1;
	/*srand(time(NULL));
	std::uniform_int_distribution<int> randomh(heightmin, heightmax);
	std::mt19937 randomNumbers(rd());
	h = randomh(randomNumbers);*/
	//int randomh = heightmin + rand() % (heightmax / 2);

	if (!spear_texture.loadFromFile("images/Obstacle.png"))
	{
		//std::cout << "Not working";
		system("pause");
	}
	spear_texture.setRepeated(true);

	spear.setTexture(spear_texture);
	spear.setPosition(x, y);
	spear.setTextureRect(sf::IntRect(x, y, w, randomh[k]));
	spears.push_back(spear);

	spear1.setTexture(spear_texture);
	spear1.setPosition(x, y + randomh[k] + gap);
	spear1.setTextureRect(sf::IntRect(x, y + randomh[k] + gap, w, 500 - randomh[k] - gap));
	spears.push_back(spear1);
	k++;
}

void Obstacle::Add()
{
	sf::Sprite spear, spear1;
	/*std::uniform_int_distribution<int> randomh(heightmin, heightmax);
	std::mt19937 randomNumbers(rd());
	h = randomh(randomNumbers);*/

	spear.setTexture(spear_texture);
	spear.setPosition(x, y);
	spear.setTextureRect(sf::IntRect(x, y, w, randomh[k]));
	spears.push_back(spear);

	spear1.setTexture(spear_texture);
	spear1.setPosition(x, y + randomh[k] + gap);
	spear1.setTextureRect(sf::IntRect(x, y + randomh[k] + gap, w, 500 - randomh[k] - gap));
	spears.push_back(spear1);
	k++;
}

void Obstacle::Restart()
{
	v = 5.0f;
	k = 0;
	i = 0;
	spears.clear();
}

void Obstacle::Draw(sf::RenderWindow& window) {
	for (unsigned short int i = 0; i < spears.size(); i++)
		window.draw(spears.at(i));
}

void Obstacle::Update() {
	if (v <= 15.0f)
		v += 0.01; //To make it more difficult
	for (unsigned short int i = 0; i < spears.size(); i++) {
		spears.at(i).move(-v, 0.0f);
	}
	if (spears.at(0).getPosition().x <= 0) {
		spears.erase(spears.begin(), spears.begin() + 2);
		i -= 2;
	}
}

bool Obstacle::score(sf::Sprite sp) {
	if (spears.size() >= i)
		if ((spears.at(i).getPosition().x <= sp.getPosition().x) && (sp.getPosition().x <= spears.at(i).getPosition().x + w)) {
			i += 2;
			return 1;
		}
	return 0;
}

bool Obstacle::score() {
	if (spears.size() >= i)
		if ((spears.at(i).getPosition().x <= 150.00f) && (150.00f <= spears.at(i).getPosition().x + w)) {
			i += 2;
			return 1;
		}
	return 0;
}

int Obstacle::returnk()
{
	//std::cout << spears.size() << " ";
	return k - spears.size() / 2;
}

sf::Sprite Obstacle::getSprite(int i)
{
	return spears.at(i);
}
