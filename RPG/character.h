#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "baseCharacter.h"

class character : public BaseCharacter
{
public:
    character(int winWidth, int winHeight);
    virtual void tick(float deltaTime) override;
    virtual Vector2 getscreenpos() override;
    Rectangle getweaponcollisionRec(){return weaponcollisionrec;};
    float getHealth() const {return health;};
    void takeDamage(float damage);
private:
    int windowwidth{};
    int windowheight{};
    Texture2D weapon{LoadTexture("character/weapon_sword.png")};
    Rectangle weaponcollisionrec{};
    float health{100.f};
 
};

#endif