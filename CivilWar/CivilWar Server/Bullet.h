#pragma once

#include "Types.h"

class Bullet
{
public:
	Bullet(Point center, Radius radius, DirectionX dirX, DirectionY dirY, Speed speedX, Speed speedY);
	~Bullet();


	Point getCenter() const { return m_center; }
	float getX() const { return m_center.x; }
	float getY() const { return m_center.y; }
	Radius getRadius() const { return m_radius; }
	DirectionX getDirectionX() const { return m_dirX; }
	DirectionY getDirectionY() const { return m_dirY; }
	Speed getSpeedX() const { return m_speedX; }
	Speed getSpeedY() const { return m_speedY; }

	void setCenter(Point center) { m_center = center; }
	void setX(float x) { m_center.x = x; }
	void setY(float y) { m_center.y = y; }
	void setRadius(Radius radius) { m_radius = radius; }
	void setDirectionX(DirectionX dirX) { m_dirX = dirX; }
	void setDirectionY(DirectionY dirY) { m_dirY = dirY; }
	void setSpeedX(Speed speedX) { m_speedX = speedX; }
	void setSpeedY(Speed speedY) { m_speedY = speedY; }

private:
	// variables
	Point m_center;
	Radius m_radius;
	DirectionX m_dirX;
	DirectionY m_dirY;
	Speed m_speedX;
	Speed m_speedY;
};
