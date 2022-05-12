#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QCameraImageCapture>

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
    QCamera * camera;
    QCameraViewfinder * finder;
    QCameraImageCapture * imageCapture;
};
#endif // MAINWIDGET_H
