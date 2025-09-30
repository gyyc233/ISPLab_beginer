#include "MyISP.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

// 亮度与对比度调整
void BCC(ImageYUV &yuv, uint8_t brightness, float contrast) {
  for (int y = 0; y < yuv.getHeight(); y++) {
    for (int x = 0; x < yuv.getWidth(); x++) {
      float Y = yuv.at(y, x).Y;

      // 对比度调整
      Y = 128.0f + contrast * (Y - 128.0f);

      // 亮度调整
      Y += brightness;

      // 裁剪到有效范围
      if (Y < 0)
        Y = 0;
      if (Y > 255)
        Y = 255;

      yuv.at(y, x).Y = static_cast<uint8_t>(Y);
    }
  }
}
