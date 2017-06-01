#include "camerawidget.h"
#include <QApplication>

using namespace std;


void test_matlab()
{
    if (!recaptureInitialize())
    {
        std::cout << "Could not initialize Matlab lib!" << std::endl;
        return;
    }
    char image_path[] = "E:\\Matlab\\software\\images\\1.jpg";
    char na_mat_path[] = "E:\\Matlab\\software\\mat_files\\testna5190.mat";
    char re_mat_path[] = "E:\\Matlab\\software\\mat_files\\testre5190.mat";


    mwArray ImagePath(image_path);
    mwArray NaPath(na_mat_path);
    mwArray RePath(re_mat_path);


    int result = 0;
    mwArray Result(result);

    main_FeatureClassifier(1, Result, ImagePath, NaPath, RePath);

    cout << "Call Result: " << Result << endl;
}


void test_call_register()
{
    qDebug() << "Start calling Register.exe";
    QProcess registProcess;
    registProcess.start("Register.exe", QStringList() << "-0" << "images\\1.jpg");
    registProcess.waitForStarted();
    registProcess.waitForFinished();
    qDebug() << QString::fromLocal8Bit(registProcess.readAll());
}


int main(int argc, char *argv[])
{
    FLAGS_log_dir = "./logs";                       // 设置日志的保存目录
    google::InitGoogleLogging(argv[0]);             // 设置日志的文件名(程序名)
    FLAGS_colorlogtostderr = true;                  // 设置输出到屏幕的日志显示相应颜色
    FLAGS_max_log_size = 100;                       // 最大日志大小为 100MB
    FLAGS_logbufsecs = 3;                           //设置可以缓冲日志的最大秒数，0指实时输出
    google::SetStderrLogging(google::GLOG_INFO);    // 在输出中打印所有的日志信息
    google::SetLogDestination(google::GLOG_INFO, "./logs/ALL_LOG_INFO_");       // 记录所有的日志信息
    google::SetLogDestination(google::GLOG_ERROR, "./logs/ERROR_");             // 记录错误信息，便于方便定位程序出错

    QApplication app(argc, argv);
    CameraWidget w;
    w.show();
    int execCode = app.exec();
    google::ShutdownGoogleLogging();

    return execCode;
}
