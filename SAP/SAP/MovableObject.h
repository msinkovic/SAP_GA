#pragma once
#include "Point2D.h"
#include "Orientation.h"

class MovableObject
{
protected:
	Point2D _point;
	Orientation _orientation;
	unsigned int _objectRadius;

public:
	explicit MovableObject();
	explicit MovableObject(const int x, const int y, const Orientation orientation, const unsigned int radius);
	explicit MovableObject(const Point2D point, const Orientation orientation, const unsigned int radius);
	~MovableObject();

	Point2D getLocation() const;
	Orientation getOrientation() const;
	unsigned int getRadius() const;

	void move();
	bool collision(const MovableObject* object) const;
};

