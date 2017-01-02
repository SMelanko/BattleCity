#ifndef _BATTLECITY_GAME_H_
#define _BATTLECITY_GAME_H_

#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "include/command/Command.h"
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
	void MainLoop();
	/// Draws game onjects.
	void Render();
	/// Starts game.
	void Start();
	/// Stops game.
	void Stop();
	/// Update game objects.
	void Update(CommandShPtr cmd);

private:
	/// (Milliseconds in 1 second) / FPS.
	const double MS_PER_UPDATE = 1000.0 / 60.0;

	/// User input handler.
	UserInput _ui;
	/// GUI engine.
	QQmlApplicationEngine _engine;

	/// TODO Game state.
	std::atomic<bool> _running;
	int i;
	/// Thread for main loop.
	std::thread _mlThread;
};

#endif // _BATTLECITY_GAME_H_
