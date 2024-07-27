#include "character.h"
#include "raymath.h"

character ::character(int winWidth, int winHeight) : windowwidth(winWidth), windowheight(winHeight)
{
    width = texture.width / maxframes;
    height = texture.height;
}

Vector2 character ::getscreenpos()
{
    return Vector2{
        (float)windowwidth / 2.0f - scale * (0.5f * width),
        (float)windowheight / 2.0f - scale * (0.5f * height)};
};

void character::tick(float deltaTime)
{
    if (!getAlive()){ return;};
    
    if (IsKeyDown(KEY_A))
        velocity.x -= 1.0;
    if (IsKeyDown(KEY_D))
        velocity.x += 1.0;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))
        velocity.y += 1.0;

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset{};
    float rotaion{};
    if (rightleft > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weaponcollisionrec = {
            getscreenpos().x + offset.x ,
            getscreenpos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};
        rotaion = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weaponcollisionrec = {
            getscreenpos().x + offset.x - weapon.width * scale,
            getscreenpos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};
        rotaion = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;
    }

    // draw the sword
    Rectangle source{0.f, 0.f, static_cast<float>(weapon.width) * rightleft, static_cast<float>(weapon.height)};
    Rectangle dest{getscreenpos().x + offset.x, getscreenpos().y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, source, dest, origin, rotaion, WHITE);
    DrawRectangleLines(
        weaponcollisionrec.x,
        weaponcollisionrec.y,
        weaponcollisionrec.width,
        weaponcollisionrec.height,
        RED);
}

void character :: takeDamage(float damage)
{
    health -= damage;
    if (health <=0.f){
        setAlive(false);
    }

}
