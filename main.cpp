#include <raylib.h>
#define MAX_MUSIC 25


Color TRANSPARENT_GRAY = { 42, 43, 43, 255 };

int main(void) 
{
    //SetConfigFlags(FLAG_FULLSCREEN_MODE);
    const int ScreenWIDTH = 1280;
    const int ScreenHEIGHT = 720;
    bool music_state;
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
    Vector2 mousePos = { 0.0f, 0.0f };

    //SetWindowState(FLAG_WINDOW_UNDECORATED);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        /*
        mousePos = GetMousePosition();
        if (CheckCollisionPointRec(mousePos, framePlay)) {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                music_state = true;
            }
        }
        if (music_state) {
            PlaySound(music[0]);
        }
        */
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawTextureRec(play_texture, framePlay, (Vector2){ScreenWIDTH / 2 - 250, ScreenHEIGHT / 2 + 100}, WHITE);

        // Temp
        DrawTextEx(GetFontDefault(), TextFormat("%i %i", GetMouseX(), GetMouseY()), (Vector2){100, 100}, 25, 10, WHITE);


        EndDrawing();
    }
    CloseWindow();
}