#include <iostream>
#include <thread>
#include <map>

#include "Timer.h"
#include "Threadsafe_queue.h"

#ifndef SINGLETHREADEXECUTOR_H
#define SINGLETHREADEXECUTOR_H

class SingleThreadExecutor {
private:
	std::thread local_thread;
	void single_thread_loop();
	void make_thread();
	bool alive = 1;
	int max_id = 1;
	std::map<int, Timer *> id_map;
	Threadsafe_queue task_queue;
public:
	SingleThreadExecutor();
	~SingleThreadExecutor();
	void exec(std::function<void()> function);
	void exec(std::function<void()> function, std::chrono::milliseconds execAfterTimeout);
	int addPeriodicTask(std::function<void()> function, std::chrono::milliseconds period);
	void removePeriodicTask(int taskId);
};

#endif
