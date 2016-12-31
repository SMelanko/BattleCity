#ifndef _BATTLECITY_PAUSECOMMAND_H_
#define _BATTLECITY_PAUSECOMMAND_H_

#include "include/command/Command.h"

///
/// The PauseCommand class.
///

class PauseCommand : public Command
{
public:
	/// Executes pause in the game.
	void Execute() noexcept override;
};

#endif // _BATTLECITY_PAUSECOMMAND_H_
