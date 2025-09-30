#include "Config.h"
#include "MyISP.h"
#include "MyOpenCV.h"
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
  int width = 1920, height = 1080;
  uint16_t *src = new uint16_t[width * height];

  FILE *fp = fopen("./data/test.RAW", "rb+");
  fread(src, sizeof(uint16_t) * height * width, 1, fp);
  fclose(fp);
  ImageRaw raw(src, height, width);

  Config config("./data/config.csv");
  DPC(raw, config.dpc_threshold, config.dpc_mode,
      config.dpc_clip); // 坏点检测

  BLC(raw, config.blc_r, config.blc_gr, config.blc_gb, config.blc_b,
      config.blc_alpha, config.blc_beta, config.bayer_pattern,
      config.blc_clip); // black level correction 黑电平补偿

  LSC(raw, config.lsc_intensity, config.lsc_minr, config.lsc_maxr,
      config.lsc_clip); // 镜头阴影矫正

  ImageRGB rgb = CFA(raw, config.cfa_mode, config.bayer_pattern,
                     config.cfa_clip); // demosaicing

  cv::Mat img = toCvMat(rgb);
  cv::imshow("Image", img);
  cv::waitKey();

  return 0;
}
