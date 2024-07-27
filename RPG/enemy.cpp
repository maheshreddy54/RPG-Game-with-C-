#include "enemy.h"
#include "raymath.h"

Enemy :: Enemy(Vector2 pos, Texture2D idle_tex, Texture2D run_tex)
{
    worldpos = pos;
    texture = idle_tex;
    idle = idle_tex;
    run = run_tex;
    width = texture.width / maxframes;
    height = texture.height;
    speed = 3.5f;
}

void Enemy:: tick(float deltaTime)
{
   //find vector enemy to character
   if (!getAlive()){ return;};
   velocity = Vector2Subtract(target -> getscreenpos(), getscreenpos()); 
   if (Vector2Length(velocity)< radius) velocity = {};
   BaseCharacter :: tick(deltaTime);
   if ( CheckCollisionRecs(target->getcollisionRec(), getcollisionRec()))
   {
        target->takeDamage(damagePersec*deltaTime);
   }
} 

Vector2 Enemy :: getscreenpos()
{
    return Vector2Subtract(worldpos, target -> getworldpos());
}