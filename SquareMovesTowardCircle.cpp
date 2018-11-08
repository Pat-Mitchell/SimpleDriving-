// SquareMovesTowardCircle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFML\Graphics.hpp"

int windowWidth = 800, windowHeight = 600;

int main()
{
	sf::CircleShape playerCircle(5);
	playerCircle.setFillColor(sf::Color::Blue);
	playerCircle.setPosition(sf::Vector2f(windowWidth/2.f, windowHeight/2.f));
	playerCircle.setOrigin(sf::Vector2f(5.f, 5.f));

	sf::RectangleShape nerdSquare(sf::Vector2f(10, 10));
	nerdSquare.setFillColor(sf::Color::Red);
	nerdSquare.setPosition(sf::Vector2f(100, 100));
	nerdSquare.setOrigin(nerdSquare.getSize() * 0.5f);

	sf::RenderWindow mainWindow(sf::VideoMode(windowWidth, windowHeight), "Square and Circle");
	mainWindow.setFramerateLimit(60);

	//Bools to control the player movement.
	bool movingRight = false;
	bool movingLeft = false;
	bool movingUp = false;
	bool movingDown = false;
	
	//Game loop
	while (mainWindow.isOpen())
	{
		sf::Event userInput;
		while (mainWindow.pollEvent(userInput))
		{
			//Lines to close the game
			if (userInput.type == sf::Event::EventType::Closed) mainWindow.close();
			if (userInput.type == sf::Event::EventType::KeyReleased && userInput.key.code == sf::Keyboard::Escape) mainWindow.close();

			//Lines for the user to control the circle
			if (userInput.type == sf::Event::EventType::KeyPressed && userInput.key.code == sf::Keyboard::Right) movingRight = true;
			if (userInput.type == sf::Event::EventType::KeyReleased && userInput.key.code == sf::Keyboard::Right) movingRight = false;
			if (userInput.type == sf::Event::EventType::KeyPressed && userInput.key.code == sf::Keyboard::Left) movingLeft = true;
			if (userInput.type == sf::Event::EventType::KeyReleased && userInput.key.code == sf::Keyboard::Left) movingLeft = false;
			if (userInput.type == sf::Event::EventType::KeyPressed && userInput.key.code == sf::Keyboard::Up) movingUp = true;
			if (userInput.type == sf::Event::EventType::KeyReleased && userInput.key.code == sf::Keyboard::Up) movingUp = false;
			if (userInput.type == sf::Event::EventType::KeyPressed && userInput.key.code == sf::Keyboard::Down) movingDown = true;
			if (userInput.type == sf::Event::EventType::KeyReleased && userInput.key.code == sf::Keyboard::Down) movingDown = false;
		}

		//Update Cycle

		//PlayerMovement
		if (movingRight) playerCircle.move(sf::Vector2f(3,0));
		if (movingLeft) playerCircle.move(sf::Vector2f(-3, 0));
		if (movingUp) playerCircle.move(sf::Vector2f(0, -3));
		if (movingDown) playerCircle.move(sf::Vector2f(0, 3));

		//Get the player and nerd coordinates
		sf::Vector2f playerCoordinates = playerCircle.getPosition();
		sf::Vector2f nerdCoordinates = nerdSquare.getPosition();

		//move the nerd towards the player
		if (playerCoordinates.x > nerdCoordinates.x) nerdSquare.move(sf::Vector2f(0.5f,0));
		else if (playerCoordinates.x < nerdCoordinates.x) nerdSquare.move(sf::Vector2f(-0.5f, 0));
		if (playerCoordinates.y > nerdCoordinates.y) nerdSquare.move(sf::Vector2f(0, 0.5f));
		else if (playerCoordinates.y < nerdCoordinates.y) nerdSquare.move(sf::Vector2f(0, -0.5f));

		//is the player colliding with the nerd
		if (playerCircle.getGlobalBounds().intersects(nerdSquare.getGlobalBounds())) mainWindow.close();

		//Render Cycle
		mainWindow.clear(sf::Color::Black);

		//Draw the two shapes
		mainWindow.draw(playerCircle);
		mainWindow.draw(nerdSquare);

		//Display the image
		mainWindow.display();
	}

	return 0;
}

