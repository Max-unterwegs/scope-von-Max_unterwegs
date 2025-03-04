/*
 * @Date: 2025-03-04 22:21:19
 * @LastEditors: Max-unterwegs && max_unterwegs@126.com 
 * @LastEditTime: 2025-03-04 22:21:53
 * @FilePath: \MDK-ARMd:\Mein_Werk\scope_project\Core\Lib\Src\wave.h
 */
#ifndef WAVEFORM_DATA_H
#define WAVEFORM_DATA_H



// 波形数据采样点数
#define SAMPLES_PER_WAVE 100

// 正弦波数据
const int sine_wave[SAMPLES_PER_WAVE] = {
    2048, 2088, 2128, 2167, 2206, 2245, 2283, 2321, 2358, 2395,
    2431, 2467, 2502, 2536, 2569, 2601, 2632, 2662, 2691, 2719,
    2746, 2772, 2797, 2820, 2843, 2864, 2885, 2905, 2924, 2942,
    2959, 2975, 2990, 3004, 3017, 3029, 3040, 3050, 3059, 3067,
    3074, 3080, 3085, 3089, 3092, 3094, 3095, 3096, 3096, 3095,
    3093, 3090, 3086, 3081, 3075, 3068, 3060, 3051, 3041, 3030,
    3018, 3005, 2991, 2976, 2960, 2943, 2925, 2906, 2886, 2865,
    2843, 2820, 2796, 2771, 2745, 2718, 2690, 2661, 2631, 2600,
    2568, 2535, 2501, 2466, 2430, 2393, 2356, 2318, 2279, 2239,
    2198, 2157, 2115, 2073, 2030, 1987, 1944, 1901, 1858, 1816
};

// 三角波数据
const int triangle_wave[SAMPLES_PER_WAVE] = {
    0, 41, 82, 123, 164, 205, 246, 287, 328, 369,
    410, 451, 492, 533, 574, 615, 656, 697, 738, 779,
    820, 861, 902, 943, 984, 1025, 1066, 1107, 1148, 1189,
    1230, 1271, 1312, 1353, 1394, 1435, 1476, 1517, 1558, 1599,
    1640, 1681, 1722, 1763, 1804, 1845, 1886, 1927, 1968, 2009,
    2050, 2091, 2132, 2173, 2214, 2255, 2296, 2337, 2378, 2419,
    2460, 2501, 2542, 2583, 2624, 2665, 2706, 2747, 2788, 2829,
    2870, 2911, 2952, 2993, 3034, 3075, 3116, 3157, 3198, 3239,
    3280, 3321, 3362, 3403, 3444, 3485, 3526, 3567, 3608, 3649,
    3690, 3731, 3772, 3813, 3854, 3895, 3936, 3977, 4018, 4059
};

// 锯齿波数据
const int sawtooth_wave[SAMPLES_PER_WAVE] = {
    0, 41, 82, 123, 164, 205, 246, 287, 328, 369,
    410, 451, 492, 533, 574, 615, 656, 697, 738, 779,
    820, 861, 902, 943, 984, 1025, 1066, 1107, 1148, 1189,
    1230, 1271, 1312, 1353, 1394, 1435, 1476, 1517, 1558, 1599,
    1640, 1681, 1722, 1763, 1804, 1845, 1886, 1927, 1968, 2009,
    2050, 2091, 2132, 2173, 2214, 2255, 2296, 2337, 2378, 2419,
    2460, 2501, 2542, 2583, 2624, 2665, 2706, 2747, 2788, 2829,
    2870, 2911, 2952, 2993, 3034, 3075, 3116, 3157, 3198, 3239,
    3280, 3321, 3362, 3403, 3444, 3485, 3526, 3567, 3608, 3649,
    3690, 3731, 3772, 3813, 3854, 3895, 3936, 3977, 4018, 4059
};

// 矩形波数据
const int square_wave[SAMPLES_PER_WAVE] = {
    4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
    4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
    4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
    4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
    4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095, 4095,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

#endif // WAVEFORM_DATA_H
