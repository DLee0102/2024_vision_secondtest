#pragma once
#include <iostream>
#include <functional>
#include <vector>

#include <chrono>
#include <thread>
#include <random>

/* 创建一个函数绑定器的宏，以便于调用 */
#define BIND(x) std::bind(x, std::placeholders::_1)

namespace customTimer {
    #define Milliseconds std::chrono::milliseconds

    class Timer
    {
    private:
        /* 控制线程阻塞 */
        bool is_blocked;

        /**
         * @brief 测量时间
         * 
         */
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

        /**
         * @brief 创建一个定时器循环
         * 
         * @param interval 
         * @param data 
         * @param funcs 
         */
        void createTimerLoop(int interval, std::vector<float>& data, 
            std::vector<std::function<float (std::vector<float>&)>>& funcs);

    private:

        /**
         * @brief 设置定时器的回调函数
         * 
         * @tparam T 
         * @tparam CallbackT 
         * @param data 
         * @param func 
         */
        template <typename T, typename CallbackT>
        void setTimeCallback(std::vector<T>& data, CallbackT func) { func(data); }
    };
};