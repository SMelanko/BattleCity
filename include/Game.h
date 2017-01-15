#ifndef _BATTLECITY_GAME_H_
#define _BATTLECITY_GAME_H_

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "include/Command.h"
#include "include/Field.h"
#include "include/UserInput.h"

#include <thread>

class Game : public QGuiApplication
{
	Q_OBJECT

public:
	/// Constructor.
	Game(int argc, char *argv[]) Q_DECL_NOEXCEPT;
	/// Destructor.
	~Game() Q_DECL_NOEXCEPT;

private:
	/// Runs game main loop.
	void mainLoop();
	/// Draws the game.
	void render();
	/// Starts game.
	void start();
	/// Stops game.
	void stop();
	/// Advances the game simulation one step.
	void update(UserInput::CommandArray cmds);

private:
	/// (Milliseconds in 1 second) / FPS.
	const double MS_PER_UPDATE = 1000.0 / 20.0;

	/// User input handler.
	UserInput _ui;
	/// GUI engine.
	QQmlApplicationEngine _engine;

	/// Thread for main loop.
	std::thread _mlThread;

	/// Instance of the user tank.
	TankShPtr _userTank;
	/// Battle field.
	FieldShPtr _field;
};

#endif // _BATTLECITY_GAME_H_
