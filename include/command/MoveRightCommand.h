#ifndef _BATTLECITY_MOVERIGHTCOMMAND_H_
#define _BATTLECITY_MOVERIGHTCOMMAND_H_

#include "include/command/Command.h"

///
/// The MoveRightCommand class.
///

class MoveRightCommand : public Command
{
public:
	/// Executes moving right.
	void Execute() noexcept override;
};

#endif // _BATTLECITY_MOVERIGHTCOMMAND_H_
