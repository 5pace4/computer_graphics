#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

GLint startX, startY, endX, endY;
void init(){
    glClearColor(1.0, 0.5, 1.0, 0.5);
    glColor3f(4.0f, 0.0f, 0.0f);
    glPointSize(3.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 600.0, 0.0, 600.0);
}

void setPixel(GLint xcoordinate, GLint ycoordinate){
    glBegin(GL_POINTS);
    glVertex2i(xcoordinate, ycoordinate);
    glEnd();
    glFlush();
}

void lineDDA(GLint x0, GLint y0, GLint xEnd, GLint yEnd){
    GLint dx = xEnd - x0;
    GLint dy = yEnd - y0;

    GLint steps = 0;
    if(abs(dx) > abs(dy)){
        steps = abs(dx);
    }
    else{
        steps = abs(dy);
    }

    float xInc = dx / (float)steps;
    float yInc = dy / (float)steps;
    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; i++){
        setPixel(round(x), round(y));
        x += xInc;
        y += yInc;
    }
}

void readInput(){
    printf("\nEnter startX, startY, endX, endY (resp): ");
    scanf("%i %i %i %i", &startX, &startY, &endX, &endY);
}

void Display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    lineDDA(startX, startY, endX, endY);
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("DDA Line Drawing Algorithm");
    readInput();
    glutDisplayFunc(Display);
    init();
    glutMainLoop();
    return 0;
}
