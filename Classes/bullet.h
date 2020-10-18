/*
 * bullet.h
 *
 *  Created on: Nov. 25, 2019
 *      Author: Chris Gritter
 */

#pragma once

#include <iostream>
#include <istream>
#include <ostream>
#include <fstream>
#include <typeinfo>
#include <string>
#include <ctype.h>
#include <cmath>


using namespace std;

class Bullet{
private:
	float x, y, speed, angle;
public:
	Bullet();
	Bullet(float, float, float, float);
	void updateBullet(float, float);
	tuple<float, float> bulletMovement();
	float getX();
	float getY();
	float getAng();
	float getSpd();
	void setX(float);
	void setY(float);
	void setAng(float);
	void setSpd(float);

};
