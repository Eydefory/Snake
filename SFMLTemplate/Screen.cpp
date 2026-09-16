#include "Game.h"
#include "Input.h"

namespace SnakeGame
{
    void SwitchState(
        Gamestate& game,
        GameScreen newState)
    {
        game.currentScreen = newState;

        switch (newState)
        {
        case GameScreen::Menu:
            game.menu.selection = 0;
            break;

        case GameScreen::Difficulty:
            game.difficulty.selection =
                game.gameplay.selectedDifficulty - 1;
            break;

        case GameScreen::Settings:
            game.settings.selection = 0;
            break;

        case GameScreen::Records:
            break;

        case GameScreen::Game:
            break;

        case GameScreen::GameOver:
            game.gameOver.selection = 0;
            game.gameOver.saveSelection = 0;
            game.gameOver.stage =
                GameOverStage::SaveQuestion;
            break;

        case GameScreen::NameInput:
            game.nameInput.inputName.clear();
            break;
        }
    }


    void MoveSelection(
        int& selection,
        int itemCount,
        bool up)
    {
        if (up)
        {
            --selection;

            if (selection < 0)
            {
                selection = itemCount - 1;
            }
        }
        else
        {
            ++selection;

            if (selection >= itemCount)
            {
                selection = 0;
            }
        }
    }


    void HandleMenuInput(
        Gamestate& game,
        sf::RenderWindow& window,
        sf::Keyboard::Key key)
    {
        constexpr int MENU_ITEMS = 5;

        if (IsUp(key))
        {
            MoveSelection(
                game.menu.selection,
                MENU_ITEMS,
                true
            );
        }
        else if (IsDown(key))
        {
            MoveSelection(
                game.menu.selection,
                MENU_ITEMS,
                false
            );
        }
        else if (IsConfirm(key))
        {
            PlayButtonSound(game);

            switch (
                static_cast<MenuItem>(
                    game.menu.selection
                    ))
            {
            case MenuItem::StartGame:
                ResetGame(game);
                SwitchState(game, GameScreen::Game);
                break;

            case MenuItem::Difficulty:
                SwitchState(
                    game,
                    GameScreen::Difficulty
                );
                break;

            case MenuItem::Records:
                SwitchState(
                    game,
                    GameScreen::Records
                );
                break;

            case MenuItem::Settings:
                SwitchState(
                    game,
                    GameScreen::Settings
                );
                break;

            case MenuItem::Exit:
                window.close();
                break;
            }
        }
    }


    void HandleDifficultyInput(
        Gamestate& game,
        sf::Keyboard::Key key)
    {
        if (IsUp(key))
        {
            MoveSelection(
                game.difficulty.selection,
                MAX_DIFFICULTY,
                true
            );
        }
        else if (IsDown(key))
        {
            MoveSelection(
                game.difficulty.selection,
                MAX_DIFFICULTY,
                false
            );
        }
        else if (IsConfirm(key))
        {
            PlayButtonSound(game);

            game.gameplay.selectedDifficulty =
                game.difficulty.selection + 1;

            SwitchState(
                game,
                GameScreen::Menu
            );
        }
        else if (IsBack(key))
        {
            PlayButtonSound(game);

            SwitchState(
                game,
                GameScreen::Menu
            );
        }
    }


    void HandleSettingsInput(
        Gamestate& game,
        sf::Keyboard::Key key)
    {
        constexpr int SETTINGS_ITEMS = 2;

        if (IsUp(key))
        {
            MoveSelection(
                game.settings.selection,
                SETTINGS_ITEMS,
                true
            );
        }
        else if (IsDown(key))
        {
            MoveSelection(
                game.settings.selection,
                SETTINGS_ITEMS,
                false
            );
        }
        else if (IsConfirm(key))
        {
            PlayButtonSound(game);

            if (game.settings.selection == 0)
            {
                game.audio.soundEnabled =
                    !game.audio.soundEnabled;
            }
            else
            {
                game.audio.musicEnabled =
                    !game.audio.musicEnabled;
            }
        }
        else if (IsBack(key))
        {
            PlayButtonSound(game);

            SwitchState(
                game,
                GameScreen::Menu
            );
        }
    }


    void HandleRecordsInput(
        Gamestate& game,
        sf::Keyboard::Key key)
    {
        if (IsBack(key))
        {
            PlayButtonSound(game);

            SwitchState(
                game,
                GameScreen::Menu
            );
        }
    }


    void HandlePauseInput(
        Gamestate& game,
        sf::Keyboard::Key key)
    {
        constexpr int PAUSE_ITEMS = 2;

        if (IsUp(key))
        {
            MoveSelection(
                game.pause.selection,
                PAUSE_ITEMS,
                true
            );
        }
        else if (IsDown(key))
        {
            MoveSelection(
                game.pause.selection,
                PAUSE_ITEMS,
                false
            );
        }
        else if (IsConfirm(key))
        {
            PlayButtonSound(game);

            if (game.pause.selection == 0)
            {
                game.gameplay.paused = false;
                game.gameplay.delayTimer = START_DELAY;
            }
            else
            {
                game.gameplay.paused = false;

                SwitchState(
                    game,
                    GameScreen::Menu
                );
            }
        }
        else if (IsPause(key))
        {
            PlayButtonSound(game);

            game.gameplay.paused = false;
            game.gameplay.delayTimer = START_DELAY;
        }
    }


    void ChangeSnakeDirection(
        Gamestate& game,
        snakeDir direction,
        snakeDir forbiddenDirection)
    {
        if (game.snake.direction != forbiddenDirection)
        {
            game.snake.direction = direction;
        }
    }


    void HandleGameInput(
        Gamestate& game,
        sf::Keyboard::Key key)
    {
        if (game.gameplay.paused)
        {
            HandlePauseInput(game, key);
            return;
        }

        if (IsPause(key))
        {
            PlayButtonSound(game);

            game.gameplay.paused = true;
            game.pause.selection = 0;
        }
        else if (IsRight(key))
        {
            ChangeSnakeDirection(
                game,
                snakeDir::Right,
                snakeDir::Left
            );
        }
        else if (IsLeft(key))
        {
            ChangeSnakeDirection(
                game,
                snakeDir::Left,
                snakeDir::Right
            );
        }
        else if (IsUp(key))
        {
            ChangeSnakeDirection(
                game,
                snakeDir::Up,
                snakeDir::Down
            );
        }
        else if (IsDown(key))
        {
            ChangeSnakeDirection(
                game,
                snakeDir::Down,
                snakeDir::Up
            );
        }
        else if (IsBack(key))
        {
            PlayButtonSound(game);

            SwitchState(
                game,
                GameScreen::Menu
            );
        }
    }


    void HandleGameOverInput(
        Gamestate& game,
        sf::Keyboard::Key key)
    {
        if (
            game.gameOver.stage ==
            GameOverStage::SaveQuestion
            )
        {
            if (IsUp(key) || IsDown(key))
            {
                game.gameOver.saveSelection =
                    1 - game.gameOver.saveSelection;
            }
            else if (IsConfirm(key))
            {
                PlayButtonSound(game);

                if (game.gameOver.saveSelection == 1)
                {
                    SwitchState(
                        game,
                        GameScreen::NameInput
                    );
                }
                else
                {
                    game.gameOver.selection = 0;
                    game.gameOver.stage =
                        GameOverStage::Result;
                }
            }

            return;
        }

        constexpr int GAME_OVER_ITEMS = 2;

        if (IsUp(key))
        {
            MoveSelection(
                game.gameOver.selection,
                GAME_OVER_ITEMS,
                true
            );
        }
        else if (IsDown(key))
        {
            MoveSelection(
                game.gameOver.selection,
                GAME_OVER_ITEMS,
                false
            );
        }
        else if (IsConfirm(key))
        {
            PlayButtonSound(game);

            if (game.gameOver.selection == 0)
            {
                ResetGame(game);

                SwitchState(
                    game,
                    GameScreen::Game
                );
            }
            else
            {
                SwitchState(
                    game,
                    GameScreen::Menu
                );
            }
        }
    }


    void HandleNameInput(
        Gamestate& game,
        sf::Keyboard::Key key)
    {
        if (IsConfirm(key))
        {
            PlayButtonSound(game);

            AddRecord(
                game,
                game.nameInput.inputName.empty()
                ? "XYZ"
                : game.nameInput.inputName
            );

            game.nameInput.inputName.clear();

            game.gameOver.stage =
                GameOverStage::Result;

            game.gameOver.selection = 0;

            game.currentScreen =
                GameScreen::GameOver;
        }
        else if (IsBack(key))
        {
            PlayButtonSound(game);

            game.nameInput.inputName.clear();

            game.gameOver.stage =
                GameOverStage::Result;

            game.gameOver.selection = 0;

            game.currentScreen =
                GameScreen::GameOver;
        }
    }


    void HandleTextInput(
        Gamestate& game,
        const sf::Event& event)
    {
        const unsigned int unicode =
            event.text.unicode;

        constexpr unsigned int BACKSPACE = 8;
        constexpr unsigned int FIRST_PRINTABLE = 32;
        constexpr unsigned int LAST_PRINTABLE = 127;

        if (unicode == BACKSPACE)
        {
            if (!game.nameInput.inputName.empty())
            {
                game.nameInput.inputName.pop_back();
            }

            return;
        }

        if (
            unicode >= FIRST_PRINTABLE &&
            unicode < LAST_PRINTABLE &&
            game.nameInput.inputName.size() <
            MAX_NAME_LENGTH
            )
        {
            game.nameInput.inputName +=
                static_cast<char>(unicode);
        }
    }


    void HandleEvents(
        Gamestate& game,
        sf::RenderWindow& window)
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                continue;
            }

            if (
                event.type == sf::Event::TextEntered &&
                game.currentScreen ==
                GameScreen::NameInput
                )
            {
                HandleTextInput(game, event);
                continue;
            }

            if (event.type != sf::Event::KeyPressed)
            {
                continue;
            }

            const sf::Keyboard::Key key =
                event.key.code;

            switch (game.currentScreen)
            {
            case GameScreen::Menu:
                HandleMenuInput(
                    game,
                    window,
                    key
                );
                break;

            case GameScreen::Difficulty:
                HandleDifficultyInput(
                    game,
                    key
                );
                break;

            case GameScreen::Settings:
                HandleSettingsInput(
                    game,
                    key
                );
                break;

            case GameScreen::Records:
                HandleRecordsInput(
                    game,
                    key
                );
                break;

            case GameScreen::Game:
                HandleGameInput(
                    game,
                    key
                );
                break;

            case GameScreen::GameOver:
                HandleGameOverInput(
                    game,
                    key
                );
                break;

            case GameScreen::NameInput:
                HandleNameInput(
                    game,
                    key
                );
                break;
            }
        }
    }
}