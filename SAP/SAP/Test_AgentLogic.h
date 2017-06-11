#pragma once
#include "AgentController.h"
class Test_AgentLogic :
	public AgentController
{
	unsigned int number = 0;
	Point2D nextLocation;

	void setNextLocation();

	bool needsToRotate(Orientation a, Orientation b);
	Orientation getOrientationToPoint(Point2D from, Point2D to);

public:
	Test_AgentLogic();
	~Test_AgentLogic();

	Action* getAction() override;
};

