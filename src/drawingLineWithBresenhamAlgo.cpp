#include <GL/glut.h>
#include <iostream>

void drawPixel(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void drawLine(float x1, float y1, float x2, float y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int dx1 = x2 - x1;
    int dy1 = y2 - y1;

    std::cout << x1 << " " << y1 << " ";

    int x{0}, y{0}, xEnd{0}, yEnd{0}, xIncrement{0}, yIncrement{0};
    float m = abs(dy / dx);

    if (m < 1)
    {
        int p = 2 * dy - dx;
        int twoDy = 2 * dy;
        int twoDyDx = 2 * (dy - dx);
        yIncrement = 1;
        if (dx1 < 0 && dy1 < 0)
        {
            dy1 = 1;
            dx1 = 1;
        }
        if (dx1 < 0 || dy1 < 0)
        {
            yIncrement = -1;
        }
        if (x1 > x2)
        {
            x = x2;
            y = y2;
            xEnd = x1;
        }
        else
        {
            x = x1;
            y = y1;
            xEnd = x2;
        }
        drawPixel(x, y);
        while (x < xEnd)
        {
            x++;
            if (p < 0)
            {
                p += twoDy;
            }
            else
            {
                y += yIncrement;
                p += twoDyDx;
            }
            drawPixel(x, y);
        }
    }
    else
    {
        int p = 2 * dx - dy;
        int twoDx = 2 * dx;
        int twoDxDy = 2 * (dx - dy);
        xIncrement = 1;
        if (dx1 < 0 && dy1 < 0)
        {
            dy1 = 1;
            dx1 = 1;
        }
        if (dx1 < 0 || dy1 < 0)
        {
            xIncrement = -1;
        }
        if (y1 > y2)
        {
            x = x2;
            y = y2;
            yEnd = y1;
        }
        else
        {
            x = x1;
            y = y1;
            yEnd = y2;
        }
        drawPixel(x, y);
        while (y < yEnd)
        {
            y++;
            if (p < 0)
            {
                p += twoDx;
            }
            else
            {
                x += xIncrement;
                p += twoDxDy;
            }
            drawPixel(x, y);
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 1.0);
    // glLineWidth(15.0);
    drawLine(20, 20, 90, 5);

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