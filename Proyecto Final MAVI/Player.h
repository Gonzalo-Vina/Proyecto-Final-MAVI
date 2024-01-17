#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Player{
	sf::RectangleShape *paddle;

	float paddleSpeed;

	sf::Clock timeToIncreasedSpeed;

public:
	Player() {
		paddle = new RectangleShape(sf::Vector2f(100, 20));
		paddle->setFillColor(sf::Color::Green);
		paddle->setPosition(350, 570);
		
		paddleSpeed = 15.0f;

		timeToIncreasedSpeed.restart();
	}

	void MoveLeft() {
		paddle->move(-paddleSpeed, 0);
	}

	void MoveRight() {
		paddle->move(paddleSpeed, 0);
	}

	void IncreaseSpeed() {
		if (timeToIncreasedSpeed.getElapsedTime().asSeconds() > 10) {
			timeToIncreasedSpeed.restart();
			paddleSpeed *= 1.3f;
		}
	}

	Vector2f GetPosition() {
		return paddle->getPosition();
	}

	RectangleShape GetPaddle() {
		return *this->paddle;
	}

	void ResetGame() {
		paddle->setPosition(350, 570);

		paddleSpeed = 15.0f;

		timeToIncreasedSpeed.restart();
	}
};