#include <GL/glut.h>
#include <iostream>

void drawPixel(float x, float y)
{
    std::cout << x << " " << y << std::endl;
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void dDLWithOutSlopDrawLine(float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = abs(dx) >= abs(dy) ? abs(dx) : abs(dy);
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;
    float x = x1;
    float y = y1;
    for (int i = 0; i <= steps; i++)
    {
        drawPixel(x, y);
        x += xIncrement;
        y += yIncrement;
    }
}

void dDLWithSlopDrawLine(float x1, float y1, float x2, float y2)
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

void bresenhamDrawLine(float x1, float y1, float x2, float y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int dx1 = x2 - x1;
    int dy1 = y2 - y1;

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

void drawMidPointCircle(float x_center, float y_center, float r)
{
    if (r < 0)
        return;

    int x = r, y = 0, p = 1 - r;
    drawPixel(x + x_center, y + y_center);
    while (x > y)
    {
        y++;
        if (p <= 0)
        {
            p = p + 2 * y + 1;
        }
        else
        {
            x--;
            p = p + (2 * y) - (2 * x) + 1;
        }
        if (x < y)
            break;
        drawPixel(x + x_center, y + y_center);
        drawPixel(x + x_center, -y + y_center);
        drawPixel(-x + x_center, -y + y_center);
        drawPixel(-x + x_center, y + y_center);
        drawPixel(y + x_center, x + y_center);
        drawPixel(y + x_center, -x + y_center);
        drawPixel(-y + x_center, -x + y_center);
        drawPixel(-y + x_center, x + y_center);
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 1.0);
    glPointSize(1.5);
    int x1 = 20, y1 = 20, x2 = 90, y2 = 5;
    int x{300}, y{250}, r{50};

    // std::cout << "Enter x1, y1, x2, y2: ";
    // std::cin >> x1 >> y1 >> x2 >> y2;
    // std::cout << "Enter x, y, r: ";
    // std::cin >> x >> y >> r;

    drawMidPointCircle(x, y, r);

    bresenhamDrawLine(20, 20, 90, 5);
    dDLWithOutSlopDrawLine(20, 20, 90, 5);
    dDLWithSlopDrawLine(10, 10, 40, 5);

    glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 50, 0.0, 50, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Line Drawing");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}