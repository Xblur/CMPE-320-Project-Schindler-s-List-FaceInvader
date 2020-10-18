/*
 * bullet.cpp
 *
 *  Created on: Nov. 25, 2019
 *      Author: Chris Gritter
 */
#include "bullet.h"
#include <tuple>

# define M_PI           3.14159265358979323846  /* pi */

using namespace std;

Bullet::Bullet() : x(0), y(0), speed(1), angle(0){}

Bullet::Bullet(float sx, float sy , float spd, float ang){
	x = sx;
	y = sy;
	speed = spd;
	angle = ang;
}

void Bullet::updateBullet(float nx, float ny){
	x = nx;
	y = ny;
}

tuple<float, float> Bullet::bulletMovement(){
	// float xincr, yincr, diagLength;
	// diagLength = sqrt(((x + speed)*(x + speed)) + ((y + speed)*(y + speed)));
	// yincr = sin(angle)*diagLength;
	// xincr = cos(angle)*diagLength;
	// //bool z = 1;
	// //while(z == 1){
	// 	x = x + xincr;
	// 	y = y + yincr;
	// 	updateBullet(x, y);
	// 	cout << "XX: ";
	// 	cout << x << endl;
	// 	cout << "YY: ";
	// 	cout << y << endl;
		/*if(x > 100 || y > 100){
			z = 0;
		}*/

	//}
	float angle_rad = angle * (M_PI / 180);
	// cout << "x before: " << x << endl;
	// cout << "y before: " << y << endl;
	// cout << "angle_deg: " << angle << endl;
	// cout << "angle_rad: " << angle_rad << endl;
	// cout << "cos(angle): " << cos(angle_rad) << endl;
	// cout << "sin(angle): " << sin(angle_rad) << endl;
	
	y = y - cos(angle_rad)*speed;
	x = x + sin(angle_rad)*speed;
	return make_tuple(x,y);

}

float Bullet::getX(){
	return x;
}

float Bullet::getY(){
	return y;
}

float Bullet::getSpd(){
	return speed;
}

float Bullet::getAng(){
	return angle;
}

void Bullet::setX(float nx){
	x = nx;
}
void Bullet::setY(float ny){
	y = ny;
}

void Bullet::setAng(float nang){
	angle = nang;
}
void Bullet::setSpd(float nspd){
	speed = nspd;
}





