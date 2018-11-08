// SquareWithMomentum.cpp : Defines the entry point for the console application.
//

/*
This draws a car on the screen that has "tank" controls instead of just moving in the cardinal directions.
The left and right arrows control the rotation of the rect
while the up and down arrows control the whether the car is moving forward or back.
For more fun, the car slows to a stop when the user halts input.

*/

#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <cmath>
#include <iostream>

void initRectangle(sf::RectangleShape& shape, sf::Vector2f const& pos) //This function is only useful when creating multiple rectagle shapes.
{
	shape.setPosition(pos);
	shape.setOrigin(shape.getSize() * 0.5f);
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "Square With Momentum");
	window.setFramerateLimit(60);

	sf::Texture carTex;
	carTex.loadFromFile("1425538124215.png");
	carTex.setSmooth(true);
	sf::Vector2u carTexSize = carTex.getSize();


	sf::RectangleShape rectagle(sf::Vector2f(carTexSize.x, carTexSize.y));
	rectagle.setScale(sf::Vector2f(0.25, 0.25));

	initRectangle(rectagle, sf::Vector2f(400,300));

	rectagle.setTexture(&carTex);

	bool leftArrow = false;
	bool rightArrow = false;
	bool upArrow = false;
	bool downArrow = false;

	double rectVelocity = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::Closed) window.close();
			if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape) window.close();
			//UserControls
			if (event.type == sf::Event::EventType::KeyPressed && event.key.code == sf::Keyboard::Right) rightArrow = true;
			if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Right) rightArrow = false;
			if (event.type == sf::Event::EventType::KeyPressed && event.key.code == sf::Keyboard::Left) leftArrow = true;
			if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Left) leftArrow = false;
			if (event.type == sf::Event::EventType::KeyPressed && event.key.code == sf::Keyboard::Up) upArrow = true;
			if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Up) upArrow = false;
			if (event.type == sf::Event::EventType::KeyPressed && event.key.code == sf::Keyboard::Down) downArrow = true;
			if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Down) downArrow = false;
		}

		/*
		Update Cycle
		*/

		if (rightArrow) rectagle.rotate(3);
		if (leftArrow) rectagle.rotate(-3);
		if (upArrow) rectVelocity += 0.3; //Up and down arrows control the rectangle's velocity
		if (!upArrow) rectVelocity -= 0.3;
		if (downArrow) rectVelocity -= 0.3;
		if (!downArrow) rectVelocity += 0.3;

		if (rectVelocity >= 5.0) rectVelocity = 5.0; //setting speed caps to prevent the rectangle from getting out of control
		if (rectVelocity <= -5.0) rectVelocity = -5.0;
		if (!upArrow && !downArrow) rectVelocity *= 0.975; //Giving the rectangle momentum. 0.975 looks like the rect is on ice.

		if (rectVelocity < 0.1 && rectVelocity > -0.1) rectVelocity = 0; //Making sure the rect actually stops eventually.

		//calculate the change in position of the rectangle based on its rotation
		rectagle.move(sf::Vector2f(rectVelocity * std::sin(rectagle.getRotation() * (3.1415 / 180.0)), -rectVelocity * std::cos(rectagle.getRotation() * (3.1415 / 180.0))));

		/*
		Render Cycle
		*/
		window.clear(sf::Color::Black);

		window.draw(rectagle);

		/*
		Display the image
		*/

		window.display();
	}

    return 0;
}

