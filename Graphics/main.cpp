// 206262719_208140111
#include <stdlib.h>
#include "glut.h"
#include <math.h>
#include <time.h>

const int W = 800;
const int H = 600;
unsigned char pixels[H][W][3]; // 3 stands for RGB
double offset = 0;

double distance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}


void init()
{
	int i, j;
	srand(time(0));
	glClearColor(255,255,255,255);// color of window background
	glOrtho(-1, 1, -1, 1, -1, 1); // defines the main axis and their range

}




void DrawFlag()
{
	glEnable(GL_BLEND); //Enable blending.
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set blending function.

	// Draw blue Star of David
	glColor3d(0,0,200); // Set color to blue
	glLineWidth(6);

	glBegin(GL_LINE_LOOP);
	glVertex2d(-0.25, -0.20);
	glVertex2d(0.25, -0.20);
	glVertex2d(0, 0.30);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex2d(-0.25, 0.15);
	glVertex2d(0.25, 0.15);
	glVertex2d(0, -0.35);
	glEnd();
	}







void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	glDrawPixels(W, H, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	DrawFlag();


	glutSwapBuffers(); // show all
}

void idle()
{
	double dist;
	offset += 0.1;

	// background
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			if (i > 80 && i < 150 || H - 80>i && H - 150 < i) // blue
			{
				pixels[i][j][0] = 0;
				pixels[i][j][1] = 0;
				pixels[i][j][2] = 155;

			}
			else { // white
				pixels[i][j][0] = 155;
				pixels[i][j][1] = 155;
				pixels[i][j][2] = 155;
			}
		}

	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
		{
			dist = distance(j, i, -W / 2, H / 2);
			pixels[i][j][0] += 100 * (1 + sin(dist / 40.0 - offset)) / 2;
			pixels[i][j][1] += 100 * (1 + sin(dist / 40.0 - offset)) / 2;
			pixels[i][j][2] += 100 * (1 + sin(dist / 40.0 - offset)) / 2;
		}

	glutPostRedisplay(); // sends a message to the window to run display function
}


void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("First Example");

	glutDisplayFunc(display); // display is a name of refresh function
	glutIdleFunc(idle);// idle is a function that runs in background

	init();

	glutMainLoop();
}