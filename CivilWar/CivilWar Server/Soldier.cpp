#include "Soldier.h"

Soldier::Soldier(Point center, Radius radius, Health health) :
	m_center(center),
	m_radius(radius),
	m_health(health)
{

}



Soldier::~Soldier()
= default;
