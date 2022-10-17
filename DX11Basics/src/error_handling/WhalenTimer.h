#pragma once
#include <chrono>

using namespace std::chrono;
// timer class to time functions
class WhalenTimer {
public:
	WhalenTimer() noexcept;
	float Mark() noexcept;
	float Peek() const noexcept;
private:
	steady_clock::time_point last;

};