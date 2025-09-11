#include "Player.h"

#include <GL/gl.h> 

Player::Player(float startX, float startY, float startZ, float playerSize) {
    x = startX;
    y = startY;
    z = startZ;

}
/**
	Return health of player
*/
int Player::getHealth(void)
{
	return health;
}

/**
	Return X location
*/
float Player::getX(void)
{
	return x;
}

/**
	Return y location
*/
float Player::getY(void)
{
	return y;
}
float Player::getZ(void)
{
	return z;
}
void Player::move(float dx, float dy, float dz) {
    x += dx;
    y += dy;
    z += dz;
}

/**
	Start tank moving forward
*/
void Player::startMoving(int x,int y,int z)
{
	moving = true;
}

/**
	Stop tank moving forward
*/
void Player::stopMoving(void)
{
	moving = false;
}

/**
	Player's update function
*/
void Player::update()
{
}

/**
	<Insert obvious comment here>
*/
void Player::draw()
{
	glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glVertex3f(0.0f, 1.0f, 0.0f);
	glEnd();
}
