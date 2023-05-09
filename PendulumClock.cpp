#include <GL/glut.h>
#include <cmath>
#include <stdlib.h>


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
	drawPoint(x + Cx, y + Cy);
	drawPoint(y + Cx, x + Cy);
	
	// Second Quadrant
	drawPoint(-x + Cx, y + Cy);
	drawPoint(-y + Cx, x + Cy);
	
	// Third Quadrant
	drawPoint(-x + Cx, -y + Cy);
	drawPoint(-y + Cx, -x + Cy);
	
	// Fourth Quadrant
	drawPoint(x + Cx, -y + Cy);
	drawPoint(y + Cx, -x + Cy);
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
	drawLine(0, 50, 0, -220);
	drawLine(0, 50, -270 * sin(degreeToRadian(45)), 50 - 270 * cos(degreeToRadian(45)));
	BresenhamCircleDrawingAlgo(0, -250, 30);
	BresenhamCircleDrawingAlgo(-300 * sin(degreeToRadian(45)), 50 - 300 * cos(degreeToRadian(45)), 30);
	
}


void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	pendulumClock();
	glFlush();
}


void Init() {
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
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
