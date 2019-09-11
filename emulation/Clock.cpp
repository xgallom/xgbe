//
// Created by Revolware Company on 2019-09-05.
//

#include "Clock.h"
#include "Log.h"

Clock::Clock() noexcept
{
	m_lastUpdate = StdClock::now();

	Log::info("Current clock: ", StdClock::period::num, "/", StdClock::period::den, " s\n");
}

uint64_t Clock::run() noexcept
{
	m_ticks += update();

	const auto elapsed = m_ticks / m_gameBoyTicks;

	m_ticks -= elapsed * m_gameBoyTicks;

	return elapsed;
}

void Clock::reset() noexcept
{
	m_ticks = 0;
	m_lastUpdate = StdClock::now();
}

double Clock::period() const noexcept
{
	return double(StdClock::period::num) / StdClock::period::den;
}

uint64_t Clock::update() noexcept
{
	const auto now = StdClock::now();

	const auto sinceLastUpdate = now - m_lastUpdate;
	m_lastUpdate = now;

	return std::chrono::duration_cast<std::chrono::nanoseconds>(sinceLastUpdate).count();
}
