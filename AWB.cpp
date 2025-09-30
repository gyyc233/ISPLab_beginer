#include "MyISP.h"
#include <math.h>

// RAW data processing
// auto white balance 自动白平衡，矫正图像中的色温偏差

/// @brief 自动白平衡
/// @param raw
/// @param r_gain r通道白平衡增益
/// @param gr_gain gr通道白平衡增益
/// @param gb_gain gb通道白平衡增益
/// @param b_gain b通道白平衡增益
/// @param bayer_pattern Bayer模式
/// @param clip 裁剪
void AWB(ImageRaw &raw, float r_gain, float gr_gain, float gb_gain,
         float b_gain, BAYER_PATTERN bayer_pattern, uint16_t clip) {
  for (int y = 0; y < raw.getHeight(); y += 2) {
    for (int x = 0; x < raw.getWidth(); x += 2) {
      // 分通道增益应用
      switch (bayer_pattern) {
      case BAYER_PATTERN_RGGB:
        raw.at(y, x) *= r_gain;
        raw.at(y, x + 1) *= gr_gain;
        raw.at(y + 1, x) *= gb_gain;
        raw.at(y + 1, x + 1) *= b_gain;
        break;
      case BAYER_PATTERN_BGGR:
        raw.at(y, x) *= b_gain;
        raw.at(y, x + 1) *= gb_gain;
        raw.at(y + 1, x) *= gr_gain;
        raw.at(y + 1, x + 1) *= r_gain;
        break;
      case BAYER_PATTERN_GBRG:
        raw.at(y, x) *= gb_gain;
        raw.at(y, x + 1) *= b_gain;
        raw.at(y + 1, x) *= r_gain;
        raw.at(y + 1, x + 1) *= gr_gain;
        break;
      case BAYER_PATTERN_GRBG:
        raw.at(y, x) *= gr_gain;
        raw.at(y, x + 1) *= r_gain;
        raw.at(y + 1, x) *= b_gain;
        raw.at(y + 1, x + 1) *= gb_gain;
        break;
      case BAYER_PATTERN_UNKNOWN:
        break;
      default:
        break;
      }
    }
  }
  raw.clip(0, clip);
}
