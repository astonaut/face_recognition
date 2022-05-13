#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>   //vertical 垂直盒子
#include <QHBoxLayout>   //Horizontal 水平盒子
#include <QTimer>
#include <QNetworkAccessManager>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    QCamera * camera;     //相机
    QCameraViewfinder * finder; //取景器
    QCameraImageCapture * imageCapture; //快门
    QTimer * refreshTimer;
    void TakePicture();
};
#endif // MAINWIDGET_H
