#include "raylib.h"
#include "game.h"


int main()
{
    // window initialization
    InitWindow(800, 600, "Pong Game");
    SetWindowState(FLAG_VSYNC_HINT);

    // game objects initialization
    Ball ball;
    InitBall(&ball, GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, 8.0f, 300.0f, 300.0f);

    Paddle leftPaddle, rightPaddle;
    InitPaddle(&leftPaddle, 10.0f, GetScreenHeight() / 2.0 - 50.0f, 10.0f, 100.0f, 10.0f);
    InitPaddle(&rightPaddle, GetScreenWidth() - 20.0f, GetScreenHeight() / 2.0 - 50.0f, 10.0f, 100.0f, 10.0f);

    const char* winnerText = NULL;

    // main loop
    while (!WindowShouldClose())
    {
        // ball moving
        MoveBall(&ball);

        // ball reflecting from paddles
        if (CheckCollisionCircleRec(GetBallCenter(&ball), ball.radius, GetPaddleRectangle(&leftPaddle)))
        {
            if (ball.speedX < 0.0f)
            {
                ball.speedX *= -1.05f;
                ball.speedY = (ball.y - leftPaddle.y) / (leftPaddle.height / 2.0f) * ball.speedX;
            }
        }

        if (CheckCollisionCircleRec(GetBallCenter(&ball), ball.radius, GetPaddleRectangle(&rightPaddle)))
        {
            if (ball.speedX > 0.0f)
            {
                ball.speedX *= -1.05f;
                ball.speedY = (ball.y - rightPaddle.y) / (rightPaddle.height / 2.0f) * -ball.speedX;
            }
        }

        // process key events
        if (IsKeyDown(KEY_W))
        {
            leftPaddle.y -= leftPaddle.speed;
        }
        if (IsKeyDown(KEY_S))
        {
            leftPaddle.y += leftPaddle.speed;
        }
        if (IsKeyDown(KEY_UP))
        {
            rightPaddle.y -= rightPaddle.speed;
        }
        if (IsKeyDown(KEY_DOWN))
        {
            rightPaddle.y += rightPaddle.speed;
        }
        
        // game over and restart 
        if (ball.x < 0.0f - ball.radius)
        {
            winnerText = "Right Player Wins!";
            ball.speedX = ball.speedY = 0.0f;
        }
        else if (ball.x > GetScreenWidth() + ball.radius)
        {
            winnerText = "Left Player Wins!";
            ball.speedX = ball.speedY = 0.0f;
        }
        if (winnerText && IsKeyPressed(KEY_SPACE))
        {
            InitBall(&ball, GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f, 8.0f, 300.0f, 300.0f);
            winnerText = NULL;
        }

        // drawing frame
        BeginDrawing();
        {
            ClearBackground(BLACK);

            DrawBall(&ball);
            DrawPaddle(&leftPaddle);
            DrawPaddle(&rightPaddle);

            if (winnerText)
            {
                int textWidth = MeasureText(winnerText, 60);
                DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 30, 60, YELLOW);
            }

            DrawFPS(10, 10);
        }
        EndDrawing();
    }


    CloseWindow();

    return 0;
}