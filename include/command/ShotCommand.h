#ifndef _BATTLECITY_SHOTCOMMAND_H_
#define _BATTLECITY_SHOTCOMMAND_H_

#include "include/command/Command.h"

///
/// The ShotCommand class.
///

class ShotCommand : public Command
{
public:
	/// Executes tank's shot.
	void Execute() noexcept override;
};

#endif // _BATTLECITY_MOVEUPCOMMAND_H_
