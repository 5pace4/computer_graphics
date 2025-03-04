#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <stack>
#include <iostream>

#define PI 3.14

using namespace std;

int vertex, radius = 50;
int centreX = 200, centreY = 200;
vector<int> x, y;

struct Color {
    GLfloat red, green, blue;
};

Color boundColor = { 1.0, 0.0, 0.0 },
    backgroundColor = { 1.0, 1.0, 1.0 },
        insideColor = { 1.0, 0.0, 1.0 };

void generatePolygonPoints() {
    for (int i = 0; i < vertex; ++i) {
        x.push_back(centreX + radius * cos(2.0 * PI * i / vertex));
        y.push_back(centreY + radius * sin(2.0 * PI * i / vertex));
    }
}

void lineDraw(int a1, int b1, int a2, int b2) {
    glBegin(GL_LINES);
    glVertex2i(a1, b1);
    glVertex2i(a2, b2);
    glEnd();
}

void drawPolygon() {
    for (int i = 0; i < vertex - 1; ++i)
        lineDraw(x[i], y[i], x[i + 1], y[i + 1]);
    lineDraw(x[vertex - 1], y[vertex - 1], x[0], y[0]);
}

Color getColorPixel(GLint x, GLint y) {
    Color color;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
    return color;
}

void fillColorPixel(GLint x, GLint y) {
    glColor3f(insideColor.red, insideColor.green, insideColor.blue);
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

bool colorNotFilled(const Color& currColor) {
    return !(currColor.red == boundColor.red && currColor.green == boundColor.green &&
        currColor.blue == boundColor.blue)
        && !(currColor.red == insideColor.red &&
            currColor.green == insideColor.green &&
            currColor.blue == insideColor.blue);
}

bool isBoundary(const Color& currColor) {
    return currColor.red == boundColor.red && currColor.green == boundColor.green &&
        currColor.blue == boundColor.blue;
}

void boundaryFillRecursion(int currX, int currY) {
    if (isBoundary(getColorPixel(currX + 1, currY)) ||
        isBoundary(getColorPixel(currX, currY + 1))
        || isBoundary(getColorPixel(currX - 1, currY)) ||
        isBoundary(getColorPixel(currX, currY - 1))) return;

    Color currColor = getColorPixel(currX, currY);
    if (colorNotFilled(currColor)) {
        fillColorPixel(currX, currY);
        boundaryFillRecursion(currX + 1, currY);
        boundaryFillRecursion(currX - 1, currY);
        boundaryFillRecursion(currX, currY + 1);
        boundaryFillRecursion(currX, currY - 1);
    }
}

void disp() {
    glColor3f(boundColor.red, boundColor.green, boundColor.blue);
    drawPolygon();
    boundaryFillRecursion(centreX, centreY);
    glFlush();
}

int main(int argc, char **argv) {
    cout << "Enter the number of vertices of the regular polygon: ";
    cin >> vertex;
    generatePolygonPoints();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(centreX * 2, centreY * 2);
    glutCreateWindow("Boundary Fill Algorithm");

    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, centreX * 2, 0, centreY * 2);
    glClearColor(backgroundColor.red, backgroundColor.green, backgroundColor.blue, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glutDisplayFunc(disp);
    glutMainLoop();
    return 0;
}
