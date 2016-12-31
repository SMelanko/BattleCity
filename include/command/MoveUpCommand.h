#ifndef _BATTLECITY_MOVEUPCOMMAND_H_
#define _BATTLECITY_MOVEUPCOMMAND_H_

#include "include/command/Command.h"

///
/// The MoveUpCommand class.
///

class MoveUpCommand : public Command
{
public:
	/// Executes moving up.
	void Execute() noexcept override;
};

#endif // _BATTLECITY_MOVEUPCOMMAND_H_
