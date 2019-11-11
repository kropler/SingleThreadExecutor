#include <iostream>
#include <queue>

#ifndef THREADSAFE_QUEUE_H
#define THREADSAFE_QUEUE_H

class Threadsafe_queue
{
private:
	std::mutex mut;
	std::queue<std::function<void()>> shared_task_queue;
	std::condition_variable cond_var;
public:
	Threadsafe_queue();
	void push(std::function<void()> new_value);
	bool try_pop(std::function<void()>& value);
	void wait_and_pop(std::function<void()>& value);
};

#endif
