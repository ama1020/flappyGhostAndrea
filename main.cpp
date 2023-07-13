#include <SFML/Graphics.hpp>
#include <windows.h> 
#include <string> 
#include "Ghost.h"
#include "Background.h"
#include "Obstacle.h"
#include "Button.h"
#include "Robot.h"
#include "Population.h"

bool Collision(sf::Sprite s1, sf::Sprite s2, bool i) {
	if (i == 1) {
		auto a1 = s1.getGlobalBounds(); //the global bounding box of the sprite
		auto a2 = s2.getGlobalBounds();
		if (a1.intersects(a2))
			return 1;
		if (a1.top + a1.height < 0) //s1 is positioned above the game window
			if ((a1.left + a1.width >= a2.left) && (a1.left + a1.width <= a2.left + a2.width)) //a1 is within the bounds of a2
				return 1; //s1 has passed through the gap between two obstacles
	}
	else {
		auto a1 = s1.getGlobalBounds();
		auto a2 = s2.getGlobalBounds();
		if (a1.intersects(a2))
			return 1;
	}
	return 0;
}

bool SpriteIsPressed(sf::RectangleShape sp, sf::RenderWindow& window) {
	auto mousex = sf::Mouse::getPosition(window).x;
	auto mousey = sf::Mouse::getPosition(window).y;
	auto spbounds = sp.getGlobalBounds();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (spbounds.contains(mousex, mousey))
			return 1;
	return 0;
}

bool SpriteIsPressed(sf::Sprite sp, sf::RenderWindow& window) {
	auto mousex = sf::Mouse::getPosition(window).x;
	auto mousey = sf::Mouse::getPosition(window).y;
	auto spbounds = sp.getGlobalBounds();
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (spbounds.contains(mousex, mousey))
			return 1;
	return 0;
}

int main()
{
	bool SpaceReleased = 0;
	//We retrieve the handle of the console window and hide it.
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	bool pause = 0;
	int score = 0;
	sf::String GameStates[6] = { "Menu", "PressButtonToStart", "Game", "GameOver", "Pause", "GameWon" };
	sf::String GameState = GameStates[0];
	sf::String players[3] = { "Input", "Learn", "Robot" };
	sf::String player = players[0];

	// Create an SFML window with a size of 800x600 pixels, title "Flappy Ghost," and style:  close button and titlebar
	sf::RenderWindow window(sf::VideoMode(800, 600), "Flappy Ghost", sf::Style::Close | sf::Style::Titlebar);
	 
	Background background;
	background.Init();

	Ghost ghost;
	ghost.Init();

	Obstacle obst;
	obst.Random();

	Button button;
	button.Init();

	//RANDOMLY GENERATED POPULATION
	Population pop;
	pop.Init();

	Robot robot;
	robot.Init();

	// MENU texts
	int rectw = 300.0f, recth = 100.0f;
	sf::RectangleShape rect1(sf::Vector2f(rectw, recth));
	rect1.setPosition(400 - rectw / 2, 50.0f);
	rect1.setFillColor(sf::Color(0, 0, 0, 255));
	sf::Text text1;
	sf::Text text2;
	sf::Text text3;
	sf::Font font;
	if (!font.loadFromFile("Font/bug2k.ttf"))
	{
		// error...
	}
	text1.setFont(font);
	text1.setString("Start");
	text1.setCharacterSize(50);
	text1.setFillColor(sf::Color::White);
	text1.setPosition(480 - rectw / 2, 60.0f);

	sf::RectangleShape rect2(sf::Vector2f(rectw, recth));
	rect2.setPosition(400 - rectw / 2, 100.0f + recth);
	rect2.setFillColor(sf::Color(0, 0, 0, 255));
	text2.setFont(font);
	text2.setString("Learn");
	text2.setCharacterSize(50);
	text2.setFillColor(sf::Color::White);
	text2.setPosition(480 - rectw / 2, 110.0f + recth);

	sf::RectangleShape rect3(sf::Vector2f(rectw, recth));
	rect3.setPosition(400 - rectw / 2, 150.0f + 2 * recth);
	rect3.setFillColor(sf::Color(0, 0, 0, 255));
	text3.setFont(font);
	text3.setString("Best");
	text3.setCharacterSize(50);
	text3.setFillColor(sf::Color::White);
	text3.setPosition(500 - rectw / 2, 160.0f + 2 * recth);

	//Game texts
	sf::Text score_text, score_text1, back;
	sf::Text gen_text, gen_text1;
	sf::Text textStart, textStart1, textLost1, textLost2, textWon1, textWon2;
	sf::Font font_score;
	if (!font_score.loadFromFile("Font/attack of the cucumbers.ttf"))
	{
		// error...
	}
	score_text.setFont(font_score);
	score_text.setString("Score:");
	score_text.setCharacterSize(25);
	score_text.setFillColor(sf::Color::White);
	score_text.setPosition(340, 20.0f);

	score_text1.setFont(font_score);
	score_text1.setString(std::to_string(score));
	score_text1.setCharacterSize(25);
	score_text1.setFillColor(sf::Color::White);
	score_text1.setPosition(430, 20.0f);

	gen_text.setFont(font_score);
	gen_text.setString("Generation:");
	gen_text.setCharacterSize(25);
	gen_text.setFillColor(sf::Color::White);
	gen_text.setPosition(300, 520.0f);

	gen_text1.setFont(font_score);
	gen_text1.setString(std::to_string(pop.gen));
	gen_text1.setCharacterSize(25);
	gen_text1.setFillColor(sf::Color::White);
	gen_text1.setPosition(455, 520.0f);

	textStart.setFont(font_score);
	textStart.setString("Press Space To Start");
	textStart.setCharacterSize(25);
	textStart.setFillColor(sf::Color::White);
	textStart.setPosition(240, 250.0f);

	textStart1.setFont(font_score);
	textStart1.setString("You Have To Reach 30 To Win");
	textStart1.setCharacterSize(25);
	textStart1.setFillColor(sf::Color::White);
	textStart1.setPosition(210, 280.0f);

	textLost1.setFont(font_score);
	textLost1.setString("You Lost!");
	textLost1.setCharacterSize(25);
	textLost1.setFillColor(sf::Color::White);
	textLost1.setPosition(340, 220.0f);

	textLost2.setFont(font_score);
	textLost2.setString("Press Space To Go Back");
	textLost2.setCharacterSize(25);
	textLost2.setFillColor(sf::Color::White);
	textLost2.setPosition(240, 250.0f);

	textWon1.setFont(font_score);
	textWon1.setString("You Won!");
	textWon1.setCharacterSize(25);
	textWon1.setFillColor(sf::Color::White);
	textWon1.setPosition(340, 220.0f);

	textWon2.setFont(font_score);
	textWon2.setString("Press Space To Go Back");
	textWon2.setCharacterSize(25);
	textWon2.setFillColor(sf::Color::White);
	textWon2.setPosition(240, 250.0f);

	back.setFont(font);
	back.setString("Menu");
	back.setCharacterSize(50);
	back.setFillColor(sf::Color::White);
	back.setPosition(500 - rectw / 2, 110.0f + recth);

	
	sf::Time t1 = sf::milliseconds(100 / 3);
	sf::Time t2 = sf::seconds(0.7);
	sf::Time tobstminus = sf::seconds(0.001);
	sf::Clock clock;
	sf::Time tobst;
	sf::Clock clockobst;
	bool sprealeased = false;

	int score1;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event)) //retrieve the next event from the event queue. The event object (event) is updated with the latest event data.
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (GameState == GameStates[0]) //MENU
		{
			if (SpriteIsPressed(rect1, window)) { //INPUT PLAYER MODE SELECTED
				player = players[0]; //Input player set
				GameState = GameStates[1]; //PressButtonToStart State set
			}
			if (!SpriteIsPressed(rect2, window)) 
				sprealeased = true; // Sprite is not currently being pressed
			if (SpriteIsPressed(rect2, window) && sprealeased) { //LEARN PLAYER MODE SELECTED
				player = players[1]; //Learn player set
				GameState = GameStates[2];//Game State set
				clock.restart();
				clockobst.restart();
				tobst = sf::seconds(2);
				obst.i = 0;
				score = 0;
				obst.Restart();
				obst.Init();
				score_text1.setString(std::to_string(score));
				sprealeased = false;
			}
			if (SpriteIsPressed(rect3, window)) { //ROBOT PLAYER MODE SELECTED
				player = players[2]; //Robot player set
				GameState = GameStates[2]; //Game State set
				clock.restart();
				robot.Restart();
				clockobst.restart();
				tobst = sf::seconds(2);
				obst.Init();
				score = 0;
				score_text1.setString(std::to_string(score));
			}
		}
		else if (GameState == GameStates[1]) { // PressButtonToStart State
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
				SpaceReleased = 1;
			if (SpaceReleased)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
					obst.Init();
					score = 0;
					GameState = GameStates[2]; //Game State set
					SpaceReleased = 0;
					clock.restart();
					clockobst.restart();
					tobst = sf::seconds(2);
				}
		}
		else if (GameState == GameStates[2]) { // Game State
			if (player == players[0]) {  //INPUT PLAYER MODE
				if (clock.getElapsedTime() >= t1) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
						ghost.velocity = ghost.jump; //When user press space, it jumps
					obst.Update();
					if (tobst >= sf::seconds(1))
						tobst -= tobstminus;
					score += obst.score(ghost.getSprite()); //If the obstacle is before the ghost, it has scored (returns 1)
					score_text1.setString(std::to_string(score));

					ghost.velocity += ghost.gravity; //To imitate the effect of gravity when jumping
					ghost.y += ghost.velocity;
					ghost.Update();
					if (ghost.Collision() || Collision(ghost.getSprite(), obst.getSprite(0), 1) || Collision(ghost.getSprite(), obst.getSprite(1), 0))
						GameState = GameStates[3]; //If collision with ground or with obstacles --> GameOver State set
					clock.restart();

					if (score == 30)
						GameState = GameStates[5]; //If passed 30 obstacles --> GameWon State set
				}
				if (clockobst.getElapsedTime() >= tobst) {
					obst.Add(); //Keep adding obstacles
					clockobst.restart();
				}
			}
			else if (player == players[1]) { //LEARN PLAYER MODE
				if (SpriteIsPressed(button.getSprite(), window)) {
					pause = 1;
				}
				if (!pause) {
					if (!pop.AllDead()) { //There's some that went through
						if (clock.getElapsedTime() >= t1) {
							//Add new obstacles and eliminate previous ones, also ++velocity
							obst.Update();
							if (tobst >= sf::seconds(1))
								tobst -= tobstminus;
							//Set new score
							score1 = std::max(score, score1);
							score += obst.score(ghost.getSprite());
							score_text1.setString(std::to_string(score));
							if (score > score1) {
								pop.modifyscorei();
							}
							//Update for each Individual: 1.it jumps, 2.it is established dead if collision with ground
							pop.Update(score, obst.v);
							//Establish dead the dots that colllide with obstacles
							for (int i = 0; i < pop.nrdots; i++)
								if (Collision(pop.getSprite(i), obst.getSprite(0), 1) || Collision(pop.getSprite(i), obst.getSprite(1), 0))
									pop.Dead(i);
							clock.restart();
							////If passed 30 obstacles --> GameWon State set (TERMINATION CRITERIUM)
							if (score == 30)
								GameState = GameStates[5];
						}
						if (clockobst.getElapsedTime() >= tobst) {
							obst.Add();
							clockobst.restart();
						}
					}
					else {
						//We need a new GENERATION
						int k2 = obst.returnk(); //number of obstacles passed
						int a = obst.randomh[k2] + obst.gap / 2; //Desired height the ghost has to be closed to
						//1. Calculate Fitness
						pop.calculateFitness(a);// for each Individual (Dot): we calculate the fitness based on the desired height
						
						//2. Natural Selection --> Use fitnesses to select parents and Create Children
						//     setBestDot(the one with the smallest fitness)
						//     selectParents -> we get the best dot so far and copy it in all parents (dots)(bestDot from previous generation or best Data written in file) 
						//			(if besDot is better than file, overwrite file --> Now on the file we have the best dot)      
						pop.naturalSelection();

						//3. Mutation --> Randomly mutate some of the children
						// We randomly mutate the Press Array of each children starting in the index scorei (where the bestDot had stopped)
						pop.mutate(); //Now the children are the parents
						//4. NextGen --> Restart values for movement for each Dot
						pop.nextgen();
						//Restart Obstacles
						obst.Restart();
						obst.i = 0;
						obst.k = 0;
						clock.restart();
						clockobst.restart();
						tobst = sf::seconds(2);
						//Run again for the new generation
						obst.Init();
						score = 0;
						score_text1.setString(std::to_string(score));
						gen_text1.setString(std::to_string(pop.gen));
					}
				}
				else if (SpriteIsPressed(rect2, window)) { //If Pause Button is pressed and Menu rectangle is pressed--> MENU State Selected
					GameState = GameStates[0]; // MENU State Set
					obst.Restart();
					obst.i = 0;
					obst.k = 0;
					clock.restart();
					clockobst.restart();
					tobst = sf::seconds(2);
					obst.Init();
					score = 0;
					score_text1.setString(std::to_string(score));
					gen_text1.setString(std::to_string(pop.gen));
					pause = 0;
					pop.nextgen();
					pop.gen = 0;
				}
			}
			else { //ROBOT PLAYER MODE --> We have read the file (value of Press of the last best Dot) and we do the jumps base on it
				if (clock.getElapsedTime() >= t1) {
					obst.Update();
					if (tobst >= sf::seconds(1))
						tobst -= tobstminus;
					score += obst.score(robot.getSprite());
					score_text1.setString(std::to_string(score));
					//std::cout << obst.k << ' ';

					robot.Update();
					if (robot.Collision() || Collision(robot.getSprite(), obst.getSprite(0), 1) || Collision(robot.getSprite(), obst.getSprite(1), 0)) {
						GameState = GameStates[3];
						robot.Restart();
					}
					clock.restart();
					if (score == 30)
						GameState = GameStates[5];
				}
				if (clockobst.getElapsedTime() >= tobst) {
					obst.Add();
					clockobst.restart();
				}
			}
		}
		else { //GAMEOVER or GAMEWON MODE
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
				SpaceReleased = 1;
			if (SpaceReleased && clock.getElapsedTime() >= t2)
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
					GameState = GameStates[0]; //Menu Mode set
					obst.Restart();
					ghost.Restart();
					SpaceReleased = 0;
				}
		}
		//For ALL
		window.clear();
		background.Draw(window);
		obst.Draw(window);
		if (player == players[0])
			ghost.Draw(window);
		else {
			if (pause) {
				window.draw(rect2);
				window.draw(back);
			}
			else
				button.Draw(window);
			if (player == players[1]) {
				window.draw(gen_text);
				window.draw(gen_text1);
				pop.Draw(window);
			}
			else {
				robot.Draw(window);
			}
		}
		if (GameState == GameStates[0]) {
			window.draw(rect1);
			window.draw(text1);
			window.draw(rect2);
			window.draw(text2);
			window.draw(rect3);
			window.draw(text3);
		}
		else {
			if (GameState == GameStates[1]) {
				window.draw(textStart);
				window.draw(textStart1);
			}
			else if (GameState == GameStates[3]) {
				window.draw(textLost2);
				window.draw(textLost1);
			}
			else if (GameState == GameStates[5]) {
				window.draw(textWon1);
				window.draw(textWon2);
			}
			window.draw(score_text);
			window.draw(score_text1);
		}
		window.display();
	}

	return 0;
}