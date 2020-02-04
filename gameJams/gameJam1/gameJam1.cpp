// kimGameJam01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <gamelib.hpp>
#include "RunnerInputComponent.hpp"
#pragma comment(lib, "gamelib.lib")

int main() {
    GameLib::Context context(1280, 720, GameLib::WindowDefault);
    GameLib::Audio audio;
    GameLib::InputHandler input;
    GameLib::Graphics graphics{ &context };

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

    GameLib::Actor player(
        new RunnerInputComponent(), new GameLib::SimpleActorComponent(), new GameLib::SimplePhysicsComponent(), new GameLib::SimpleGraphicsComponent());
    
    player.position.x = graphics.getCenterX() / (float)graphics.getTileSizeX();
    player.position.y = graphics.getCenterY() / (float)graphics.getTileSizeY();
    player.spriteLibId = 0;
    player.spriteId = 4;
    world.actors.push_back(&player);

    HFLOGDEBUG("Player position X %5.1f", player.position.x);
    HFLOGDEBUG("Player position Y %5.1f", player.position.y);

    GameLib::Actor enemy(
        nullptr, new GameLib::SimpleActorComponent(), new GameLib::SimplePhysicsComponent(), new GameLib::SimpleGraphicsComponent());

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

        // for (unsigned x = 0; x < world.worldSizeX; x++) {
        //    for (unsigned y = 0; y < world.worldSizeY; y++) {
        //        GameLib::SPRITEINFO s;
        //        s.position = { x * 32, y * 32 };
        //        auto t = world.getTile(x, y);
        //        context.drawTexture(s.position, 0, t.charDesc);
        //    }
        //}

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
