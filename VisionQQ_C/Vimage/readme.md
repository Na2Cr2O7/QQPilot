## Vimage
对VisionQQ用到的图片处理功能的C++实现
## 注意
使用前需要下载[Cimg.h](https://github.com/GreycLab/CImg/blob/master/CImg.h)并放在Vimage目录下

在`cmakelist.txt`中也有`fetchcontent`的设置

```cmake
include(FetchContent)

FetchContent_Declare(
    cimg
    URL https://github.com/GreycLab/CImg/blob/master/CImg.h
)

FetchContent_MakeAvailable(cimg)
```