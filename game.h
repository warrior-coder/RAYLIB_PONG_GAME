#ifndef _GAME_H_
#define _GAME_H_

// define game objects
typedef struct _Ball
{
    float x, y;
    float radius;
    float speedX, speedY;
}Ball;

typedef struct _Paddle
{
    float x, y;
    float speed;
    float width, height;

}Paddle;

// game logic function
void InitBall(Ball* ball, float x, float y, float radius, float speedX, float speedY)
{
    ball->x = x;
    ball->y = y;
    ball->radius = radius;
    ball->speedX = speedX;
    ball->speedY = speedY;
}

void DrawBall(Ball* ball)
{
    DrawCircle(ball->x, ball->y, ball->radius, WHITE);
}

Vector2 GetBallCenter(Ball* ball)
{
    Vector2 center = { ball->x, ball->y };

    return center;
}

void MoveBall(Ball* ball)
{
    ball->x += ball->speedX * GetFrameTime();
    ball->y += ball->speedY * GetFrameTime();

    if (ball->y < 0.0f + ball->radius)
    {
        ball->y = 0.0f + ball->radius;
        ball->speedY *= -1.0f;
    }
    else if (ball->y > GetScreenHeight() - ball->radius)
    {
        ball->y = GetScreenHeight() - ball->radius;
        ball->speedY *= -1.0f;
    }
}

void DrawPaddle(Paddle* paddle)
{
    DrawRectangle(paddle->x, paddle->y, paddle->width, paddle->height, WHITE);
}

void InitPaddle(Paddle* paddle, float x, float y, float widht, float height, float speed)
{
    paddle->x = x;
    paddle->y = y;
    paddle->width = widht;
    paddle->height = height;
    paddle->speed = speed;
}

Rectangle GetPaddleRectangle(Paddle* paddle)
{
    Rectangle rectangle = { paddle->x, paddle->y, paddle->width, paddle->height };

    return rectangle;
}


#endif // _GAME_H_ 