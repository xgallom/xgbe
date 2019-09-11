//
// Created by Revolware Company on 2019-09-05.
//

#include "Emulation.h"
#include "GameBoy.h"
#include "Log.h"
#include "GameBoyLoader.h"

struct Emulation::InternalThreadContext {
	InternalThreadContext() : gameBoy{GameBoyLoader::load()} {}

	GameBoy gameBoy;
	InternalState internalState = GetClocks;
	uint64_t cycles = 0;
};

Emulation::Emulation() : m_thread(Emulation::ThreadHandler, std::ref(m_threadContext)) {}

Emulation::~Emulation() noexcept
{
	m_threadContext.controlState.store(Quit, std::memory_order_relaxed);
	m_thread.join();
}

void Emulation::start() noexcept
{
	m_threadContext.controlState.store(ApplicationConfig.logDebug ? Paused : Running, std::memory_order_release);
}

void Emulation::step() noexcept
{
	m_threadContext.controlState.store(Step, std::memory_order_relaxed);
}

bool Emulation::pauseOrResume() noexcept
{
	ControlState required = Running;
	if(!m_threadContext.controlState.compare_exchange_weak(required, Paused, std::memory_order_relaxed)) {
		required = Paused;
		if(!m_threadContext.controlState.compare_exchange_weak(required, Running, std::memory_order_relaxed))
			return false;
	}

	return true;
}

void Emulation::sendKey(KeyCommand::Enum key) noexcept
{
	KeyCommand::Enum required = KeyCommand::None;

	while(!m_threadContext.keyPress.compare_exchange_weak(
			required, key,
			std::memory_order_relaxed, std::memory_order_relaxed
	))
		required = KeyCommand::None;
}

void Emulation::ThreadHandler(ThreadContext &context) noexcept
{
	while(context.controlState.load(std::memory_order_acquire) == Init) {}

	try {
		InternalThreadContext internalContext = {};

		Log::info("Game boy size: ", sizeof(internalContext.gameBoy), "\n");

		Log::info("Emulation started\n");
		while(RunThreadCycle(context, internalContext)) {}
		Log::info("Emulation finished\n");
	} catch(std::runtime_error &error) {
		Log::error("Emulation failed with error: ", error.what());
	}
}

bool Emulation::RunThreadCycle(ThreadContext &context, InternalThreadContext &internalContext) noexcept
{
	switch(context.controlState.load(std::memory_order_relaxed)) {
		case Running:
			RunGameBoyCycle(context, internalContext);
			break;

		case Step:
			Log::info("Step\n");
			RunGameBoyStep(context, internalContext);
			context.controlState.store(Paused, std::memory_order_relaxed);
			break;


		case Paused:
			//Log::info("Paused\n");
			std::this_thread::sleep_for(std::chrono::milliseconds{10});
			internalContext.cycles = 0;
			internalContext.gameBoy.clock().reset();
			break;

		case Quit:
			return false;

		case Init:
			break;
	}

	return true;
}

void Emulation::RunGameBoyCycle(ThreadContext &context, InternalThreadContext &internalContext) noexcept
{
	HandleKeyInput(context, internalContext);

	switch(internalContext.internalState) {
		case GetClocks:
			internalContext.cycles += internalContext.gameBoy.clock().run();
			internalContext.internalState = RunCpu;
			break;

		case RunCpu:
			if(!internalContext.gameBoy.runCycles(internalContext.gameBoy, internalContext.cycles))
				internalContext.internalState = GetClocks;
			break;
	}
}

void Emulation::RunGameBoyStep(ThreadContext &context, InternalThreadContext &internalContext) noexcept
{
	HandleKeyInput(context, internalContext);

	internalContext.gameBoy.runOnce(internalContext.gameBoy);
}

void Emulation::HandleKeyInput(ThreadContext &context, InternalThreadContext &internalContext) noexcept
{
	const auto key = context.keyPress.load(std::memory_order_relaxed);
	if(key != KeyCommand::None) {
		context.keyPress.store(KeyCommand::None, std::memory_order_relaxed);
		Log::info("Key press: ", key, "\n");
	}
}
