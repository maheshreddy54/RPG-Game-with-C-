#include "raylib.h"

#ifndef BASE_CHARACTER_H
#define BASE_CHARACTER_H

class BaseCharacter
{
    public:
    BaseCharacter();
    Vector2 getworldpos() { return worldpos; }
    void undoMovement();
    Rectangle getcollisionRec();
    virtual void tick(float deltaTime);
    virtual Vector2 getscreenpos() = 0;
    bool getAlive() { return alive;};
    void setAlive(bool isAlive){ alive = isAlive;};

    protected:
    Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
    Vector2 worldpos{};
    float runningtime{};
    int frame{};
    int maxframes{6};
    float updatetime{1.0 / 12.0};
    float speed{4.f};
    float rightleft{};
    float width{};
    float height{};
    Vector2 worldposlastframe{};
    float scale{4.0f};
    Vector2 velocity{};

    private:
    bool alive{true};

};

#endif