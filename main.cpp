#include <raylib.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <iostream>

#define MAX_SONGS 25

using namespace std::chrono_literals;

int main(void) 
{
    const int ScreenWIDTH = 1280;
    const int ScreenHEIGHT = 720;
    bool pause = false;
    float timePlayed = 0.0f;
    int currentIndex = 0;
    Music music[MAX_SONGS] = { 0 };
    FilePathList files = LoadDirectoryFiles("C:/Users/cat/Documents/Music_test");

    InitWindow(ScreenWIDTH, ScreenHEIGHT, "Music Player");
    InitAudioDevice();
    
    
   
    if (files.count == 0) {
        std::cout << "Could not open folder or no files detected" << "\n";
        return 1;
    }
    for (int i = 0; i < files.count; i++) {
        
        music[i] = LoadMusicStream(files.paths[i]);
        if (music[i].frameCount == 0) {
            std::cout << "[!] Another file extension detected\n";
            return 1;
        }
        
    }
    PlayMusicStream(music[currentIndex]);


    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        UpdateMusicStream(music[currentIndex]);
        if (IsKeyDown(KEY_RIGHT)) {
            StopMusicStream(music[currentIndex]);
            if (currentIndex >= files.count-1) { 
                currentIndex = 0; 
            } else {
                currentIndex++;
            }
            std::cout << currentIndex << "\n";
            PlayMusicStream(music[currentIndex]);
            std::this_thread::sleep_for(0.2s);
        }
        if (IsKeyDown(KEY_SPACE)) {
            pause = !pause; 
            if (pause) PauseMusicStream(music[currentIndex]);
            else ResumeMusicStream(music[currentIndex]);
            std::this_thread::sleep_for(0.2s);
        }
        timePlayed = GetMusicTimePlayed(music[currentIndex])/GetMusicTimeLength(music[currentIndex]);
        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangle(425, 360, 400, 12, WHITE);
        DrawRectangle(425, 360, (int)(timePlayed*400.0f), 12, GRAY);

        DrawTextEx(GetFontDefault(), TextFormat("%.0f", GetMusicTimePlayed(music[currentIndex])), (Vector2){ ScreenWIDTH / 2 - 270, ScreenHEIGHT / 2}, 15, 10, WHITE);
        DrawTextEx(GetFontDefault(), TextFormat("%.0f", GetMusicTimeLength(music[currentIndex])), (Vector2){ ScreenWIDTH / 2 + 200, ScreenHEIGHT / 2}, 15, 10, WHITE);
        DrawTextEx(GetFontDefault(), GetFileNameWithoutExt(files.paths[currentIndex]), (Vector2){ ScreenWIDTH / 2 - 100, 300}, 15, 10, WHITE);

        EndDrawing();
    }
    CloseWindow();
    for (int i = 0; i < files.count; i++) {
        UnloadMusicStream(music[i]);
    }
    CloseAudioDevice();
    UnloadDirectoryFiles(files);
}