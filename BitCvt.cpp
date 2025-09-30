#include "MyISP.h"
#include <math.h>

// RAW data processing
// 10bit to 8bit 位深转换函数，将RAW数据的位深进行调整

/// @brief 将RAW图像的位深转换为目标位深
/// @param raw
/// @param bit 转换为指定位深 比如8
void BitCvt(ImageRaw &raw, int bit) {
  int maxval = 1 << bit;
  for (int y = 0; y < raw.getHeight(); y++) {
    for (int x = 0; x < raw.getWidth(); x++) {
      // 当前实现假设输入是10位数据(0-1023)
      // 就是乘以一个比例因子
      raw.at(y, x) = raw.at(y, x) * maxval / 1024;
    }
  }
}
