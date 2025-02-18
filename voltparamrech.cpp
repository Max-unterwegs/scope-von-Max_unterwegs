#include <QtMath>
#include <QVector>
#include <algorithm>
#include <numeric>
#include "voltparamrech.h"
using namespace std;


const size_t MAX_CAPACITY = 1000;
const float is0vstandard = 0.1;



// 计算最大值
// 参数 voltages 是一个存储电压值的向量
// 返回电压值中的最大值
float getMaxVoltage(const QVector<float>& voltages)
{
    // 使用标准库函数 max_element 找到向量中的最大值
    return *std::max_element(voltages.begin(), voltages.end());
}

// 计算最小值
// 参数 voltages 是一个存储电压值的向量
// 返回电压值中的最小值
float getMinVoltage(const QVector<float>& voltages)
{
    // 使用标准库函数 min_element 找到向量中的最小值
    return *std::min_element(voltages.begin(), voltages.end());
}

// 计算峰峰值
// 参数 voltages 是一个存储电压值的向量
// 返回电压值的峰峰值（最大值减去最小值）
float getPeakToPeakVoltage(const QVector<float>& voltages)
{
    // 调用 getMaxVoltage 和 getMinVoltage 函数计算峰峰值
    return getMaxVoltage(voltages) - getMinVoltage(voltages);
}

// 计算平均值
// 参数 voltages 是一个存储电压值的向量
// 返回电压值的平均值
float getAverageVoltage(const QVector<float>& voltages)
{
    // 使用标准库函数 accumulate 计算电压值的总和，然后除以电压值的数量
    return std::accumulate(voltages.begin(), voltages.end(), 0.0) / voltages.size();
}

// 计算有效值
// 参数 voltages 是一个存储电压值的向量
// 返回电压值的有效值（均方根值）
float getRMSVoltage(const QVector<float>& voltages)
{
    // 计算电压值的平方和
    float sum_of_squares = std::accumulate(voltages.begin(), voltages.end(), 0.0, [](float sum, float val) {
        return sum + val * val;
    });
    // 返回平方和的平均值的平方根
    return qSqrt(sum_of_squares / voltages.size());
}

// 计算占空比（假设波形为方波）
// 参数 voltages 是一个存储电压值的向量
// 返回波形的占空比
float getDutyCycle(const QVector<float>& voltages)
{
    // 计算电压值大于0的样本数量
    int high_count = std::count_if(voltages.begin(), voltages.end(), [](float val) {
        return val > is0vstandard;
    });
    // 返回高电平样本数量与总样本数量的比值
    return static_cast<float>(high_count) / voltages.size();
}

// 计算脉冲宽度（假设波形为方波）
// 参数 voltages 是一个存储电压值的向量
// 参数 sampling_interval 是采样间隔
// 返回波形的脉冲宽度
float getPulseWidth(const QVector<float>& voltages, float sampling_interval)
{
    // 计算电压值大于0的样本数量
    int high_count = std::count_if(voltages.begin(), voltages.end(), [](float val) {
        return val > is0vstandard;
    });
    // 返回高电平样本数量乘以采样间隔
    return high_count * sampling_interval;
}

// 计算相位差（假设两个通道的波形为正弦波）
// 参数 voltages1 是通道1的电压值向量
// 参数 voltages2 是通道2的电压值向量
// 参数 frequency 是波形的频率
// 返回两个波形的相位差
float getPhaseDifference(const QVector<float>& voltages1, const QVector<float>& voltages2, float frequency)
{
    // 找到两个波形的第一个零点
    auto zero_crossing1 = std::find_if(voltages1.begin(), voltages1.end(), [](float val) {
        return val >= is0vstandard;
    });
    auto zero_crossing2 = std::find_if(voltages2.begin(), voltages2.end(), [](float val) {
        return val >= is0vstandard;
    });

    // 计算零点之间的样本数
    int sample_difference = std::distance(voltages1.begin(), zero_crossing1) - std::distance(voltages2.begin(), zero_crossing2);

    // 计算相位差
    return (sample_difference / static_cast<float>(voltages1.size())) * 360.0;
}

// 计算频率（假设波形为正弦波）
// 参数 voltages 是一个存储电压值的向量
// 参数 sampling_interval 是采样间隔
// 返回波形的频率
float getFrequency(const QVector<float>& voltages, float sampling_interval)
{
    return 1.0 / getPeriod(voltages, sampling_interval);
}

// 计算周期（假设波形为正弦波）
// 参数 voltages 是一个存储电压值的向量
// 参数 sampling_interval 是采样间隔
// 返回波形的周期
float getPeriod(const QVector<float>& voltages, float sampling_interval)
{
    int zero_crossings = 0;
    // 计算零点交叉的次数
    for (int i = 1; i < voltages.size(); ++i)
    {
        if ((voltages[i - 1] < 0 && voltages[i] >= 0) || (voltages[i - 1] >= 0 && voltages[i] < 0))
        {
            zero_crossings++;
        }
    }
    // 计算周期
    float period = (zero_crossings / 2) * sampling_interval;
    // 返回周期
    return period;
}