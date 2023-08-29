#include "Cpphw.h"
#include <cmath>
// 加法
float Add(std::vector<float>& data)
{
    std::cout << "Adding numbers in the vector:\n";
    float sum = 0.0f;
    for (const float& metadata : data)
    {
        sum += metadata;
    }
    std::cout << "  The sum is: " << sum << std::endl;
    std::cout << " ------------- \n";
    return sum;
}

// 平均数
float Average(std::vector<float>& data)
{
    std::cout << "Computing the average of numbers in the vector:\n";
    float sum = 0.0f;
    float average = 0.0f;
    for (const float& metadata : data)
    {
        sum += metadata;
    }
    average = sum / (float)data.size();
    std::cout << "  The average is " << average << std::endl;
    std::cout << " ------------- \n";
    return average;
}

// 方差
float Variance(std::vector<float>& data)
{
    std::cout << "Computing the variance of numbers in the vector:\n";
    float sum = 0.0f;
    float average = 0.0f;
    float variance = 0.0f;
    for (const float& metadata : data)
    {
        sum += metadata;
    }
    average = sum / (float)data.size();
    for (const float& metadata : data)
    {
        variance += pow(metadata - average, 2); 
    }
    variance = variance / (float)data.size();
    std::cout << "  The variance is " << variance << std::endl;
    std::cout << " ------------- \n";
    return variance;
}

// 乘法
float Multiply(std::vector<float>& data)
{
    std::cout << "Multiplying numbers in the vector:\n";
    float result = 1.0f;
    for (const float& metadata : data)
    {
        result *= metadata;
    }
    std::cout << "  The Multiplied result is: " << result << std::endl;
    std::cout << " ------------- \n";
    return result;
}

int main()
{
    /* 生成100个随机数 */
    std::vector<float> data(100, 0.0f);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(0.0f, 5.0f);
    for (int i = 0; i < data.size(); i ++)
    {
        data[i] = dist(gen);
    }
    /* 创建一个函数指针列表 */
    std::vector<std::function<float (std::vector<float> &)>> funcs = 
        {BIND(Add), BIND(Average), BIND(Variance), BIND(Multiply)};

    /* 创建一个定时器 */
    customTimer::Timer timer;
    timer.createTimerLoop(500, data, funcs);
}