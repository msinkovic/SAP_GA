#include "Point2D.h"
#include <cmath>

Point2D::Point2D()
{
	X = 0;
	Y = 0;
}


Point2D::Point2D(const int x, const int y)
{
	this->X = x;
	this->Y = y;
}


Point2D::~Point2D()
{
}


double Point2D::distanceToPoint(const Point2D &point) const
{
	return std::sqrt(pow((point.X - this->X), 2.) + pow((point.Y - this->Y), 2.));
}


int Point2D::manhattanDistanceToPoint(const Point2D &point) const
{
	return abs(point.X - this->X) + abs(point.Y - this->X);
}


Point2D Point2D::operator+(const Point2D& otherPoint) const
{
	Point2D newPoint;
	newPoint.X = this->X + otherPoint.X;
	newPoint.Y = this->Y + otherPoint.Y;

	return newPoint;
}


Point2D Point2D::operator-(const Point2D& otherPoint) const
{
	Point2D newPoint;
	newPoint.X = this->X - otherPoint.X;
	newPoint.Y = this->Y - otherPoint.Y;

	return newPoint;
}


Point2D Point2D::operator*(const Point2D& otherPoint) const
{
	Point2D newPoint;
	newPoint.X = this->X * otherPoint.X;
	newPoint.Y = this->Y * otherPoint.Y;

	return newPoint;
}


Point2D Point2D::operator*(const int multiplier) const
{
	Point2D newPoint;
	newPoint.X = this->X * multiplier;
	newPoint.Y = this->Y * multiplier;

	return newPoint;
}


bool Point2D::operator==(const Point2D& otherPoint) const
{
	bool equal = this->X == otherPoint.X;
	equal = equal && (this->Y == otherPoint.Y);

	return equal;
}


bool Point2D::operator!=(const Point2D& otherPoint) const
{
	return !(*this == otherPoint);
}


//	Converts orientation to point one unit apart from origin in specified orientation  
Point2D Point2D::orientationToPoint(const Orientation orientation)
{
	switch (orientation)
	{
	case Orientation::N:
		return Point2D(0, 1);
	case Orientation::NE:
		return Point2D(1, 1);
	case Orientation::NW:
		return Point2D(-1, 1);
	case Orientation::S:
		return Point2D(0, -1);
	case Orientation::SE:
		return Point2D(1, -1);
	case Orientation::SW:
		return Point2D(-1, -1);
	case Orientation::E:
		return Point2D(1, 0);
	case Orientation::W:
		return Point2D(-1, 0);
	default:
		return Point2D();
	}
}



bool operator<(const Point2D& a, const Point2D& b)
{
	if (a.X < b.X) {
		return true;
	}
	else if (a.X == b.X) {
		if (a.Y < b.Y) {
			return true;
		}
	}

	return false;
}

std::ostream& operator<<(std::ostream& out, const Point2D& point)
{
	out << "(" << point.X << "," << point.Y << ")";
	return out;
}