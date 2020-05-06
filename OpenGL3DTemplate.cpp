#include <iostream>
#include <math.h>
#include <glut.h>
//Arrow for control

bool playing = false;
bool straight = false;
bool slightright = false;
bool slightleft = false;
bool switchforight = false; //going to right
bool moveright = false;
bool moveleft = false;
bool up = false;
bool switchforleft = false; //going to the left


bool upplay = false;
bool switchforup = false; //going up

int score = 0;

float yball = 0;
float zball = 0;
float xball = 0;


int brickcolor = 0;


size_t j;
float rup = 0;
float r = 0;
using namespace std;
#define DEG2RAD(a) (a * 0.0174532925)



void print(float x, float y, float z, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos3f(x, y, z);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}

//class Vector3f {
//public:
//	float x, y, z;
//
//	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
//		x = _x;
//		y = _y;
//		z = _z;
//	}
//
//	Vector3f operator+(Vector3f& v) {
//		return Vector3f(x + v.x, y + v.y, z + v.z);
//	}
//
//	Vector3f operator-(Vector3f& v) {
//		return Vector3f(x - v.x, y - v.y, z - v.z);
//	}
//
//	Vector3f operator*(float n) {
//		return Vector3f(x * n, y * n, z * n);
//	}
//
//	Vector3f operator/(float n) {
//		return Vector3f(x / n, y / n, z / n);
//	}
//
//	Vector3f unit() {
//		return *this / sqrt(x * x + y * y + z * z);
//	}
//
//	Vector3f cross(Vector3f v) {
//		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
//	}
//};
//
//class Camera {
//public:
//	Vector3f eye, center, up;
//
//	Camera(float eyeX =0.719765 , float eyeY = 0.178343,float  eyeZ = 0.16874,float  centerX = -0.272696,float centerY= 0.229187,float centerZ = 0.29877,float upX = 0.0220451 ,float upY = 0.976588,float upZ = -0.213984) {
//		eye = Vector3f(eyeX, eyeY, eyeZ);
//		center = Vector3f(centerX, centerY, centerZ);
//		up = Vector3f(upX, upY, upZ);
//	}
//
//	void moveX(float d) {
//		Vector3f right = up.cross(center - eye).unit();
//		eye = eye + right * d;
//		center = center + right * d;
//	}
//
//	void moveY(float d) {
//		eye = eye + up.unit() * d;
//		center = center + up.unit() * d;
//	}
//
//	void moveZ(float d) {
//		Vector3f view = (center - eye).unit();
//		eye = eye + view * d;
//		center = center + view * d;
//	}
//
//	void rotateX(float a) {
//		Vector3f view = (center - eye).unit();
//		Vector3f right = up.cross(view).unit();
//		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
//		up = view.cross(right);
//		center = eye + view;
//	}
//
//	void rotateY(float a) {
//		Vector3f view = (center - eye).unit();
//		Vector3f right = up.cross(view).unit();
//		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
//		right = view.cross(up);
//		center = eye + view;
//	}
//
//	void look() {
//		gluLookAt(
//			eye.x, eye.y, eye.z,
//			center.x, center.y, center.z,
//			up.x, up.y, up.z
//		);
//		cout << "eye.x: " << eye.x << " eye.y: " << eye.y << " eye.z: " << eye.z << " center.x: " << center.x << " center.y: " << center.y
//			<< " center.z: " << center.z << " up.x: " << up.x << " up.y: " << up.y << " up.z: " << up.z << endl;
//	}
//};
//
//Camera camera;



void drawBrick(int color) {



	if (color == 0)
	{
		glColor3f(0, 1, 1); //cyan
		glutSolidCube(0.1);
	}
	if (color == 1)
	{

		glColor3f(1, 0, 1); //Magenta
		glutSolidCube(0.1);
	}

	if (color == 2)
	{
		glColor3f(1, 1, 1); //white
		glutSolidCube(0.1);
	}
	if (color == 3)
	{
		glColor3f(0, 0, 0); //black
		glutSolidCube(0.1);
	}


}
void rowblackwhite() {//ceiling
	glPushMatrix();

	for (int i = 0; i < 4; i++) {
		if (i % 2 == 0) {
			glTranslatef(0.1, 0, 0);
			drawBrick(3);//grey
		}
		else
		{
			glTranslatef(0.1, 0, 0);
			drawBrick(2);//mag
		}

	}
	glPopMatrix();
}

void rowCyanmag() {

	glPushMatrix();

	for (int i = 0; i < 4; i++) {
		if (i % 2 == 0) {
			glTranslated(0.1, 0, 0);
			drawBrick(0);//cyan
		}
		else
		{
			glTranslated(0.1, 0, 0);
			drawBrick(1);//mag
		}

	}
	glPopMatrix();

}
void stickywallrow() {
	glPushMatrix();
	for (int i = 0; i < 5; i++) {
		glTranslated(0.1, 0, 0);
		drawBrick(3);
	}
	glPopMatrix();
}



void drawWall(double thickness) {
	glPushMatrix();
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}


void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}

//void setupCamera() {
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(-0.5, 0.5, -0.5, 0.5, -1, 1);
//	//gluPerspective(60, 640 / 480, 0.001, 100);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	gluLookAt(0.719765 , 0.178343,0.16874,0.272696,0.229187,0.29877,0.0220451 ,0.976588,-0.213984);
//}


void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1, 1, -1, 1, -1, 1);
	gluPerspective(60, 640 / 480, 0.01, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//camera.look();
	gluLookAt(0.809241, 0.174438, 0.160114, -0.189229, 0.206756, 0.204978, 0.0220451, 0.976588, -0.213984);
}

void drawCeil() {
	rowblackwhite();

	glPushMatrix();
	glTranslatef(0, 0, 0.1);
	rowCyanmag();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.2);
	rowblackwhite();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.3);
	rowCyanmag();
	glPopMatrix();
}

void stickywall() {

	stickywallrow();

	glPushMatrix();
	glTranslatef(0, 0, 0.1);
	stickywallrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.2);
	stickywallrow();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0.3);
	stickywallrow();
	glPopMatrix();
}

void drawRow1() {
	float j = 1;
	int c = 0;
	for (float i = 0.6; i > -1; i -= 0.4) {
		if (c % 2 == 0) {
			glColor3f(0, 1, 1); //cyan)
		}
		else {
			glColor3f(1, 0, 1);//Magenta
		}
		glBegin(GL_QUADS);
		glVertex3f(j, 0, 0.6);
		glVertex3f(i, 0, 0.6);
		glVertex3f(i, 0, 1);
		glVertex3f(j, 0, 1);
		glEnd();
		c += 1;
		j -= 0.4;
	}
}

void drawBall() {
	glPushMatrix();//drawball
	glColor3f(1.0, 0.0, 0.0);
	glTranslatef(0.53, 0.1, 0.19);
	glutSolidSphere(0.02, 30, 30);
	glPopMatrix();
}









void drawArrow() {
	glPushMatrix(); //ARROW
	glColor3f(1, 0, 0);
	glTranslatef(0.54, 0.04, 0.19);
	glRotatef(-90, 0, 1, 0);
	glRotatef(-90, 1, 0, 0);
	glScalef(0.1, 0.1, 0.1);
	//glTranslated(1.0, 0, 1.0); // cone at (1,0,1) 
	glutSolidCone(0.1, 0.4, 10, 8);//arrow

	glPopMatrix();
}






void Display() {
	setupLights();
	setupCamera();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(1, 0, 0);
	print(0.55, 0.085, 0.10, "white=1");
	print(0.55, 0.070, 0.103, "Black=2");
	print(0.55, 0.055, 0.104, "Blue=3");
	print(0.55, 0.043, 0.11, " Pink=4");



	glPushMatrix();
	glColor3f(1, 0, 0);
	char* scores[20];
	sprintf((char*)scores, "Score is %d", score);
	print(0.55, 0.03, 0.11, (char *)scores);
	glPopMatrix();


	glPushMatrix();//arrow
	glTranslatef(0.54, 0.04, 0.19);
	glRotated(rup, 0, 0, 1);
	glRotated(r, 1, 0, 0);
	glTranslated(-0.54, -0.04, -0.19);
	drawArrow();
	glPopMatrix();

	glPushMatrix();
	glTranslated(xball, yball, zball);
	drawBall();
	glPopMatrix();

	drawCeil();//floor

	glPushMatrix(); //ceil bgd
	glTranslated(0, 0.4, 0);
	drawCeil();
	glPopMatrix();

	glPushMatrix(); //right wall 
	glRotatef(-90, 1, 0, 0);
	drawCeil();
	glPopMatrix();

	glPushMatrix();//sticky wall
	glTranslatef(0, -0.1, 0);
	glPushMatrix();
	glRotatef(90, 0, 0, 1);
	stickywall();
	glPopMatrix();
	glPopMatrix();



	glPushMatrix(); //left wall 
	glTranslated(0, 0, 0.4);
	glRotatef(-90, 1, 0, 0);
	drawCeil();
	glPopMatrix();



	//drawRow1();
	/*glPushMatrix();
	glRotatef(90, 0, 0, 1);
	glScalef(0.25,1 ,0.25) ;

	drawRow1();*/
	//glBegin(GL_QUADS);
	//glVertex3f(0.6, 1, 0);
	//glVertex3f(0.6, 0.6, 0);
	//glVertex3f(1,0.6 , 0);
	//glVertex3f(1, 1, 0);
	//glEnd();
	glPopMatrix();



	//drawBrick(1);
	//drawWall(0.1);
	//cout <<"r "<<r<<" up "<<up<<" upplay "<<upplay<<" rup "<<rup<<" moleft "<<moveleft<<"slight left "<<slightleft<<"move right "<<moveright<<"slight right "<<slightright<<"straight "<<straight << endl;
	glFlush();
}
//
//void Keyboard(unsigned char key, int x, int y) {
//	float d = 0.01;
//
//	switch (key) {
//	case 'w':
//		camera.moveY(d);
//		break;
//	case 's':
//		camera.moveY(-d);
//		break;
//	case 'a':
//		camera.moveX(d);
//		break;
//	case 'd':
//		camera.moveX(-d);
//		break;
//	case 'q':
//		camera.moveZ(d);
//		break;
//	case 'e':
//		camera.moveZ(-d);
//		break;
//	}
//
//	glutPostRedisplay();
//}

void Anim()
{
	if (playing == true && xball <= -0.42) {
		playing = false;
		xball = 0;
		yball = 0;
		zball = 0;
		r = 0;
		rup = 0;
		straight = false;
		moveleft = false;
		up = false;
		moveright = false;
		slightleft = false;
		slightright = false;
		switchforleft = false;
		switchforup = false;
		upplay = false;
		for (int i = 0; i < 100000050; i++)
		{

		}
		score = 0;

	}
	else
	{

		if (playing == true) {

			if (upplay == true && up == true) {
				if (up == true && switchforup == false) {
					xball += -0.00021;
					yball += 0.0005;
					if (yball >= 0.2) {
						switchforup = true;
						if (xball >= -0.2) {
							score += 1;
						}
						else {
							score += 2;
						}
						cout << "s" << score << endl;

					}
				}
				else {
					if (up == true && switchforup == true) {
						xball += -0.00043;
						yball -= 0.0005;
						if (yball <= 0.001) {
							switchforup = false;
							score += 2;
						}


					}
				}
			}

			else
			{
				if (upplay == false) {


					if (straight == true)
						xball += -0.001;
					else
					{
						if (slightleft == true) {
							xball += -0.001;
							zball += 0.00025;
						}
						else {
							if (slightright == true) {
								xball += -0.001;
								zball += -0.00025;

							}
							else {
								if (moveleft == true) {

									if (moveleft == true && switchforleft == false) {
										xball += -0.00035;
										zball += 0.0005;
										if (zball >= 0.15) {
											switchforleft = true;
											score += 4;
										}
									}
									else {
										if (moveleft == true && switchforleft == true) {
											xball += -0.00015;
											zball += -0.0005;
											if (zball <= -0.12) {
												switchforleft = false;
												score += 3;
											}
										}
									}

								}
								else {
									if (moveright == true) {
										if (moveright == true && switchforight == false) {
											xball += -0.00035;
											zball -= 0.0005;
											if (zball <= -0.12) {
												switchforight = true;
												score += 4;
											}
										}
										else {
											if (moveright == true && switchforight == true) {
												xball += -0.00035;
												zball += 0.0005;
												if (zball >= 0.15) {
													switchforight = false;
													score += 3;
												}
											}
										}
									}
								}
							}
						}


					}

				}
			}
		}
	}



	glutPostRedisplay();
}
void Special(int key, int x, int y) {


	switch (key) {
	case GLUT_KEY_UP:
		if (rup > -8 && playing == false) {
			rup -= 2;
			upplay = true;
		}
		break;
	case GLUT_KEY_DOWN:
		if (rup < 38 && playing == false) {
			rup += 2;
			upplay = true;
		}
		break;
	case GLUT_KEY_LEFT:
		if (r < 36 && playing == false) {
			r += 2;
			upplay = false;
		}
		break;
	case GLUT_KEY_RIGHT:
		if (r > -46 && playing == false) {
			r -= 2;
			upplay = false;
		}
		break;
	}



	//cout << rup << endl;
	glutPostRedisplay();
}

void keyUp(unsigned char k, int x, int y)//keyboard up function is called whenever the keyboard key is released
{
	if (k == 32 && playing == false && upplay == true) {//if the letter q is pressed, then the object will go back to it's original color.
		playing = true;

		up = true;

	}

	else
	{



		if (k == 32 && playing == false && upplay == false) {//if the letter q is pressed, then the object will go back to it's original color.
			playing = true;

			if (22 <= r)
				moveleft = true;
			else
			{
				if (10 <= r) {
					slightleft = true;
				}
				else
				{
					if (-12 <= r) {
						straight = true;
					}
					else
					{
						if (-30 <= r) {
							slightright = true;
						}
						else
						{
							if (-46 <= r)
								moveright = true;
						}

					}

				}

			}


		}
	}


	glutPostRedisplay();//redisplay to update the screen with the changed
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Assignment 2- Sandy");
	glutDisplayFunc(Display);

	//glutKeyboardFunc(Keyboard);

	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(Special);
	glutIdleFunc(Anim);
	//glutSpecialUpFunc(speUp);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glShadeModel(GL_SMOOTH);

	glutMainLoop();
}


//void setupCamera() {
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	//glOrtho(-1, 1, -1, 1, -1, 1);
//	gluPerspective(60, 640 / 480, 0.01, 1000);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	camera.look();
//}
//
//void Display() {
//	setupLights();
//	setupCamera();
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//	glPushMatrix();
//	drawWall(); //right wall
//	glPopMatrix();
//
//	glPushMatrix();
//	glRotatef(90, 1, 0, 0);
//	drawWall(); //floor
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, 0, 0.4);
//	drawWall(); //left wall 
//	glPopMatrix();
//
//	glPushMatrix();
//	glTranslatef(0, 0.4, 0);
//	glRotatef(90, 1, 0, 0);
//	drawWall(); //ceiling
//	glPopMatrix();
//
//	glPushMatrix();
//	glRotatef(-90, 0, 1, 0);
//	drawWall(); //fel wesh
//	glPopMatrix();
//
//	glPushMatrix();
//	glColor3d(0, 0, 0);
//	glTranslatef(0.4, 0.1, 0.2);
//	glRotated(30, 0, 1, 0);
//	glutSolidSphere(0.01, 30, 30);
//	glPopMatrix();
//	glFlush();
//}
//
//
//void Keyboard(unsigned char key, int x, int y) {
//	
//
//	switch (key) {
//	case 'w'://up + in y
//		camera.moveY(d);
//		break;
//	case 's': //down - in y
//		camera.moveY(-d);
//		break;
//	case 'a':
//		camera.moveX(d);
//		break;
//	case 'd':
//		camera.moveX(-d);
//		break;
//	case 'q':
//		camera.moveZ(d);
//		break;
//	case 'e':
//		camera.moveZ(-d);
//		break;
//	}
//
//	glutPostRedisplay();
//}
//void Special(int key, int x, int y) {
//	float a = 1.0;
//
//	switch (key) {
//	case GLUT_KEY_UP:
//		camera.rotateX(a);
//		break;
//	case GLUT_KEY_DOWN:
//		camera.rotateX(-a);
//		break;
//	case GLUT_KEY_LEFT:
//		camera.rotateY(a);
//		break;
//	case GLUT_KEY_RIGHT:
//		camera.rotateY(-a);
//		break;
//	}
//
//	glutPostRedisplay();
//}
//
//
//void main(int argc, char** argv) {
//	glutInit(&argc, argv);
//
//	glutInitWindowSize(640, 480);
//	glutInitWindowPosition(50, 50);
//
//	glutCreateWindow("Lab 5");
//	glutDisplayFunc(Display);
//	glutKeyboardFunc(Keyboard);
//	glutSpecialFunc(Special);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
//	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
//
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_LIGHTING);
//	glEnable(GL_LIGHT0);
//	glEnable(GL_NORMALIZE);
//	glEnable(GL_COLOR_MATERIAL);
//
//	glShadeModel(GL_SMOOTH);
//
//	glutMainLoop();
//}
