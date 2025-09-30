#include "MyISP.h"
#include <math.h>

// RAW data processing
// anti-aliasing filter 抗锯齿滤波，减少高频噪声
void AAF(ImageRaw &raw) {
  ImageRaw *raw_pad = new ImageRaw(raw);
  raw_pad->padding(2, PADDING_MODE_REFLECT);

  for (int y = 0; y < raw_pad->getHeight() - 4; y++) {
    for (int x = 0; x < raw_pad->getWidth() - 4; x++) {
      // 使用了一个5*5的卷积核，权重分布中间是8,其它8个点是１,其余是0
      // 中心权重: 8/16 = 0.5
      // 对角权重: 1/16 = 0.0625 (每个角点)
      // 总权重和: (8 + 8×1) / 16 = 1.0

      uint16_t p0, p1, p2, p3, p4, p5, p6, p7, p8;
      p0 = raw_pad->at(y + 2, x + 2);
      p1 = raw_pad->at(y, x);
      p2 = raw_pad->at(y, x + 2);
      p3 = raw_pad->at(y, x + 4);
      p4 = raw_pad->at(y + 2, x);
      p5 = raw_pad->at(y + 2, x + 4);
      p6 = raw_pad->at(y + 4, x);
      p7 = raw_pad->at(y + 4, x + 2);
      p8 = raw_pad->at(y + 4, x + 4);
      raw.at(y, x) = (p0 * 8 + p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8) / 16.0;
    }
  }
  delete raw_pad;
}
