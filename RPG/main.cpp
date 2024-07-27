#include "raylib.h"
#include "raymath.h"
#include "character.h"
#include "Prop.h"
#include "enemy.h"
#include <string>

int main()
{
    int windowDim[2];
    windowDim[0] = 384;
    windowDim[1] = 384;
    InitWindow(windowDim[0], windowDim[1], "Mahesh's Window");

    Texture2D Map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 Map_pos{0.0, 0.0};
    float mapscale{4.0f};

    character knight(windowDim[0], windowDim[1]);

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png")};

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png")};

    Enemy *enemies[]{
        &goblin,
        &slime};

    for (auto enemy : enemies)
    {
        enemy->setTarget(&knight);
    }

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Map_pos = Vector2Scale(knight.getworldpos(), -1.f);
        // draw map
        DrawTextureEx(Map, Map_pos, 0.0, mapscale, WHITE);

        // draw props
        for (auto prop : props)
        {
            prop.render(knight.getworldpos());
        }

        if (!knight.getAlive())
        {
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        }

        else
        {
            std ::string knightHealth = "Health : ";
            knightHealth.append(std::to_string(knight.getHealth()), 0, 5);
            DrawText(knightHealth.c_str(), knight.getscreenpos().x, knight.getscreenpos().y, 10.f, RED);
        }

        knight.tick(GetFrameTime());
        // check map bounds
        if (knight.getworldpos().x < 0.f ||
            knight.getworldpos().y < 0.f ||
            knight.getworldpos().x + windowDim[0] > Map.width * mapscale ||
            knight.getworldpos().y + windowDim[1] > Map.height * mapscale)
        {
            knight.undoMovement();
        }

        // check prop collision
        for (auto prop : props)
        {
            if (CheckCollisionRecs(prop.getcollisionrec(knight.getworldpos()), knight.getcollisionRec()))
            {
                knight.undoMovement();
            }
        }

        // enemies
        for (auto enemy : enemies)
        {
            enemy->tick(GetFrameTime());
        }

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            for (auto enemy : enemies)
            {
                if (CheckCollisionRecs(enemy->getcollisionRec(), knight.getweaponcollisionRec()))
                {
                    enemy->setAlive(false);
                }
            }
        }

        EndDrawing();
    }
    UnloadTexture(Map);
    CloseWindow();
}
