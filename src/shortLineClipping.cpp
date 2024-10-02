
#include <GL/glut.h>
#include <iostream>

double xmin = -100, ymin = -100, xmax = 100, ymax = 100;
enum
{
    INSIDE = 0,
    LEFT = 1,
    RIGHT = 2,
    BOTTOM = 4,
    TOP = 8
};
int computeCode(double x, double y) { return (x < xmin ? LEFT : x > xmax ? RIGHT
                                                                         : INSIDE) |
                                             (y < ymin ? BOTTOM : y > ymax ? TOP
                                                                           : INSIDE); }
void cohenSutherlandClip(double &x1, double &y1, double &x2, double &y2)
{
    int code1 = computeCode(x1, y1), code2 = computeCode(x2, y2);
    while (true)
    {
        if (!(code1 | code2))
            break;
        if (code1 & code2)
            return;
        int codeOut = code1 ? code1 : code2;
        double x, y;
        if (codeOut & TOP)
            y = ymax, x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
        else if (codeOut & BOTTOM)
            y = ymin, x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
        else if (codeOut & RIGHT)
            x = xmax, y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
        else if (codeOut & LEFT)
            x = xmin, y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
        (codeOut == code1) ? (x1 = x, y1 = y, code1 = computeCode(x1, y1)) : (x2 = x, y2 = y, code2 = computeCode(x2, y2));
    }
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-200, 200, -200, 200, -1.0, 1.0);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(xmin, ymin);
    glVertex2d(xmax, ymin);
    glVertex2d(xmax, ymax);
    glVertex2d(xmin, ymax);
    glEnd();
    double x1{-200}, y1{-200}, x2{200}, y2{200};
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();
    cohenSutherlandClip(x1, y1, x2, y2);
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
