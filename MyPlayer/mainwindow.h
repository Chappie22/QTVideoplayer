#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QLayout>
#include <QSlider>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void SetTimeLabel();

private slots:
    void on_play_clicked();

    void on_horizontalSlider_2_valueChanged(int value);

    void on_comboBox_activated(int index);

    void on_directory_clicked();

    void on_horizontalSlider_sliderMoved(int position);
private:
    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
    QVBoxLayout *layout;
    QSlider *slider;
    bool pause = false;
};

#endif // MAINWINDOW_H
