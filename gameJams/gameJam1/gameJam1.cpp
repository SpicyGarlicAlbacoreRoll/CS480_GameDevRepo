// kimGameJam01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <gamelib.hpp>
#include "RunnerInputComponent.hpp"
#include "RunnerActorComponent.hpp"
#include "MonsterActorComponent.hpp"
#include "BoxCollisionComponent.hpp"

#pragma comment(lib, "gamelib.lib")

class QuitCommand : public GameLib::InputCommand {
public:
    const char* type() const override { return "QuitCommand"; }

    bool execute(float amount) override {
        GameLib::Locator::getContext()->quitRequested = true;
        return true;
    }
};

class MovementCommand : public GameLib::InputCommand {
public:
    const char* type() const override {
        return "MovementCommand";
    }
    bool execute(float amount) override {
        if (amount < 0.1f && amount > -0.1f)
            amount = 0.0f;
        else if (amount > 0.5f)
            amount = 1.0f;
        else if (amount < -0.5f)
            amount = -1.0f;
        else if (amount > 0.0f)
            amount = 0.5f;
        else
            amount = -0.5f;
        return InputCommand::execute(amount);
    }
};

class ShiftCommand : public GameLib::InputCommand {
public:
    const char* type() const override {
        return "ShiftCommand";
    }

    bool execute(float amount) override {
        if (amount < 0.1f && amount > -0.1f) {
            amount = 0.0f;
            buttonDown = false;
        }
        else if (buttonDown == false) {
            if (amount > 0.0f)
                amount = 1.0f;
            else
            amount = -1.0f;

            buttonDown = true;
        }
        return InputCommand::execute(amount);
    }

private:
    boolean buttonDown = false;
};

int main() {
    GameLib::Context context(1280, 720, GameLib::WindowDefault);
    GameLib::Audio audio;
    GameLib::InputHandler input;
    GameLib::Graphics graphics{ &context };

    QuitCommand quitCommand;
    MovementCommand yAxisCommand;
    MovementCommand xAxisCommand;

    input.back = &quitCommand;
    input.axis1Y = &yAxisCommand;
    input.axis1X = &xAxisCommand;

    GameLib::Locator::provide(&context);
    if (context.audioInitialized())
        GameLib::Locator::provide(&audio);
    GameLib::Locator::provide(&input);
    GameLib::Locator::provide(&graphics);
//    context.addSearchPath("./assets");
    context.addSearchPath("../assets");

    graphics.setTileSize(16, 16);
    int spriteCount = context.loadTileset(0, 16, 16, "GameJam01Tileset.png");

    if (!spriteCount) {
        HFLOGWARN("Tileset not found");
    }
    else {
        HFLOGDEBUG("Sprite count %i", spriteCount);
    }

    //spriteCount = context.loadTileset(1, 16, 16, "GameJam01Tileset.png");

    GameLib::World world;
    GameLib::Locator::provide(&world);

    //std::string worldPath = context.findSearchPath("world.txt");
    //if (!world.load(worldPath)) {
    //    HFLOGWARN("world.txt not found");
    //}
    for (float y = 0; y < graphics.getHeight(); y++) {
        int val = rand() % 30 + (-15);

        if (val % 2 == 0) {
            GameLib::Actor* Crate = new GameLib::Actor(
                nullptr, new GameLib::SimpleActorComponent(), new BoxCollisionComponent("environment"), new GameLib::SimpleGraphicsComponent());

            

            Crate->spriteLibId = 0;
            Crate->spriteId = 2;
            if (val > 0) {
                Crate->position.x = graphics.getCenterX() / (float)graphics.getTileSizeX() - 1;
                Crate->position.y = y;
            }
            else {
                Crate->position.x = graphics.getCenterX() / (float)graphics.getTileSizeX() + 1;
                Crate->position.y = y;
            }

            world.actors.push_back(Crate);
        }
        
        GameLib::Actor* wallLeft = new GameLib::Actor(
            nullptr, new GameLib::SimpleActorComponent(), new BoxCollisionComponent("environment"), new GameLib::SimpleGraphicsComponent());

        world.actors.push_back(wallLeft);
        wallLeft->position.x = graphics.getCenterX() / (float)graphics.getTileSizeX() - 2;
        wallLeft->position.y = y;
        wallLeft->spriteLibId = 0;
        wallLeft->spriteId = 1;



        GameLib::Actor* wallRight = new GameLib::Actor(
            nullptr, new GameLib::SimpleActorComponent(), new GameLib::SimplePhysicsComponent(), new GameLib::SimpleGraphicsComponent());

        world.actors.push_back(wallRight);
        wallRight->position.x = graphics.getCenterX() / (float)graphics.getTileSizeX() + 2;
        wallRight->position.y = y;
        wallRight->spriteLibId = 0;
        wallRight->spriteId = 1;


    }


    GameLib::Actor player(
        new RunnerInputComponent(), new RunnerActorComponent(), new BoxCollisionComponent("player"), new GameLib::SimpleGraphicsComponent());
    
    player.position.x = graphics.getCenterX() / (float)graphics.getTileSizeX();
    player.position.y = (graphics.getHeight() / (float)graphics.getTileSizeY()) - 1;
    player.spriteLibId = 0;
    player.spriteId = 4;
    const auto* name = "player";
    player.rename(name);
    //const char * ugh = player.name;
    HFLOGDEBUG(name);
    world.actors.push_back(&player);

    HFLOGDEBUG("Player position X %5.1f", player.position.x);
    HFLOGDEBUG("Player position Y %5.1f", player.position.y);

    GameLib::Actor enemy(
        nullptr, new MonsterActorComponent(), new BoxCollisionComponent("enemy"), new GameLib::SimpleGraphicsComponent());

    enemy.position.x = graphics.getCenterX() / (float)graphics.getTileSizeX();
    enemy.position.y = 1;
    enemy.spriteLibId = 0;
    enemy.spriteId = 3;
    
    HFLOGDEBUG("Enemy position X %5.1f", enemy.position.x);
    HFLOGDEBUG("Enemy position Y %5.1f", enemy.position.y);
    world.actors.push_back(&enemy);



    Hf::StopWatch stopwatch;
    double frames = 0;

    float t0 = stopwatch.Stop_sf();
    while (!context.quitRequested) {
        float t1 = stopwatch.Stop_sf();
        float dt = t1 - t0;
        t0 = t1;
        GameLib::Context::deltaTime = dt;
        GameLib::Context::currentTime_s = t1;
        GameLib::Context::currentTime_ms = t1 * 1000;

        context.getEvents();
        input.handle();

        context.clearScreen(GameLib::Black);
        for (float y = 0; y * graphics.getTileSizeY() < graphics.getHeight(); y++) {

            for (float x = 0; x < 3; x++) {
                GameLib::SPRITEINFO s;
                s.position = {
                graphics.getCenterX() + (x - 1) * graphics.getTileSizeY(),
                y * graphics.getTileSizeY()
                };
                //s.center = { 0.0f, 0.0f };
                //s.flipFlags = 0;

                context.drawTexture(s.position, 0, 0);
            }
        }

        world.update(dt, graphics);

        //minchofont.draw(0, 0, "Hello, world!", GameLib::Red, GameLib::Font::SHADOWED);
        //gothicfont.draw((int)graphics.getWidth(), 0, "Hello, world!", GameLib::Blue, GameLib::Font::HALIGN_RIGHT | GameLib::Font::SHADOWED);

        int x = (int)graphics.getCenterX();
        int y = (int)graphics.getCenterY();
        float s = GameLib::wave(t1, 1.0f);
        SDL_Color c = GameLib::MakeColorHI(7, 4, s, false);
        //minchofont72.draw(x, y, "GingerRun", c, GameLib::Font::SHADOWED | GameLib::Font::HALIGN_CENTER | GameLib::Font::VALIGN_CENTER);

        //minchofont.draw(0, (int)graphics.getHeight() - 2, "HP: 56", GameLib::Gold, GameLib::Font::VALIGN_BOTTOM | GameLib::Font::SHADOWED);

        context.swapBuffers();
        frames++;
        std::this_thread::yield();
    }
    return 0;
    // std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
