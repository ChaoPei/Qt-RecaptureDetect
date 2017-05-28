#include "camerawidget.h"
#include "ui_camerawidget.h"

CameraWidget::CameraWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraWidget)
{
    ui->setupUi(this);

    cam = NULL;
    timer = new QTimer(this);
    image = new QImage();
    // imgName = "11.jpg";    // 测试使用
    registProcess = new QProcess(this);
    recognizeProcess = new QProcess(this);


    // 信号槽
    connect(timer, SIGNAL(timeout()), this, SLOT(readFrame()));  // 时间到，读取摄像头信息
    connect(ui->button_openCam, SIGNAL(clicked()), this, SLOT(openCamera()));
    connect(ui->button_takPic, SIGNAL(clicked()), this, SLOT(takingPicture()));
    connect(ui->button_closeCam, SIGNAL(clicked()), this, SLOT(closeCamera()));
    connect(ui->button_regist, SIGNAL(clicked()), this, SLOT(regist()));
    connect(ui->button_detect, SIGNAL(clicked()), this, SLOT(detect()));

}


// 打开摄像头
void CameraWidget::openCamera()
{
    // 获取摄像头视频
    cam = cvCreateCameraCapture(0);

    // 开始计时，超时则发出timeout()信号
    timer->start(3);
}


// 读取摄像头信息
void CameraWidget::readFrame()
{
    // 从摄像头中获取一帧图像
    frame = cvQueryFrame(cam);
    // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
    QImage qImage = QImage((const uchar*)frame->imageData,
                           frame->width, frame->height,
                           QImage::Format_RGB888).rgbSwapped();
    // 将图片显示到label上
    ui->label_cam->setPixmap(QPixmap::fromImage(qImage));
}

// 拍照
void CameraWidget::takingPicture()
{
    frame = cvQueryFrame(cam);

    // 保存图片
    cv::Mat camMat = cv::Mat(frame);
    cv::Mat dstImage = camMat.clone();
    imgName = getPicNameString();
    cv::imwrite("images\\" + imgName.toStdString(), dstImage);

    // 将抓取到的帧，转换为QImage格式。QImage::Format_RGB888不同的摄像头用不同的格式。
    QImage qImage = QImage((const uchar*)frame->imageData,
                           frame->width, frame->height,
                           QImage::Format_RGB888).rgbSwapped();
    // 将图片显示到label上
    ui->label_pic->setPixmap(QPixmap::fromImage(qImage));
}


// 关闭摄像头
void CameraWidget::closeCamera()
{
    timer->stop();         // 停止读取数据。

    cvReleaseCapture(&cam);//释放内存；
}


void CameraWidget::regist()
{
    qDebug() << "Click register button";
    QString program = "Register.exe";
    QStringList arguments;
    arguments << "-0" << "images\\" + imgName;
    connect(registProcess,
            SIGNAL(readyRead()),
            this,
            SLOT(readRegisterResult()));

    // 执行注册程序
    registProcess->start(program, arguments);
    registProcess->waitForStarted();
    qDebug() << QString::fromLocal8Bit(registProcess->readAll());
}

void CameraWidget::readRegisterResult()
{
    QProcess *pProces = (QProcess *)sender();
    QString result = pProces->readAll();

    // 注册成功返回信息正则表达式
    QString successStr("Register successfully, ID: (.*)");
    QRegExp successRegExp(successStr);
    QString failStr("Faces are not detected.");
    QRegExp failRegExp(failStr);


    // 将执行结果用提示框展示
    if(result.indexOf(successRegExp) >= 0)
    {
        QString id = successRegExp.cap(1);
        QMessageBox::information(NULL,
                                 "注册提示",
                                 "恭喜你，注册成功 ! ID: " + id);
        //imgName = "11.jpg";
    }
    else if(result.indexOf(failRegExp) >= 0)
    {
        QMessageBox::warning(NULL,
                             "注册提示",
                             "注册失败，未检测到人脸 !");
        // 注册失败需要关闭程序
        registProcess->close();

        // imgName = "1.jpg";
        qDebug() << "Register.exe was killed and exited.";

    }
    else
    {
        qDebug() << "Register stdout : " << result;
    }

    qDebug() << "Show messagebox ok !";
}

void CameraWidget::detect()
{
    qDebug() << "Click detect button";

    if (!RemakeInitialize())
    {
        std::cout << "Could not initialize Matlab lib!" << std::endl;
        return;
    }

    // Debug 目录
    // qDebug() << "app path : " <<  QCoreApplication::applicationDirPath();
    // build 目录
    qDebug() << "current path: " << QDir::currentPath();

    const QString NATURE_MAT = "testna5190.mat";
    const QString RECAPTURE_MAT = "testre5190.mat";
    QString imagePath = QDir::currentPath() + "/images/" + imgName;
    QString nature_mat = QDir::currentPath() + "/mats/" + NATURE_MAT;
    QString recapture_mat = QDir::currentPath() + "/mats/" + RECAPTURE_MAT;
    int result = 0;

    mwArray ImagePath(imagePath.toStdString().c_str());
    mwArray NaPath(nature_mat.toStdString().c_str());
    mwArray RePath(recapture_mat.toStdString().c_str());
    mwArray Result(result);

    qDebug() << "Start detect recapture for : " << imgName;
    main_FeatureClassifier(1, Result, ImagePath, NaPath, RePath);
    std::stringstream oss;
    oss << Result;
    if(oss.str() == "1")
    {
        qDebug() << "It's natural picture...";
        qDebug() << "Start face recognize...";
        QString program = "Register.exe";
        QStringList arguments;
        arguments << "-1" << "images\\" + imgName;
        connect(recognizeProcess,
                SIGNAL(readyRead()),
                this,
                SLOT(readRecognizeResult()));

        // 执行注册程序
        recognizeProcess->start(program, arguments);
        recognizeProcess->waitForStarted();
        qDebug() << QString::fromLocal8Bit(recognizeProcess->readAll());
    }
    else
    {
        qDebug() << "It's recapture pciture...";
        QMessageBox::warning(NULL,
                             "识别信息",
                             "该图片是翻拍 !");
    }
}


void CameraWidget::readRecognizeResult()
{
    QProcess *pProces = (QProcess *)sender();
    QString result = pProces->readAll();

    // 注册成功返回信息正则表达式
    QString successStr("ID: (.*)\r\n");
    QRegExp successRegExp(successStr);
    QString failStr("Faces are not detected.");
    QRegExp failRegExp(failStr);

    // 将执行结果用提示框展示
    if(result.indexOf(successRegExp) >= 0)
    {
        QString id = successRegExp.cap(1);
        QMessageBox::information(NULL,
                                 "识别信息",
                                 "识别成功，ID: " + id);
        //imgName = "11.jpg";
    }
    else if(result.indexOf(failRegExp) >= 0)
    {
        QMessageBox::warning(NULL,
                             "识别信息",
                             "识别错误，未检测到人脸 !");
        // 注册失败需要关闭程序
        registProcess->close();
        //imgName = "1.jpg";
        qDebug() << "Register.exe was killed and exited.";
    }
    else
    {
        qDebug() << "Recognize stdout : " << result;
    }
    qDebug() << "Show messagebox ok !";
}


QString CameraWidget::getPicNameString()
{
    QDateTime time = QDateTime::currentDateTime();
    QString name = time.toString("yyyy-MM-dd_hh-mm-ss") + ".jpg";
    return name;
}

CameraWidget::~CameraWidget()
{
    delete ui;
}
