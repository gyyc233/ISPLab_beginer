#include "MyISP.h"
#include <math.h>

// RGB data processing
// gamma correction gamma 矫正，矫正人眼对亮度的感知，提升暗部细节，
void GC(ImageRGB &rgb, int bit_depth, float gamma) {
  float maxval = pow(2, bit_depth) - 1;
  float inv_gamma = 1.0f / gamma; // 使用逆伽马值

  for (int y = 0; y < rgb.getHeight(); y++) {
    for (int x = 0; x < rgb.getWidth(); x++) {
      // 归一化 → 伽马校正 → 还原到原始范围
      float r_norm = rgb.at(y, x).R / maxval;
      float g_norm = rgb.at(y, x).G / maxval;
      float b_norm = rgb.at(y, x).B / maxval;

      rgb.at(y, x).R = pow(r_norm, inv_gamma) * maxval;
      rgb.at(y, x).G = pow(g_norm, inv_gamma) * maxval;
      rgb.at(y, x).B = pow(b_norm, inv_gamma) * maxval;
    }
  }
}
