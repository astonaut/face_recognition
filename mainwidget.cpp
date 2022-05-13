#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDebug>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);

    //展示摄像头信息
    const QList<QCameraInfo> CameraInfoList = QCameraInfo::availableCameras();
    for (const QCameraInfo &tmpcam:CameraInfoList) {
//        qDebug() << tmpcam.description() ;
        ui->comboBox->addItem(tmpcam.description());
    }
    //可从下拉列表选择不同摄像头
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this,[=](int index){
            qDebug() << CameraInfoList.at(index).description() << Qt::endl;

            refreshTimer->stop();
            camera->stop();

            camera->deleteLater(); //delete brfore camera
            camera = new QCamera(CameraInfoList.at(index));  //create new camera

            imageCapture->deleteLater();
            imageCapture = new QCameraImageCapture(camera);

            camera->setViewfinder(finder);
            //设置拍照模式
            camera->setCaptureMode(QCamera::CaptureStillImage);
            //设置照片存储位置 存到buffer
            imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);

            connect(imageCapture, &QCameraImageCapture::imageCaptured,
                    this, [=](int id, const QImage &preview){
                Q_UNUSED(id)
                ui->label->setPixmap(QPixmap::fromImage(preview));
            });

            camera->start();
            refreshTimer->start(40);
    });

    // 摄像头配置
    camera = new QCamera();
    finder = new QCameraViewfinder();
    imageCapture = new QCameraImageCapture(camera);
    camera->setViewfinder(finder);

    //设置拍照模式
    camera->setCaptureMode(QCamera::CaptureStillImage);
    //设置照片存储位置 存到buffer
    imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);

    connect(imageCapture, &QCameraImageCapture::imageCaptured,
            this, [=](int id, const QImage &preview){
        Q_UNUSED(id)
        ui->label->setPixmap(QPixmap::fromImage(preview));
    });

    camera->start();

    //设置定时器刷新界面
    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout,
            this, &MainWidget::TakePicture);
    refreshTimer->start(40);


    //设置布局
    QVBoxLayout *vboxl = new QVBoxLayout();
    vboxl->addWidget(ui->label);
    vboxl->addWidget(ui->pushButton);

    QVBoxLayout *vboxr = new QVBoxLayout();
    vboxr->addWidget(ui->comboBox);
    vboxr->addWidget(finder);

    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->addLayout(vboxl);
    hbox->addLayout(vboxr);

    this->setLayout(hbox);

    //设置按钮点击事件
    connect(ui->pushButton, &QPushButton::clicked,
            this,&MainWidget::TakePicture);

    //支持https协议
    QNetworkAccessManager *tokenManager = new QNetworkAccessManager(this);
    qDebug() << tokenManager->supportedSchemes();
    bool bSupp = QSslSocket::supportsSsl();
        QString buildVersion = QSslSocket::sslLibraryBuildVersionString();
        QString version = QSslSocket::sslLibraryVersionString();
        qDebug() << bSupp << buildVersion << version << Qt::endl;
}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::TakePicture()
{
    imageCapture->capture();   //异步
}
