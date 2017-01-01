#ifndef _BATTLECITY_GAME_H_
#define _BATTLECITY_GAME_H_

#include <QObject>

#include "include/UserInput.h"

#include <thread>

class KeyEventFilter;

class Game : public QObject
{
	Q_OBJECT

public:
	explicit Game(KeyEventFilter *kef, QObject *parent = Q_NULLPTR);

	~Game() noexcept;

public:
	/// Starts game.
	void Play();

private:
	/// Draws game onjects.
	void Render();
	/// Runs game main loop
	void Run();
	/// Update game objects.
	void Update();

private:
	static const double MS_PER_UPDATE;

	/// Game state.
	std::atomic<bool> _running;
	/// Thread for main loop.
	std::thread _t;
	/// User input.
	UserInput _ui;
};

#endif // _BATTLECITY_GAME_H_
