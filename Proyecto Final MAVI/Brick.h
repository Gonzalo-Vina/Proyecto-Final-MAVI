#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

class Brick {

	sf::RectangleShape* brick;

	int numberBricks = 10;

public:
	Brick(int i) {
		brick = new RectangleShape(sf::Vector2f(50, 20));
		brick->setFillColor(sf::Color::Blue);
		if (i < 10) {
			brick->setPosition(50 + i * 70, 50);
		}
		else if (i >= 10 && i < 20){
			brick->setPosition(50 + (i - 10) * 70, 130);
		}
		else {
			brick->setPosition(50 + (i - 20) * 70, 210);
		}
	}

	void Destroy() {
		brick->setSize(sf::Vector2f(0, 0));
	}

	RectangleShape GetBrick() {
		return *this->brick;
	}
};