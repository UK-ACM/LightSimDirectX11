#include "WhalenTimer.h"

using namespace std::chrono;

WhalenTimer::WhalenTimer() noexcept {
	last = steady_clock::now();
}

float WhalenTimer::Mark() noexcept {
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frametime = last - old;
	return frametime.count();

}

float WhalenTimer::Peek() const noexcept {
	return duration<float>(steady_clock::now() - last).count();
}