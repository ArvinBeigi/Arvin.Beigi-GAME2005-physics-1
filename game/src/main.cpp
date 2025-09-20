/*
This project uses the Raylib framework to provide us functionality for math, graphics, GUI, input etc.
See documentation here: https://www.raylib.com/, and examples here: https://www.raylib.com/examples.html
*/

#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "game.h"

const unsigned int TARGET_FPS = 50; //frames/second
float dt = 1.0f / TARGET_FPS; //seconds/frame
float time = 0;
float x = 500;
float y = 500;
float frequency = 1;
float amplitude = 100;

// Lab variables
Vector2 launchPosition = { 400, 300 }; // Starting point
float launchAngle = 45.0f;             // Degrees
float launchSpeed = 200.0f;            // Pixels per second

// Helper: compute velocity from angle + speed
Vector2 GetLaunchVelocity(float angleDeg, float speed)
{
    float rad = angleDeg * DEG2RAD;
    return { cosf(rad) * speed, -sinf(rad) * speed }; // -sin so positive angle aims upward
}

//Changes world state
void update()
{
    dt = 1.0f / TARGET_FPS;
    time += dt;

    x = x + (-sin(time * frequency)) * frequency * amplitude * dt;
    y = y + (cos(time * frequency)) * frequency * amplitude * dt;
}

//Display world state
void draw()
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("Arvin Beigi 101447957", 10, float(GetScreenHeight() - 30), 20, LIGHTGRAY);

    // Existing GUI + visuals
    GuiSliderBar(Rectangle{ 10, 15, 1000, 20 }, "", TextFormat("%.2f", time), &time, 0, 240);
    DrawText(TextFormat("T: %6.2f", time), GetScreenWidth() - 140, 10, 30, LIGHTGRAY);

    DrawCircle(x, y, 70, RED);
    DrawCircle(500 + cos(time * frequency) * amplitude, 500 + sin(time * frequency) * amplitude, 70, GREEN);

    // --- Lab-specific controls and vector drawing ---
    GuiSliderBar({ 10, 60, 200, 20 }, "Angle", TextFormat("%.1f", launchAngle), &launchAngle, 0, 90);
    GuiSliderBar({ 10, 90, 200, 20 }, "Speed", TextFormat("%.1f", launchSpeed), &launchSpeed, 0, 400);

    Vector2 velocity = GetLaunchVelocity(launchAngle, launchSpeed);
    Vector2 endPoint = Vector2Add(launchPosition, Vector2Scale(velocity, 0.2f));

    DrawCircleV(launchPosition, 8, GREEN); // launch origin
    DrawLineV(launchPosition, endPoint, RED); // velocity vector

    DrawText(TextFormat("Angle: %.1f deg", launchAngle), 10, 120, 20, LIGHTGRAY);
    DrawText(TextFormat("Speed: %.1f", launchSpeed), 10, 145, 20, LIGHTGRAY);
    DrawText(TextFormat("Velocity: (%.1f, %.1f)", velocity.x, velocity.y), 10, 170, 20, LIGHTGRAY);

    EndDrawing();
}

int main()
{
    InitWindow(InitialWidth, InitialHeight, "GAME2005 Arvin Beigi 101447957");
    SetTargetFPS(TARGET_FPS);

    while (!WindowShouldClose()) // Loops TARGET_FPS times per second
    {
        update();
        draw();
    }

    CloseWindow();
    return 0;
}
