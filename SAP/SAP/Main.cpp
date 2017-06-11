#include <thread>
#include "GL\freeglut.h"
#include "GraphicsEngine.h"
#include "Test_AgentLogic.h"

void startGame(GameSimulator*);

int main(int argc, char** argv)
{
	Test_AgentLogic p1;
	Test_AgentLogic p2;
	ConfigurableParameters configuration;
	GameSimulator simulator(configuration, &p1, &p2);

	graphicsEngine::game = simulator.getGameState();

	glutInit(&argc, argv);
	glutInitWindowPosition(750, 50);
	glutInitWindowSize(720, 720);
	glutSetOption(GLUT_MULTISAMPLE, 4);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutCreateWindow("SAP 2017 - Goluban, Juratovic, Sinkovic");

	glutReshapeFunc(graphicsEngine::resizeAspectRatio);
	glutTimerFunc(0, graphicsEngine::redraw, 0); 
	glutDisplayFunc(graphicsEngine::draw);

	std::thread gameThread(startGame, &simulator);
	graphicsEngine::initialize();

	glutMainLoop();

	gameThread.join();

	system("pause");
	return 0;
}


void startGame(GameSimulator* gs)
{
	gs->play();
}