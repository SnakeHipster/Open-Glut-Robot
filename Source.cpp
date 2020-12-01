
#include <iostream>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;
bool wireframe =false;
bool light1 =false;
bool light2 =false;
bool raiseLegs = false;
bool raiseArms = false;
bool direction =false;

float _legAngle = 90.0f;
float _legAngleChange = 0.0f;
float _footZaxis = 0.0f;
float _footYaxis = 0.0f;
float _footY = -6.5f;
float _footZ = -22.0f;

float _armAngle = 90.0f;
float _armAngleChange = 0.0f;
float _armZaxis = 0.0f;
float _armYaxis = 0.0f;
float _armY = -0.0f;
float _armZ = -22.0f;

float _headAngle = 0.0f;

void changeWireMode(){
	if (wireframe == true){
		wireframe = false;
	} else {
		wireframe = true;
	}
}


//Called when a key is pressed
void handleKeypress(unsigned char key, int x, int y) {
	switch (key) {
		case 'w':
			changeWireMode();
			break;
		case 27: //Escape key
			exit(0);
			break;
		case 'a':
			light1 =false;
			break;
		case 'b':
			light1 =true;
			break;
		case 'c':
			light2 =false;
			break;
		case 'd':
			light2 =true;
			break;
		case 'l':
			if (raiseLegs == true){
				raiseLegs = false;
			} else {
				raiseLegs = true;
			}
			break;
		case 'o':
			if (raiseArms == true){
				raiseArms = false;
			} else {
				raiseArms = true;
			}
			break;
		case 'p':
			if (direction == true){
				direction = false;
			} else {
				direction = true;
			}
			break;
		
	}
}

//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING); //Enable lighting
	glEnable(GL_LIGHT0); //Enable light #0
	glEnable(GL_LIGHT1); //Enable light #1
	glEnable(GL_NORMALIZE);
}

//Called when the window is resized
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

float _angle = 0.0f;
float _cameraAngle = 0.0f;



//Draws the 3D scene
void drawScene() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	//glRotatef(-_cameraAngle, 0.0f, 0.0f, -20.0f); //Rotate the camera
	glRotatef(_cameraAngle,0.0f,0.0f,-20.0f);
	glTranslatef(0.0f, 0.0f, -30.0f); //Move forward 5 units


	GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
	if (light1 == true){
		//Add positioned light
		GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
		GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	} else {
		GLfloat lightColor0[] = {0.0f, 0.0f, 0.0f, 0.0f};
		GLfloat lightPos0[] = {0.0f, 0.0f, 0.0f, 0.0f}; //Positioned at (4, 0, 8)
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	}
	if (light2 == true){
		//Add directed light
		GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
		//Coming from the direction (-1, 0.5, 0.5)
		GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	} else {
		GLfloat lightColor1[] = {0.0f, 0.0f, 0.0f, 0.0f}; //Color (0.5, 0.2, 0.2)
		GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	}


	//Neck
	glPushMatrix(); //Save the current state of transformations

	glTranslatef(0.0f, 7.0f, -24.0f); 
	glRotatef(90.0f, 10.0f, 0.0f, 0.0f); //Rotate about the the vector (1, 2, 3)
	glColor3f(1,1,0);
	if (wireframe == true){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else if (wireframe == false){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glBegin(GL_POLYGON);
	GLUquadricObj *obj = gluNewQuadric();
	gluCylinder(obj, 1.5, 1.5, 1, 30, 30);
	glEnd();
	
	glPopMatrix(); //Undo the move to the center of the triangle

	
	//Body
	glPushMatrix(); //Save the current state of transformations

	glTranslatef(0.0f, 0.0f, -20.0f); 
	glColor3f(1,0,0);
	if (wireframe == true){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else if (wireframe == false){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glBegin(GL_QUADS);
	//GLUquadricObj *obj = gluNewQuadric();
	//gluCylinder(obj, 3, 3, 10, 30, 30);



	glVertex3f(-3.0f,0.0f,0.0f);
	glVertex3f(3.0f,0.0f,0.0f);//front
	glVertex3f(3.0f,6.0f,0.0f);
	glVertex3f(-3.0f,6.0f,0.0f);

	glVertex3f(3.0f,0.0f,0.0f);
	glVertex3f(3.0f,0.0f,-3.0f);//Right side
	glVertex3f(3.0f,6.0f,-3.0f);
	glVertex3f(3.0f,6.0f,0.0f);

	glVertex3f(-3.0f,0.0f,0.0f);
	glVertex3f(-3.0f,6.0f,0.0f);
	glVertex3f(0.0f,6.0f,-3.0f);
	glVertex3f(0.0f,0.0f,-3.0f);//Left side
	
	glVertex3f(-3.0f,6.0f,0.0f);
	glVertex3f(3.0f,6.0f,0.0f); //Top
	glVertex3f(3.0f,6.0f,-3.0f);
	glVertex3f(-3.0f,6.0f,-3.0f);

	glVertex3f(-3.0f,0.0f,0.0f);
	glVertex3f(-3.0f,0.0f,-3.0f);//Bottom
	glVertex3f(3.0f,0.0f,-3.0f);
	glVertex3f(3.0f,0.0f,0.0f);

	glVertex3f(-3.0f,1.0f,-3.0f);
	glVertex3f(-3.0f,6.0f,-3.0f); //back
	glVertex3f(3.0f,6.0f,-3.0f);
	glVertex3f(3.0f,1.0f,-3.0f);

	glEnd();
	
	glPopMatrix(); //Undo the move to the center of the triangle

	//Left Arm
	glPushMatrix(); //Save the current state of transformations

	glTranslatef(4.0f, 6.0f, -22.0f); 
	_armAngle = _armAngle + _armAngleChange;
	glRotatef(_armAngle, 10.0f, 0.0f, 0.0f); //Rotate about the the vector (1, 2, 3)
	glColor3f(0,1,0);
	if (wireframe == true){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else if (wireframe == false){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glBegin(GL_POLYGON);
	GLUquadricObj *obj2 = gluNewQuadric();
	gluCylinder(obj2, 1, 1, 10, 30, 30);
	glEnd();
	
	glPopMatrix(); //Undo the move to the center of the triangle

	//Right Arm
	glPushMatrix(); //Save the current state of transformations

	glTranslatef(-4.0f, 6.0f, -22.0f); 
	glRotatef(_armAngle, 10.0f, 0.0f, 0.0f); //Rotate about the the vector (1, 2, 3)
	glColor3f(0,1,0);
	if (wireframe == true){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else if (wireframe == false){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glBegin(GL_POLYGON);
	GLUquadricObj *obj3 = gluNewQuadric();
	gluCylinder(obj3, 1, 1, 10, 30, 30);
	glEnd();
	
	glPopMatrix(); //Undo the move to the center of the triangle
	
	//Right Leg
	glPushMatrix(); //Save the current state of transformations

	glTranslatef(-2.0f, 0.0f, -22.0f); 
	_legAngle = _legAngle +_legAngleChange;
	glRotatef(_legAngle, 10.0f, 0.0f, 0.0f); //Rotate about the the vector (1, 2, 3)
	glColor3f(0,0,1);
	if (wireframe == true){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else if (wireframe == false){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glBegin(GL_POLYGON);
	GLUquadricObj *obj4 = gluNewQuadric();
	gluCylinder(obj4, 1, 1, 10, 30, 30);
	glEnd();
	
	glPopMatrix();

	//Left Leg
	glPushMatrix(); //Save the current state of transformations

	glTranslatef(2.0f, 0.0f, -22.0f); 
	glRotatef(90.0f, 10.0f, 0.0f, 0.0f); //Rotate about the the vector (1, 2, 3)
	glColor3f(0,0,1);
	if (wireframe == true){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else if (wireframe == false){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glBegin(GL_POLYGON);
	GLUquadricObj *obj5 = gluNewQuadric();
	gluCylinder(obj5, 1, 1, 10, 30, 30);
	glEnd();
	
	glPopMatrix();

	//Head
	glPushMatrix(); //Save the current state of transformations

	glTranslatef(0.0f, 6.0f, -22.0f); 
	_headAngle = _headAngle + _angle;
	glRotatef(_headAngle, 0.0f, 1.0f, 0.0f);
	glColor3f(0,1,1);
	if (wireframe == true){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else if (wireframe == false){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glBegin(GL_QUADS);
	glVertex3f(-2.0f,1.0f,2.0f);
	glVertex3f(2.0f,1.0f,2.0f);//front
	glVertex3f(2.0f,5.0f,2.0f);
	glVertex3f(-2.0f,5.0f,2.0f);

	glVertex3f(-2.0f,1.0f,2.0f);
	glVertex3f(2.0f,1.0f,2.0f); //bottom
	glVertex3f(2.0f,1.0f,-2.0f);
	glVertex3f(-2.0f,1.0f,-2.0f);

	glVertex3f(-2.0f,1.0f,-2.0f);
	glVertex3f(2.0f,1.0f,-2.0f);
	glVertex3f(2.0f,5.0f,-2.0f); //back
	glVertex3f(-2.0f,5.0f,-2.0f);

	glVertex3f(-2.0f,5.0f,2.0f);
	glVertex3f(2.0f,5.0f,2.0f); //top
	glVertex3f(2.0f,5.0f,-2.0f);
	glVertex3f(-2.0f,5.0f,-2.0f);

	glVertex3f(-2.0f,1.0f,2.0f);
	glVertex3f(-2.0f,1.0f,-2.0f);//Left
	glVertex3f(-2.0f,5.0f,-2.0f);
	glVertex3f(-2.0f,5.0f,2.0f);

	glVertex3f(2.0f,1.0f,2.0f);
	glVertex3f(2.0f,1.0f,-2.0f);//right
	glVertex3f(2.0f,5.0f,-2.0f);
	glVertex3f(2.0f,5.0f,2.0f);

	glEnd();
	
	glPopMatrix();

	//nose
	glPushMatrix(); //Save the current state of transformations

	glTranslatef(0.0f, 5.5f, -20.0f); 
	glColor3f(1,1,0);
	if (wireframe == true){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else if (wireframe == false){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glBegin(GL_QUADS);
	

	glVertex3f(-0.3f,3.0f,0.5f);
	glVertex3f(0.3f,3.0f,0.5f);
	glVertex3f(0.3f,3.6f,0.5f); //front
	glVertex3f(-0.3f,3.6f,0.5f);

	glVertex3f(0.3f,3.6f,0.5f);
	glVertex3f(0.3f,3.0f,0.5f); //Left side
	glVertex3f(0.3f,3.0f,0.0f); 
	glVertex3f(0.3f,3.6f,0.0f);

	glVertex3f(-0.3f,3.0f,0.5f);
	glVertex3f(-0.3f,3.6f,0.5f);//Right Side
	glVertex3f(-0.3f,3.6f,0.0f); 
	glVertex3f(-0.3f,3.0f,0.0f);

	glVertex3f(-0.3f,3.6f,0.5f);
	glVertex3f(0.3f,3.6f,0.5f); //Top
	glVertex3f(0.3f,3.6f,0.0f); 
	glVertex3f(-0.3f,3.6f,0.0f);

	glVertex3f(0.3f,3.0f,0.5f);
	glVertex3f(-0.3f,3.0f,0.5f); //bottom
	glVertex3f(-0.3f,3.0f,0.0f); 
	glVertex3f(0.3f,3.0f,0.0f);

	glEnd();
	glPopMatrix();

	//Left Foot
	glPushMatrix(); //Save the current state of transformations

	glTranslatef(2.0f, -6.5f, -22.0f); //-(_angle/9)
	glRotatef(0.0f, 1000.0f, 100.0f, 0.0f); //Rotate about the the vector (1, 2, 3)
	glColor3f(0,0,1);
	if (wireframe == true){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else if (wireframe == false){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
		
	glutSolidSphere( 1.2, 20.0, 20.0); 

	glPopMatrix();

	//Right Foot
	glPushMatrix(); //Save the current state of transformations

	_footY = _footY + _footYaxis;
	_footZ = _footZ + _footZaxis;
	glTranslatef(-2.0f, _footY, _footZ); //-(_angle/9)
	glRotatef(0.0f, 1000.0f, 100.0f, 0.0f); //Rotate about the the vector (1, 2, 3)
	glColor3f(0,0,1);
	if (wireframe == true){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else if (wireframe == false){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
		
	glutSolidSphere( 1.2, 20.0, 20.0); 

	glPopMatrix();

	//Right Hand
	glPushMatrix(); //Save the current state of transformations

	_armY = _armY + _armYaxis;
	_armZ = _armZ + _armZaxis;
	glTranslatef(-4.0f, _armY, _armZ); //-(_angle/9)
	glRotatef(0.0f, 1000.0f, 100.0f, 0.0f); //Rotate about the the vector (1, 2, 3)
	glColor3f(0,1,0);
	if (wireframe == true){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else if (wireframe == false){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
		
	glutSolidSphere( 1.2, 20.0, 20.0); 

	glPopMatrix();

	//Left Hand
	glPushMatrix(); //Save the current state of transformations

	glTranslatef(4.0f, _armY, _armZ); //-(_angle/9)
	glRotatef(0.0f, 1000.0f, 100.0f, 0.0f); //Rotate about the the vector (1, 2, 3)
	glColor3f(0,1,0);
	if (wireframe == true){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else if (wireframe == false){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
		
	glutSolidSphere( 1.2, 20.0, 20.0); 

	glPopMatrix();

	//test Hand
	glPushMatrix(); //Save the current state of transformations

	glTranslatef(6.0f, 0.0f, -22.0f); //-(_angle/9)
	glRotatef(_angle, 6.0f, 10.0f, -22.0f); //Rotate about the the vector (1, 2, 3)
	glColor3f(0,1,0);
	if (wireframe == true){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else if (wireframe == false){
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
		
	glutSolidSphere( 1.2, 20.0, 20.0); 

	glPopMatrix();
		
		
	
	glutSwapBuffers();
}

void update(int value) {
	//_cameraAngle +=1.0f;
	if (direction==true && _angle > 0.0f){
		_angle += -5.0f;
	} else if (direction==false && _angle < 90.0f){
		_angle += 5.0f;
	} else {
		_angle =0.0f;
	}
	
	if (raiseLegs == true && _legAngle > 40.0f){
		_legAngleChange = -5.0f;
		_footZaxis = 0.766f;
		_footYaxis = 0.3f;
	} else if (raiseLegs == false && _legAngle < 90.0f){
		_legAngleChange = 5.0f;
		_footZaxis = -0.766f;
		_footYaxis = -0.3f;
	} else {
		_legAngleChange = 0.0f;
		_footZaxis = 0.0f;
		_footYaxis = 0.0f;
	}

	if (raiseArms == true && _armAngle > 0.0f){
		_armAngleChange = -5.0f;
		_armZaxis = 0.34f;
		_armYaxis = 0.34f;
	} else if (raiseArms == false && _armAngle < 90.0f){
		_armAngleChange = 5.0f;
		_armZaxis = -0.34f;
		_armYaxis = -0.34f;
	} else {
		_armAngleChange = 0.0f;
		_armZaxis = 0.0f;
		_armYaxis = 0.0f;
	}

	
	glutPostRedisplay(); //Tell GLUT that the display has changed
	
	//Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(25, update, 0);
}

int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	
	//Create the window
	glutCreateWindow("Simon Page Robot Coursework");
	initRendering();
	
	//Set handler functions
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	
	glutTimerFunc(25, update, 0); //Add a timer
	
	glutMainLoop();
	return 0;
}
