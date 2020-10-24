//Jeff Chastine
#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include <GL\glut.h>



// load game object libraries
#include "Entity.h"
#include "Projectile.h"
#include "Platform.h"
#include "Enemy.h"

using namespace std;


// window dimensions
int windowWidth = 800;
int windowHeight = 600;
float aspect = windowWidth / windowHeight;
float xCoordMax = ((float)windowWidth / (float) windowHeight) * 1.0;
float xCoordMin = ((float)windowWidth / (float) windowHeight) * -1.0;
float yCoordMax = 1.0f;
float yCoordMin = -1.0f;




// user interaction variables
bool keys[256];
bool jumpKeyPressed = false;
bool isShooting = false;
bool isLeft = false;
bool isJumping = false;
bool onGround = true;
bool onFloor = true;
bool falling = false;
bool leftPlat = false;
bool rightPlat = false;

// menu variables
bool startGame = false;
bool onMenu = true;
bool options = false;
bool onExit = false;
bool gameOver = false;
float arrowYPos = 0.3f;
float arrowXPos = 0.5f;
int menuIndex = 0;




// world constants
const float gAccel = 0.006f;
const float maxXAccel = 0.004f;
const int maxBullets = 10;
float worldWidth = 4.0f;
float worldHeight = 2.0f;

float ySpeed = 0.0f;
float xAccel = 0.0f;
float xAccelP = 0.0f;
float r = 0.0f;

// timing
int refresh = 1; // in ms

// create entities
Entity mainPlayer(-0.5f, (yCoordMin + 0.1f), 0.00025f, 0.1f, 0.2f);
Enemy e1(0.0f, -0.4f, 0.00025f, 0.2f, 0.2f);
int mainPlayerHealth = 3;



Projectile mainPlayerProjectile(0.0f, 0.0f, 0.005f, 0.025f, 0.025f, 1);
Platform ground(worldWidth - xCoordMin, 0.1f, xCoordMin, yCoordMin);
Platform platform1(0.5f, 0.1f, 0.0f, -0.6f); // first platform (width, height, xstart, ystart)
Platform platform2(0.8f, 0.1f, -1.0f, -0.1f);
Platform platform3(0.4f, 0.1f, 0.2f, 0.3f); 
Platform platform4(0.5f, 0.1f, -0.7f, 0.8f);
Platform platform7(0.5f, 0.1f, -0.3f, 1.2f);
Platform platform5(0.2f, 0.5f, 1.0f, yCoordMin + 0.1f);
Platform lava(1.8f, 0.1f, 1.2f, yCoordMin + 0.1f);
Platform movingPlatform(0.2f, 0.1f, 1.2f, yCoordMin + 0.5f);
Platform platform8(0.3f, 0.1f, 2.05f, yCoordMin + 0.5f);
Platform platform9(0.2f, 0.1f, 2.6f, yCoordMin + 0.5f);
Platform platform10(1.0f, 0.5f, 3.0f, yCoordMin + 0.1f);


static Projectile projectiles[maxBullets];




vector<Platform> platforms;
vector<Entity> entities;







// handle resizing
void reshape(GLsizei width, GLsizei height) {

	// ensure that when I resize the window that the aspect ratio is maintained
	// for when the clipping area gets mapped to the viewport

	GLfloat aspectRatio = (float)width / (float)height;

	windowWidth = width;
	windowHeight = height;


	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width >= height) {
		gluOrtho2D(-1.0 * aspectRatio, 1.0 * aspectRatio, -1.0, 1.0);
		xCoordMin = -1.0 * aspectRatio;
		xCoordMax = 1.0 * aspectRatio;
		yCoordMax = 1.0;
		yCoordMin = -1.0;
	}
	else {
		gluOrtho2D(-1.0, 1.0, -1.0 / aspectRatio, 1.0 / aspectRatio);
		xCoordMin = -1.0;
		xCoordMax = 1.0;
		yCoordMax = 1.0 / aspectRatio;
		yCoordMin = -1.0 / aspectRatio;
	}


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

// timer function
void Timer(int value) {
	/* HANDLE SHOOTING */
	if (isShooting == true) {

		for (int i = 0; i < maxBullets; i++) {
			float projectilePosX = mainPlayer.getPosX();
			float projectilePosY = mainPlayer.getPosY() + 0.1f;

			if (projectiles[i].getOnScreen() == false) {

				if (isLeft) {
					projectiles[i].setLeft(true);
					projectilePosX -= 0.1f;
				}
				else {
					projectiles[i].setLeft(false);
					projectilePosX += 0.1f;
				}
				
				projectiles[i].setSpeed(0.005f);
				projectiles[i].setHeight(0.025f);
				projectiles[i].setWidth(0.025f);
				projectiles[i].setPosX(projectilePosX);
				projectiles[i].setPosY(projectilePosY);
				projectiles[i].setAccel(0.001f);
				projectiles[i].setOnScreen(true);
				break;
			}
		}
		isShooting = false;
		isLeft = false;
	}


	for (int i = 0; i < maxBullets; i++) {
		if (projectiles[i].getOnScreen()) {
			if(projectiles[i].getLeft())
				projectiles[i].setPosX(projectiles[i].getPosX() - projectiles[i].getSpeed());
			else
				projectiles[i].setPosX(projectiles[i].getPosX() + projectiles[i].getSpeed());
		}
		if (projectiles[i].getPosX() > xCoordMax || projectiles[i].getPosX() < xCoordMin)
			projectiles[i].setOnScreen(false);
	}



	glutPostRedisplay();
	glutTimerFunc(refresh, Timer, value);
}




void changeViewPort(int w, int h) {
	glViewport(0, 0, w, h);
}



void initGL() {
	platforms.push_back(platform1);
	platforms.push_back(platform2);
	platforms.push_back(platform3);
	platforms.push_back(platform4);
	platforms.push_back(platform5);
	platforms.push_back(platform7);
	platforms.push_back(lava);
	platforms.push_back(movingPlatform);
	platforms.push_back(platform8);
	platforms.push_back(platform9);
	platforms.push_back(platform10);
	entities.push_back(mainPlayer);

	glClearColor(0.0, 0.0, 0.0, 1.0);

}


// detect collision - Crossing Number Algorithm
bool isCollision(float pointX, float pointY, vector<float> shape) {
	int noOfPoints = shape.size() - 3;
	int count = 0;

	for (int i = 0; i < noOfPoints; i++) {

		if ((shape[i + 1] <= pointY) && (shape[i + 3] > pointY) ||
			(shape[i + 1] > pointY) && (shape[i + 3] <= pointY)) {

			float vt = (float)(pointY - shape[i + 1] / shape[i + 3] - shape[i + 1]);
			if (pointX < shape[i] + vt * (shape[i + 2] - shape[i]))
				++count;
		}

	}

	return (count % 2 == 0);
}


/*COLLISION FUNCTIONS*/

bool farAway(float x1, float y1, float x2, float y2) {





	return sqrt((((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)))) < (x2 - x1) + (y2 + y1);
} 

bool canCollide(Entity e, Platform p) {

	float entityRadius, platformRadius;
	float squareCentreX = (e.getCenterPosX() - p.getCenterPosX()) * (e.getCenterPosX() - p.getCenterPosX());
	float squareCentreY = (e.getCenterPosY() - p.getCenterPosY()) * (e.getCenterPosY() - p.getCenterPosY());

	
	if (e.getWidth() >= e.getHeight()) {
		entityRadius = e.getWidth();
	}
	else {
		entityRadius = e.getHeight();
	}


	if (p.getWidth() >= p.getHeight())
		platformRadius = p.getWidth();
	else
		platformRadius = p.getHeight();
		




	cout << "Platform radius " << platformRadius << " entity radius" << entityRadius << endl;
	cout << "Platform center x by y " << p.getCenterPosX() << " x " << p.getCenterPosY() << " entity center x by y " << e.getCenterPosX() << " x " << e.getCenterPosY() << endl;


	return ((entityRadius) + (platformRadius)) > squareCentreX + squareCentreY;

}
bool AABB(Entity& mainPlayer, Platform& p1) {

	float min1X = mainPlayer.getPosX();
	float min1Y = mainPlayer.getPosY();
	float max1X = mainPlayer.getPosX() + mainPlayer.getWidth();
	float max1Y = mainPlayer.getPosY() + mainPlayer.getHeight();
	float min2X = p1.getXStart();
	float min2Y = p1.getYStart();
	float max2X = p1.getXStart() + p1.getWidth();
	float max2Y = p1.getYStart() + p1.getHeight();


	float d1x = min2X - max1X;
	float d1y = min2Y - max1Y;
	float d2x = min1X - max2X;
	float d2y = min1Y - max2Y;

	if (d1x > 0.0f || d1y > 0.0f || d2x > 0.0f || d2y > 0.0f) {
		return false;
	}


	return true;
}
bool AABBPlat(Platform& mainPlayer, Platform& p1) {
	float min1X = mainPlayer.getXStart();
	float min1Y = mainPlayer.getYStart();
	float max1X = mainPlayer.getXStart() + mainPlayer.getWidth();
	float max1Y = mainPlayer.getYStart() + mainPlayer.getHeight();
	float min2X = p1.getXStart();
	float min2Y = p1.getYStart();
	float max2X = p1.getXStart() + p1.getWidth();
	float max2Y = p1.getYStart() + p1.getHeight();


	float d1x = min2X - max1X;
	float d1y = min2Y - max1Y;
	float d2x = min1X - max2X;
	float d2y = min1Y - max2Y;

	if (d1x > 0.0f || d1y > 0.0f || d2x > 0.0f || d2y > 0.0f) {
		return false;
	}


	return true;
}

// collision response

void collisionResponse(Entity& mainPlayer, Platform& p1) {
	cout << "Mainplayer x: " << mainPlayer.getPosX() << " platform x: " << p1.getXStart() << endl;
	cout << "Mainplayer y: " << mainPlayer.getPosY() << " platform y: " << p1.getYStart() << endl;
	
	float diffX = (mainPlayer.getPosX() + mainPlayer.getWidth()) - p1.getXStart();
	float diffY = (mainPlayer.getPosY() + mainPlayer.getHeight()) - p1.getYStart();


	float rightSideX = mainPlayer.getPosX() + mainPlayer.getWidth();
	float leftSideX = mainPlayer.getPosX();
	float upSide = mainPlayer.getPosY() + mainPlayer.getHeight();
	float downSide = mainPlayer.getPosY();


	float platformLeft = p1.getXStart();
	float platformRight = p1.getXStart() + p1.getWidth();
	float platformUp = p1.getYStart() + p1.getHeight();
	float platformDown = p1.getYStart();


	// rigth
	if (leftSideX < platformRight && rightSideX > platformRight + 0.95 * mainPlayer.getWidth()) {
		mainPlayer.setPosX(p1.getXStart() + p1.getWidth());
		ySpeed = 0;
	}
	// left
	if (leftSideX < platformLeft - 0.8 * mainPlayer.getWidth() && rightSideX > platformLeft) {
		mainPlayer.setPosX(p1.getXStart() - mainPlayer.getWidth());
		ySpeed = 0;
	}

	// down
	if (upSide > platformDown && downSide < platformDown - 0.9 * mainPlayer.getHeight()) {
		mainPlayer.setPosY(p1.getYStart() - mainPlayer.getHeight());
		ySpeed = 0;
	}

	// up
	if (downSide < platformUp  && downSide > platformDown && upSide >= platformUp + 0.95 * mainPlayer.getHeight()) {
		mainPlayer.setPosY(p1.getYStart() + p1.getHeight());
		ySpeed = 0.0;
		onGround = true;
	}



	// new test
	/*

	// COL TEST LEFT
	cout << "MAIN PLAYER Y POS" << upSide << p1.getYStart() + p1.getHeight() + mainPlayer.getHeight() << endl;
	if (rightSideX > p1.getXStart() && leftSideX < p1.getXStart()
		&& upSide < (p1.getYStart() + p1.getHeight()) && upSide > p1.getYStart() &&
		downSide > p1.getYStart() && downSide < p1.getYStart() + p1.getHeight()) {
		mainPlayer.setPosX(p1.getXStart() - mainPlayer.getWidth() - 0.001f);
		ySpeed = 0.0;
		leftPlat = true;
	}


	// COL TEST RIGHT
	// leftSideX < (p1.getXStart() + p1.getWidth())
	else if (rightSideX >(p1.getXStart() + p1.getWidth()) &&  leftSideX < (p1.getXStart() + p1.getWidth()) && upSide < (p1.getYStart() + p1.getHeight() + mainPlayer.getHeight()) && 
		downSide > p1.getYStart() - mainPlayer.getHeight() && downSide < p1.getYStart() + p1.getHeight()) {

		mainPlayer.setPosX(p1.getXStart() + p1.getWidth());

		ySpeed = 0.0;
		rightPlat = true;
		
	}


	// COL TEST BOTTOM

	else if (upSide > p1.getYStart() && downSide < p1.getYStart() &&
		rightSideX > p1.getXStart() && leftSideX < (p1.getXStart() + p1.getWidth()) && rightPlat == false) {

		mainPlayer.setPosY(p1.getYStart() - mainPlayer.getHeight());
		ySpeed = 0.0;
	}




	// COL TEST TOP
	else if (downSide < (p1.getYStart() + p1.getHeight()) && leftSideX < (p1.getXStart() + p1.getWidth()) &&
		 upSide > (p1.getYStart() + p1.getHeight()) && (leftSideX > p1.getXStart() || rightSideX > p1.getXStart()) && rightPlat == false) {
		mainPlayer.setPosY(p1.getYStart() + p1.getHeight());
		ySpeed = 0.0;
		onGround = true;
		cout << "UPUPUPUPUPUPUPUPUPUPUPUP" << endl;
	}
	

	 */
	/*

	//cout << "Collision response: diffX: " << diffX << endl;
	//cout << "Collision response: diffY: " << diffY << endl;
	if (diffX < 0) {
		cout << "LEFT " << endl;
		ySpeed = 0.00f;
		mainPlayer.setPosX(diffX - mainPlayer.getWidth());
	}

	else if ((mainPlayer.getPosX() - (p1.getXStart() + p1.getWidth()) >= 0)) {



		mainPlayer.setPosX(p1.getWidth() - diffX);
		ySpeed = 0.00f;
		cout << "RIGHT" << endl;
	}
	// mainPlayer.getPosY() - p1.getYStart() > (p1.getYStart() + p1.getHeight() - mainPlayer.getPosY())
	 else if ((p1.getHeight()+p1.getYStart() > mainPlayer.getPosY()) && 
			  (mainPlayer.getPosY() + mainPlayer.getHeight()) > p1.getYStart() + p1.getHeight()) { // 
		mainPlayer.setPosY((mainPlayer.getPosY() + ((p1.getYStart() + p1.getHeight()) - mainPlayer.getPosY())));


		ySpeed = 0.0f;
		onGround = true;
		
	//cout << "Platform height: " << p1.getHeight() << endl;
		//cout << "Platform y pos: " << p1.getYStart() + p1.getHeight() << endl;
		//cout << "Player y pos: " << mainPlayer.getPosY() << endl;

	}
	*/

}

bool platformCheck(vector<Platform> platforms) {
	for (int i = 0; i < platforms.size(); i++) {
		//cout << "platform " << i << " has player " << platforms[i].getHasPlayer() << endl;
		if (platforms[i].getHasPlayer())
			return true;
	}


	return false;
}

void collisionChecks(Entity& mainPlayer, vector<Platform> platforms) {
	for (int i = 0; i < platforms.size(); i++) {

//		cout << "coll check!" << endl;

		//if (canCollide(mainPlayer, platforms[i])) {
			if (AABB(mainPlayer, platforms[i])) {
				//cout << "Collision with " << i << endl;


				collisionResponse(mainPlayer, platforms[i]);
				isJumping = false;
				platforms[i].setHasPlayer(true);
				//cout << "Player pos after collision: " << mainPlayer.getPosX() << " and y: " << mainPlayer.getPosY() << endl;

				if (i == 6)
					gameOver = true;

				if (i == 7) {
					cout << "this is the moving platform" << endl;
					cout << "move platform x: " << platforms[i].getXStart() << " y: " << platforms[i].getYStart() << endl;
				}
			}
			else {
				platforms[i].setHasPlayer(false);
			}

			if (!platformCheck(platforms)) {
				//cout << "DID NOT COLLIDE SO FALLING fopr platform " << i << endl;
				onGround = false;
			}
		//}
	}
}
void collisionChecksEnemy(Entity& e1, vector<Platform> platforms) {
	for (int i = 0; i < platforms.size(); i++) {


		if (!(farAway(e1.getCenterPosX(), e1.getCenterPosY(), platforms[i].getCenterPosX(), platforms[i].getCenterPosY()))) {
			if (AABB(e1, platforms[i])) {
				collisionResponse(e1, platforms[i]);
			
			}
			else {
				e1.setPosY(e1.getPosY() - e1.getSpeed());
			}
		}
	}
}


// platform against platform

/* END COLLISION FUNCTIONS */


/* DRAWING FUNCTIONS */
// player entity
void drawEntity(float X, float Y, float width, float height) {
	glBegin(GL_POLYGON);
		glVertex2f(X, Y);
		glVertex2f(X, Y + height);
		glVertex2f(X + width, Y + height);
		glVertex2f(X + width, Y);
	glEnd();
}
void drawArrow(float X, float Y, float width, float height) {
	glPushMatrix();
		glTranslatef(X, Y, 0);
		glRotatef(90, 0.0f, 0.0f, 1.0f);
		glTranslatef(-X, -Y, 0);
		glBegin(GL_POLYGON);
			glVertex2f(X, Y);
			glVertex2f(X + width, Y + height);
			glVertex2f(X + 2 * width, Y);
		glEnd();
		glBegin(GL_POLYGON);
			glVertex2f(X + width / 2, Y);
			glVertex2f(X + width / 2, Y - height);
			glVertex2f(X + width + width/2, Y - height);
			glVertex2f(X + width + width/2, Y);
		glEnd();
	glPopMatrix();
}



// FONT draw
void text(const char *string) {
	glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char*) string);
}
/* END DRAWING FUNCTIONS */
void keyboard(unsigned char key, int x, int y) {
	cout << (int)key;
	keys[(int)key] = true;


	
	switch (key) {
		case 32:

		break;
		case 'z':
			isLeft = true;
			isShooting = true;
		break;
		case 'x':
			isLeft = false;
			isShooting = true;
		break;
		case 'i':
			cout << "Window Dimensions: " << xCoordMax << " x " << yCoordMax << endl;
			cout << "Window min: " << xCoordMin << " x " << yCoordMin << endl;
			cout << " PLATFORM DATA: " << endl;
			for (int i = 0; i < platform1.getPoints().size(); i++) {
				cout << platform1.getPoints()[i] << endl;
			}
			cout << "END PLATFORM DATA" << endl;
		break;

		case 13: // enter key for menu navigation
			

		break;
	}
}
void keyboardRelease(unsigned char key, int x, int y) {
	keys[(int)key] = false;

	switch (key) {
	case 'z':
	case 'x':
		isShooting = false;
		break;
	}
}
void input(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_RIGHT: // moving right
			keys[key] = true;
		break;
		case GLUT_KEY_LEFT: // moving left

			keys[key] = true;

		break;

		
		case GLUT_KEY_DOWN: // menu navigate
			if (onMenu || options) {
				keys[key] = true;
			}
		break;
		case GLUT_KEY_UP: // menu navigate
			if (onMenu || options) {
				keys[key] = true;
			}
		break;


	}

}

void inputRelease(int key, int x, int y) {
	keys[key] = false;

}




// handles events and drawing objects
void render(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();



	/*EXIT*/
	if (onExit) {
		exit(0);
	}
	/* END EXIT */

	/* OPTIONS */
	if (options) {
		glColor3f(0.0f, 1.0f, 0.0f);
		drawArrow(arrowXPos, arrowYPos, 0.1f, 0.3f);
		drawEntity(-0.6f, 0.3f, 0.6f, 0.2f);
		drawEntity(-0.6f, -0.1f, 0.6f, 0.2f);
		drawEntity(-0.6f, -0.5f, 0.6f, 0.2f);
		if (keys[GLUT_KEY_DOWN] && menuIndex < 2) {
			arrowYPos -= 0.4f;
			menuIndex++;
			cout << "Options index: " << menuIndex << endl;
			keys[GLUT_KEY_DOWN] = false;
		}
		else if (keys[GLUT_KEY_UP] && menuIndex > 0) {
			arrowYPos += 0.4f;
			menuIndex--;
			cout << "Options index: " << menuIndex << endl;
			keys[GLUT_KEY_UP] = false;
		}
		if (keys[13]) {
			keys[13] = false;

			switch (menuIndex) {
			case 0: // change resolution

				break;

			case 1: // file path for score

				break;

			case 2: // back
				onMenu = true;
				options = false;
				menuIndex = 0;
				arrowYPos = 0.3f;
				cout << startGame << endl;
				break;




			}
		}
	}

	/* END OPTIONS */


	/* MENU */

	if (onMenu) {
		
		glColor3f(0.0f, 0.0f, 1.0f);
		drawArrow(arrowXPos, arrowYPos, 0.1f, 0.3f);

		// menu items
		drawEntity(-0.6f, 0.3f, 0.6f, 0.2f);
		drawEntity(-0.6f, -0.1f, 0.6f, 0.2f);
		drawEntity(-0.6f, -0.5f, 0.6f, 0.2f);


		// draw fonts
	




		if (keys[GLUT_KEY_DOWN] && menuIndex < 2) {
			arrowYPos -= 0.4f;
			menuIndex++;
			cout << "Menu index: " << menuIndex << endl;
			keys[GLUT_KEY_DOWN] = false;
		}
		else if (keys[GLUT_KEY_UP] && menuIndex > 0) {
			arrowYPos += 0.4f;
			menuIndex--;
			cout << "Menu index: " << menuIndex << endl;
			keys[GLUT_KEY_UP] = false;
		}

		// menu navigation
		if (keys[13]) {
			keys[13] = false;
			switch (menuIndex) {
				case 0: // start game
					startGame = true;
					cout << "START GAME" << endl;
					onMenu = false;
					menuIndex = 0;
				break;

				case 1: // options
					options = true;
					arrowYPos = 0.3f;
					cout << "OPTIONS" << endl;
					onMenu = false;
					menuIndex = 0;
				break;

				case 2: // exit
					onExit = true;
					cout << "EXIT" << endl;
					onMenu = false;
					menuIndex = 0;
				break;


			}
		}


	}






	/* END MENU */


	// game started
	if (startGame) {


		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		float distBetweenGround = mainPlayer.getPosY() - ground.getYStart();

		float top = 1.0;
		float left = mainPlayer.getPosX() - (2.0 * aspect / 2.0);
		float right = left + 2.0;
		float bottom = -1.0;

		cout << rightPlat << " is right plat " << endl;


		if (mainPlayer.getPosX() < xCoordMin)
			mainPlayer.setPosX(xCoordMin);
		if (mainPlayer.getPosX() + mainPlayer.getWidth() > worldWidth)
			mainPlayer.setPosX(worldWidth - mainPlayer.getWidth());
		

		

		

		if (mainPlayer.getPosY() > 0.0f) {
			top = mainPlayer.getPosY() + (2.0 / 2.0);
			bottom = top - 2.0;
		}


		

		if(windowWidth >= windowHeight)
			gluOrtho2D(left , right, bottom, top);
		else
			gluOrtho2D(left, right, bottom,top);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// draw entities
		drawEntity(mainPlayer.getPosX(), mainPlayer.getPosY(), mainPlayer.getWidth(), mainPlayer.getHeight());


		// draw projectiles
		for (int i = 0; i < maxBullets; i++) {
			if (projectiles[i].getOnScreen() == true) {
				drawEntity(projectiles[i].getPosX(), projectiles[i].getPosY(), projectiles[i].getWidth(), projectiles[i].getHeight());
			}
		}


		// draw platforms
		glColor3f(0.0f, 1.0f, 0.5f);

		drawEntity(ground.getXStart(), ground.getYStart(), ground.getWidth(), ground.getHeight()); // draw ground
		drawEntity(platform1.getXStart(), platform1.getYStart(), platform1.getWidth(), platform1.getHeight()); // p0
		drawEntity(platform2.getXStart(), platform2.getYStart(), platform2.getWidth(), platform2.getHeight()); // p1
		drawEntity(platform3.getXStart(), platform3.getYStart(), platform3.getWidth(), platform3.getHeight()); // p2
		drawEntity(platform4.getXStart(), platform4.getYStart(), platform4.getWidth(), platform4.getHeight()); // p3
		drawEntity(platform5.getXStart(), platform5.getYStart(), platform5.getWidth(), platform5.getHeight()); // p3
		drawEntity(platform7.getXStart(), platform7.getYStart(), platform7.getWidth(), platform7.getHeight()); // p7
		drawEntity(platform8.getXStart(), platform8.getYStart(), platform8.getWidth(), platform8.getHeight()); // p7
		drawEntity(platform9.getXStart(), platform9.getYStart(), platform9.getWidth(), platform9.getHeight()); // p7
		glPushMatrix();
		glLoadIdentity();
		glColor3f(0.0f, 0.0f, 1.0f);
		drawEntity(platforms[7].getXStart(), platforms[7].getYStart(), platforms[7].getWidth(), platforms[7].getHeight()); // p7
		glLoadIdentity();
		glPopMatrix();
		drawEntity(platform10.getXStart(), platform10.getYStart(), platform10.getWidth(), platform10.getHeight()); // p7




		glPushMatrix();
		glLoadIdentity();
		glColor3f(1.0f, 0.0f, 0.0f);
		drawEntity(lava.getXStart(), lava.getYStart(), lava.getWidth(), lava.getHeight()); // p7
		glLoadIdentity();
		glPopMatrix();


		/* PLAYER MOVEMENT HANDLING */
		// handling movement
		// right
		if (keys[GLUT_KEY_RIGHT] && xAccel == 0) {
			xAccel = 0.0005 * (xCoordMax - xCoordMin);

		}
		if (xAccel != 0 && keys[GLUT_KEY_RIGHT] && xAccel < maxXAccel) {
			xAccel += mainPlayer.getSpeed();
		}
		if (xAccel != 0 && keys[GLUT_KEY_RIGHT]) {
			mainPlayer.setPosX(mainPlayer.getPosX() + xAccel);
		}
		// left
		if (keys[GLUT_KEY_LEFT] && xAccel == 0) {
			xAccel = 0.0005 * (xCoordMax - xCoordMin);
		}
		if (xAccel != 0 && keys[GLUT_KEY_LEFT] && xAccel < maxXAccel) {
			xAccel += mainPlayer.getSpeed();
		}
		if (xAccel != 0 && keys[GLUT_KEY_LEFT]) {
			mainPlayer.setPosX(mainPlayer.getPosX() - xAccel);
		}

		/*
		if (!(farAway(mainPlayer.getCenterPosX(), mainPlayer.getCenterPosY(), platform1.getCenterPosX(), platform1.getCenterPosY()))) {


			if (AABB(mainPlayer, platform1)) {

				collisionResponse(mainPlayer, platform1);

				cout << "COLLISION!" << endl;
				isJumping = false;

				ySpeed = 0.01f;
			}

		} */
		//cout << "POS BEFORE Y: " << mainPlayer.getPosY() << endl;




		// if collide with left, move right
		if (AABBPlat(platforms[7], platform5)) {
			platforms[7].setSpeed(0.0012f);
		}
		else if (AABBPlat(platforms[7], platform8)) {
			platforms[7].setSpeed(-0.0012f);
		}
		if (AABB(mainPlayer, platforms[7])) {
			mainPlayer.setPosX(platforms[7].getSpeed() + mainPlayer.getPosX());
		}


		//collisionChecksEnemy(e1, platforms);



		if (mainPlayer.getPosY() < (ground.getHeight() + ground.getYStart())) {
			cout << mainPlayer.getPosY() << endl;
			cout << "in ground " << endl;
			cout << ground.getHeight() + ground.getYStart() << endl;
			mainPlayer.setPosY((yCoordMin + 0.1f));
			cout << mainPlayer.getPosY() << endl;
			cout << (mainPlayer.getPosY() < (ground.getHeight() + ground.getYStart())) << endl;
			isJumping = false;
			onGround = true;
			onFloor = true;
			ySpeed = 0;
		}


		/*
		cout << "On ground: " << onGround << endl;
		cout << "Is jumping: " << isJumping << endl;
		cout << "y speed: " << ySpeed << endl;
		cout << "POS AFTER Y: " << mainPlayer.getPosY() << endl;
		*/
		// HANDLE JUMPING
		

		/*
		if (keys[32] && isJumping == false && (onGround == true || onFloor == true)) {
			ySpeed = 0.01f;
			isJumping = true;
			onGround = false;
			onFloor = false;
			cout << "Jump hit " << endl;
			keys[32] = false;
		}  */


		if(keys[32] && isJumping == false && !falling) {
			isJumping = true;
			falling = false;
			keys[32] = false;
		}

		if (falling) {
			rightPlat = false;
			leftPlat = false;
		}



		if (onGround && !isJumping) {
			ySpeed = 0.0f;
			falling = false;
		}

		if (onGround && isJumping) {
			ySpeed = 0.001f;
			onGround = false;
		}

		if (!onGround && isJumping) {
			if (ySpeed == 0)
				ySpeed = 0.001f;
			if (ySpeed < 0.01f && !falling)
				ySpeed += 0.005f;
			else {
				ySpeed -= 0.00012f;
				falling = true;
			}
		}


		if (!isJumping && !onGround) {
			ySpeed -= 0.0001f;
			falling = true;
		}


		//cout << "is jumping " << isJumping << " onGround " << onGround <<  "falling " << falling << " yspeed " << ySpeed << endl;



		mainPlayer.setPosY(mainPlayer.getPosY() + ySpeed);
		platforms[7].setXStart(platforms[7].getXStart() + platforms[7].getSpeed());
		cout << "level of moving " << platforms[7].getYStart() << " other plats " << platform5.getYStart() + platform5.getHeight() << " " << platform8.getYStart() << endl;
		collisionChecks(mainPlayer, platforms);
		/*

		
		if (!isJumping && ySpeed != 0 && onGround == false) {
			ySpeed -= 0.0001f;
		}
		if (!isJumping && ySpeed != 0 && onGround == false) {
			mainPlayer.setPosY(mainPlayer.getPosY() - ySpeed);
			cout << "falling down" << endl;
		}
		// END COLLIDE 



		if (isJumping && ySpeed != 0 && onGround == false) {
			mainPlayer.setPosY(mainPlayer.getPosY() + ySpeed);
			cout << "going up" << endl;
		}

		if (isJumping && ySpeed != 0 && onGround == false) {
			ySpeed -= 0.00012f;
		}

		if (onGround) {
			ySpeed = 0;
		}
		*/
		if (mainPlayerHealth == 0) {
			mainPlayerHealth = 3;
			gameOver = true;
			startGame = false;

		}

		// handling firing a projectile z = 
		if (keys[122])
			cout << "z pressed";
		/* END PLAYER MOVEMENT HANDLING */
	}


	// GAME OVER
	if (gameOver) {
		drawArrow(arrowXPos, arrowYPos-0.4f, 0.1f, 0.3f);
	}




	glutSwapBuffers();
	glFlush();
}





int main(int argc, char* argv[]) {


	// Initialization of GLUT ---------------------------------------------
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE); // allow double buffering
	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// Set the window size and position the window in the center of the screen
	glutInitWindowSize(800, 600);


	glutInitWindowPosition(((glutGet(GLUT_SCREEN_WIDTH) - windowWidth) / 2), 
							(glutGet(GLUT_SCREEN_HEIGHT) - windowHeight) / 2);

	// Set title of window
	glutCreateWindow("Graphics 1 Game");
	// End of Initialization of GLUT --------------------------------------

	// user interaction
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardRelease);
	glutSpecialFunc(input);
	glutSpecialUpFunc(inputRelease);



	// Bind the two functions (above) to respond when necessary
	glutReshapeFunc(reshape);
	glutDisplayFunc(render);
	glutTimerFunc(0, Timer, 0);
	initGL();



	glutMainLoop();
	return 0;
}