#include "SingleThreadExecutor.h"

SingleThreadExecutor::SingleThreadExecutor()
{
	make_thread();
}

SingleThreadExecutor::~SingleThreadExecutor()
{

}

void SingleThreadExecutor::exec(std::function<void()> function)
{
	task_queue.push(function);
}

void SingleThreadExecutor::exec(std::function<void()> function, std::chrono::milliseconds execAfterTimeout)
{
	Timer t = Timer();
	t.setTimeout([&]() { exec(function); }, execAfterTimeout);
}

int SingleThreadExecutor::addPeriodicTask(std::function<void()> function, std::chrono::milliseconds period)
{
	exec(function);
	Timer *t = new Timer();
	t->setInterval( [&]() { exec(function); }, period);
	id_map.insert(std::pair<int,Timer*>(max_id, t));
	max_id++;
	return (max_id - 1);
}

void SingleThreadExecutor::removePeriodicTask(int taskId)
{
	if (id_map[taskId])
	{
		id_map[taskId]->stop();
		id_map.erase(taskId);
	}
}

void SingleThreadExecutor::single_thread_loop()
{
	std::function<void()> task;
	bool success;
	while (alive) {
		success = task_queue.try_pop(task);
		if (success)
		{
			task();
			continue;
		}
		else
		{
			task_queue.wait_and_pop(task);
			task();
		}
	}
}

void SingleThreadExecutor::make_thread()
{
	local_thread = std::thread(&SingleThreadExecutor::single_thread_loop, this);
	local_thread.detach();
}
