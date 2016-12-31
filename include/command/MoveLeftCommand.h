#ifndef _BATTLECITY_MOVELEFTCOMMAND_H_
#define _BATTLECITY_MOVELEFTCOMMAND_H_

#include "include/command/Command.h"

///
/// The MoveLeftCommand class.
///

class MoveLeftCommand : public Command
{
public:
	/// Executes moving left.
	void Execute() noexcept override;
};

#endif // _BATTLECITY_MOVELEFTCOMMAND_H_
