#include "include/Clock.h"
#include "include/Game.h"
#include "include/KeyEventFilter.h"

Game::Game(int argc, char *argv[]) Q_DECL_NOEXCEPT
	: QGuiApplication{ argc, argv }
{
	KeyEventFilter* kef = new KeyEventFilter{ this };
	installEventFilter(kef);
	QObject::connect(kef, &KeyEventFilter::Send, &_ui, &UserInput::OnReceive);

	_engine.load(QUrl(QLatin1String("qrc:/qml/Main.qml")));

	Start();
}

Game::~Game() Q_DECL_NOEXCEPT
{
	Stop();
}

void Game::MainLoop()
{
	while (_running) {
		const auto start = Clock<>::Now();

		auto cmd = _ui.Process();
		Update(cmd);
		Render();

		const auto end = Clock<>::Now();
		const auto elapsed = Clock<>::Duration(start, end);
		if (elapsed < MS_PER_UPDATE) {
			const int64_t val = MS_PER_UPDATE - elapsed - 1;
			std::this_thread::sleep_for(std::chrono::milliseconds(val));
		}
	}
}

void Game::Render()
{
}

void Game::Start()
{
	_running = true;
	_mlThread = std::thread{ &Game::MainLoop, this };
}

void Game::Stop()
{
	_running = false;
	_mlThread.join();
}

void Game::Update(CommandShPtr cmd)
{
	cmd->Execute();
}
