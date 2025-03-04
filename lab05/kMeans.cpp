#include <GL/freeglut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cfloat>

using namespace std;

struct Point {
    float x, y;
    int cluster;
};

vector<Point> points;
int K = 2;

float distance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void kMeans(vector<Point>& points, int K, vector<int>& assignments, vector<Point>& centroids) {
    srand(time(0));
    centroids.resize(K);

    centroids[0] = points[rand() % points.size()];

    for (int i = 1; i < K; i++) {
        float maxDist = -1.0;
        int selectedIndex = -1;
        for (int j = 0; j < points.size(); j++) {
            float minDist = FLT_MAX;
            for (int c = 0; c < i; c++) {
                float dist = distance(points[j], centroids[c]);
                minDist = fmin(minDist, dist);
            }
            if (minDist > maxDist) {
                maxDist = minDist;
                selectedIndex = j;
            }
        }
        centroids[i] = points[selectedIndex];
    }

    bool changed;
    do {
        changed = false;

        for (int i = 0; i < points.size(); i++) {
            int closest = -1;
            float minDist = FLT_MAX;
            for (int j = 0; j < K; j++) {
                float dist = distance(points[i], centroids[j]);
                if (dist < minDist) {
                    minDist = dist;
                    closest = j;
                }
            }

            if (assignments[i] != closest) {
                assignments[i] = closest;
                changed = true;
            }
        }

        vector<Point> newCentroids(K, {0, 0});
        vector<int> clusterSizes(K, 0);

        for (int i = 0; i < points.size(); i++) {
            newCentroids[assignments[i]].x += points[i].x;
            newCentroids[assignments[i]].y += points[i].y;
            clusterSizes[assignments[i]]++;
        }

        for (int i = 0; i < K; i++) {
            if (clusterSizes[i] > 0) {
                newCentroids[i].x /= clusterSizes[i];
                newCentroids[i].y /= clusterSizes[i];
            }
        }

        centroids = newCentroids;

    } while (changed);
}

void drawCircle(float cx, float cy, float radius, int numSegments = 100) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < numSegments; i++) {
        float angle = 2 * M_PI * i / numSegments;
        float x = cx + radius * cos(angle);
        float y = cy + radius * sin(angle);
        glVertex2f(x, y);
    }
    glEnd();
}

void GetInput() {
    cout << "Enter the number of points: ";
    int n;
    cin >> n;
    points.resize(n);
    cout << "Enter the points: ";
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    cout << "Enter the number of clusters: ";
    cin >> K;
}

void adjustProjection() {
    float minX = FLT_MAX, minY = FLT_MAX, maxX = -FLT_MAX, maxY = -FLT_MAX;

    for (const auto& point : points) {
        if (point.x < minX) minX = point.x;
        if (point.x > maxX) maxX = point.x;
        if (point.y < minY) minY = point.y;
        if (point.y > maxY) maxY = point.y;
    }

    float padding = 1.0f;
    glOrtho(minX - padding, maxX + padding, minY - padding, maxY + padding, -1.0, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    GetInput();
    vector<int> assignments(points.size(), -1);
    vector<Point> centroids;
    kMeans(points, K, assignments, centroids);

    adjustProjection();

    glColor3f(0.0f, 0.0f, 0.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    for (const auto& point : points) {
        glVertex2f(point.x, point.y);
    }
    glEnd();

    for (int i = 0; i < K; i++) {
        float maxDist = 0.0f;

        for (int j = 0; j < points.size(); j++) {
            if (assignments[j] == i) {
                float dist = distance(centroids[i], points[j]);
                if (dist > maxDist) {
                    maxDist = dist;
                }
            }
        }

        glColor3f(0.0f, 1.0f, 0.0f);
        drawCircle(centroids[i].x, centroids[i].y, maxDist);
    }

    glutSwapBuffers();
}

void initOpenGL() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("K-means Clustering");

    initOpenGL();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
