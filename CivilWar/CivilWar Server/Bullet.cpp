#include "Bullet.h"

Bullet::Bullet(Point center, Radius radius, DirectionX dirX, DirectionY dirY, Speed speedX, Speed speedY) :
	m_center(center),
	m_radius(radius),
	m_dirX(dirX),
	m_dirY(dirY),
	m_speedX(speedX),
	m_speedY(speedY)
{

}



Bullet::~Bullet()
= default;
