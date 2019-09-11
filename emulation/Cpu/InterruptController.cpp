//
// Created by Revolware Company on 2019-09-07.
//

#include "InterruptController.h"
#include "GameBoy.h"
#include "Operations/Interrupt.h"
#include "Operations/Sp.h"
#include "Operations/Pc.h"

namespace InterruptController {
	static void executeInterrupt(GameBoy &gameBoy, uint8_t interrupt)
	{
		SpOperations::pushWord(gameBoy, PcOperations::read(gameBoy));
		PcOperations::store(gameBoy,
							InterruptVectorAddress | (interrupt << InterruptVectorOffset)
		);
	}

	void handleInterrupts(GameBoy &gameBoy) noexcept
	{
		if(InterruptOperations::readIME(gameBoy)) {
			const uint8_t IE = InterruptOperations::readIE(gameBoy), IF = InterruptOperations::readIF(gameBoy);
			const auto eligibleInterrupts = IE & IF;

			for(uint8_t interrupt = 0; interrupt < InterruptRegisters::InterruptsSize; ++interrupt) {
				const uint8_t interruptMask = 1u << interrupt;

				if(eligibleInterrupts & interruptMask) {
					InterruptOperations::refIF(gameBoy) &= ~interruptMask;
					executeInterrupt(gameBoy, interrupt);
				}
			}
		}
	}
}
