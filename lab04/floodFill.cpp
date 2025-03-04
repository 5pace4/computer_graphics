#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

vector<int> x;
vector<int> y;
int vertex = 4;

int centreX = 200;
int centreY = 200;
int rectWidth, rectHeight; 

struct Color {
    GLfloat red;
    GLfloat green;
    GLfloat blue;
};
Color boundColor = {1.0, 0.0, 0.0};      // red boundary
Color backgroundColor = {1.0, 1.0, 1.0}; // white bg
Color insideColor = {1.0, 0.0, 0.0};     // fill inside with red color


void generatePolygonPoints(){
    cin >> rectWidth >> rectHeight;

    x.clear();
    y.clear();

    // Bottom-left
    int blX = centreX - rectWidth / 2;
    int blY = centreY - rectHeight / 2;
    // Bottom-right
    int brX = centreX + rectWidth / 2;
    int brY = blY;
    // Top-right
    int trX = brX;
    int trY = centreY + rectHeight / 2;
    // Top-left
    int tlX = blX;
    int tlY = trY;
    
    x.push_back(blX); y.push_back(blY);
    x.push_back(brX); y.push_back(brY);
    x.push_back(trX); y.push_back(trY);
    x.push_back(tlX); y.push_back(tlY);
}


void lineDraw(int x1, int y1, int x2, int y2){
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

void drawPolygon(){
    for (int i = 0; i < (vertex - 1); i++)
        lineDraw(x[i], y[i], x[i+1], y[i+1]); 
    
    lineDraw(x[vertex-1], y[vertex-1], x[0], y[0]);
}

// check whether current pixel color is same as background color
int colorEqual(Color currentColor){
    return (currentColor.red == backgroundColor.red &&
            currentColor.green == backgroundColor.green &&
            currentColor.blue == backgroundColor.blue);
}

Color getColorPixel(GLint pointX, GLint pointY){
    Color pointColor;
    // Read pixel data at (pointX, pointY)
    glReadPixels(pointX, pointY, 1, 1, GL_RGB, GL_FLOAT, &pointColor);
    return pointColor;
}

void fillColorPixel(GLint pointX, GLint pointY){
    glColor3f(insideColor.red, insideColor.green, insideColor.blue);
    glBegin(GL_POINTS);
    glVertex2i(pointX, pointY);
    glEnd();
    glFlush();
}

// fill inside of rectangle using flood fill algorithm
void FloodFill(int currX, int currY){
    Color currColor = getColorPixel(currX, currY);
    if (!colorEqual(currColor))
        return;
    
    fillColorPixel(currX, currY);
    FloodFill(currX + 1, currY);
    FloodFill(currX, currY + 1);
    FloodFill(currX - 1, currY);
    FloodFill(currX, currY - 1);
    return;
}

void disp() {
    glColor3f(boundColor.red, boundColor.green, boundColor.blue); // red for boundary
    drawPolygon(); 
    FloodFill(centreX, centreY); // start flood fill from the center
    glFlush();
}

int main(int argc, char **argv){

    generatePolygonPoints();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(centreX * 2, centreY * 2); // window size
    glutInitWindowPosition(800, 50); // window position
    glutCreateWindow("Flood Fill Algorithm for Rectangle");

    // Initialize OpenGL window
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, centreX * 2, 0, centreY * 2);
    glClearColor(backgroundColor.red, backgroundColor.green, backgroundColor.blue, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    glutDisplayFunc(disp);
    glutMainLoop();
    return 0;
}
