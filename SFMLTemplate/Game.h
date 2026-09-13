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
    struct ScoreEntry
    {
        std::string name = "XYZ";
        int score = 0;
    };

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

		

        bool soundEnabled = true;
        bool musicEnabled = true;

        bool paused = false;
        bool hasWon = false;

        int score = 0;

        int selectedDifficulty = 1;

        int menuSelection = 0;
        int difficultySelection = 0;
        int settingsSelection = 0;
        int gameOverSelection = 0;
        int saveSelection = 0;
        int gameOverStage = 0;
        int pauseSelection = 0;

        float moveTimer = 0.f;
        float delayTimer = START_DELAY;

        std::string inputName;

        std::vector<ScoreEntry> records;

        GameScreen currentScreen = GameScreen::Menu;
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

        assert(game.menuMusic.openFromFile("Resources/menu-music.ogg"));
        game.menuMusic.setLoop(true);
        game.menuMusic.setVolume(20.f);

        assert(game.gameMusic.openFromFile("Resources/game-music.ogg"));
        game.gameMusic.setLoop(true);
        game.gameMusic.setVolume(20.f);

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

        assert(game.gameOverSoundBuffer.loadFromFile("Resources/end.wav"));

		

        game.gameOverSound.setBuffer(game.gameOverSoundBuffer);

        game.gameOverSound.setVolume(80.f);

        std::ifstream file("scores.txt");

        ScoreEntry entry;

        while (file >> entry.name >> entry.score)
            game.records.push_back(entry);

        std::sort(
            game.records.begin(),
            game.records.end(),
            [](const ScoreEntry& first,
                const ScoreEntry& second)
            {
                return first.score > second.score;
            }
        );




        if (game.records.size() > 10)
            game.records.resize(10);

        game.apples.numApples = 1;
        game.selectedDifficulty = 1;
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

    void AddRecord(
        Gamestate& game,
        const std::string& name
    );

    void PlayButtonSound(Gamestate& game);
}