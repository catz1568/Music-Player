#include <raylib.h>
#include <iostream>
#define MAX_MUSIC 25


int main(void) 
{
    //SetConfigFlags(FLAG_FULLSCREEN_MODE);
    const int ScreenWIDTH = 1200;
    const int ScreenHEIGHT = 950;
    Sound music[MAX_MUSIC] = { 0 };

    InitWindow(ScreenWIDTH, ScreenHEIGHT, "Music Player");
    
    FilePathList files = LoadDirectoryFiles("C:/Users/cat/Documents/Music_test");
    for (int i = 0; i < files.count; i++) {
        music[i] = LoadSound(files.paths[i]);
    }
    // Play Button
    Image Play_Button = LoadImage("Resources/Play.png");
    ImageResizeNN(&Play_Button, 500, 250);
    Texture2D play_texture = LoadTextureFromImage(Play_Button);
    Rectangle framePlay = {  0.0f, 0.0f, (float) play_texture.width, (float) play_texture.height  };

    //SetWindowState(FLAG_WINDOW_UNDECORATED);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawTextureRec(play_texture, framePlay, (Vector2){300, 650}, GRAY);

        EndDrawing();
    }
    CloseWindow();
}