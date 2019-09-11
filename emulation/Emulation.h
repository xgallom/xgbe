//
// Created by Revolware Company on 2019-09-05.
//

#ifndef XGBE_EMULATION_H
#define XGBE_EMULATION_H

#include <thread>
#include "KeyCommand.h"

class GameBoy;

class Emulation {
public:
	Emulation();
	~Emulation() noexcept;

	void start() noexcept;
	void step() noexcept;
	[[nodiscard]] bool pauseOrResume() noexcept;
	void sendKey(KeyCommand::Enum key) noexcept;

private:
	enum ControlState {
		Init,
		Running,
		Paused,
		Step,
		Quit
	};
	enum InternalState {
		GetClocks,
		RunCpu
	};

	struct ThreadContext {
		std::atomic<ControlState> controlState = Init;
		std::atomic<KeyCommand::Enum> keyPress = KeyCommand::None;
	} m_threadContext = {};
	struct InternalThreadContext;

	std::thread m_thread;

	static void ThreadHandler(ThreadContext &context) noexcept;
	static bool RunThreadCycle(ThreadContext &context, InternalThreadContext &internalContext) noexcept;
	static void RunGameBoyCycle(ThreadContext &context, InternalThreadContext &internalContext) noexcept;
	static void RunGameBoyStep(ThreadContext &context, InternalThreadContext &internalContext) noexcept;
	static void HandleKeyInput(ThreadContext &context, InternalThreadContext &internalContext) noexcept;
};


#endif //XGBE_EMULATION_H
