#include "Game.h"

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

int main()
{
    using namespace SnakeGame;

    srand(static_cast<unsigned int>(time(0)));

    sf::RenderWindow window(
        sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
        "Snake Game"
    );
    window.setFramerateLimit(60);

    Gamestate game;
    InitGame(game);

    sf::Clock gameClock;

    while (window.isOpen())
    {
        const float deltaTime = gameClock.restart().asSeconds();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                continue;
            }

            if (event.type == sf::Event::TextEntered &&
                game.currentScreen == GameScreen::NameInput)
            {
                const unsigned int unicode = event.text.unicode;

                if (unicode == 8)
                {
                    if (!game.inputName.empty())
                        game.inputName.pop_back();
                }
                else if (unicode >= 32 && unicode < 127)
                {
                    if (game.inputName.size() < 12)
                        game.inputName += static_cast<char>(unicode);
                }

                continue;
            }

            if (event.type != sf::Event::KeyPressed)
                continue;

            const sf::Keyboard::Key key = event.key.code;

            
            if (game.currentScreen == GameScreen::Menu)
            {
                if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
                {
                                        game.menuSelection--;
                    if (game.menuSelection < 0)
                        game.menuSelection = 4;
                }
                else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
                {

                    
                    game.menuSelection++;
                    if (game.menuSelection > 4)
                        game.menuSelection = 0;
                }
                else if (key == sf::Keyboard::Enter)
                {
                    PlayButtonSound(game);
                    if (game.menuSelection == 0)
                    {
                        ResetGame(game);
                            game.currentScreen = GameScreen::Game;
                    }
                    else if (game.menuSelection == 1)
                    {
                        game.difficultySelection = game.selectedDifficulty - 1;
                        game.currentScreen = GameScreen::Difficulty;
                    }
                    else if (game.menuSelection == 2)
                    {
                        game.currentScreen = GameScreen::Records;
                    }
                    else if (game.menuSelection == 3)
                    {
                        game.currentScreen = GameScreen::Settings;
                    }
                    else
                    {
                        window.close();
                    }
                }
            }

            
            else if (game.currentScreen == GameScreen::Difficulty)
            {
                if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
                {

                    
                    game.difficultySelection--;
                    if (game.difficultySelection < 0)
                        game.difficultySelection = 4;
                }
                else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
                {

                    
                    game.difficultySelection++;
                    if (game.difficultySelection > 4)
                        game.difficultySelection = 0;
                }
                else if (key == sf::Keyboard::Enter)
                {
                    PlayButtonSound(game);
                    game.selectedDifficulty = game.difficultySelection + 1;
                    game.currentScreen = GameScreen::Menu;
                }
                else if (key == sf::Keyboard::B || key == sf::Keyboard::Escape)
                {

                    PlayButtonSound(game);
                    game.currentScreen = GameScreen::Menu;
                }
            }

           
            else if (game.currentScreen == GameScreen::Settings)
            {
                if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
                {

                    
                    game.settingsSelection--;
                    if (game.settingsSelection < 0)
                        game.settingsSelection = 1;
                }
                else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
                {

                    
                    game.settingsSelection++;
                    if (game.settingsSelection > 1)
                        game.settingsSelection = 0;
                }
                else if (key == sf::Keyboard::Enter)
                {
                    PlayButtonSound(game);
                    if (game.settingsSelection == 0)
                        game.soundEnabled = !game.soundEnabled;
                    else
                        game.musicEnabled = !game.musicEnabled;
                }
                else if (key == sf::Keyboard::B || key == sf::Keyboard::Escape)
                {
                    PlayButtonSound(game);
                    game.currentScreen = GameScreen::Menu;
                }
            }

          
            else if (game.currentScreen == GameScreen::Records)
            {
                if (key == sf::Keyboard::B || key == sf::Keyboard::Escape)
                {
                    PlayButtonSound(game);
                    game.currentScreen = GameScreen::Menu;
                }
            }

         
            else if (game.currentScreen == GameScreen::Game)
            {
                if (game.paused)
                {
                    if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
                    {
                        
                        game.pauseSelection--;
                        if (game.pauseSelection < 0)
                            game.pauseSelection = 1;
                    }
                    else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
                    {
                        
                        game.pauseSelection++;
                        if (game.pauseSelection > 1)
                            game.pauseSelection = 0;
                    }
                    else if (key == sf::Keyboard::Enter)
                    {
                        PlayButtonSound(game);
                        if (game.pauseSelection == 0)
                        {
                            game.paused = false;
                            game.delayTimer = START_DELAY;
                        }
                        else
                        {
                            game.paused = false;
                            game.currentScreen = GameScreen::Menu;
                        }
                    }
                    else if (key == sf::Keyboard::P)
                    {
                        PlayButtonSound(game);
                        game.paused = false;
                        game.delayTimer = START_DELAY;
                    }
                    continue;
                }

                if (key == sf::Keyboard::P)
                {
                    PlayButtonSound(game);
                    game.paused = true;
                    game.pauseSelection = 0;
                }
                else if (key == sf::Keyboard::D || key == sf::Keyboard::Right)
                {
                    if (game.snake.direction != snakeDir::Left)
                        game.snake.direction = snakeDir::Right;
                }
                else if (key == sf::Keyboard::A || key == sf::Keyboard::Left)
                {
                    if (game.snake.direction != snakeDir::Right)
                        game.snake.direction = snakeDir::Left;
                }
                else if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
                {
                    if (game.snake.direction != snakeDir::Down)
                        game.snake.direction = snakeDir::Up;
                }
                else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
                {
                    if (game.snake.direction != snakeDir::Up)
                        game.snake.direction = snakeDir::Down;
                }
                else if (key == sf::Keyboard::B || key == sf::Keyboard::Escape)
                {
                    PlayButtonSound(game);
                    game.currentScreen = GameScreen::Menu;
                }
            }

           
            else if (game.currentScreen == GameScreen::GameOver)
            {
               
                if (game.gameOverStage == 0)
                {
                    if (key == sf::Keyboard::W || key == sf::Keyboard::Up ||
                        key == sf::Keyboard::S || key == sf::Keyboard::Down)
                    {
                        
                        game.saveSelection = 1 - game.saveSelection;
                    }
                    else if (key == sf::Keyboard::Enter)
                    {
                        PlayButtonSound(game);
                        if (game.saveSelection == 1)
                        {
                            game.inputName = "";
                            game.currentScreen = GameScreen::NameInput;
                        }
                        else
                        {
                            
                            game.gameOverSelection = 0;
                            game.gameOverStage = 1;
                        }
                    }
                }
                else
                {
                    if (key == sf::Keyboard::W || key == sf::Keyboard::Up)
                    {
                        
                        game.gameOverSelection--;
                        if (game.gameOverSelection < 0)
                            game.gameOverSelection = 1;
                    }
                    else if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
                    {
						
                        game.gameOverSelection++;
                        if (game.gameOverSelection > 1)
                            game.gameOverSelection = 0;
                    }
                    else if (key == sf::Keyboard::Enter)
                    {
                        PlayButtonSound(game);
                        if (game.gameOverSelection == 0)
                        {
                            ResetGame(game);
                            game.currentScreen = GameScreen::Game;
                        }
                        else
                        {
                            game.currentScreen = GameScreen::Menu;
                        }
                    }
                }
            }

            
            else if (game.currentScreen == GameScreen::NameInput)
            {
                if (key == sf::Keyboard::Enter)
                {
                    PlayButtonSound(game);
                    SnakeGame::AddRecord(game, game.inputName.empty() ? "XYZ" : game.inputName);
                    game.inputName.clear();
                    game.currentScreen = GameScreen::GameOver;
                    game.gameOverStage = 1;
                    game.gameOverSelection = 0;
                }
                else if (key == sf::Keyboard::Escape)
                {
                    PlayButtonSound(game);
                    game.inputName.clear();
                    game.currentScreen = GameScreen::GameOver;
                    game.gameOverStage = 1;
                    game.gameOverSelection = 0;
                }
            }
        }

        UpdateGame(game, deltaTime, window);
        DrawGame(game, window);
    }

    return 0;
}
