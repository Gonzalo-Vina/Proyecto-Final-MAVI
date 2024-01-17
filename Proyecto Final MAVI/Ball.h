#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Player.h"
#include "Brick.h"

using namespace sf;

class Ball {
	sf::CircleShape *ball;

	float ballSpeedX = 5.0f;
	float ballSpeedY = -5.0f;

	int hits;

	sf::Clock timeToIncreasedSpeed;

	SoundBuffer bounceBallBuffer;
	SoundBuffer brickBreakBuffer;

	Sound soundBounce;
	Sound soundBreak;

public:
	Ball() {
		ball = new CircleShape(10);
		ball->setFillColor(sf::Color::Red);
		ball->setPosition(350, 550);

		hits = 0;

		timeToIncreasedSpeed.restart();

		bounceBallBuffer.loadFromFile("SFX/bounceBall.wav");
		if (!bounceBallBuffer.loadFromFile("SFX/bounceBall.wav")) {
			std::cout << "ERROR";
		}
		soundBounce.setBuffer(bounceBallBuffer);

		brickBreakBuffer.loadFromFile("SFX/brickBreak.wav");
		if (!brickBreakBuffer.loadFromFile("SFX/brickBreak.wav")) {
			std::cout << "ERROR";
		}
		soundBreak.setBuffer(brickBreakBuffer);
	}

	void Move() {
		ball->move(ballSpeedX, ballSpeedY);

		// Rebotar la pelota en los bordes de la ventana
		if (ball->getPosition().x <= 0 || ball->getPosition().x >= 790) {
			soundBounce.play();
			ballSpeedX = -ballSpeedX;
		}
		if (ball->getPosition().y <= 0 || ball->getPosition().y >= 590) {
			soundBounce.play();
			ballSpeedY = -ballSpeedY;
		}

		IncreaseSpeed();
	}

	void CheckCollision(Player *player, std::vector<Brick> bricks) {
		// Detectar colisión entre la pelota y la paleta
		if (ball->getGlobalBounds().intersects(player->GetPaddle().getGlobalBounds())) {
			soundBounce.play();
			ballSpeedY = -ballSpeedY;
		}

		// Detectar colisión entre la pelota y los ladrillos
		for (auto& brick : bricks) {
			if (ball->getGlobalBounds().intersects(brick.GetBrick().getGlobalBounds())) {
				soundBreak.play();
				brick.Destroy();
				hits++;
				ballSpeedY = -ballSpeedY;
			}
		}
	}

	void IncreaseSpeed() {
		if (timeToIncreasedSpeed.getElapsedTime().asSeconds() > 10) {
			timeToIncreasedSpeed.restart();
			ballSpeedX *= 1.25f;
			ballSpeedY *= 1.25f;
		}
	}

	CircleShape GetBall() {
		return *this->ball;
	}

	void ResetGame() {
		ball->setPosition(350, 550);
		hits = 0;

		timeToIncreasedSpeed.restart();
	}

	int GetHits() {
		return hits;
	}

	Vector2f GetPosition() {
		return ball->getPosition();
	}
};
