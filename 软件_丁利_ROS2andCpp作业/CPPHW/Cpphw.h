#pragma once
#include <iostream>
#include <functional>
#include <vector>

#include <chrono>
#include <thread>
#include <random>

#define BIND(x) std::bind(x, std::placeholders::_1)

namespace customTimer {
    #define Milliseconds std::chrono::milliseconds

    class Timer
    {
    private:
        // 控制线程阻塞
        bool is_blocked;

        // 测量运行时间
        struct MeasureTime
        {
            std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
            std::chrono::duration<float> duration;

            MeasureTime()
            {
                std::cout << "TimerLoop Thread Started... Press ENTER to finish.\n\n";
                start = std::chrono::high_resolution_clock::now();
            }

            ~MeasureTime()
            {
                end = std::chrono::high_resolution_clock::now();
                duration = end - start;
                
                float ms = duration.count() * 1000.0f;
                std::cout << "TimerLoop Thread finished in " << ms << "ms\n";
            }
        };
    public:
        Timer();
        void createTimerLoop(int interval, std::vector<float>& data, 
            std::vector<std::function<float (std::vector<float>&)>>& funcs);

    private:
        template <typename T, typename CallbackT>
        void setTimeCallback(std::vector<T>& data, CallbackT func) { func(data); }
    };
};