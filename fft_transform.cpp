/*
 * @Date: 2025-02-17 20:07:53
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-17 20:24:32
 * @details fft�任��������ʵ��
 * @FilePath: \M_Uscope\fft_transform.cpp
 */
#include "fft_transform.h"
#include <stdexcept> // �����쳣����

void fft_transform(const QVector<float>& input, QVector<std::complex<float>>& output, int nfft) {
    // ��������С�Ƿ�ƥ��
    if (input.size() != nfft) {
        throw std::invalid_argument("Input size must match nfft");
    }

    // ���� FFT ���ýṹ��
    kiss_fft_cfg cfg = kiss_fft_alloc(nfft, 0, nullptr, nullptr); // 0 ��ʾ���� FFT

    // �����������飨������ʽ��
    kiss_fft_cpx* cin = new kiss_fft_cpx[nfft];
    for (int i = 0; i < nfft; ++i) {
        cin[i].r = input[i]; // ʵ����ֵ
        cin[i].i = 0.0f;     // �鲿Ϊ 0
    }

    // ����������飨������ʽ��
    kiss_fft_cpx* cout = new kiss_fft_cpx[nfft];

    // ִ�� FFT
    kiss_fft(cfg, cin, cout);

    // ������� KISS FFT �ĸ�����ʽת��Ϊ std::complex<float>
    output.resize(nfft);
    for (int i = 0; i < nfft; ++i) {
        output[i] = std::complex<float>(cout[i].r/nfft, cout[i].i/nfft);
    }

    // �ͷ���Դ
    delete[] cin;
    delete[] cout;
    kiss_fft_free(cfg);
}

