#pragma once
#pragma warning(disable : 4996)

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <string>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

class UI_Controller {
	Font font;

	Text textGameOver;
	Text textScore;
	Text textScoreNumber;
	Text textReset;
	Text TextExit;

public:
	UI_Controller() {
		font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf");

		textGameOver.setPosition(100, 30);
		textGameOver.setFont(font);
		textGameOver.setColor(Color::White);
		textGameOver.setCharacterSize(100.0f);

		textScore.setPosition(250, 180);
		textScore.setFont(font);
		textScore.setColor(Color::White);
		textScore.setCharacterSize(50.0f);

		textScoreNumber.setPosition(350, 250);
		textScoreNumber.setFont(font);
		textScoreNumber.setColor(Color::White);
		textScoreNumber.setCharacterSize(80.0f);

		textReset.setPosition(120, 450);
		textReset.setFont(font);
		textReset.setColor(Color::White);
		textReset.setCharacterSize(50.0f);

		TextExit.setPosition(120, 510);
		TextExit.setFont(font);
		TextExit.setColor(Color::White);
		TextExit.setCharacterSize(50.0f);

		textGameOver.setString("GAME OVER");
		textScore.setString("Tu punjate es:");
		textScoreNumber.setString("0");
		textReset.setString("Presiona R para reiniciar.");
		TextExit.setString("Preciona ESC para salir.");
	}

	void SetTextScore(int score) {

		textScoreNumber.setString(std::to_string(score));
	}

	void Dibujar(RenderWindow* wnd) {
		wnd->draw(textGameOver);
		wnd->draw(textScore);
		wnd->draw(textScoreNumber);
		wnd->draw(textReset);
		wnd->draw(TextExit);
	}
};