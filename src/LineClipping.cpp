#include <GL/glut.h>
#include <iostream>

// Define the clipping window bounds
double xmin = -100, ymin = -100, xmax = 100, ymax = 100;

// Region codes for Cohen-Sutherland
enum RegionCode
{
    INSIDE = 0, // 0000
    LEFT = 1,   // 0001
    RIGHT = 2,  // 0010
    BOTTOM = 4, // 0100
    TOP = 8     // 1000
};

// Function to compute the region code for a point
int computeCode(double x, double y)
{
    int code = INSIDE;
    if (x < xmin)
        code |= LEFT;
    else if (x > xmax)
        code |= RIGHT;
    if (y < ymin)
        code |= BOTTOM;
    else if (y > ymax)
        code |= TOP;
    return code;
}

// Function to find the intersection of a line with a boundary
void findIntersection(double &x, double &y, double x1, double y1, double x2, double y2, int codeOut)
{
    if (codeOut & TOP)
    {
        y = ymax;
        x = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
    }
    else if (codeOut & BOTTOM)
    {
        y = ymin;
        x = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
    }
    else if (codeOut & RIGHT)
    {
        x = xmax;
        y = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
    }
    else if (codeOut & LEFT)
    {
        x = xmin;
        y = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
    }
}

// Cohen-Sutherland clipping algorithm
void cohenSutherlandClip(double x1, double y1, double x2, double y2)
{
    int code1 = computeCode(x1, y1), code2 = computeCode(x2, y2);
    bool accept = false;

    // Draw the full line in red (original line)
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
    glEnd();

    while (true)
    {
        if ((code1 | code2) == 0)
        { // Both inside
            accept = true;
            break;
        }
        else if (code1 & code2)
        { // Both outside in the same region
            break;
        }
        else
        {
            double x, y;
            int codeOut = code1 ? code1 : code2;
            findIntersection(x, y, x1, y1, x2, y2, codeOut);
            (codeOut == code1) ? (x1 = x, y1 = y, code1 = computeCode(x1, y1)) : (x2 = x, y2 = y, code2 = computeCode(x2, y2));
        }
    }

    // Draw the clipped part of the line in green
    if (accept)
    {
        glColor3f(0.0, 1.0, 0.0); // Green
        glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
        glEnd();
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-200, 200, -200, 200, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    // Draw the clipping window in blue
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2d(xmin, ymin);
    glVertex2d(xmax, ymin);
    glVertex2d(xmax, ymax);
    glVertex2d(xmin, ymax);
    glEnd();

    // Example lines to clip
    float x1{-0}, y1{-150}, x2{150}, y2{150};
    std::cin >> x1 >> y1 >> x2 >> y2;
    cohenSutherlandClip(x1, y1, x2, y2);

    glFlush();
}

int main(int argc, char **argv)
{
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Cohen-Sutherland Line Clipping");

    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
