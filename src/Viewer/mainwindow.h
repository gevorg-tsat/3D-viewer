#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtOpenGL/QtOpenGL>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWidget>
#include <QFileDialog>
#include <QColorDialog>
#include <QColor>

#include "ogl.h"
#include "qgifimage.h"

extern "C" {
  #include "../affine.h"
  #include "../file_to_object.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_open_file_clicked();

    void onTrXChanged(int);
    void onTrYChanged(int);
    void onTrZChanged(int);
    void onRtXChanged(int);
    void onRtYChanged(int);
    void onRtZChanged(int);
    void onScrollScChanged(int);
    void onSpinScChanged(double);

    void on_radioButton_projection_par_clicked();
    void on_radioButton_projection_cent_clicked();
    void on_radioButton_edges_solid_clicked();
    void on_radioButton_edges_dashed_clicked();
    void on_radioButton_verctices_display_none_clicked();
    void on_radioButton_verctices_display_circle_clicked();
    void on_radioButton_verctices_display_square_clicked();

    void on_pushButton_edges_color_clicked();
    void on_pushButton_vertices_color_clicked();

    void on_pushButton_gif_record_clicked();
    void on_pushButton_image_save_clicked();
    void save_video();

    void on_slider_edges_thickness_valueChanged(int value);
    void on_slider_vertices_size_valueChanged(int value);

    void on_pushButton_background_color_clicked();
    void on_pushButton_init_view_settings_clicked();

    void setMouseRotation(double x, double y);
    void setWheelScale(int increase_scale);

    void open_obj_file();

private:
    Ui::MainWindow *ui;
    void connectSignals();
    void disconnectSignals();
    QGifImage *gif;
    QImage *frame;
    QTimer *timer;
    int count;
    QString file_name;
};
#endif // MAINWINDOW_H
