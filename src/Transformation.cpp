#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>

struct Point
{
    float x, y;
};

std::vector<Point> originalPoints;
std::vector<Point> transformedPoints;

void drawLine(Point p1, Point p2)
{
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(2.0);
    for (size_t i = 0; i < originalPoints.size(); ++i)
    {
        drawLine(originalPoints[i], originalPoints[(i + 1) % originalPoints.size()]);
    }

    glColor3f(1.0, 0.0, 1.0);
    for (size_t i = 0; i < transformedPoints.size(); ++i)
    {
        drawLine(transformedPoints[i], transformedPoints[(i + 1) % transformedPoints.size()]);
    }

    glFlush();
}

void translate(float dx, float dy)
{
    for (auto &point : transformedPoints)
    {
        point.x += dx;
        point.y += dy;
    }
}

void scale(float sx, float sy, float fx, float fy)
{
    for (auto &point : transformedPoints)
    {
        point.x = fx + (point.x - fx) * sx;
        point.y = fy + (point.y - fy) * sy;
    }
}

void rotate(float angle, float rx, float ry)
{
    float radians = angle * M_PI / 180.0;
    for (auto &point : transformedPoints)
    {
        float newX = rx + (point.x - rx) * cos(radians) - (point.y - ry) * sin(radians);
        float newY = ry + (point.x - rx) * sin(radians) + (point.y - ry) * cos(radians);
        point.x = newX;
        point.y = newY;
    }
}

void reflect(char axis)
{
    for (auto &point : transformedPoints)
    {
        if (axis == 'x')
        {
            point.y = -point.y;
        }
        else if (axis == 'y')
        {
            point.x = -point.x;
        }
        else if (axis == 'c')
        {
            float temp = point.x;
            point.x = point.y;
            point.y = temp;
        }
    }
}

void shear(char axis, float factor)
{
    for (auto &point : transformedPoints)
    {
        if (axis == 'X')
        {
            point.x += factor * point.y;
        }
        else if (axis == 'Y')
        {
            point.y += factor * point.x;
        }
    }
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-200, 200, -200, 200, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

void calculatePolygonPoints(int n, float cx, float cy, float armLength)
{
    originalPoints.clear();
    transformedPoints.clear();

    float angleIncrement = 360.0 / n;
    for (int i = 0; i < n; ++i)
    {
        float angle = i * angleIncrement * M_PI / 180.0;
        Point p;
        p.x = cx + armLength * cos(angle);
        p.y = cy + armLength * sin(angle);
        originalPoints.push_back(p);
        transformedPoints.push_back(p);
    }
}

void applyTransformation(int transformation)
{
    switch (transformation)
    {
    case 1:
        translate(30, -40);
        break;
    case 2:
        scale(0.5, 0.5, 30, 60);
        break;
    case 3:
        rotate(90, 50, 50);
        break;
    case 4:
        reflect('x');
        break;
    case 5:
        shear('X', 0.2);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

void handleInput(unsigned char key, int x, int y)
{
    if (key == '1')
        applyTransformation(1); // Translation
    else if (key == '2')
        applyTransformation(2); // Scaling
    else if (key == '3')
        applyTransformation(3); // Rotation
    else if (key == '4')
        applyTransformation(4); // Reflection
    else if (key == '5')
        applyTransformation(5); // Shearing
}

void inputPolygon()
{
    int n;
    float cx, cy, armLength;
    std::cout << "Enter number of points for the polygon (e.g. 3 for triangle, 4 for rectangle): ";
    std::cin >> n;

    std::cout << "Enter center coordinates (cx, cy): ";
    std::cin >> cx >> cy;

    std::cout << "Enter the length of the arm (distance from center to vertices): ";
    std::cin >> armLength;

    calculatePolygonPoints(n, cx, cy, armLength);
}

int main(int argc, char **argv)
{
    inputPolygon();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Transformation Demonstrations");

    glClearColor(1.0, 1.0, 1.0, 0.0);
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(handleInput);

    glutMainLoop();
    return 0;
}
