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
#include <SFML/Audio.hpp>

#include "Player.h"
#include "Ball.h"
#include "Brick.h"
#include "UI_Controller.h"

using namespace sf;

class GameController {
	RenderWindow* _wnd;

    UI_Controller* _UI_Controller;

    Player* _player;
    Ball* _ball;

    int numberBricks = 30;
    std::vector<Brick> _bricks;

    bool isPaused;
    sf::Clock timeToPause;

    bool gameOver;

    sf::Music music;
    sf::Clock timeToMusic;

    int score;

public:
	GameController() {
		_wnd = new RenderWindow(VideoMode(800, 600), "Brick Breaker");
		_wnd->setMouseCursorVisible(false);
		_wnd->setFramerateLimit(60);

        _UI_Controller = new UI_Controller();

        _player = new Player();
        _ball = new Ball();

        StartBricks();

        isPaused = false;
        timeToPause.restart();

        gameOver = false;

        if (!music.openFromFile("SFX/Driving Concern.wav")) 
            std::cout << "ERROR";

        music.play();
        timeToMusic.restart();

        score = 0;
	}

    void MainLoop() {
        while (_wnd->isOpen()) {
            ProcesarEventos();

            if (!isPaused) {
                Actualizar();
                Dibujar();
            }
        }
    }

    void ProcesarEventos() {
        Event evt;
        while (_wnd->pollEvent(evt)) {

            switch (evt.type)
            {
            case Event::Closed:
                _wnd->close();
                break;
            }

            if (Keyboard::isKeyPressed(Keyboard::Escape) == true)
                _wnd->close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !isPaused) {
                if(_player->GetPosition().x > 0)
                _player->MoveLeft();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !isPaused) {
                if (_player->GetPosition().x < 700)
                _player->MoveRight();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && timeToPause.getElapsedTime().asSeconds() > 1.0f) {
                timeToPause.restart();
                isPaused = !isPaused;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && gameOver) {
                ResetGame();
            }
        }
    }

    void Actualizar() {
        if (!gameOver) {
            _ball->Move();
            _ball->CheckCollision(_player, _bricks);
        }

        CheckMusicBackground();
        CheckScore();
        CheckBallPosition();
    }

    void Dibujar() {
        _wnd->clear();

        if (!gameOver) {
            _wnd->draw(_player->GetPaddle());
            _wnd->draw(_ball->GetBall());

            for (int i = 0; i < numberBricks; ++i) {
                _wnd->draw(_bricks[i].GetBrick());
            }
        }
        else {
            _UI_Controller->Dibujar(_wnd);
        }

        _wnd->display();
    }

    void CheckScore() {
        if (_ball->GetHits() == 30) {
            //GANASTE
            GameOver();
        }
    }

    void CheckBallPosition() {
        if (_ball->GetPosition().y >= 590) {
            GameOver();
        }
    }

    void GameOver() {
        gameOver = true;

        score = _ball->GetHits() * 10;

        _UI_Controller->SetTextScore(score);
    }

    void ResetGame() {
        score = 0;

        isPaused = false;
        gameOver = false;

        _player->ResetGame();
        _ball->ResetGame();
        _bricks.clear();

        StartBricks();
    }

    void StartBricks() {
        for (int i = 0; i < numberBricks; ++i) {
            Brick* _brick = new Brick(i);
            _bricks.push_back(*_brick);
        }
    }

    void CheckMusicBackground() {
        if (timeToMusic.getElapsedTime().asSeconds() > 200.0f) {
            timeToMusic.restart();
            music.play();
        }
    }
};
