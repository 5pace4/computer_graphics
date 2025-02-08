# DDA Line Drawing Algorithm in OpenGL

## Overview
This program implements the **DDA (Digital Differential Analyzer) algorithm** to draw a straight line between two points using OpenGL. The DDA algorithm is an incremental method that calculates intermediate points along a line path by evaluating differential changes in the x and y coordinates.

## Prerequisites
Ensure you have the following installed:
- **OpenGL Utility Toolkit (GLUT)**
- **C++ Compiler (g++)**
- **Standard OpenGL libraries**

## Code Explanation

### Header Files
```cpp
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <bits/stdc++.h>
```
- `GL/glut.h` - Used for OpenGL functions and window handling.
- `stdio.h`, `stdlib.h` - Standard I/O functions.
- `bits/stdc++.h` - Includes common C++ libraries.

### Global Variables
```cpp
GLint startX, startY, endX, endY;
```
These variables store the starting and ending coordinates of the line.

### `init()` Function
```cpp
void init(){
    glClearColor(1.0, 0.5, 1.0, 0.5);
    glColor3f(4.0f, 0.0f, 0.0f);
    glPointSize(3.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 600.0, 0.0, 600.0);
}
```
- **Sets background color** to purple (`glClearColor`).
- **Sets drawing color** to red (`glColor3f`).
- **Sets point size** for better visibility (`glPointSize`).
- **Defines the coordinate system** using `gluOrtho2D` with a range of 600x600.

### `setPixel()` Function
```cpp
void setPixel(GLint xcoordinate, GLint ycoordinate){
    glBegin(GL_POINTS);
    glVertex2i(xcoordinate, ycoordinate);
    glEnd();
    glFlush();
}
```
- This function places a pixel at `(x, y)`.
- `glBegin(GL_POINTS)` initializes point drawing.
- `glVertex2i(x, y)` sets the pixel position.
- `glEnd()` and `glFlush()` ensure immediate rendering.

### `lineDDA()` Function
```cpp
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
```
#### Steps of DDA Algorithm:
1. Calculate `dx` and `dy`.
2. Determine the number of `steps` (max of `|dx|` and `|dy|`).
3. Compute `xInc` and `yInc` to incrementally update coordinates.
4. Start from `(x0, y0)` and iterate `steps` times, rounding and setting pixels.

### `readInput()` Function
```cpp
void readInput(){
    printf("\nEnter startX, startY, endX, endY (resp): ");
    scanf("%i %i %i %i", &startX, &startY, &endX, &endY);
}
```
- Reads user input for line coordinates.

### `Display()` Function
```cpp
void Display(void){
    glClear(GL_COLOR_BUFFER_BIT);
    lineDDA(startX, startY, endX, endY);
}
```
- Clears the window and calls `lineDDA()` to draw the line.

### `main()` Function
```cpp
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
```
- **Initializes GLUT** with `glutInit()`.
- **Sets the display mode** (`GLUT_SINGLE | GLUT_RGB`).
- **Creates a window** (`glutCreateWindow`).
- **Calls `readInput()`** to take user input.
- **Registers the display function (`glutDisplayFunc`)**.
- **Calls `init()`** for OpenGL setup.
- **Starts the event loop (`glutMainLoop()`)**.

## Compilation & Execution
### Compile:
```sh
g++ dda_algorithm.cpp -o dda -lGL -lGLU -lglut
```
### Run:
```sh
./dda
```
Enter values for `startX`, `startY`, `endX`, and `endY` when prompted.

## Expected Output
The program will generate a window displaying a line from `(startX, startY)` to `(endX, endY)` based on the **DDA Algorithm**.

## Key Features of DDA Algorithm
- Uses **floating-point arithmetic** for accuracy.
- Suitable for **line drawing** in computer graphics.
- Easy to implement but **less efficient** than Bresenham’s algorithm.

## Possible Enhancements
- Implement **Bresenham’s Algorithm** for improved performance.
- Allow user to draw **multiple lines**.
- Extend to **3D line drawing**.

## Conclusion
This program efficiently demonstrates the **DDA Line Drawing Algorithm** using **OpenGL**. The implementation allows users to input coordinates and visualize the generated line.

---
**Author:** Tofayel Ahmmed Babu 
**Date:** 2025-02-09
**License:** MIT
