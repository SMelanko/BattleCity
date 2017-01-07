#ifndef _BATTLECITY_CLOCK_H_
#define _BATTLECITY_CLOCK_H_

#include <chrono>

///
/// The Clock class.
///

template<typename ClockT = std::chrono::steady_clock>
class Clock
{
public:
	/// Type alias.
	using TimePointT = typename ClockT::time_point;

public:
	/// Returns the current time point in the frame of the clock.
	static auto now() noexcept -> decltype(ClockT::now())
	{
		return ClockT::now();
	}
	/// Returns the internal count.
	template<typename PeriodT = std::milli>
	static auto duration(const TimePointT& t1,
		const TimePointT& t2) noexcept -> double
	{
		return std::chrono::duration<double, PeriodT>(t2 - t1).count();
	}
};

#endif // _BATTLECITY_CLOCK_H_
