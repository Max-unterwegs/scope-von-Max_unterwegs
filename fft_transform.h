/*
 * @Date: 2025-02-17 20:07:25
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-17 20:12:41
 * @FilePath: \M_Uscope\fft_transform.h
 */
#ifndef FFT_TRANSFORM_H
#define FFT_TRANSFORM_H

#include <QVector>
#include <complex>
#include "kiss_fft.h" // ���� KISS FFT ��ͷ�ļ�

// ��һά float ����������� FFT �任�ĺ���
void fft_transform(const QVector<float>& input, QVector<std::complex<float>>& output, int nfft);

#endif // FFT_TRANSFORM_H
