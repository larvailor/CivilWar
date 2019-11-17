#pragma once

#include "Types.h"

class Bullet
{
public:
	Bullet(Point center, Radius radius, DirectionX dirX, DirectionY dirY, Speed speed);
	~Bullet();


	Point getCenter() const { return m_center; }
	Radius getRadius() const { return m_radius; }
	DirectionX getDirectionX() const { return m_dirX; }
	DirectionY getDirectionY() const { return m_dirY; }
	Speed getSpeed() const { return m_speed; }

	void setCenter(Point center) { m_center = center; }
	void setRadius(Radius radius) { m_radius = radius; }
	void setDirectionX(DirectionX dirX) { m_dirX = dirX; }
	void setDirectionY(DirectionY dirY) { m_dirY = dirY; }
	void setSpeed(Speed speed) { m_speed = speed; }

private:
	// variables
	Point m_center;
	Radius m_radius;
	DirectionX m_dirX;
	DirectionY m_dirY;
	Speed m_speed;



	// methods
};
