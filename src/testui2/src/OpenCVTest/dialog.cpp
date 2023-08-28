#include "dialog.h"
#include "ui_dialog.h"

#include "opencv/highgui.h"

#include <QDebug>
#include <QTimer>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    // these options was pre-defined in the dialog.ui
    ui->label->setMaximumSize(800, 600);
    ui->label->setScaledContents(true);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    CvCapture   *capture = cvCaptureFromFile("d:/test.mp4");

    if (capture) {
        auto    timer = new QTimer(this);

        connect(timer, &QTimer::timeout, [=]()mutable {
            IplImage    *frame = cvQueryFrame(capture);

            if (capture && frame) {
                auto    image = QImage((uchar *)frame->imageData, frame->width, frame->height, QImage::Format_RGB888);

                ui->label->setPixmap(QPixmap::fromImage(image));
            }
            else {
                timer->stop();
                cvReleaseCapture(&capture);
                timer->deleteLater();
            }
        });

        timer->start(30);
    }
}
