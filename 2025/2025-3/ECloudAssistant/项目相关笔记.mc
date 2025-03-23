

## 环境配置相关
必要的环境配置：
C++17
# 添加 FFmpeg 的头文件路径
INCLUDEPATH += D:/ffmpeg-6.0-full_build-shared/include
# 添加 FFmpeg 的库文件路径
LIBS += -LD:/ffmpeg-6.0-full_build-shared/lib
# 如果需要链接 FFmpeg 的库，可以指定需要的库文件
LIBS += -lavcodec -lavformat -lavutil -lswresample -lswscale



