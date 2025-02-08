#include <GL/glut.h>
#include <iostream>

using namespace std;
int xc, yc, r; // Circle center and radius

// Function to plot points in all octants
void plotPoints(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
    glEnd();
}

// Midpoint Circle Drawing Algorithm
void drawCircle() {
    int x = 0, y = r;
    int p = 1 - r; // Initial decision parameter

    while (x <= y) {
        plotPoints(x, y);
        x++;
        if (p < 0) {
            p += 2 * x + 3;
        }
        else {
            y--;
            p += 2 * (x - y) + 5;
        }
    }
    glFlush();
}

// Display function to draw the circle
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle();
    glFlush();
}

// Function to initialize OpenGL settings
void init() {
    glClearColor(1.0, 0.0, 0.0, 0.0);  // Set bg color white
    glColor3f(0.0, 0.0, 0.0);          // Set drawing color black
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Centering the window coordinate system
    gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char** argv) {
    cout << "Enter circle center (xc yc): ";
    cin >> xc >> yc;
    cout << "Enter circle radius (r): ";
    cin >> r;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Midpoint Circle Algorithm");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
