#include "Threadsafe_queue.h"

Threadsafe_queue::Threadsafe_queue()
{

}

void Threadsafe_queue::push(std::function<void()> const new_value)
{
	std::unique_lock<std::mutex> locker(mut);
	shared_task_queue.push(new_value);
	locker.unlock();
	cond_var.notify_one();
}

void Threadsafe_queue::wait_and_pop(std::function<void()>& value)
{
	std::unique_lock<std::mutex> locker(mut);
	cond_var.wait(locker, [this]{return !shared_task_queue.empty();});
	value = shared_task_queue.front();
	shared_task_queue.pop();
	locker.unlock();
}

bool Threadsafe_queue::try_pop(std::function<void()>& value)
{
	std::unique_lock<std::mutex> locker(mut);
	if(shared_task_queue.empty())
	{
		locker.unlock();
		return false;
	}
	value = shared_task_queue.front();
	shared_task_queue.pop();
	locker.unlock();
	return true;
}
