#include "valuepack.h"
#include <cstring>
#include <QDebug>
unsigned char readValuePack(RxPack *pack, unsigned char *buffer, long long len)
{
    for (long long i = 0; i < len; ++i) {
        if (buffer[i] == PACK_HEAD) {
            // 找到包头，检查包尾和校验和
            if (i + 10 < len && buffer[i + 10] == PACK_TAIL) {
                int tmp = 0;
                for (int j = 1; j < 9; ++j) {
                    tmp += buffer[i + j];
                }
                char jy = (tmp) & 0xff;
                if (buffer[i + 9] == jy) {
                    // 解析数据包
                    qDebug() << "Find check";
                    for (int k = 0; k < RX_FLOAT_NUM; ++k) {
                        int intValue = 0;
                        intValue |= buffer[i + 1 + k * 4] & 0xff;
                        intValue |= (buffer[i + 2 + k * 4] & 0xff) << 8;
                        intValue |= (buffer[i + 3 + k * 4] & 0xff) << 16;
                        intValue |= (buffer[i + 4 + k * 4] & 0xff) << 24;
                        pack->floats[k] = *(float *)&intValue;
                    }
                    return 1;
                }
            }
        }
    }
    return 0;
}
