#include "MyISP.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

// 图像边缘增强 使用拉普拉斯锐化技术在YUV空间的亮度分量上进行处理
void EE(ImageYUV &yuv, float ee[][3], float gain) {
  ImageYUV *yuv_pad = new ImageYUV(yuv);
  yuv_pad->padding(1);

  for (int y = 0; y < yuv.getHeight(); y++) {
    for (int x = 0; x < yuv.getWidth(); x++) {
      float Y = yuv.at(y, x).Y;
      float lap = 0;

      // 3*3卷积
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
          lap = lap + ee[i][j] * yuv_pad->at(y + i, x + j).Y;
        }
      }

      // 边缘增强：原始 + 增益 × 高频
      Y = Y + gain * lap;
      if (Y < 0)
        Y = 0;
      if (Y > 255)
        Y = 255;
      yuv.at(y, x).Y = Y;
    }
  }

  delete yuv_pad;
}
