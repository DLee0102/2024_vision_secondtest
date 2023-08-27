#include "Cpphw.h"

namespace customTimer {
    Timer::Timer()
    {
        is_blocked = false;
    }
    void Timer::createTimerLoop(int interval, std::vector<float>& data, 
        std::vector<std::function<float (std::vector<float>&)>>& funcs)
    {
        std::random_device rd;  // 用于生成真正的随机数种子
        std::mt19937 gen(rd()); // 使用 Mersenne Twister 作为随机数引擎
        // 创建一个均匀分布的随机数生成器，范围在 [0, 3]
        std::uniform_int_distribution<int> dist(0, funcs.size() - 1);

        // 创建一个新线程来执行定时循环
        // [&] 可以捕获所有外部变量
        std::thread timer_thread([&]() {
            MeasureTime measuretime;
            int random_number = 0;
            while (!is_blocked) {
                random_number = dist(gen);
                this->setTimeCallback(data, funcs[random_number]);
                std::this_thread::sleep_for(std::chrono::milliseconds(interval));
            }
        });

        // 主线程并行执行,轮询是否按下Enter,若按下Enter则阻塞子进程
        std::cin.get();
        is_blocked = true;

        timer_thread.join();
        std::cout << "Finished. \n";

    }
}