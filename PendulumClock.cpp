#include <GL/glut.h>
#include <cmath>
#include <stdlib.h>
#include <iostream>

using namespace std;

// Global Variables for storing window dimensions.
int windowWidth, windowHeight;


// Utility function to draw a point
void drawPoint(float x, float y) {
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

// Utility Function to convert degrees to radians.
float degreeToRadian(float degree) {
	return degree * (M_PI / 180.0);
}


void drawLine(int x1, int y1, int x2, int y2) {
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}


void drawPointInAllQuadrants(float x, float y, float Cx, float Cy) {
    // First Quadrant
    float x1 = x + Cx, y1 = y + Cy, x2 = y + Cx, y2 = x + Cy;
    drawPoint(x1, y1);
    drawPoint(x2, y2);

    // Second Quadrant
    x1 = -x + Cx; x2 = -y + Cx; 
    drawPoint(x1, y1);
    drawPoint(x2, y2);

    // Third Quadrant
    y1 = -y + Cy; y2 = -x + Cy;
    drawPoint(x1, y1);
    drawPoint(x2, y2);

    // Fourth Quadrant
    x1 = x + Cx; x2 = y + Cx; 
    drawPoint(x1, y1);
    drawPoint(x2, y2);
}

void BresenhamCircleDrawingAlgo(float Cx, float Cy, float radius) {
	float pk = 3 - (2 * radius);
	float x = 0, y = radius;
	
	while (x <= y) {
		if (pk < 0) {
			x++;
			pk += (4 * x) + 6;
		}
		else {
			x++;
			y--;
			pk += 4 * (x - y) + 10;
		}
		drawPointInAllQuadrants(x, y, Cx, Cy);
	}
}

void pendulumClock() {
	BresenhamCircleDrawingAlgo(0, 200, 150);
	BresenhamCircleDrawingAlgo(0, 200, 125);
	
	int length = 15;
	drawLine(110, 200 , 110 + length, 200);
	drawLine(-110, 200, -110 - length, 200);
	drawLine(0, 310, 0, 310 + length);
	drawLine(0, 90, 0, 90 - length);
	
	drawLine(0, 200, -50 * sin(degreeToRadian(15.0)), 200 - 50 * cos(degreeToRadian(15.9)));
	drawLine(0, 200, 100, 200);
}

void pendulum() {
	
	for (float degree = 45.0; degree > -45.1; degree -= 0.01) {
		glClear(GL_COLOR_BUFFER_BIT);
		pendulumClock();
		drawLine(0, 50, -270 * sin(degreeToRadian(degree)), 50 - 270 * cos(degreeToRadian(degree)));
		BresenhamCircleDrawingAlgo(-300 * sin(degreeToRadian(degree)),
		 50 - 300 * cos(degreeToRadian(degree)), 30);
		
		glutSwapBuffers();
	}
	for (float degree = -45.0; degree < 45.1; degree += 0.01) {
		glClear(GL_COLOR_BUFFER_BIT);
		pendulumClock();
		drawLine(0, 50, -270 * sin(degreeToRadian(degree)), 50 - 270 * cos(degreeToRadian(degree)));
		BresenhamCircleDrawingAlgo(-300 * sin(degreeToRadian(degree)),
		 50 - 300 * cos(degreeToRadian(degree)), 30);
		
		glutSwapBuffers();
	}
	pendulum();
}


void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	pendulum();
	glutSwapBuffers();
}


void Init() {
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-windowWidth/2, windowWidth/2, -windowHeight/2, windowHeight/2);
}


int main(int argc, char** argv) {	
	windowWidth = 600;
	windowHeight = 800;
		
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("PendulumClock");
	
	Init();
	glutDisplayFunc(myDisplay);
	
	glutMainLoop();
}
