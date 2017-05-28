#include "mainwindow.h"

#include <QAction>
#include <QMessageBox>
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 设置主窗口名称
    setWindowTitle(tr("Main Window"));

    // 设置图标和名称
    openAction = new QAction(QIcon(":/images/github-icon"), tr("&Open..."), this);
    // 设置快捷键
    openAction->setShortcuts(QKeySequence::Open);
    // 设置鼠标悬停动作
    openAction->setStatusTip(tr("Open an existing file"));
    // 设置事件监听
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    QMenu *file = menuBar()->addMenu(tr("&File"));
    file->addAction(openAction);

    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);

    statusBar();
}

MainWindow::~MainWindow()
{

}

void MainWindow::open()
{
    QMessageBox::information(this, tr("Information"), tr("Open"));
}
