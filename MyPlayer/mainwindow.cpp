#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <string>


using std::to_string;
using std::string;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    layout = new QVBoxLayout();

    layout->addWidget(videoWidget);
    ui->groupBox_2->setLayout(layout);
    player->setVideoOutput(videoWidget);

    connect(player, &QMediaPlayer::durationChanged, ui->horizontalSlider, &QSlider::setMaximum);
    connect(player, &QMediaPlayer::positionChanged, ui->horizontalSlider, &QSlider::setValue);
    ui->directory->setIcon(QIcon(":/new/prefix1/Icons/015-folder.png"));


    this->on_horizontalSlider_2_valueChanged(0);
}

MainWindow::~MainWindow()
{
    delete player;
    delete layout;
    delete videoWidget;
    delete ui;
}

void MainWindow::on_play_clicked()
{
    if (pause) {
        ui->play->setText("Play");
        ui->play->setIcon(QIcon(":/new/prefix1/Icons/022-video.png"));
        pause = false;
        player->pause();
    }
    else {
        ui->play->setText("Pause");
        ui->play->setIcon(QIcon(":/new/prefix1/Icons/023-video-1.png"));
        pause = true;
        player->play();
        //This fixing not controlled zoom
        videoWidget->resize(videoWidget->width()+1, videoWidget->height());
        videoWidget->resize(videoWidget->width()-1, videoWidget->height());
    }
    this->SetTimeLabel();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    player->setVolume(value);
}

void MainWindow::on_comboBox_activated(int index)
{
    qreal rate = 0;
    switch (index) {
        case 0:
        {
            rate = 1;
            break;
        }
    case 1:
        {
            rate = 0.5;
            break;
        }
    case 2:
        {
            rate = 2;
            break;
        }
    }
        player->setPlaybackRate(rate);
}

void MainWindow::on_directory_clicked()
{
    QString path = QFileDialog::getOpenFileName(this,"Choose videofile..","","*.mp4");
    player->setMedia(QUrl::fromLocalFile(path));

}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    player->setPosition(position);
}

void MainWindow::SetTimeLabel()
{
    int seconds = (int)player->duration()/1000;
    int minutes = 0, hours = 0;
    string stringData;

    if ((minutes = seconds / 60) > 0) seconds -= minutes * 60;
        if ((hours = minutes / 60) > 0)  minutes -= hours * 60;

    if (hours > 9) stringData = to_string(hours) + ":";
    else stringData = to_string(hours) + "0:";

    if (minutes > 9) stringData += to_string(minutes) + ":";
    else stringData += "0" + to_string(minutes) + ":";

    if (seconds > 9) stringData += to_string(seconds);
    else stringData += "0" + to_string(seconds);

    ui->endTime->setText(QString::fromStdString(stringData));

}

