# ISPLab
An open-source image signal processing (ISP) pipeline implemented by C++

## Introduction
ISPLab is an open-source and platform-free ISP pipeline converting 10-bit RAW data to 8-bit RGB/YUV image without any 3rdparty libs (If you want to show the result and use deep learning, then OpenCV is required). 

## Result
| Raw input | RGB output |
|-----------|------------|
|![](raw.png)|![](rgb.png)|

## Methods
The pipeline of ISPLab includes following methods:
- RAW data processing
    - Dead pixel correction (DPC)
      - 用邻域像素梯度对屏幕坏点矫正
    - Black level correction (BLC)
      - 黑点平补偿，传感器即使在完全黑暗的环境中也会产生一定的信号输出，这个基础偏移量就是黑电平
    - Lens shading correction (LSC)
      - 镜头阴影矫正,补偿由镜头光学特性导致的图像亮度不均匀问题
    - Anti-aliasing filtering (AAF)
    - Auto white balance (AWB)
    - Chroma noise filtering (CNF)
- Demosaicing
- RGB image processing
    - Color correction (CCM)
    - Gamma correction (GC)
- Color space convertion
- YUV image processing
    - Noise reduction (NR)
    - Edge enhancement (EE)
    - Hue & saturatiton control (HSC)
    - Brightness & contrast control (BCC)

You can easily change the parameters of different methods in the config.csv, or change the Config.cpp file.

Contact me: liuyuqing@mail.dlut.edu.cn
