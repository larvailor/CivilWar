#include "Bullet.h"

Bullet::Bullet(Point center, Radius radius, DirectionX dirX, DirectionY dirY, Speed speed) :
	m_center(center),
	m_radius(radius),
	m_dirX(dirX),
	m_dirY(dirY),
	m_speed(speed)
{

}



Bullet::~Bullet()
= default;
