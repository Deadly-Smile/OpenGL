#include <GL/glut.h>
#include <iostream>
void drawPixel(float x, float y)
{
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}
void drawLine(float x1, float y1, float x2, float y2, bool bresenham = false, bool slopeBased = false)
{
    if (bresenham)
    {
        int dx = abs(x2 - x1), dy = abs(y2 - y1);
        int x = x1, y = y1, xEnd = x2, p = 2 * dy - dx;
        int twoDy = 2 * dy, twoDyDx = 2 * (dy - dx);
        int xIncrement = (x1 < x2) ? 1 : -1, yIncrement = (y1 < y2) ? 1 : -1;
        drawPixel(x, y);
        if (dx > dy)
        {
            while (x != xEnd)
            {
                x += xIncrement;
                p < 0 ? p += twoDy : (y += yIncrement, p += twoDyDx);
                drawPixel(x, y);
            }
        }
        else
        {
            while (y != y2)
            {
                y += yIncrement;
                p < 0 ? p += twoDy : (x += xIncrement, p += twoDyDx);
                drawPixel(x, y);
            }
        }
    }
    else if (slopeBased)
    {
        float dx = x2 - x1, dy = y2 - y1, m = dy / dx;
        float xInc = 0, yInc = 0;
        if (dx == 0)
            yInc = 1;
        else if (m >= 0 && m <= 1)
            (x1 < x2) ? (xInc = 1, yInc = m) : (xInc = -1, yInc = -m);
        else if (m >= -1 && m < 0)
            (x1 < x2) ? (xInc = 1, yInc = m) : (xInc = -1, yInc = -m);
        else
            (x1 < x2) ? (xInc = 1 / abs(m), yInc = 1) : (xInc = -(1 / abs(m)), yInc = -1);
        float x = x1, y = y1;
        for (int i = 0; i <= abs(dx) + abs(dy); i++, x += xInc, y += yInc)
            drawPixel(x, y);
    }
    else
    {
        float dx = x2 - x1, dy = y2 - y1, steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
        float xInc = dx / steps, yInc = dy / steps, x = x1, y = y1;
        for (int i = 0; i <= steps; i++, x += xInc, y += yInc)
            drawPixel(x, y);
    }
}
void drawCircle(float x_center, float y_center, float r)
{
    int x = r, y = 0, p = 1 - r;
    while (x > y)
    {
        drawPixel(x + x_center, y + y_center);
        drawPixel(x + x_center, -y + y_center);
        drawPixel(-x + x_center, -y + y_center);
        drawPixel(-x + x_center, y + y_center);
        drawPixel(y + x_center, x + y_center);
        drawPixel(y + x_center, -x + y_center);
        drawPixel(-y + x_center, x + y_center);
        drawPixel(-y + x_center, -x + y_center);
        y++;
        p <= 0 ? p += 2 * y + 1 : (x--, p += 2 * y - 2 * x + 1);
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 1.0);
    drawCircle(0, 0, 50);
    drawLine(20, 20, 90, 5, true);
    drawLine(20, 20, 90, 5);
    drawLine(10, 10, 40, 5, false, true);
    glFlush();
}
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
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
