#include "include/Clock.h"
#include "include/Game.h"
#include "include/KeyEventFilter.h"
#include "include/TankFactory.h"

#include <QQmlContext>

Game::Game(int argc, char *argv[]) Q_DECL_NOEXCEPT
	: QGuiApplication{ argc, argv }
{
	_userTank = UserTankFactory{}.create();

	KeyEventFilter* kef = new KeyEventFilter{ _userTank, this };
	installEventFilter(kef);
	QObject::connect(kef, &KeyEventFilter::send, &_ui, &UserInput::onReceive);

	_engine.rootContext()->setContextProperty("userTank", _userTank.get());
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

		auto cmd = _ui.process();
		update(cmd);
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

void Game::update(CommandShPtr cmd)
{
	cmd->execute();
}
