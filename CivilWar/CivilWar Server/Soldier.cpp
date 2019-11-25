#include "Soldier.h"

Soldier::Soldier(Point center, Radius radius, Health health, Speed speed) :
	m_center(center),
	m_radius(radius),
	m_health(health),
	m_speed(speed)
{

}



Soldier::~Soldier()
= default;
