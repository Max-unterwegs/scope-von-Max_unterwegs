#include <QtMath>
#include <QVector>
#include <algorithm>
#include <numeric>
#include "voltparamrech.h"
using namespace std;


const size_t MAX_CAPACITY = 1000;
const float is0vstandard = 0.1;



// �������ֵ
// ���� voltages ��һ���洢��ѹֵ������
// ���ص�ѹֵ�е����ֵ
float getMaxVoltage(const QVector<float>& voltages)
{
    // ʹ�ñ�׼�⺯�� max_element �ҵ������е����ֵ
    return *std::max_element(voltages.begin(), voltages.end());
}

// ������Сֵ
// ���� voltages ��һ���洢��ѹֵ������
// ���ص�ѹֵ�е���Сֵ
float getMinVoltage(const QVector<float>& voltages)
{
    // ʹ�ñ�׼�⺯�� min_element �ҵ������е���Сֵ
    return *std::min_element(voltages.begin(), voltages.end());
}

// ������ֵ
// ���� voltages ��һ���洢��ѹֵ������
// ���ص�ѹֵ�ķ��ֵ�����ֵ��ȥ��Сֵ��
float getPeakToPeakVoltage(const QVector<float>& voltages)
{
    // ���� getMaxVoltage �� getMinVoltage ����������ֵ
    return getMaxVoltage(voltages) - getMinVoltage(voltages);
}

// ����ƽ��ֵ
// ���� voltages ��һ���洢��ѹֵ������
// ���ص�ѹֵ��ƽ��ֵ
float getAverageVoltage(const QVector<float>& voltages)
{
    // ʹ�ñ�׼�⺯�� accumulate �����ѹֵ���ܺͣ�Ȼ����Ե�ѹֵ������
    return std::accumulate(voltages.begin(), voltages.end(), 0.0) / voltages.size();
}

// ������Чֵ
// ���� voltages ��һ���洢��ѹֵ������
// ���ص�ѹֵ����Чֵ��������ֵ��
float getRMSVoltage(const QVector<float>& voltages)
{
    // �����ѹֵ��ƽ����
    float sum_of_squares = std::accumulate(voltages.begin(), voltages.end(), 0.0, [](float sum, float val) {
        return sum + val * val;
    });
    // ����ƽ���͵�ƽ��ֵ��ƽ����
    return qSqrt(sum_of_squares / voltages.size());
}

// ����ռ�ձȣ����貨��Ϊ������
// ���� voltages ��һ���洢��ѹֵ������
// ���ز��ε�ռ�ձ�
float getDutyCycle(const QVector<float>& voltages)
{
    // �����ѹֵ����0����������
    int high_count = std::count_if(voltages.begin(), voltages.end(), [](float val) {
        return val > is0vstandard;
    });
    // ���ظߵ�ƽ���������������������ı�ֵ
    return static_cast<float>(high_count) / voltages.size();
}

// ���������ȣ����貨��Ϊ������
// ���� voltages ��һ���洢��ѹֵ������
// ���� sampling_interval �ǲ������
// ���ز��ε�������
float getPulseWidth(const QVector<float>& voltages, float sampling_interval)
{
    // �����ѹֵ����0����������
    int high_count = std::count_if(voltages.begin(), voltages.end(), [](float val) {
        return val > is0vstandard;
    });
    // ���ظߵ�ƽ�����������Բ������
    return high_count * sampling_interval;
}

// ������λ���������ͨ���Ĳ���Ϊ���Ҳ���
// ���� voltages1 ��ͨ��1�ĵ�ѹֵ����
// ���� voltages2 ��ͨ��2�ĵ�ѹֵ����
// ���� frequency �ǲ��ε�Ƶ��
// �����������ε���λ��
float getPhaseDifference(const QVector<float>& voltages1, const QVector<float>& voltages2, float frequency)
{
    // �ҵ��������εĵ�һ�����
    auto zero_crossing1 = std::find_if(voltages1.begin(), voltages1.end(), [](float val) {
        return val >= is0vstandard;
    });
    auto zero_crossing2 = std::find_if(voltages2.begin(), voltages2.end(), [](float val) {
        return val >= is0vstandard;
    });

    // �������֮���������
    int sample_difference = std::distance(voltages1.begin(), zero_crossing1) - std::distance(voltages2.begin(), zero_crossing2);

    // ������λ��
    return (sample_difference / static_cast<float>(voltages1.size())) * 360.0;
}

// ����Ƶ�ʣ����貨��Ϊ���Ҳ���
// ���� voltages ��һ���洢��ѹֵ������
// ���� sampling_interval �ǲ������
// ���ز��ε�Ƶ��
float getFrequency(const QVector<float>& voltages, float sampling_interval)
{
    return 1.0 / getPeriod(voltages, sampling_interval);
}

// �������ڣ����貨��Ϊ���Ҳ���
// ���� voltages ��һ���洢��ѹֵ������
// ���� sampling_interval �ǲ������
// ���ز��ε�����
float getPeriod(const QVector<float>& voltages, float sampling_interval)
{
    int zero_crossings = 0;
    // ������㽻��Ĵ���
    for (int i = 1; i < voltages.size(); ++i)
    {
        if ((voltages[i - 1] < 0 && voltages[i] >= 0) || (voltages[i - 1] >= 0 && voltages[i] < 0))
        {
            zero_crossings++;
        }
    }
    // ��������
    float period = (zero_crossings / 2) * sampling_interval;
    // ��������
    return period;
}