#ifndef _BATTLECITY_MOVEDOWNCOMMAND_H_
#define _BATTLECITY_MOVEDOWNCOMMAND_H_

#include "include/command/Command.h"

///
/// The MoveDownCommand class.
///

class MoveDownCommand : public Command
{
public:
	/// Executes moving down.
	void Execute() noexcept override;
};

#endif // _BATTLECITY_MOVEDOWNCOMMAND_H_
