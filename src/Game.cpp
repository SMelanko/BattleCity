#include "include/Clock.h"
#include "include/Game.h"
#include "include/KeyEventFilter.h"

#include <QDebug>

const double Game::MS_PER_UPDATE = 1000.0 / 60.0;

Game::Game(KeyEventFilter *kef, QObject *parent)
	: QObject{ parent }
{
	QObject::connect(kef, &KeyEventFilter::Send, &_ui, &UserInput::OnReceive);
}

Game::~Game() noexcept
{
	_running = false;
	_t.join();
}

void Game::Render()
{
}

void Game::Run()
{
	auto previous = Clock<>::Now();
	auto lag = 0.0;

	while (_running) {
		const auto current = Clock<>::Now();
		const auto elapsed = Clock<>::Duration(previous, current);
		previous = current;
		lag += elapsed;

		auto cmd = _ui.Process();
		cmd->Execute();

		while (lag >= MS_PER_UPDATE) {
			Update();
			lag -= MS_PER_UPDATE;
		}

		Render();
	}
}

void Game::Play()
{
	_t = std::thread{ &Game::Run, this };
	_running = true;
}

void Game::Update()
{
}
