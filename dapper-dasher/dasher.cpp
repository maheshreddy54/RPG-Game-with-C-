#include "raylib.h"

struct Animdata
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

//ground check func
bool isOnGround(Animdata data, int height)
{
    return data.pos.y>=height - data.rec.height;
}

//update animation frame
Animdata updateanimdata(Animdata Data, float dt, bool gndcheck, int maxframe)
{
    Data.runningTime+=dt;
    if (Data.runningTime>=Data.updateTime && !gndcheck)
        {
            Data.runningTime = 0.0;
            Data.rec.x = Data.frame * Data.rec.width;
            Data.frame++;
            if (Data.frame>maxframe)
            {
                Data.frame = 0;
            }     
        }

    return Data;
}

//draw backgrounds



int main()
{
    int windowDim[2];
    windowDim[0] = 512;
    windowDim[1] = 380;
    InitWindow(windowDim[0], windowDim[1], "Mahesh's Window");

    int velocity{0};
    const int gravity{1000};//px/s/s

    //scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Animdata scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowDim[0]/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowDim[1]/2 - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.runningTime = 0;
    scarfyData.updateTime = 1.0/12.0;

    //animdata for nebula
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    int nebsize =2;

    Animdata nebulae[nebsize]{};

    int adddist = 300;

    for (int i=0; i<nebsize; i++)
    {
        nebulae[i].rec.x =0.0;
        nebulae[i].rec.y=0.0;
        nebulae[i].rec.width=nebula.width/8;
        nebulae[i].rec.height=nebula.height/8;
        nebulae[i].pos.y = windowDim[1]-nebulae[i].rec.height;
        nebulae[i].frame =0;
        nebulae[i].runningTime=0.0;
        nebulae[i].updateTime = 1.0/16.0; 
        nebulae[i].pos.x = windowDim[0] + adddist;
        adddist+=400;
    };

    float finishline{nebulae[nebsize - 1].pos.x};

    int nebvel{-200};
    
    bool isInAir{};
    //jump velocity
    int jumpVel = -600;

    //load backgrounds
    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX{};
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX{};
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX{};

    bool collision{};

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        const float dt{GetFrameTime()};
        //start drawing
        BeginDrawing();
        ClearBackground(WHITE);
        bgX-=20*dt;
        if (bgX<= -background.width*2)
        {
            bgX = 0.0;
        }
        mgX-=40*dt;
        if (mgX<= -midground.width*2)
        {
            mgX = 0.0;
        }
        fgX-=80*dt;
        if (fgX<= -foreground.width*2)
        {
            fgX = 0.0;
        }

        //draw background
        Vector2 bgPos{bgX, 0.0};
        DrawTextureEx(background, bgPos, 0.0, 2.0, WHITE);
        Vector2 bg2Pos{bgX + background.width*2, 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);
        //midground
        Vector2 mgPos{mgX, 0.0};
        DrawTextureEx(midground, mgPos, 0.0, 2.0, WHITE);
        Vector2 mg2Pos{mgX + midground.width*2, 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);
        //foreground
        Vector2 fgPos{fgX, 0.0};
        DrawTextureEx(foreground, fgPos, 0.0, 2.0, WHITE);
        Vector2 fg2Pos{fgX + foreground.width*2, 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);
        
        //perform ground check
        if (isOnGround(scarfyData, windowDim[1]))
        {
            velocity = 0;
            isInAir = false;
        }
        else
        {
            velocity+=gravity*dt;
            isInAir = true;
        }

        if (IsKeyPressed(KEY_SPACE)&& !isInAir)
        {
            velocity+=jumpVel;
        }

        //update nebula position
        for (int i = 0; i < nebsize; i++)
        {
            nebulae[i].pos.x+=nebvel*dt;
        }
        finishline+=nebvel*dt;

        //UPDATE POSTION   
        scarfyData.pos.y+=velocity*dt;

        //update scarfy animation data
        scarfyData = updateanimdata(scarfyData, dt, isInAir, 5);
        
        //update nebula animation
        for (int i=0;i<nebsize;i++)
        {
            nebulae[i] = updateanimdata(nebulae[i], dt, isInAir, 7);    
        }


        for (Animdata nebula : nebulae)
        {
            float pad{50};
            Rectangle nebRec{
                nebula.pos.x+pad,
                nebula.pos.y+pad,
                nebula.rec.width - 2*pad,
                nebula.rec.height - 2*pad
            };
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.rec.width,
                scarfyData.rec.height
            };
            if (CheckCollisionRecs(nebRec, scarfyRec))
            {
                collision = true;
            }
        }
        
        if (collision)
        {
            DrawText("Game Over!", windowDim[0]/4, windowDim[1]/2, 40, WHITE);
        }
        else if (scarfyData.pos.x>finishline)
        {
            DrawText("You Win!", windowDim[0]/4, windowDim[1]/2, 40, WHITE);
        }
        else
        {
            //Draw nebulae
            for (int i = 0; i < nebsize; i++)
            {
                DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, WHITE);
            }

            //Draw scarfy       
            DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);
        }
        
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
    
}