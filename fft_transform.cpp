/*
 * @Date: 2025-02-17 20:07:53
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-02-17 20:24:32
 * @details fft变换函数调用实现
 * @FilePath: \M_Uscope\fft_transform.cpp
 */
#include "fft_transform.h"
#include <stdexcept> // 用于异常处理

void fft_transform(const QVector<float>& input, QVector<std::complex<float>>& output, int nfft) {
    // 检查输入大小是否匹配
    if (input.size() != nfft) {
        throw std::invalid_argument("Input size must match nfft");
    }

    // 分配 FFT 配置结构体
    kiss_fft_cfg cfg = kiss_fft_alloc(nfft, 0, nullptr, nullptr); // 0 表示正向 FFT

    // 创建输入数组（复数形式）
    kiss_fft_cpx* cin = new kiss_fft_cpx[nfft];
    for (int i = 0; i < nfft; ++i) {
        cin[i].r = input[i]; // 实部赋值
        cin[i].i = 0.0f;     // 虚部为 0
    }

    // 创建输出数组（复数形式）
    kiss_fft_cpx* cout = new kiss_fft_cpx[nfft];

    // 执行 FFT
    kiss_fft(cfg, cin, cout);

    // 将结果从 KISS FFT 的复数格式转换为 std::complex<float>
    output.resize(nfft);
    for (int i = 0; i < nfft; ++i) {
        output[i] = std::complex<float>(cout[i].r/nfft, cout[i].i/nfft);
    }

    // 释放资源
    delete[] cin;
    delete[] cout;
    kiss_fft_free(cfg);
}

