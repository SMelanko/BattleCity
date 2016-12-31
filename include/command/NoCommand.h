#ifndef _BATTLECITY_NOCOMMAND_H_
#define _BATTLECITY_NOCOMMAND_H_

#include "include/command/Command.h"

///
/// The NoCommand class.
///

class NoCommand : public Command
{
public:
	/// Executes nothing.
	void Execute() noexcept override;
};

#endif // _BATTLECITY_NOCOMMAND_H_
