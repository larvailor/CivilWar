#pragma once

#include "Types.h"

class Soldier
{
public:
	Soldier(Point center, Radius radius, Health health, Speed speed);
	~Soldier();

	Point getCenter() const { return m_center; }
	float getX() const { return m_center.x; }
	float getY() const { return m_center.y; }
	Radius getRadius() const { return m_radius; }
	Health getHealth() const { return m_health; }
	Speed getSpeed() const { return m_speed; }

	void setCenter(Point center) { m_center = center; }
	void setX(float x) { m_center.x = x; }
	void setY(float y) { m_center.y = y; }
	void setRadius(Radius radius) { m_radius = radius; }
	void setHealth(Health health) { m_health = health; }
	void setHealth(Speed speed) { m_speed = speed; }

private:
	Point m_center;
	Radius m_radius;
	Health m_health;
	Speed m_speed;
};
