//
// Created by Revolware Company on 2019-09-05.
//

#ifndef XGBE_CLOCK_H
#define XGBE_CLOCK_H

#include <chrono>

namespace XGbe {
	constexpr uint64_t round(double x) noexcept { return uint64_t(x) + (x - uint64_t(x) >= 0.5 ? 1 : 0); }
}

class Clock {
public:
	static constexpr auto
			GBFrequency = 4.19e6,
			GBPeriod = 1.0 / GBFrequency,
			GBCFrequency = 8e6,
			GBCPeriod = 1.0 / GBCFrequency;

	static constexpr uint64_t
			GBTicks = XGbe::round(1e9 * GBPeriod),
			GBCTicks = XGbe::round(1e9 * GBCPeriod);

	Clock() noexcept;

	using StdClock = std::chrono::steady_clock;

	uint64_t run() noexcept;
	void reset() noexcept;
	[[nodiscard]] double period() const noexcept;

private:
	uint64_t update() noexcept;

	uint64_t m_ticks = 0, m_gameBoyTicks = GBCTicks;
	StdClock::time_point m_lastUpdate = {};
};


#endif //XGBE_CLOCK_H
