#ifndef VOLTPARAMRECH_H
#define VOLTPARAMRECH_H

#include <QVector>



// 计算最大值
float getMaxVoltage(const QVector<float>& voltages);

// 计算最小值
float getMinVoltage(const QVector<float>& voltages);

// 计算峰峰值
float getPeakToPeakVoltage(const QVector<float>& voltages);

// 计算平均值
float getAverageVoltage(const QVector<float>& voltages);

// 计算有效值
float getRMSVoltage(const QVector<float>& voltages);

// 计算占空比
float getDutyCycle(const QVector<float>& voltages);

// 计算脉冲宽度
float getPulseWidth(const QVector<float>& voltages, float sampling_interval);

// 计算相位差
float getPhaseDifference(const QVector<float>& voltages1, const QVector<float>& voltages2);

// 计算周期
float getPeriod(const QVector<float>& voltages, float sampling_interval);

// 计算频率
float getFrequency(const QVector<float>& voltages, float sampling_interval);



#endif // VOLTPARAMRECH_H
