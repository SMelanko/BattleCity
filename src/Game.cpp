#include "include/Clock.h"
#include "include/Game.h"
#include "include/KeyEventFilter.h"

#include <QQmlContext>

Game::Game(int argc, char *argv[]) Q_DECL_NOEXCEPT
	: QGuiApplication{ argc, argv }
{
	_field = std::make_shared<Field>();
	_field->loadStage(1);
	_userTank = std::make_shared<UserTank>(_field);

	KeyEventFilter* kef = new KeyEventFilter{ _userTank, this };
	installEventFilter(kef);
	QObject::connect(kef, &KeyEventFilter::setMoveCommand, &_ui, &UserInput::onSetMoveCommand);
	QObject::connect(kef, &KeyEventFilter::setShotCommand, &_ui, &UserInput::onSetShotCommand);
	QObject::connect(kef, &KeyEventFilter::removeMoveCommand, &_ui, &UserInput::onRemoveMoveCommand);
	QObject::connect(kef, &KeyEventFilter::removeShotCommand, &_ui, &UserInput::onRemoveShotCommand);

	_engine.rootContext()->setContextProperty("userTank", _userTank.get());
	_engine.rootContext()->setContextProperty("field", _field.get());
	_engine.load(QUrl(QLatin1String("qrc:/qml/Main.qml")));

	start();
}

Game::~Game() Q_DECL_NOEXCEPT
{
	stop();
}

void Game::mainLoop()
{
	while (_userTank->isAlive()) {
		const auto start = Clock<>::now();

		auto cmds = _ui.process();
		update(cmds);
		render();

		const auto end = Clock<>::now();
		const auto elapsed = Clock<>::duration(start, end);
		if (elapsed < MS_PER_UPDATE) {
			const int64_t val = MS_PER_UPDATE - elapsed - 1;
			std::this_thread::sleep_for(std::chrono::milliseconds(val));
		}
	}
}

void Game::render()
{
	_userTank->render();
}

void Game::start()
{
	_mlThread = std::thread{ &Game::mainLoop, this };
}

void Game::stop()
{
	if (_mlThread.joinable()) {
		_userTank->explosion(); // TODO: Just for now.
		_mlThread.join();
	}
}

void Game::update(UserInput::CommandArray cmds)
{
	for (const auto& cmd : cmds) {
		if (cmd) {
			cmd->execute();
		}
	}
}
