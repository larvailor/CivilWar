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



void Bullet::move()
{
	// X direction
	switch (m_dirX) {
	case LEFT:
		m_center.x -= m_speedX;
		break;
	case RIGHT:
		m_center.x += m_speedX;
	case NONE_X:
		break;
	}

	// Y direction
	switch (m_dirY) {
	case UP:
		m_center.y -= m_speedY;
		break;
	case DOWN:
		m_center.y += m_speedY;
	case NONE_Y:
		break;
	}
}
