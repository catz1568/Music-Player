#include <raylib.h>
#include <chrono>
#include <thread>
#include <iostream>

#define MAX_SONGS 25

using namespace std::chrono_literals;


struct musicobject {
    Rectangle source;
    Rectangle bounds;
    Vector2 position;
    Color color;
};
int main(void) 
{
    //SetConfigFlags(FLAG_FULLSCREEN_MODE);
    const int ScreenWIDTH = 1280;
    const int ScreenHEIGHT = 720;
    bool pause = false;
    int currentIndex = 0;
    Music music[MAX_SONGS] = { 0 };

    InitWindow(ScreenWIDTH, ScreenHEIGHT, "Music Player");
    InitAudioDevice();
    
    FilePathList files = LoadDirectoryFiles("C:/Users/cat/Documents/Music_test");
    std::cout << files.count << "\n";
   
    if (files.count == 0) {
        std::cout << "Could not open folder or no files detected" << "\n";
        return 1;
    }
    for (int i = 0; i < files.count; i++) {
        music[i] = LoadMusicStream(files.paths[i]);
    }
    PlayMusicStream(music[currentIndex]);

    // Play Button
    Image Play_Button = LoadImage("Resources/Play.png");
    ImageResizeNN(&Play_Button, 500, 250);
    Texture2D play_texture = LoadTextureFromImage(Play_Button);
    musicobject Play = {
        .source = { 0.0f, 0.0f, (float) play_texture.width, (float) play_texture.height },
        .bounds = { ScreenWIDTH / 2 - 250, ScreenHEIGHT / 2, (float) play_texture.width, (float) play_texture.height},
        .position = { ScreenWIDTH / 2 - 250, ScreenHEIGHT / 2 },
        .color = WHITE,
    };
    Vector2 mousePos = { 0.0f, 0.0f };

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateMusicStream(music[currentIndex]);
        mousePos = GetMousePosition();
        if (GetMusicTimeLength(music[currentIndex]) == GetMusicTimePlayed(music[currentIndex]) || IsKeyDown(KEY_RIGHT)) {
            StopMusicStream(music[currentIndex]);

            if (currentIndex >= files.count-1) { 
                currentIndex = 0; 
            } else {
                ++currentIndex;
            }
            std::cout << currentIndex << "\n";
            PlayMusicStream(music[currentIndex]);
            std::this_thread::sleep_for(0.5s);
        }
        if (CheckCollisionPointRec(mousePos, Play.bounds)) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                pause = !pause; 
                if (pause) PauseMusicStream(music[currentIndex]);
                else ResumeMusicStream(music[currentIndex]);
                std::this_thread::sleep_for(0.2s);
            }
        }
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawTextureRec(play_texture, Play.source, (Vector2){Play.bounds.x, Play.bounds.y}, WHITE);
        DrawTextEx(GetFontDefault(), TextFormat("%.2f", GetMusicTimePlayed(music[currentIndex])), (Vector2){ ScreenWIDTH / 2 - 400, ScreenHEIGHT / 2 - 300}, 15, 25, WHITE);
        DrawTextEx(GetFontDefault(), TextFormat("%.2f", GetMusicTimeLength(music[currentIndex])), (Vector2){ ScreenWIDTH / 2 + 500, ScreenHEIGHT / 2 - 300}, 15, 25, WHITE);

        //DrawTextEx(GetFontDefault(), TextFormat("%i %i", GetMouseX(), GetMouseY()), (Vector2){100, 100}, 20, 10, WHITE);
        EndDrawing();
    }
    CloseWindow();
    for (int i = 0; i < files.count; i++) {
        UnloadMusicStream(music[i]);
    }
    CloseAudioDevice();
}