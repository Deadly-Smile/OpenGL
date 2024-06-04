#include <GL/glut.h>

void drawPixel(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void drawLine(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float m = dy / dx;
    float mP = abs(m);

    float xIncrement = 0;
    float yIncrement = 0;

    if (dx == 0)
    {
        yIncrement += 1;
    }
    else if (m >= 0 && m <= 1 && dx >= 0 && dy >= 0)
    {
        xIncrement = 1;
        yIncrement = mP;
    }
    else if (m >= 0 && m <= 1 && dx < 0 && dy < 0)
    {
        xIncrement = -1;
        yIncrement = -mP;
    }
    else if (m >= -1 && m < 0 && dx > 0 && dy < 0)
    {
        xIncrement = 1;
        yIncrement = -mP;
    }
    else if (m >= -1 && m < 0 && dx < 0 && dy > 0)
    {
        xIncrement = -1;
        yIncrement = mP;
    }
    else if (m > 1 && dx > 0 && dy > 0)
    {
        xIncrement = 1 / mP;
        yIncrement = 1;
    }
    else if (m > 1 && dx < 0 && dy < 0)
    {
        xIncrement = -(1 / mP);
        yIncrement = -1;
    }
    else if (m < -1 && dx > 0 && dy < 0)
    {
        xIncrement = 1 / mP;
        yIncrement = -1;
    }
    else if (m < -1 && dx < 0 && dy > 0)
    {
        xIncrement = -(1 / mP);
        yIncrement = 1;
    }

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++)
    {
        drawPixel(x, y);
        x += xIncrement;
        y += yIncrement;
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 1.0);

    drawLine(122, 100, 2, 200);

    glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 500.0, 0.0, 500.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Line Drawing");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}