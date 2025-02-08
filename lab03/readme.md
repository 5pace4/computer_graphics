# Midpoint Circle Drawing Algorithm

## Introduction

The **Midpoint Circle Algorithm** is an efficient way to draw a circle in computer graphics using rasterization techniques. It is an optimized version of Bresenham's circle algorithm and works by determining the next pixel location based on the decision parameter.

This implementation uses OpenGL (GLUT) to visualize the circle on a graphical window.

## Code Breakdown

### **1. Header Files**

```cpp
#include <GL/glut.h>
#include <iostream>
```

- `GL/glut.h`: OpenGL Utility Toolkit (GLUT) header for window management and graphics rendering.
- `iostream`: Standard C++ library for input and output operations.

### **2. Global Variables**

```cpp
int xc, yc, r; // Circle center and radius
```

- `xc`, `yc`: Coordinates of the circle center.
- `r`: Radius of the circle.

### **3. Function to Plot Points in All Octants**

```cpp
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
```

- The Midpoint Circle Algorithm exploits **8-way symmetry**, so we only compute one octant and reflect the points.
- `glVertex2i(x, y)`: Plots a point in OpenGL.

### **4. Midpoint Circle Algorithm Implementation**

```cpp
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
```

- The algorithm begins with the topmost point `(0, r)`.
- The **decision parameter** `p` determines whether the next pixel should be **horizontal** `(x+1, y)` or **diagonal** `(x+1, y-1)`.
- If `p < 0`, the next pixel remains in the same row (east).
- If `p ≥ 0`, the next pixel moves diagonally (southeast).
- The process stops when `x > y` (completing one octant).

### **5. Display Function**

```cpp
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawCircle();
    glFlush();
}
```

- `glClear(GL_COLOR_BUFFER_BIT)`: Clears the screen before drawing.
- Calls `drawCircle()` to execute the Midpoint Algorithm.

### **6. OpenGL Initialization**

```cpp
void init() {
    glClearColor(1.0, 0.0, 0.0, 0.0);  // Background color (red)
    glColor3f(0.0, 0.0, 0.0);          // Drawing color (black)
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250); // Set up coordinate system
}
```

- `glClearColor(1.0, 0.0, 0.0, 0.0)`: Sets the **background color** (red).
- `glColor3f(0.0, 0.0, 0.0)`: Sets the **drawing color** (black).
- `gluOrtho2D(-250, 250, -250, 250)`: Defines a **2D coordinate system**.

### **7. Main Function**

```cpp
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
```

- Takes user input for `xc`, `yc`, and `r`.
- Initializes the GLUT window with `glutInit()`.
- Calls `init()` for OpenGL settings.
- Calls `glutDisplayFunc(display)` to link the drawing function.
- `glutMainLoop()` keeps the window running indefinitely.

## Algorithm Explanation

1. **Initialization:**

   - Start at `(x, y) = (0, r)`.
   - Compute the **initial decision parameter**: `p = 1 - r`.

2. **Decision Making:**

   - If `p < 0`, choose the **east pixel** (x+1, y).
   - If `p ≥ 0`, choose the **southeast pixel** (x+1, y-1).

3. **Plot Points:**

   - Use **8-way symmetry** to plot points in all octants.

4. **Loop Until Completion:**
   - Stop when `x > y`.

## Output Example

After running the program and entering the values:

```
Enter circle center (xc yc): 0 0
Enter circle radius (r): 100
```

The program will generate a **circle centered at (0,0) with radius 100**.

## Advantages

✅ **Efficient:** Uses only integer calculations (avoiding floating-point arithmetic).

✅ **Symmetric Drawing:** Plots points in all octants.

✅ **Optimized Algorithm:** Faster than trigonometric calculations.

## Conclusion

The **Midpoint Circle Algorithm** is a fundamental technique in computer graphics for rasterizing circles. By using integer calculations and decision parameters, it efficiently determines the next pixel position, resulting in a smooth and symmetrical circle.

---

✅ **Compiled with:** g++ (MinGW for Windows, GCC for Linux/macOS)

🔹 **Run the program:**

```bash
g++ midpoint_circle.cpp -o circle -lfreeglut -lopengl32 -lglu32
d ./circle
```
