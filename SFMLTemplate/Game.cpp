#include "Game.h"

namespace SnakeGame
{
    int DifficultyPoints(int difficulty)
    {
        if (difficulty < MIN_DIFFICULTY)
            difficulty = MIN_DIFFICULTY;

        if (difficulty > MAX_DIFFICULTY)
            difficulty = MAX_DIFFICULTY;

        return DIFFICULTY_POINTS[difficulty - 1];
    }

    float DifficultySpeed(int difficulty)
    {
        if (difficulty < MIN_DIFFICULTY)
            difficulty = MIN_DIFFICULTY;

        if (difficulty > MAX_DIFFICULTY)
            difficulty = MAX_DIFFICULTY;

        return DIFFICULTY_SPEEDS[difficulty - 1];
    }

    const char* DifficultyName(int difficulty)
    {
        switch (difficulty)
        {
        case 1:
            return "Easy";

        case 2:
            return "Harder than Easy";

        case 3:
            return "Normal";

        case 4:
            return "Harder than Normal";

        default:
            return "Hard";
        }
    }

	

    void PlayEatSound(Gamestate& game)
    {
        if (game.soundEnabled)
            game.eatSound.play();
    }

    void PlayCrashSound(Gamestate& game)
    {
        if (game.soundEnabled)
            game.crashSound.play();
    }

    void PlayGameOverSound(Gamestate& game)
    {
        if (game.soundEnabled)
            game.gameOverSound.play();
    }

    void PlayStartSound(Gamestate& game)
    {
        if (game.soundEnabled)
            game.startSound.play();
    }

    void PlayButtonSound(Gamestate& game)
    {
        if (game.soundEnabled)
            game.buttonSound.play();
    }

    void UpdateMusic(Gamestate& game)
    {
        if (!game.musicEnabled)
        {
            game.menuMusic.stop();
            game.gameMusic.stop();
            return;
        }

        if (game.currentScreen == GameScreen::Menu)
        {
            game.gameMusic.stop();

            if (game.menuMusic.getStatus() != sf::SoundSource::Playing)
                game.menuMusic.play();
        }
        else if (game.currentScreen == GameScreen::Game)
        {
            game.menuMusic.stop();

            if (game.gameMusic.getStatus() != sf::SoundSource::Playing)
                game.gameMusic.play();
        }
        else
        {
            game.menuMusic.stop();
            game.gameMusic.stop();
        }
    }

    

    void SetBodyTexture(
        Gamestate& game,
        int index)
    {
        const int size =
            static_cast<int>(game.snake.segments.size());

        if (index <= 0 || index >= size - 1)
            return;

        const Position2D current =
            game.snake.segments[index].position;

        const Position2D previous =
            game.snake.segments[index - 1].position;

        const Position2D next =
            game.snake.segments[index + 1].position;

        bool left = false;
        bool right = false;
        bool up = false;
        bool down = false;

        if (previous.x < current.x)
            left = true;

        if (previous.x > current.x)
            right = true;

        if (previous.y < current.y)
            up = true;

        if (previous.y > current.y)
            down = true;

        if (next.x < current.x)
            left = true;

        if (next.x > current.x)
            right = true;

        if (next.y < current.y)
            up = true;

        if (next.y > current.y)
            down = true;

        if (left && right)
        {
            game.snake.segments[index].sprite.setTexture(
                game.bodyHorizontalTexture
            );
        }
        else if (up && down)
        {
            game.snake.segments[index].sprite.setTexture(
                game.bodyVerticalTexture
            );
        }
        else if (up && left)
        {
            game.snake.segments[index].sprite.setTexture(
                game.bodyTopLeftTexture
            );
        }
        else if (up && right)
        {
            game.snake.segments[index].sprite.setTexture(
                game.bodyTopRightTexture
            );
        }
        else if (down && left)
        {
            game.snake.segments[index].sprite.setTexture(
                game.bodyBottomLeftTexture
            );
        }
        else if (down && right)
        {
            game.snake.segments[index].sprite.setTexture(
                game.bodyBottomRightTexture
            );
        }
    }

    void SetSnakeTextures(Gamestate& game)
    {
        const int size =
            static_cast<int>(game.snake.segments.size());

        if (size == 0)
            return;

        for (int i = 0; i < size; ++i)
        {
            SnakeSegment& segment =
                game.snake.segments[i];

            if (i == 0)
            {
                if (segment.direction == snakeDir::Up)
                {
                    segment.sprite.setTexture(
                        game.headUpTexture
                    );
                }
                else if (segment.direction == snakeDir::Down)
                {
                    segment.sprite.setTexture(
                        game.headDownTexture
                    );
                }
                else if (segment.direction == snakeDir::Left)
                {
                    segment.sprite.setTexture(
                        game.headLeftTexture
                    );
                }
                else
                {
                    segment.sprite.setTexture(
                        game.headRightTexture
                    );
                }
            }
            else if (i == size - 1)
            {
                const Position2D current =
                    segment.position;

                const Position2D previous =
                    game.snake.segments[i - 1].position;

                if (previous.x > current.x)
                {
                    segment.sprite.setTexture(
                        game.tailLeftTexture
                    );
                }
                else if (previous.x < current.x)
                {
                    segment.sprite.setTexture(
                        game.tailRightTexture
                    );
                }
                else if (previous.y > current.y)
                {
                    segment.sprite.setTexture(
                        game.tailUpTexture
                    );
                }
                else if (previous.y < current.y)
                {
                    segment.sprite.setTexture(
                        game.tailDownTexture
                    );
                }
            }
            else
            {
                SetBodyTexture(game, i);
            }

            const sf::Texture* texture =
                segment.sprite.getTexture();

            if (texture != nullptr &&
                texture->getSize().x > 0 &&
                texture->getSize().y > 0)
            {
                segment.sprite.setScale(
                    PLAYER_SIZE / texture->getSize().x,
                    PLAYER_SIZE / texture->getSize().y
                );
            }

            segment.sprite.setPosition(
                segment.position.x,
                segment.position.y
            );
        }
    }

    void ResetGame(Gamestate& game)
    {
        game.snake.segments.clear();

        for (int i = 0;
            i < INITIAL_SNAKE_LENGTH;
            ++i)
        {
            SnakeSegment segment;

            segment.position.x =
                400.f - i * PLAYER_SIZE;

            segment.position.y = 300.f;

            segment.direction = snakeDir::Right;

            game.snake.segments.push_back(segment);
        }

        game.snake.direction = snakeDir::Right;

        game.snake.snakeSpeed =
            DifficultySpeed(game.selectedDifficulty);

        game.snake.isAlive = true;

        game.score = 0;
        game.moveTimer = 0.f;
        game.delayTimer = START_DELAY;

        game.paused = false;
        game.hasWon = false;

        game.saveSelection = 0;
        game.gameOverStage = 0;
        game.gameOverSelection = 0;
        game.pauseSelection = 0;

        game.inputName.clear();

        InitApples(game.apples, game);

        SetSnakeTextures(game);
    }

    void MoveSnake(Gamestate& game)
    {
        std::vector<Position2D> oldPositions;
        std::vector<snakeDir> oldDirections;

        oldPositions.reserve(
            game.snake.segments.size()
        );

        oldDirections.reserve(
            game.snake.segments.size()
        );

        for (const SnakeSegment& segment :
            game.snake.segments)
        {
            oldPositions.push_back(
                segment.position
            );

            oldDirections.push_back(
                segment.direction
            );
        }

        SnakeSegment& head =
            game.snake.segments[0];

        if (game.snake.direction == snakeDir::Right)
        {
            head.position.x += PLAYER_SIZE;
        }
        else if (game.snake.direction == snakeDir::Left)
        {
            head.position.x -= PLAYER_SIZE;
        }
        else if (game.snake.direction == snakeDir::Up)
        {
            head.position.y -= PLAYER_SIZE;
        }
        else if (game.snake.direction == snakeDir::Down)
        {
            head.position.y += PLAYER_SIZE;
        }

        head.direction =
            game.snake.direction;

        for (int i = 1;
            i < static_cast<int>(
                game.snake.segments.size());
            ++i)
        {
            game.snake.segments[i].position =
                oldPositions[i - 1];

            game.snake.segments[i].direction =
                oldDirections[i - 1];
        }
    }

    bool CheckWallCollision(const Snake& snake)
    {
        if (snake.segments.empty())
            return false;

        const Position2D head =
            snake.segments[0].position;

        return
            head.x < PLAYER_SIZE ||
            head.x >= SCREEN_WIDTH - PLAYER_SIZE ||
            head.y < PLAYER_SIZE ||
            head.y >= SCREEN_HEIGHT - PLAYER_SIZE;
    }

    bool CheckSelfCollision(const Snake& snake)
    {
        if (snake.segments.empty())
            return false;

        for (int i = 1;
            i < static_cast<int>(
                snake.segments.size());
            ++i)
        {
            if (SamePosition(
                snake.segments[0].position,
                snake.segments[i].position))
            {
                return true;
            }
        }

        return false;
    }

    void SaveRecords(const Gamestate& game)
    {
        std::ofstream file(
            "scores.txt",
            std::ios::trunc
        );

        for (const ScoreEntry& entry :
            game.records)
        {
            file << entry.name
                << ' '
                << entry.score
                << '\n';
        }
    }

    void AddRecord(
        Gamestate& game,
        const std::string& name)
    {
        ScoreEntry entry;

        entry.name =
            name.empty() ? "XYZ" : name;

        entry.score = game.score;

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

        SaveRecords(game);
    }

    void EatApple(Gamestate& game)
    {
        for (int i = 0;
            i < static_cast<int>(
                game.apples.applePos.size());
                ++i)
        {
            if (game.apples.isAppleEaten[i])
                continue;

            if (!SamePosition(
                game.snake.segments[0].position,
                game.apples.applePos[i]))
            {
                continue;
            }

            game.apples.isAppleEaten[i] = true;

            game.score +=
                DifficultyPoints(
                    game.selectedDifficulty
                );

            PlayEatSound(game);

            for (int grow = 0;
                grow < GROWTH_PER_APPLE;
                ++grow)
            {
                const int last =
                    static_cast<int>(
                        game.snake.segments.size()
                        ) - 1;

                SnakeSegment newSegment;

                const Position2D tail =
                    game.snake.segments[last].position;

                if (last > 0)
                {
                    const Position2D beforeTail =
                        game.snake.segments[last - 1].position;

                    newSegment.position.x =
                        tail.x +
                        (tail.x - beforeTail.x);

                    newSegment.position.y =
                        tail.y +
                        (tail.y - beforeTail.y);
                }
                else
                {
                    newSegment.position = tail;
                }

                newSegment.direction =
                    game.snake.segments[last].direction;

                game.snake.segments.push_back(
                    newSegment
                );
            }

            Position2D newPosition;

            if (!FindFreeApplePosition(
                game.apples,
                game,
                newPosition))
            {
                game.hasWon = true;
                game.snake.isAlive = false;
                return;
            }

            game.apples.applePos[i] =
                newPosition;

            game.apples.isAppleEaten[i] =
                false;

            game.apples.appleSprite[i].setPosition(
                newPosition.x,
                newPosition.y
            );
        }
    }

    void UpdateGame(
        Gamestate& game,
        float deltaTime,
        sf::RenderWindow&)
    {
        UpdateMusic(game);

        if (game.currentScreen != GameScreen::Game)
            return;

        if (game.paused)
            return;

        if (game.delayTimer > 0.f)
        {
            game.delayTimer -= deltaTime;

            if (game.delayTimer <= 0.f)
            {
                game.delayTimer = 0.f;
                PlayStartSound(game);
            }

            return;
        }

        if (!game.snake.isAlive)
        {
            if (!game.hasWon)
                PlayCrashSound(game);

            game.currentScreen =
                GameScreen::GameOver;

            PlayGameOverSound(game);

            game.gameOverSelection = 0;
            game.saveSelection = 0;
            game.gameOverStage = 0;

            return;
        }

        game.moveTimer += deltaTime;

        const float moveDelay =
            PLAYER_SIZE /
            game.snake.snakeSpeed;

        if (game.moveTimer < moveDelay)
            return;

        game.moveTimer -= moveDelay;

        MoveSnake(game);

        if (CheckWallCollision(game.snake) ||
            CheckSelfCollision(game.snake))
        {
            game.snake.isAlive = false;

            PlayCrashSound(game);
            PlayGameOverSound(game);

            game.currentScreen =
                GameScreen::GameOver;

            game.gameOverSelection = 0;
            game.saveSelection = 0;
            game.gameOverStage = 0;

            return;
        }

        EatApple(game);

        SetSnakeTextures(game);
    }

    void DrawText(
        sf::RenderWindow& window,
        sf::Font& font,
        const std::string& text,
        float x,
        float y,
        unsigned int size,
        sf::Color color = sf::Color::White)
    {
        sf::Text label;

        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(size);
        label.setFillColor(color);
        label.setPosition(x, y);

        window.draw(label);
    }

    void DrawCentered(
        sf::RenderWindow& window,
        sf::Font& font,
        const std::string& text,
        float y,
        unsigned int size,
        sf::Color color = sf::Color::White)
    {
        sf::Text label;

        label.setFont(font);
        label.setString(text);
        label.setCharacterSize(size);
        label.setFillColor(color);

        const sf::FloatRect bounds =
            label.getLocalBounds();

        label.setPosition(
            (SCREEN_WIDTH - bounds.width) / 2.f -
            bounds.left,
            y
        );

        window.draw(label);
    }

    void DrawMenu(
        Gamestate& game,
        sf::RenderWindow& window)
    {
        window.clear(
            sf::Color(25, 25, 35)
        );

        DrawCentered(
            window,
            game.font2,
            "SNAKE",
            55.f,
            52
        );

        const char* items[] =
        {
            "Start game",
            "Difficulty",
            "Records",
            "Settings",
            "Exit"
        };

        for (int i = 0;
            i < 5;
            ++i)
        {
            DrawCentered(
                window,
                game.font,
                items[i],
                160.f + i * 55.f,
                27,
                game.menuSelection == i
                ? sf::Color::Green
                : sf::Color::White
            );
        }

        DrawCentered(
            window,
            game.font,
            "W/S - Select     ENTER - Choose",
            500.f,
            20,
            sf::Color(180, 180, 180)
        );

        window.display();
    }

    void DrawDifficulty(
        Gamestate& game,
        sf::RenderWindow& window)
    {
        window.clear(
            sf::Color(25, 25, 35)
        );

        DrawCentered(
            window,
            game.font,
            "DIFFICULTY",
            50.f,
            44
        );

        for (int i = 0;
            i < MAX_DIFFICULTY;
            ++i)
        {
            const int level = i + 1;

            const std::string line =
                std::to_string(level) +
                " - " +
                DifficultyName(level) +
                " | Speed " +
                std::to_string(
                    static_cast<int>(
                        DIFFICULTY_SPEEDS[i]
                        )
                ) +
                " | Points " +
                std::to_string(
                    DIFFICULTY_POINTS[i]
                );

            DrawCentered(
                window,
                game.font,
                line,
                135.f + i * 58.f,
                21,
                game.difficultySelection == i
                ? sf::Color::Green
                : sf::Color::White
            );
        }

        DrawCentered(
            window,
            game.font,
            "B - Back",
            510.f,
            20,
            sf::Color(180, 180, 180)
        );

        window.display();
    }

    void DrawSettings(
        Gamestate& game,
        sf::RenderWindow& window)
    {
        window.clear(
            sf::Color(25, 25, 35)
        );

        DrawCentered(
            window,
            game.font,
            "SETTINGS",
            60.f,
            44
        );

        const std::string sound =
            std::string("Sound: ") +
            (game.soundEnabled ? "ON" : "OFF");

        const std::string music =
            std::string("Music: ") +
            (game.musicEnabled ? "ON" : "OFF");

        DrawCentered(
            window,
            game.font,
            sound,
            190.f,
            28,
            game.settingsSelection == 0
            ? sf::Color::Green
            : sf::Color::White
        );

        DrawCentered(
            window,
            game.font,
            music,
            250.f,
            28,
            game.settingsSelection == 1
            ? sf::Color::Green
            : sf::Color::White
        );

        DrawCentered(
            window,
            game.font,
            "W/S - Select     ENTER - Toggle     B - Back",
            500.f,
            20,
            sf::Color(180, 180, 180)
        );

        window.display();
    }

    void DrawRecords(
        Gamestate& game,
        sf::RenderWindow& window)
    {
        window.clear(
            sf::Color(25, 25, 35)
        );

        DrawCentered(
            window,
            game.font,
            "LEADERBOARD",
            45.f,
            44
        );

        if (game.records.empty())
        {
            DrawCentered(
                window,
                game.font,
                "No records yet",
                180.f,
                28
            );
        }
        else
        {
            const int count =
                static_cast<int>(
                    game.records.size()
                    ) < 10
                ? static_cast<int>(
                    game.records.size()
                    )
                : 10;

            for (int i = 0;
                i < count;
                ++i)
            {
                const std::string line =
                    std::to_string(i + 1) +
                    ". " +
                    game.records[i].name +
                    " - " +
                    std::to_string(
                        game.records[i].score
                    );

                DrawCentered(
                    window,
                    game.font,
                    line,
                    125.f + i * 38.f,
                    22
                );
            }
        }

        DrawCentered(
            window,
            game.font,
            "B - Back",
            545.f,
            20,
            sf::Color(180, 180, 180)
        );

        window.display();
    }

    void DrawGameField(
        Gamestate& game,
        sf::RenderWindow& window)
    {
        window.clear(
            sf::Color(33, 41, 74)
        );

        sf::RectangleShape border;

        border.setPosition(0.f, 0.f);

        border.setSize(
            sf::Vector2f(
                static_cast<float>(SCREEN_WIDTH),
                static_cast<float>(SCREEN_HEIGHT)
            )
        );

        border.setFillColor(
            sf::Color::Transparent
        );

        border.setOutlineColor(
            sf::Color(80, 80, 95)
        );

        border.setOutlineThickness(4.f);

        window.draw(border);

        for (int i = 0;
            i < static_cast<int>(
                game.apples.appleSprite.size());
            ++i)
        {
            if (!game.apples.isAppleEaten[i])
                window.draw(
                    game.apples.appleSprite[i]
                );
        }

        for (int i =
            static_cast<int>(
                game.snake.segments.size()
                ) - 1;
            i >= 0;
            --i)
        {
            window.draw(
                game.snake.segments[i].sprite
            );
        }

        DrawText(
            window,
            game.font,
            "Score: " +
            std::to_string(game.score),
            680.f,
            35.f,
            22
        );

        DrawText(
            window,
            game.font,
            "Level: " +
            std::to_string(
                game.selectedDifficulty
            ),
            12.f,
            35.f,
            18,
            sf::Color::White
        );

        DrawText(
            window,
            game.font,
            "P - Pause",
            368.f,
            35.f,
            18,
            sf::Color::White
        );

        if (game.delayTimer > 0.f)
        {
            int seconds =
                static_cast<int>(
                    game.delayTimer
                    ) + 1;

            DrawCentered(
                window,
                game.font,
                "Starting in " +
                std::to_string(seconds),
                250.f,
                35
            );
        }

        if (game.paused)
        {
            sf::RectangleShape overlay;

            overlay.setSize(
                sf::Vector2f(
                    static_cast<float>(SCREEN_WIDTH),
                    static_cast<float>(SCREEN_HEIGHT)
                )
            );

            overlay.setFillColor(
                sf::Color(0, 0, 0, 160)
            );

            window.draw(overlay);

            DrawCentered(
                window,
                game.font,
                "PAUSED",
                150.f,
                48
            );

            DrawCentered(
                window,
                game.font,
                "Continue",
                250.f,
                28,
                game.pauseSelection == 0
                ? sf::Color::Green
                : sf::Color::White
            );

            DrawCentered(
                window,
                game.font,
                "Main menu",
                305.f,
                28,
                game.pauseSelection == 1
                ? sf::Color::Green
                : sf::Color::White
            );

            DrawCentered(
                window,
                game.font,
                "W/S - Select     ENTER - Choose",
                400.f,
                20,
                sf::Color(190, 190, 190)
            );
        }

        window.display();
    }

    void DrawTopFive(
        Gamestate& game,
        sf::RenderWindow& window,
        float y)
    {
        DrawText(
            window,
            game.font,
            "Top 5",
            560.f,
            y,
            21
        );

        const int count =
            static_cast<int>(
                game.records.size()
                ) < 5
            ? static_cast<int>(
                game.records.size()
                )
            : 5;

        for (int i = 0;
            i < count;
            ++i)
        {
            DrawText(
                window,
                game.font,
                std::to_string(i + 1) +
                ". " +
                game.records[i].name +
                "  " +
                std::to_string(
                    game.records[i].score
                ),
                560.f,
                y + 32.f + i * 28.f,
                18
            );
        }
    }

    void DrawGameOver(
        Gamestate& game,
        sf::RenderWindow& window)
    {
        window.clear(
            sf::Color(40, 15, 20)
        );

        DrawCentered(
            window,
            game.font,
            game.hasWon
            ? "YOU WIN!"
            : "GAME OVER",
            35.f,
            45
        );

        DrawCentered(
            window,
            game.font,
            "Score: " +
            std::to_string(game.score),
            95.f,
            27
        );

        DrawTopFive(
            game,
            window,
            160.f
        );

        if (game.gameOverStage == 0)
        {
            DrawCentered(
                window,
                game.font,
                "Save your score?",
                150.f,
                28
            );

            DrawCentered(
                window,
                game.font,
                "NO",
                250.f,
                27,
                game.saveSelection == 0
                ? sf::Color::Green
                : sf::Color::White
            );

            DrawCentered(
                window,
                game.font,
                "YES",
                305.f,
                27,
                game.saveSelection == 1
                ? sf::Color::Green
                : sf::Color::White
            );

            DrawCentered(
                window,
                game.font,
                "W/S - Select     ENTER - Choose",
                500.f,
                20,
                sf::Color(190, 190, 190)
            );
        }
        else
        {
            DrawCentered(
                window,
                game.font,
                "Restart",
                330.f,
                27,
                game.gameOverSelection == 0
                ? sf::Color::Green
                : sf::Color::White
            );

            DrawCentered(
                window,
                game.font,
                "Main menu",
                385.f,
                27,
                game.gameOverSelection == 1
                ? sf::Color::Green
                : sf::Color::White
            );

            DrawCentered(
                window,
                game.font,
                "W/S - Select     ENTER - Choose",
                500.f,
                20,
                sf::Color(190, 190, 190)
            );
        }

        window.display();
    }

    void DrawNameInput(
        Gamestate& game,
        sf::RenderWindow& window)
    {
        window.clear(
            sf::Color(25, 25, 35)
        );

        DrawCentered(
            window,
            game.font,
            "NEW RECORD",
            100.f,
            45
        );

        DrawCentered(
            window,
            game.font,
            "Enter your name:",
            190.f,
            27
        );

        DrawCentered(
            window,
            game.font,
            game.inputName.empty()
            ? "XYZ"
            : game.inputName,
            250.f,
            35,
            sf::Color::Green
        );

        DrawCentered(
            window,
            game.font,
            "ENTER - Save     ESC - Cancel",
            400.f,
            20,
            sf::Color(190, 190, 190)
        );

        window.display();
    }

    void DrawGame(
        Gamestate& game,
        sf::RenderWindow& window)
    {
        if (game.currentScreen == GameScreen::Menu)
        {
            DrawMenu(game, window);
            return;
        }

        if (game.currentScreen == GameScreen::Difficulty)
        {
            DrawDifficulty(game, window);
            return;
        }

        if (game.currentScreen == GameScreen::Settings)
        {
            DrawSettings(game, window);
            return;
        }

        if (game.currentScreen == GameScreen::Records)
        {
            DrawRecords(game, window);
            return;
        }

        if (game.currentScreen == GameScreen::GameOver)
        {
            DrawGameOver(game, window);
            return;
        }

        if (game.currentScreen == GameScreen::NameInput)
        {
            DrawNameInput(game, window);
            return;
        }

        DrawGameField(game, window);
    }
}