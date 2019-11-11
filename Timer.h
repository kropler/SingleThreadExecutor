#include <iostream>
#include <thread>

#ifndef TIMER_H
#define TIMER_H

class Timer {
private:
	bool clear = false;

public:
	void setTimeout(std::function<void()> function, std::chrono::milliseconds delay);
	void setInterval(std::function<void()> function, std::chrono::milliseconds interval);
	void stop();
};

#endif
