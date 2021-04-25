#include "raylib.h"
#include "consts.h"
#include <stdbool.h>

struct Player {
    float x;
    float y;
    int width;
    int height;
    bool isStop;
};
struct GameState {
    int x;
    int y;
    int clicks;
};


void InitGame(Camera2D *camera, struct Player *player) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ducks");
    camera->target = (Vector2) {player->x + 30.0f, player->y + 30.0f};
    camera->offset = (Vector2) {(float) SCREEN_WIDTH / 2.0f, (float) SCREEN_HEIGHT / 2.0f};
    camera->rotation = 0.0f;
    camera->zoom = 1.0f;

    SetTargetFPS(20);
}

bool ChampionMovement(struct Player *champion, struct GameState *state) {
    Vector2 mousePos = GetMousePosition();
    if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) && (champion->y > 100)) {
        if ((mousePos.x + state->x > champion->x + champion->width / 2) ||
            ((mousePos.x < champion->x - champion->width / 2))) {
            return false;
        }
        if ((mousePos.y + state->y > champion->y - champion->height)) {
            return false;
        }

        state->y -= 100;
        champion->y -= 100;
        state->clicks++;
        champion->isStop = false;
        return true;
    }
    if ((!champion->isStop)) {
        champion->y += GRAVITY;
        state->y += GRAVITY;
    }
    if ((champion->y > 5970)) {
        champion->isStop = true;
        return false;
    }
    return false;
}


void DrawHelpMap(struct GameState *state) {
    DrawRectangle(10, 10, 260, 150, Fade(SKYBLUE, 0.5f)); //map area
    DrawText("* Get out of the hole!", 20, 20, 20, BLACK);
    DrawText("* Click on the duck", 20, 40, 20, BLACK);
    DrawText("* R - Restart", 20, 60, 20, BLACK);
    DrawText("* R - Restart", 20, 60, 20, BLACK);
    DrawText(TextFormat("Your Clicks: %d", state->clicks), 20, 100, 30, BLACK);
}


int main(void) {
    Camera2D camera = {0};
    struct Player champion = {(float) SCREEN_WIDTH / 2, (float) SCREEN_HEIGHT - 300,
                              100, 100, false};
    struct GameState state = {false, 0, 0};
    InitGame(&camera, &champion);
    Image championTexture = LoadImage("../assets/duck.png");
    Texture2D championImg = LoadTextureFromImage(championTexture);
    DrawText("* Get out of the hole!", 20, 20, 20, BLACK);

    UnloadImage(championTexture);
    InitAudioDevice();
    Sound fxWav = LoadSound("../assets/background.wav");
    Sound krya = LoadSound("../assets/krya.wav");

    PlaySound(fxWav);
    Texture2D background = LoadTexture("../assets/background.png");

    champion.y += 4000;
    while (!WindowShouldClose()) {
        camera.target = (Vector2) {champion.x + 20, champion.y + 20};
        bool isMovement = ChampionMovement(&champion, &state);
        if (isMovement) {
            PlaySound(krya);
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode2D(camera);
        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(championImg, (int) champion.x - champion.width / 2, (int) champion.y - champion.height / 2, WHITE);

        if (IsKeyPressed(KEY_R)) {
            state.x = 0;
            state.clicks = 0;
            state.y = 0;
            champion.x = (float) SCREEN_WIDTH / 2;
            champion.y = 4000;
            champion.isStop = false;
        }

        EndMode2D();
        DrawHelpMap(&state);
        DrawRectangle(0, 0, SCREEN_WIDTH, 5, RED);
        DrawRectangle(0, 5, 5, SCREEN_HEIGHT - 10, RED);
        DrawRectangle(SCREEN_WIDTH - 5, 5, 5, SCREEN_HEIGHT - 10, RED);
        DrawRectangle(0, SCREEN_HEIGHT - 5, SCREEN_WIDTH, 5, RED);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    UnloadSound(fxWav);     // Unload sound data

    CloseAudioDevice();     // Close audio device

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}