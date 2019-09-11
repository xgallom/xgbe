//
// Created by Revolware Company on 2019-09-10.
//

#include "RealTimeClock.h"
#include <GameBoy.h>

void RealTimeClock::advance(GameBoy &gameBoy, double time) noexcept
{
	m_secondsSinceLastUpdate += time;

	const double decreasedTime = m_secondsSinceLastUpdate - 1.0;
	if(!get<DH, Halt>() && decreasedTime > 0.0) {
		m_secondsSinceLastUpdate = decreasedTime;

		advance(gameBoy);
	}
}

void RealTimeClock::reset() noexcept
{
	m_registers[S] = m_registers[M] = m_registers[H] = m_registers[DL] = m_registers[DH] = 0;
}

void RealTimeClock::advance(GameBoy &gameBoy) noexcept
{
	if(++ref<S>() >= 60) {
		write<S>(0);

		if(++ref<M>() >= 60) {
			write<M>(0);

			if(++ref<H>() >= 24) {
				write<H>(0);

				if(!++ref<DL>())
					advanceDH(gameBoy);
			}
		}
	}
}

void RealTimeClock::advanceDH(GameBoy &gameBoy) noexcept
{
	if(get<DH, DCMsb>()) {
		clear<DH, DCMsb>();
		set<DH, DCCarry>();
	} else
		set<DH, DCMsb>();
}
