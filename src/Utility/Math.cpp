#include "Math.h"

bool BoundingBox::Collide(const BoundingBox& other) const
{
	return (other.min.x <= this->max.x && other.max.x >= this->min.x)
		&& (other.min.y <= this->max.y && other.max.y >= this->min.y);
}