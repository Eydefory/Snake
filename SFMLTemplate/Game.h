#pragma once

#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Constants.h"
#include "Math.h"
#include "Snake.h"
#include "Apple.h"

namespace SnakeGame
{
    constexpr int MAX_RECORDS = 10;
    constexpr int TOP_RECORDS = 5;
    constexpr int MAX_NAME_LENGTH = 12;

    enum class GameScreen
    {
        Menu,
        Game,
        Difficulty,
        Settings,
        Records,
        GameOver,
        NameInput
    };

    enum class MenuItem
    {
        StartGame = 0,
        Difficulty,
        Records,
        Settings,
        Exit
    };

    enum class GameOverStage
    {
        SaveQuestion = 0,
        Result
    };

    struct ScoreEntry
    {
        std::string name = "XYZ";
        int score = 0;
    };

    struct MenuState
    {
        int selection = 0;
    };

    struct DifficultyState
    {
        int selection = 0;
    };

    struct SettingsState
    {
        int selection = 0;
    };

    struct PauseState
    {
        int selection = 0;
    };

    struct GameOverState
    {
        int selection = 0;
        int saveSelection = 0;
        GameOverStage stage = GameOverStage::SaveQuestion;
    };


    
    struct GamePlayState
    {
        bool paused = false;
        bool hasWon = false;

        int score = 0;
        int selectedDifficulty = 1;

        float moveTimer = 0.f;
        float delayTimer = START_DELAY;
    };


    
    struct AudioState
    {
        bool soundEnabled = true;
        bool musicEnabled = true;
    };


    
    struct NameInputState
    {
        std::string inputName;
    };


    struct RecordsState : public std::vector<ScoreEntry>
    {
    };


    struct Gamestate
    {
        Snake snake;
        Apples apples;

        sf::Texture appleTexture;

        sf::Texture headUpTexture;
        sf::Texture headDownTexture;
        sf::Texture headLeftTexture;
        sf::Texture headRightTexture;

        sf::Texture bodyHorizontalTexture;
        sf::Texture bodyVerticalTexture;
        sf::Texture bodyTopLeftTexture;
        sf::Texture bodyTopRightTexture;
        sf::Texture bodyBottomLeftTexture;
        sf::Texture bodyBottomRightTexture;

        sf::Texture tailUpTexture;
        sf::Texture tailDownTexture;
        sf::Texture tailLeftTexture;
        sf::Texture tailRightTexture;

        sf::Font font;
        sf::Font font2;

        sf::SoundBuffer eatSoundBuffer;
        sf::Sound eatSound;

        sf::SoundBuffer crashSoundBuffer;
        sf::Sound crashSound;

        sf::SoundBuffer startSoundBuffer;
        sf::Sound startSound;

        sf::Music menuMusic;
        sf::Music gameMusic;

        sf::SoundBuffer buttonSoundBuffer;
        sf::Sound buttonSound;

        sf::SoundBuffer gameOverSoundBuffer;
        sf::Sound gameOverSound;


        
        GameScreen currentScreen = GameScreen::Menu;

        MenuState menu;
        DifficultyState difficulty;
        SettingsState settings;
        PauseState pause;
        GameOverState gameOver;


        
        GamePlayState gameplay;
        AudioState audio;
        NameInputState nameInput;
        RecordsState records;
    };


    inline void InitGame(Gamestate& game)
    {
        assert(
            game.appleTexture.loadFromFile(
                "Resources/apple.png"
            )
        );

        assert(
            game.headUpTexture.loadFromFile(
                "Resources/head_up.png"
            )
        );

        assert(
            game.headDownTexture.loadFromFile(
                "Resources/head_down.png"
            )
        );

        assert(
            game.headLeftTexture.loadFromFile(
                "Resources/head_left.png"
            )
        );

        assert(
            game.headRightTexture.loadFromFile(
                "Resources/head_right.png"
            )
        );

        assert(
            game.bodyHorizontalTexture.loadFromFile(
                "Resources/body_horizontal.png"
            )
        );

        assert(
            game.bodyVerticalTexture.loadFromFile(
                "Resources/body_vertical.png"
            )
        );

        assert(
            game.bodyTopLeftTexture.loadFromFile(
                "Resources/body_topleft.png"
            )
        );

        assert(
            game.bodyTopRightTexture.loadFromFile(
                "Resources/body_topright.png"
            )
        );

        assert(
            game.bodyBottomLeftTexture.loadFromFile(
                "Resources/body_bottomleft.png"
            )
        );

        assert(
            game.bodyBottomRightTexture.loadFromFile(
                "Resources/body_bottomright.png"
            )
        );

        assert(
            game.tailUpTexture.loadFromFile(
                "Resources/tail_up.png"
            )
        );

        assert(
            game.tailDownTexture.loadFromFile(
                "Resources/tail_down.png"
            )
        );

        assert(
            game.tailLeftTexture.loadFromFile(
                "Resources/tail_left.png"
            )
        );

        assert(
            game.tailRightTexture.loadFromFile(
                "Resources/tail_right.png"
            )
        );

        assert(
            game.font.loadFromFile(
                "Resources/Fonts/Roboto-Light.ttf"
            )
        );

        assert(
            game.font2.loadFromFile(
                "Resources/Fonts/Roboto-Medium.ttf"
            )
        );

        assert(
            game.menuMusic.openFromFile(
                "Resources/menu-music.ogg"
            )
        );

        game.menuMusic.setLoop(true);
        game.menuMusic.setVolume(10.f);

        assert(
            game.gameMusic.openFromFile(
                "Resources/game-music.ogg"
            )
        );

        game.gameMusic.setLoop(true);
        game.gameMusic.setVolume(10.f);

        assert(
            game.buttonSoundBuffer.loadFromFile(
                "Resources/button.wav"
            )
        );

        game.buttonSound.setBuffer(
            game.buttonSoundBuffer
        );

        game.buttonSound.setVolume(15.f);

        assert(
            game.eatSoundBuffer.loadFromFile(
                "Resources/apple-bite-short.wav"
            )
        );

        game.eatSound.setBuffer(
            game.eatSoundBuffer
        );

        game.eatSound.setVolume(15.f);

        assert(
            game.startSoundBuffer.loadFromFile(
                "Resources/start-sound.wav"
            )
        );

        game.startSound.setBuffer(
            game.startSoundBuffer
        );

        game.startSound.setVolume(30.f);

        assert(
            game.crashSoundBuffer.loadFromFile(
                "Resources/crash.wav"
            )
        );

        game.crashSound.setBuffer(
            game.crashSoundBuffer
        );

        game.crashSound.setVolume(15.f);

        assert(
            game.gameOverSoundBuffer.loadFromFile(
                "Resources/end.wav"
            )
        );

        game.gameOverSound.setBuffer(
            game.gameOverSoundBuffer
        );

        game.gameOverSound.setVolume(80.f);


        std::ifstream file("scores.txt");

        ScoreEntry entry;

        while (file >> entry.name >> entry.score)
        {
            game.records.push_back(entry);
        }

        std::sort(
            game.records.begin(),
            game.records.end(),
            [](const ScoreEntry& first,
                const ScoreEntry& second)
            {
                return first.score > second.score;
            }
        );

        if (game.records.size() > MAX_RECORDS)
        {
            game.records.resize(MAX_RECORDS);
        }

        game.apples.numApples = 1;
        game.gameplay.selectedDifficulty = 1;
        game.currentScreen = GameScreen::Menu;
    }


    void ResetGame(Gamestate& game);

    void UpdateGame(
        Gamestate& game,
        float deltaTime,
        sf::RenderWindow& window
    );

    void DrawGame(
        Gamestate& game,
        sf::RenderWindow& window
    );

    void HandleEvents(
        Gamestate& game,
        sf::RenderWindow& window
    );

    void SwitchState(
        Gamestate& game,
        GameScreen newState
    );

    void AddRecord(
        Gamestate& game,
        const std::string& name
    );

    void PlayButtonSound(Gamestate& game);
}