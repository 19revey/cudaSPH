//#include <iostream>
//using namespace std;
//
//#include "Solver.h"
//
//int main()
//{
//	
//
//	
//	while (true)
//	{
//		solver.Update();
//		i++;
//		cout << i << endl;
//	}
//
//	return 0;
//}

#include <GL\glut.h>

#include <iostream>
#include <ctime>
using namespace std;

#include "Solver.h"


struct Vec3f
{
	float x;
	float y;
	float z;
};

typedef Vec3f Translate;
typedef Vec3f Rotate;


Rotate rot;
Translate trans;

Solver solver(1024 * 16);

GLfloat sun_light_position[] = { 25.0f, 15.0f, 0.0f, 0.0f };

int i = 0;

clock_t st = 0, en = 0;


void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glShadeModel(GL_SMOOTH);

	rot.x = 0.0f;
	rot.y = 0.0f;
	rot.z = 0.0f;

	trans.x = 0.0f;
	trans.y = 0.0f;
	trans.z = -90.0f;
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(trans.x, trans.y, trans.z);
	glRotatef(rot.x, 1.0f, 0.0f, 0.0f);
	glRotatef(rot.y, 0.0f, 1.0f, 0.0f);
	glRotatef(rot.z, 0.0f, 0.0f, 1.0f);
	glPushMatrix();
	glScalef(50.0f, 30.0f, 40.0f);
	glutWireCube(1.0f);
	glPopMatrix();

	solver.Update();
	i++;
	//cout << i << endl;

	float3* temp = solver.GetPos();

	for (int index = 0; index < 16 * 1024; index++)
	{
		glPushMatrix();
		glTranslatef(temp[index].x-25.0f, temp[index].y-15.0f, temp[index].z-20.0f);
		glutSolidSphere(0.5f, 10, 10);
		glPopMatrix();
	}

	st = clock();

	float dura = float(st - en) / 1000.0f;

	//cout << dura << endl;

	en = st;

	//char fname[12];
	//sprintf(fname, "%d.jpg", cycle);

	//SaveBMPFromOpenGl(fname);

	char text[32];
	sprintf_s(text, "The frame is %f: ", 1.0f / dura);
	glutSetWindowTitle(text);

	glutSwapBuffers();
}

void reshape(int width, int height)
{
	glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, static_cast<float>(width) / (height = (height == 0 ? 1 : height)), 0.01, 1000.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	default:
		break;
	}

	glutPostRedisplay();
}

void special(int key, int x, int y)
{
	switch (key)
	{
	default:
		break;
	}

	glutPostRedisplay();
}

void processMenuEvents(int option)
{
	switch (option)
	{
	default:
		break;
	}
}

void createGLUTMenus(int& menu)
{
	menu = glutCreateMenu(processMenuEvents);

	/*glutAddMenuEntry("Red",RED);
	glutAddMenuEntry("Blue",BLUE);
	glutAddMenuEntry("Green",GREEN);
	glutAddMenuEntry("White",WHITE);*/

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		if (GLUT_DOWN == state)
		{
		}
		else if (GLUT_UP == state)
		{
		}
		break;


	case GLUT_MIDDLE_BUTTON:
		if (GLUT_DOWN == state)
		{
		}
		else if (GLUT_UP == state)
		{
		}
		break;


	case GLUT_RIGHT_BUTTON:
		if (GLUT_DOWN == state)
		{
		}
		else if (GLUT_UP == state)
		{
		}
		break;


	default:
		break;
	}

	glutPostRedisplay();
}

void motion(int x, int y)
{
}

void passivemotion(int x, int y)
{
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(512, 512);
	glutCreateWindow(argv[0]);
	en = clock();
	init();
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);

	int menu;
	createGLUTMenus(menu);

	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passivemotion);

	glutMainLoop();

	glutDetachMenu(GLUT_RIGHT_BUTTON);
	glutDestroyMenu(menu);

	return 0;
}