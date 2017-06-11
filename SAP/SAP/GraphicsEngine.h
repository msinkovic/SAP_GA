#pragma once
#include "GameSimulator.h"
#include "GL\freeglut.h"
#include <cmath>

namespace graphicsEngine
{
	GameState* game = nullptr;
	void initialize();
	void draw();
	void resizeAspectRatio(int, int);
	void stopMainLoop();
	const double math_pi = 3.14159265359;

	struct RGB_Color {
		float red;
		float green;
		float blue;
		float alpha;

		RGB_Color(float r, float g, float b, float a) :red(r), green(g), blue(b), alpha(a) {}
	};

	struct {
		float Circle_LineWidth = 2;
		double Circle_ScaleFactor = 2.;
		unsigned int Circle_MinRadius = 3;
		unsigned int Circle_Resolution = 64;
		RGB_Color Player1_Color = RGB_Color(0.f, 0.7f, 0.2f, 1.f);
		RGB_Color Player2_Color = RGB_Color(0.f, 0.f, 1.f, 1.f);
		RGB_Color Missile_Color = RGB_Color(1.f, 0.f, 0.f, 1.f);
		RGB_Color OrbitalMissile_Color = RGB_Color(1.f, 0.f, 0.f, 1.f);
		RGB_Color PlayArea_Color = RGB_Color(1.f, 1.f, 1.f, 1.f);
		RGB_Color Resource_Color_Gas = RGB_Color(0.f, 0.6f, 1.f, 1.f);
		RGB_Color Resource_Color_Missile = RGB_Color(1.f, 0.6f, 0.f, 1.f);
		RGB_Color Resource_Color_OrbitalMissile = RGB_Color(0.7f, 0.f, 1.f, 1.f);
		unsigned int refreshTime = 15;
	} parameters;

	void drawPlayer1();
	void drawPlayer2();

	void drawMissiles();
	void drawOrbitalMissiles();
	void drawResources();

	void drawPlayArea();

	void initialize()
	{
		glClearColor(0.f, 0.f, 0.f, 1.f);
	}

	void draw()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		drawPlayer1();
		drawPlayer2();

		drawMissiles();
		drawOrbitalMissiles();
		drawResources();

		drawPlayArea();

		glutSwapBuffers();
	}


	void redraw(int a)
	{
		glutPostRedisplay();
		if (game->IsDone) {
			stopMainLoop();
		}
		else {
			glutTimerFunc(parameters.refreshTime, redraw, 0);
		}
	}

	void resizeAspectRatio(int width, int height)
	{
		if (height == 0) {
			height = 1;
		}

		glViewport(0, 0, width, height);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		double ratio = static_cast<double>(width) / static_cast<double>(height);
		double worldSize = static_cast<double>(game->config_ptr->World_Radius) * parameters.Circle_ScaleFactor;

		if (width >= height) {
			gluOrtho2D(-1 * (worldSize) * ratio, worldSize * ratio, -1 * worldSize, worldSize);
		}
		else {
			gluOrtho2D(-1 * worldSize, worldSize, -1 * worldSize / ratio, worldSize / ratio);
		}
	}

	void stopMainLoop()
	{
		glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
		glutLeaveMainLoop();
	}

	const double scaleRadius(const unsigned int& radius)
	{
		if (radius == 0) {
			return 1.;
		}
		return static_cast<double>(radius) * parameters.Circle_ScaleFactor;
	}
	const Point2D scaleCoordinate(const Point2D& point)
	{
		return point * static_cast<const int>(parameters.Circle_ScaleFactor);
	}

	void drawFilledCircle(const Point2D& center, const unsigned int& radius, const RGB_Color& color)
	{
		const double inc = math_pi / static_cast<double>(parameters.Circle_Resolution);
		const double max = 2 * math_pi;
		const double R = scaleRadius(radius);
		const Point2D C = scaleCoordinate(center);

		glPushMatrix();

		glBegin(GL_POLYGON);
		glColor4f(color.red, color.green, color.blue, color.alpha);
		for (double d = 0; d < max; d += inc) {
			glVertex2f(static_cast<float> (std::cos(d) * R + C.X), static_cast<float> (std::sin(d) * R + C.Y));
		}
		glEnd();
		glPopMatrix();
	}

	void drawCircle(const Point2D& center, const unsigned int& radius, const RGB_Color& color)
	{
		const double inc = math_pi / static_cast<double>(parameters.Circle_Resolution);
		const double max = 2 * math_pi;
		const double R = scaleRadius(radius);
		const Point2D C = scaleCoordinate(center);

		glPushMatrix();
		glLineWidth(parameters.Circle_LineWidth);

		glBegin(GL_LINE_LOOP);
		glColor4f(color.red, color.green, color.blue, color.alpha);

		for (double d = 0; d < max; d += inc) {
			glVertex2f(static_cast<float> (std::cos(d) * R + C.X), static_cast<float>(std::sin(d) * R + C.Y));
		}

		glEnd();
		glPopMatrix();
	}

	void drawPlayer1()
	{
		drawFilledCircle(game->Player1.getLocation(), game->Player1.getRadius(), parameters.Player1_Color);
	}

	void drawPlayer2()
	{
		drawFilledCircle(game->Player2.getLocation(), game->Player2.getRadius(), parameters.Player2_Color);
	}

	void drawMissiles()
	{
		const unsigned int radius = game->config_ptr->Missile_Radius;
		for (auto x : game->MissileList)
		{
			drawFilledCircle(x.getLocation(), radius, parameters.Missile_Color);
		}
	}

	void drawOrbitalMissiles()
	{
		const unsigned int radius = game->config_ptr->OrbitalMissile_Radius;
		for (auto x : game->OrbitalMissileList)
		{
			drawCircle(x.getTarget(), radius, parameters.OrbitalMissile_Color);
		}
	}

	void drawResources()
	{
		for (auto x : game->ResourceMap)
		{
			switch (x.second) {
			case ResourceIndentifier::Gas:
				drawFilledCircle(x.first, 0, parameters.Resource_Color_Gas);
				break;
			case ResourceIndentifier::Missile:
				drawFilledCircle(x.first, 0, parameters.Resource_Color_Missile);
				break;
			case ResourceIndentifier::OrbitalMissile:
				drawFilledCircle(x.first, 0, parameters.Resource_Color_OrbitalMissile);
				break;
			}
		}
	}

	void drawPlayArea()
	{
		drawCircle(Point2D(), game->Radius, parameters.PlayArea_Color);
	}
}
