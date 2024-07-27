#include "baseCharacter.h"
#include "raymath.h"

BaseCharacter ::BaseCharacter()
{

}

void BaseCharacter::undoMovement()
{
    worldpos = worldposlastframe;
}

Rectangle BaseCharacter:: getcollisionRec()
{
    return Rectangle{
        getscreenpos().x,
        getscreenpos().y,
        width*scale,
        height*scale
    };
}

void BaseCharacter :: tick(float deltaTime)
{
    worldposlastframe = worldpos;
    // update animation frame
    runningtime += deltaTime;
    if (runningtime >= updatetime)
    {
        frame++;
        runningtime = 0.f;
        if (frame > maxframes)
            frame = 0;
    }

    if (Vector2Length(velocity) != 0.0)
    {
        worldpos = Vector2Add(worldpos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? rightleft = -1.f : rightleft = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    velocity = {};

    // draw chracter
    Rectangle source{frame * width, 0.f, rightleft * width, height};
    Rectangle dest{getscreenpos().x, getscreenpos().y, scale * width, scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
};