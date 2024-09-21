#include <GL/glut.h>
#include <iostream>

// Paddle settings
const float paddleWidth = 20.0f;
const float paddleHeight = 5.0f;
const float paddleSpeed = 2.5f; // Increased paddle speed for better movement

// Ball settings
float ballPosX = 0.0f, ballPosY = 0.0f;
float ballDirX = 0.4f, ballDirY = 0.4f; // Increased ball speed
const float ballSize = 5.0f;

// Paddle positions
float paddle1X = -50.0f;
float paddle2X = -50.0f;
const float paddleY1 = -90.0f; // Player 1 (Bottom paddle)
const float paddleY2 = 85.0f;  // Player 2 (Top paddle)

// Window size
const int windowWidth = 800;
const int windowHeight = 600;

void drawRectangle(float x, float y, float width, float height)
{
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

// Function to draw the ball
void drawBall()
{
    glColor3f(1.0f, 0.0f, 0.0f); // Red ball
    drawRectangle(ballPosX, ballPosY, ballSize, ballSize);
}

// Function to draw paddles
void drawPaddles()
{
    // Paddle 1 (Bottom)
    glColor3f(0.0f, 0.0f, 1.0f); // Blue paddle
    drawRectangle(paddle1X, paddleY1, paddleWidth, paddleHeight);

    // Paddle 2 (Top)
    glColor3f(0.0f, 1.0f, 0.0f); // Green paddle
    drawRectangle(paddle2X, paddleY2, paddleWidth, paddleHeight);
}

// Function to handle ball movement and collisions
void updateBall()
{
    ballPosX += ballDirX;
    ballPosY += ballDirY;

    // Ball collision with walls (left and right)
    if (ballPosX <= -100 || ballPosX + ballSize >= 100)
        ballDirX = -ballDirX;

    // Ball collision with paddles
    if (ballPosY <= paddleY1 + paddleHeight && ballPosY >= paddleY1 &&
        ballPosX + ballSize >= paddle1X && ballPosX <= paddle1X + paddleWidth)
    {
        ballDirY = -ballDirY; // Bounce off paddle 1
    }

    if (ballPosY + ballSize >= paddleY2 && ballPosY <= paddleY2 + paddleHeight &&
        ballPosX + ballSize >= paddle2X && ballPosX <= paddle2X + paddleWidth)
    {
        ballDirY = -ballDirY; // Bounce off paddle 2
    }

    // Ball goes beyond paddles (missed by players)
    if (ballPosY < -100 || ballPosY > 100)
    {
        // Reset ball position
        ballPosX = 0.0f;
        ballPosY = 0.0f;
        ballDirY = -ballDirY; // Reverse direction
    }
}

// Function to render the game
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw paddles and ball
    drawPaddles();
    drawBall();

    glFlush();
}

// Function to handle paddle movement (Player 1: 'A', 'D', Player 2: Arrow Left, Arrow Right)
void handleKeypress(unsigned char key, int x, int y)
{
    // Player 1 (A and D keys)
    if (key == 'a' || key == 'A')
    {
        if (paddle1X > -100)
            paddle1X -= paddleSpeed; // Move left
    }
    else if (key == 'd' || key == 'D')
    {
        if (paddle1X + paddleWidth < 100)
            paddle1X += paddleSpeed; // Move right
    }

    glutPostRedisplay();
}

void handleSpecialKeypress(int key, int x, int y)
{
    // Player 2 (Left and Right arrow keys)
    if (key == GLUT_KEY_LEFT)
    {
        if (paddle2X > -100)
            paddle2X -= paddleSpeed; // Move left
    }
    else if (key == GLUT_KEY_RIGHT)
    {
        if (paddle2X + paddleWidth < 100)
            paddle2X += paddleSpeed; // Move right
    }

    glutPostRedisplay();
}

// Function to update game (ball movement)
void timer(int value)
{
    updateBall();
    glutPostRedisplay();         // Redraw the screen
    glutTimerFunc(16, timer, 0); // Approx. 60 FPS
}

// Initialize OpenGL settings
void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100, 100, -100, 100, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Two Player Tennis Game");

    glClearColor(0.0, 0.0, 0.0, 0.0); // Black background
    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);             // Set up the timer for ball movement
    glutKeyboardFunc(handleKeypress);       // Keyboard input for Player 1
    glutSpecialFunc(handleSpecialKeypress); // Special keys input for Player 2 (Arrow keys)

    glutMainLoop();
    return 0;
}
