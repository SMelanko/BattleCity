#ifndef _BATTLECITY_COMMAND_H_
#define _BATTLECITY_COMMAND_H_

#include <memory>

///
/// The Command class.
///

class Command
{
public:
	virtual ~Command() noexcept = default;

public:
	/// Executes action.
	virtual void Execute() noexcept = 0;
};

using CommandUnPtr = std::unique_ptr<Command>;
using CommandShPtr = std::shared_ptr<Command>;

#endif // _BATTLECITY_COMMAND_H_
