#include "camerawidget.h"
#include <QApplication>

using namespace std;


void test_matlab()
{
    if (!RemakeInitialize())
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
    QApplication a(argc, argv);
    CameraWidget w;
    w.show();

    return a.exec();

}
