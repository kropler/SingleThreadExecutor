#include "Timer.h"

void Timer::setTimeout(std::function<void()> function, std::chrono::milliseconds delay)
{
	clear = false;
	std::thread t([=]() {
		if(clear)
			return;
		std::this_thread::sleep_for(delay);
		if(clear)
			return;
		function();
	});
	t.detach();
}

void Timer::setInterval(std::function<void()> function, std::chrono::milliseconds interval)
{
	clear = false;
	std::thread t([=]() {
		while(true) {
			if(clear)
				return;
			std::this_thread::sleep_for(interval);
			if(clear)
				return;
			function();
		}
	});
	t.detach();
}

void Timer::stop() {
	clear = true;
}
