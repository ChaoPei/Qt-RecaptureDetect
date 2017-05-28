#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QImage>
#include <QDateTime>
#include <QString>
#include <QRegExp>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>
#include <QLibrary>
#include <QDir>
#include <QCoreApplication>

#include <sstream>
#include <iostream>
#include <string>

#include <highgui.h>  //包含opencv库头文件
#include <cv.h>

#include "Remake.h"


namespace Ui {
class CameraWidget;
}

class CameraWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CameraWidget(QWidget *parent = 0);
    ~CameraWidget();

private slots:
    void openCamera();    // 打开摄像头
    void readFrame();     // 读取当前帧信息
    void closeCamera();   // 关闭摄像头
    void takingPicture(); // 拍照
    void regist();        // 注册
    void detect();        // 检测
    void readRegisterResult();  // 读取注册结果
    void readRecognizeResult(); // 读取识别结果

private:
    Ui::CameraWidget *ui;
    QTimer *timer;
    QImage *image;
    CvCapture *cam;  // 视频获取
    IplImage *frame; // 申请空间，用于存放每一帧图像
    QString imgName; // 保存抓拍后的图像名称
    QProcess *registProcess;
    QProcess *recognizeProcess;

    // 获取一个用于图片命名的字符串，字符串由当前时间生成
    QString getPicNameString();
};

#endif // CAMERAWIDGET_H
