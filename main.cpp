#include "SingleThreadExecutor.h"

int main()
{
	std::thread background_thread([](){std::this_thread::sleep_for(std::chrono::seconds(10)); });

	std::function<void()> function1 = [](){ std::cout << "single Task1" << std::endl; };
	std::function<void()> function2 = [](){ std::cout << "single Task2" << std::endl; };
	std::function<void()> function3 = [](){ std::cout << "single delayed Task3" << std::endl; };
	std::function<void()> function4 = [](){ std::cout << "periodic Task4" << std::endl; };
	std::function<void()> function5 = [](){ std::cout << "periodic Task5" << std::endl; };
	std::function<void()> function6 = [](){ std::cout << "single delayed Task6" << std::endl; };

	SingleThreadExecutor MyExecutor;
	MyExecutor.exec(function1);
	MyExecutor.exec(function2);
	MyExecutor.exec(function3, std::chrono::milliseconds(1000));
	int task_id_1 = MyExecutor.addPeriodicTask(function4, std::chrono::milliseconds(1000));
	int task_id_2 = MyExecutor.addPeriodicTask(function5, std::chrono::milliseconds(1000));

	Timer del_timer = Timer();
	del_timer.setTimeout([&]() { std::cout << "remove periodic task with id: " << task_id_1 << std::endl; MyExecutor.removePeriodicTask(task_id_1); }, std::chrono::milliseconds(5000));
	del_timer.setTimeout([&]() { std::cout << "remove periodic task with id: " << task_id_2 << std::endl; MyExecutor.removePeriodicTask(task_id_2); }, std::chrono::milliseconds(8000));

	MyExecutor.exec(function6,std::chrono::milliseconds(7000));

	background_thread.join();
	return 0;
}
