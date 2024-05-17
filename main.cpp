#include "raylib.h"

int main()
{
    int size = 900;
    SetTargetFPS(120);
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_TOPMOST |
                   FLAG_WINDOW_UNDECORATED | FLAG_WINDOW_TRANSPARENT);
    InitWindow(size, size, "Window");

    Image image = LoadImage("image.png");
    Texture texture = LoadTextureFromImage(image);
    SetTextureFilter(texture, TEXTURE_FILTER_BILINEAR);
    UnloadImage(image);

    Shader shader = LoadShader(0, "shader.fs");
    unsigned int sizeLoc = GetShaderLocation(shader, "size");

    while (!WindowShouldClose())
    {
        size = GetScreenWidth();
        float scroll = GetMouseWheelMoveV().y;
        size *= scroll * 0.1f + 1;
        
        SetWindowSize(size, size);

        float fSize = (float)size;
        SetShaderValue(shader, sizeLoc, &fSize, SHADER_UNIFORM_FLOAT);

        float hScale = fSize / texture.width;
        float vScale = fSize / texture.height;
        float scale = hScale > vScale ? hScale : vScale;
        float hPad = 0.5f * (fSize - texture.width * scale);
        float vPad = 0.5f * (fSize - texture.height * scale);

        BeginDrawing();
        ClearBackground(BLANK);
        BeginShaderMode(shader);
        DrawTextureEx(texture, {hPad, vPad}, 0, scale, WHITE);
        EndShaderMode();
        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();
    return 0;
}