#include "pch.h"

#include "CCone.h"

CCone::CCone(const double density, const double radius, const double height)
	: CSolidBody("Conus", density)
	, m_radius(radius)
	, m_height(height)
{
}

double CCone::GetRadius() const
{
	return m_radius;
}

double CCone::GetHeight() const
{
	return m_height;
}

double CCone::GetVolume() const
{
	return pow(GetRadius(), 2) * M_PI * GetHeight() / 3;
}

void CCone::AppendProperties(std::ostream& out) const 
{
	out << "radius = " << GetRadius() << '\n';
	out << "height = " << GetHeight() << '\n';
}
