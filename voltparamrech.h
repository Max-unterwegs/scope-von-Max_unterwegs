#ifndef VOLTPARAMRECH_H
#define VOLTPARAMRECH_H

#include <QVector>

// ���õ�ѹֵ
void setCH_voltage(float voltage1, float voltage2);

// �������ֵ
float getMaxVoltage(const QVector<float>& voltages);

// ������Сֵ
float getMinVoltage(const QVector<float>& voltages);

// ������ֵ
float getPeakToPeakVoltage(const QVector<float>& voltages);

// ����ƽ��ֵ
float getAverageVoltage(const QVector<float>& voltages);

// ������Чֵ
float getRMSVoltage(const QVector<float>& voltages);

// ����ռ�ձ�
float getDutyCycle(const QVector<float>& voltages);

// ����������
float getPulseWidth(const QVector<float>& voltages, float sampling_interval);

// ������λ��
float getPhaseDifference(const QVector<float>& voltages1, const QVector<float>& voltages2, float frequency);

// ��������
float getPeriod(const QVector<float>& voltages, float sampling_interval);

// ����Ƶ��
float getFrequency(const QVector<float>& voltages, float sampling_interval);



#endif // VOLTPARAMRECH_H