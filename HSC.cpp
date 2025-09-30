#include "MyISP.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#define PI 3.1415926535

// 色调与饱和度调整
void HSC(ImageYUV &yuv, float hue, float saturation) {
  float lut_sin = sin(hue * PI / 180);
  float lut_cos = cos(hue * PI / 180);

  float U, V;

  for (int y = 0; y < yuv.getHeight(); y++) {
    for (int x = 0; x < yuv.getWidth(); x++) {
      float U_orig = yuv.at(y, x).U;
      float V_orig = yuv.at(y, x).V;

      // 减去偏移量（YUV格式中UV分量以128为中心）
      float U_centered = U_orig - 128.0f;
      float V_centered = V_orig - 128.0f;

      // Hue　色度旋转
      U = U_centered * lut_cos + V_centered * lut_sin;
      V = -U_centered * lut_sin + V_centered * lut_sin;

      // Saturation 饱和度调整后加回偏移
      U = saturation * (U) + 128;
      V = saturation * (V) + 128;

      if (U < 16)
        U = 16;
      if (U > 240)
        U = 240;
      if (V < 16)
        V = 16;
      if (V > 240)
        V = 240;

      yuv.at(y, x).U = U;
      yuv.at(y, x).V = V;
    }
  }
}