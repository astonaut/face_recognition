#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    const QList<QCameraInfo> CameraInfoList = QCameraInfo::availableCameras();
    for (const QCameraInfo &tmpcam:CameraInfoList) {
//        qDebug() << tmpcam.description() ;
        ui->comboBox->addItem(tmpcam.description());
    }
}

MainWidget::~MainWidget()
{
    delete ui;
}

