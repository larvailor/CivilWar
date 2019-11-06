#pragma once

#include "Types.h"

class Soldier
{
public:
	Soldier(Point center, Radius radius, Health health);
	~Soldier();

	Point getCenter() const { return m_center; }
	Radius getRadius() const { return m_radius; }
	Health getHealth() const { return m_health; }

	void setCenter(Point center) { m_center = center; }
	void setRadius(Radius radius) { m_radius = radius; }
	void setHealth(Health health) { m_health = health; }

private:
	Point m_center;
	Radius m_radius;
	Health m_health;
};
