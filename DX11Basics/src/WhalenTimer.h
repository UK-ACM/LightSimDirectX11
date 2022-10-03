#pragma once
#include <chrono>

using namespace std::chrono;
// timer class to time functions
class WhalenTimer {
public:
	WhalenTimer();
	float Mark();
	float Peek() const;
private:
	steady_clock::time_point last;

};