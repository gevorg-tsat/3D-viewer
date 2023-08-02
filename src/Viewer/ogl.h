#ifndef OGL_H
#define OGL_H

#include <QMainWindow>
#include <QtOpenGL/QtOpenGL>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>

extern "C" {
    #include "../affine.h"
    #include "../file_to_object.h"
}

typedef enum { NONE = 0, CIRCLE, SQUARE } vert_form;
typedef enum { SOLID = 0, DASHED } stripe_type;
typedef enum { PERSEPCTIVE = 0, CENTRAL } project;

class OGL: public QOpenGLWidget {
    Q_OBJECT

public:
    OGL(QWidget *parent = nullptr);
    ~OGL();
    double x_moved;
    double y_moved;
    double z_moved;
    double x_rotate;
    double y_rotate;
    double z_rotate;
    double x_moved_curr;
    double y_moved_curr;
    double z_moved_curr;
    double x_rotate_curr;
    double y_rotate_curr;
    double z_rotate_curr;
    double scale;
    double scale_curr;
    int file_opened;
    project project_curr;

    // настройки
    double color_red;
    double color_green;
    double color_blue;
    project projection;
    double line_red;
    double line_green;
    double line_blue;
    double line_thickness;
    stripe_type stripe;
    double vert_red;
    double vert_green;
    double vert_blue;
    double vert_size;
    vert_form vert_type;
    file_data obj;


private:
    QTimer timer;
    double xRot, yRot, zRot;
    double xRot_curr, yRot_curr, zRot_curr;
    QPoint mPos;
    void update_view();
    void do_scaling();
    void initializeGL() override;
    void paintGL() override;

signals:
    void mouseTrigger(double x, double y);
    void wheelTrigger(int increase_scale);

protected:
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void wheelEvent(QWheelEvent *event) override;
};


#endif // OGL_H
