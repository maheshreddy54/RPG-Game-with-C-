#include "prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex): 
    worldpos(pos),
    texture(tex)
{

}

void Prop::render(Vector2 knightpos)
{
    Vector2 screenpos{ Vector2Subtract(worldpos, knightpos)};
    DrawTextureEx(texture, screenpos, 0.f, scale, WHITE);
}

Rectangle Prop::getcollisionrec(Vector2 knightpos){
    Vector2 screenpos{ Vector2Subtract(worldpos, knightpos)};
    return Rectangle{
        screenpos.x,
        screenpos.y,
        texture.width*scale,
        texture.height*scale
    };
}