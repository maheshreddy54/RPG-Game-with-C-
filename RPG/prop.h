#include "raylib.h"

class Prop
{
    public:
        Prop(Vector2 pos, Texture2D tex);
        void render(Vector2 knightpos);
        Rectangle getcollisionrec(Vector2 knightpos);

    private:
        Vector2 worldpos{};
        Texture2D texture{};
        float scale{4.f};

};