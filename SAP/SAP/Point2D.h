#pragma once
#include "Orientation.h"
#include <iostream>

struct Point2D
{
	explicit Point2D();
	explicit Point2D(const int x, const int y);
	~Point2D();

	double distanceToPoint(const Point2D &point) const;
	int manhattanDistanceToPoint(const Point2D &point) const;

	Point2D operator+(const Point2D& otherPoint) const;
	Point2D operator-(const Point2D& otherPoint) const;
	Point2D operator*(const Point2D& otherPoint) const;
	Point2D operator*(const int multiplier) const;
	bool operator==(const Point2D& otherPoint) const;
	bool operator!=(const Point2D& otherPoint) const;

	static Point2D orientationToPoint(const Orientation orientation);

	int X;
	int Y;
};

bool operator<(const Point2D& a, const Point2D& b);
std::ostream& operator<<(std::ostream& out, const Point2D& point);