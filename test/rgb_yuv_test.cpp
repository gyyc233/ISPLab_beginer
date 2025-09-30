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

  // raw域降噪未实现
  NRraw(raw); // noise reduction for raw image, not implemented

  // 抗锯齿滤波
  AAF(raw);

  // 自动白平衡
  AWB(raw, config.awb_r_gain, config.awb_gr_gain, config.awb_gb_gain,
      config.awb_b_gain, config.bayer_pattern,
      config.awb_clip); // auto white balance

  // 将raw文件位深从16转到8
  BitCvt(raw, config.bitcvt_bit); // convert 10-bit raw data to k-bit(k=8)

  // 彩色噪声过滤
  CNF(raw, config.bayer_pattern, config.cnf_threshold, config.cnf_r_gain,
      config.cnf_gr_gain, config.cnf_gb_gain, config.cnf_b_gain,
      config.cnf_clip); // chroma noise filtering, this is for 8-bit raw data

  ImageRGB rgb = CFA(raw, config.cfa_mode, config.bayer_pattern,
                     config.cfa_clip); // demosaicing

  // cmm矩阵的选择会影响颜色矫正效果
  CCM(rgb, config.ccm_param); // 颜色矫正

  // gamma矫正
  GC(rgb, config.gc_bw, config.gc_gamma);

  fp = fopen("./rgb.RAW", "wb+");
  fwrite(rgb.getData(), sizeof(PixelRGB) * height * width, 1, fp);
  fclose(fp);

  ImageYUV yuv = CSC(rgb); // rgb2yuv 色彩空间转换

  // 在YUV色彩空间中实现的中值滤波降噪
  NRchroma(yuv, config.nr_chroma_d); // 对色度分量U和V进行中值滤波
  NRluma(yuv, config.nr_luma_d);     // 对亮度分量Y进行中值滤波
  EE(yuv, config.ee_matrix, config.ee_gain);       // 图像边缘增强
  HSC(yuv, config.hsc_hue, config.hsc_saturation); // 色温与饱和度调整
  BCC(yuv, config.bcc_brightness, config.bcc_brightness); // 亮度与对比度调整

  ImageRGB yuv2rgb = CSC(yuv); // yuv2rgb

  fp = fopen("./yuv2rgb.RAW", "wb+");
  fwrite(yuv2rgb.getData(), sizeof(PixelRGB) * height * width, 1, fp);
  fclose(fp);

  fp = fopen("yuv.RAW", "wb+");
  fwrite(yuv.getData(), sizeof(PixelYUV) * height * width, 1, fp);
  fclose(fp);

  cv::Mat img = toCvMat(yuv2rgb);
  cv::imshow("Image", img);
  cv::waitKey();

  return 0;
}