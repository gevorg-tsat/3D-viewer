#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ogl.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QSettings mySettings("Viewer");
    ui->radioButton_projection_cent->setChecked((project) mySettings.value("projection").toUInt());
    ui->radioButton_edges_dashed->setChecked(mySettings.value("stripe").toUInt());
    ui->slider_edges_thickness->setValue(mySettings.value("line size").toInt());
    ui->radioButton_verctices_display_circle->setChecked((vert_form) mySettings.value("vertice type").toUInt() == CIRCLE);
    ui->radioButton_verctices_display_square->setChecked((vert_form) mySettings.value("vertice type").toUInt() == SQUARE);
    ui->slider_vertices_size->setValue(mySettings.value("vertice size").toInt());

    connectSignals();

    connect(ui->OGLWindow, &OGL::mouseTrigger, this, &MainWindow::setMouseRotation);
    connect(ui->OGLWindow, &OGL::wheelTrigger, this, &MainWindow::setWheelScale);
}

MainWindow::~MainWindow() {

  delete ui;
}

void MainWindow::on_pushButton_open_file_clicked()
{
  file_name = QFileDialog::getOpenFileName(this, "Open File", QDir::homePath(), "OBJ File (*.obj)");
  ui->lineEdit_file_name->setText(file_name);

  open_obj_file();
}

void MainWindow::onTrXChanged(int trX)
{
  disconnectSignals();
  ui->scroll_translate_x->setValue(trX);
  ui->spin_translate_x->setValue(trX);
  connectSignals();

  ui->OGLWindow->x_moved = (double)trX / 100;
}

void MainWindow::onTrYChanged(int trY)
{
  disconnectSignals();
  ui->scroll_translate_y->setValue(trY);
  ui->spin_translate_y->setValue(trY);
  connectSignals();

  ui->OGLWindow->y_moved = (double)trY / 100;
}

void MainWindow::onTrZChanged(int trZ)
{
  disconnectSignals();
  ui->scroll_translate_z->setValue(trZ);
  ui->spin_translate_z->setValue(trZ);
  connectSignals();

  ui->OGLWindow->z_moved = (double)trZ / 100;
}

void MainWindow::onRtXChanged(int rtX)
{
  disconnectSignals();
  ui->scroll_rotate_x->setValue(rtX);
  ui->spin_rotate_x->setValue(rtX);
  connectSignals();

  ui->OGLWindow->x_rotate = (double)rtX * M_PI / 180.;
}

void MainWindow::onRtYChanged(int rtY)
{
  disconnectSignals();
  ui->scroll_rotate_y->setValue(rtY);
  ui->spin_rotate_y->setValue(rtY);
  connectSignals();

  ui->OGLWindow->y_rotate = (double)rtY * M_PI / 180.;
}

void MainWindow::onRtZChanged(int rtZ)
{
  disconnectSignals();
  ui->scroll_rotate_z->setValue(rtZ);
  ui->spin_rotate_z->setValue(rtZ);
  connectSignals();

  ui->OGLWindow->z_rotate = (double)rtZ * M_PI / 180.;
}

void MainWindow::onScrollScChanged(int sc)
{
  disconnectSignals();
  ui->scroll_scale->setValue(sc);
  ui->spin_scale->setValue(sc > 110. ? (double)(sc - 100.) / 10. : (double)sc / 100.);
  connectSignals();

  ui->OGLWindow->scale = sc > 110. ? (double)(sc - 100.) / 10. : (double)sc / 100.;
}

void MainWindow::onSpinScChanged(double sc)
{
  disconnectSignals();
  ui->scroll_scale->setValue(sc < 1.09001 ? sc * 100. : sc * 10. + 100.);
  ui->spin_scale->setValue(sc);
  connectSignals();

  ui->OGLWindow->scale = sc;
}

void MainWindow::on_radioButton_projection_par_clicked()
{
  ui->OGLWindow->projection = PERSEPCTIVE;
}

void MainWindow::on_radioButton_projection_cent_clicked()
{
  ui->OGLWindow->projection = CENTRAL;
}

void MainWindow::on_radioButton_edges_solid_clicked()
{
  ui->OGLWindow->stripe = SOLID;
}

void MainWindow::on_radioButton_edges_dashed_clicked()
{
  ui->OGLWindow->stripe = DASHED;
}

void MainWindow::on_radioButton_verctices_display_none_clicked()
{
  ui->OGLWindow->vert_type = NONE;
}

void MainWindow::on_radioButton_verctices_display_circle_clicked()
{
  ui->OGLWindow->vert_type = CIRCLE;
}

void MainWindow::on_radioButton_verctices_display_square_clicked()
{
  ui->OGLWindow->vert_type = SQUARE;
}

void MainWindow::on_pushButton_edges_color_clicked()
{
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color.isValid()) {
    ui->OGLWindow->line_blue = color.blueF();
    ui->OGLWindow->line_green = color.greenF();
    ui->OGLWindow->line_red = color.redF();
  }
}

void MainWindow::on_pushButton_vertices_color_clicked()
{
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color.isValid()) {
    ui->OGLWindow->vert_blue = color.blueF();
    ui->OGLWindow->vert_green = color.greenF();
    ui->OGLWindow->vert_red = color.redF();
  }
}

void MainWindow::on_pushButton_gif_record_clicked()
{
  gif = new QGifImage;
  frame = new QImage;
  timer = new QTimer(this);
  count = 0;
  connect(timer, SIGNAL(timeout()), this, SLOT(save_video()));
  timer->start(50);
}

void MainWindow::save_video() {
  count++;
  *frame = ui->OGLWindow->grabFramebuffer().scaled(640, 480, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  gif->addFrame(*frame);
  if (count == 50) {
    timer->stop();
    QString save = NULL;
    save = QFileDialog::getSaveFileName(this, NULL, NULL, "GIF (*.gif)");
    if (!save.isNull()) gif->save(save);
  }
}

void MainWindow::on_pushButton_image_save_clicked()
{
  QString save = NULL;
  save = QFileDialog::getSaveFileName(this, NULL, NULL,
                                      "JPEG (*.jpeg) ;; BMP (*.bmp)");
  if (!save.isNull()) ui->OGLWindow->grabFramebuffer().save(save, NULL, 100);
}


void MainWindow::on_slider_edges_thickness_valueChanged(int value)
{
  ui->OGLWindow->line_thickness = value;
}

void MainWindow::on_slider_vertices_size_valueChanged(int value)
{
  ui->OGLWindow->vert_size = value;
}

void MainWindow::connectSignals()
{
  connect(ui->scroll_translate_x, &QScrollBar::valueChanged, this, &MainWindow::onTrXChanged);
  connect(ui->spin_translate_x, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::onTrXChanged);
  connect(ui->scroll_translate_y, &QScrollBar::valueChanged, this, &MainWindow::onTrYChanged);
  connect(ui->spin_translate_y, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::onTrYChanged);
  connect(ui->scroll_translate_z, &QScrollBar::valueChanged, this, &MainWindow::onTrZChanged);
  connect(ui->spin_translate_z, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::onTrZChanged);

  connect(ui->scroll_rotate_x, &QScrollBar::valueChanged, this, &MainWindow::onRtXChanged);
  connect(ui->spin_rotate_x, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::onRtXChanged);
  connect(ui->scroll_rotate_y, &QScrollBar::valueChanged, this, &MainWindow::onRtYChanged);
  connect(ui->spin_rotate_y, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::onRtYChanged);
  connect(ui->scroll_rotate_z, &QScrollBar::valueChanged, this, &MainWindow::onRtZChanged);
  connect(ui->spin_rotate_z, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::onRtZChanged);

  connect(ui->scroll_scale, &QScrollBar::valueChanged, this, &MainWindow::onScrollScChanged);
  connect(ui->spin_scale, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onSpinScChanged);
}

void MainWindow::disconnectSignals()
{
  disconnect(ui->scroll_translate_x, &QScrollBar::valueChanged, this, &MainWindow::onTrXChanged);
  disconnect(ui->spin_translate_x, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::onTrXChanged);
  disconnect(ui->scroll_translate_y, &QScrollBar::valueChanged, this, &MainWindow::onTrYChanged);
  disconnect(ui->spin_translate_y, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::onTrYChanged);
  disconnect(ui->scroll_translate_y, &QScrollBar::valueChanged, this, &MainWindow::onTrYChanged);
  disconnect(ui->spin_translate_y, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::onTrYChanged);
  disconnect(ui->scroll_translate_z, &QScrollBar::valueChanged, this, &MainWindow::onTrZChanged);
  disconnect(ui->spin_translate_z, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::onTrZChanged);

  disconnect(ui->scroll_rotate_x, &QScrollBar::valueChanged, this, &MainWindow::onRtXChanged);
  disconnect(ui->spin_rotate_x, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::onRtXChanged);
  disconnect(ui->scroll_rotate_y, &QScrollBar::valueChanged, this, &MainWindow::onRtYChanged);
  disconnect(ui->spin_rotate_y, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::onRtYChanged);
  disconnect(ui->scroll_rotate_z, &QScrollBar::valueChanged, this, &MainWindow::onRtZChanged);
  disconnect(ui->spin_rotate_z, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::onRtZChanged);

  disconnect(ui->scroll_scale, &QScrollBar::valueChanged, this, &MainWindow::onScrollScChanged);
  disconnect(ui->spin_scale, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &MainWindow::onSpinScChanged);
}

void MainWindow::on_pushButton_background_color_clicked()
{
  QColor color = QColorDialog::getColor(Qt::white, this, "Choose Color");
  if (color.isValid()) {
    ui->OGLWindow->color_blue = color.blueF();
    ui->OGLWindow->color_green = color.greenF();
    ui->OGLWindow->color_red= color.redF();
  }
}

void MainWindow::on_pushButton_init_view_settings_clicked()
{
    ui->scroll_translate_x->setValue(0);
    ui->scroll_translate_y->setValue(0);
    ui->scroll_translate_z->setValue(0);

    ui->scroll_rotate_x->setValue(0);
    ui->scroll_rotate_y->setValue(0);
    ui->scroll_rotate_z->setValue(0);

    ui->spin_scale->setValue(1.);
    onSpinScChanged(1.);

    on_radioButton_projection_cent_clicked();
    ui->radioButton_projection_cent->setChecked(true);

    on_radioButton_edges_solid_clicked();
    ui->radioButton_edges_solid->setChecked(true);

    on_slider_edges_thickness_valueChanged(1);
    ui->slider_edges_thickness->setValue(1);

    on_radioButton_verctices_display_none_clicked();
    ui->radioButton_verctices_display_none->setChecked(true);

    on_slider_vertices_size_valueChanged(1);
    ui->slider_vertices_size->setValue(1);

    ui->OGLWindow->color_blue = 1.;
    ui->OGLWindow->color_green = 1.;
    ui->OGLWindow->color_red= 1;

    ui->OGLWindow->vert_blue = 0.;
    ui->OGLWindow->vert_green = 0.;
    ui->OGLWindow->vert_red = 0.;

    ui->OGLWindow->line_blue = 0.;
    ui->OGLWindow->line_green = 0.;
    ui->OGLWindow->line_red = 0.;

//    if (ui->OGLWindow->file_opened) {
//        clear_obj(&ui->OGLWindow->obj);
//        parse_file(obj_file_name, &ui->OGLWindow->obj);
//    }
}

void MainWindow::setMouseRotation(double x, double y) {
    int shift_x = static_cast<int>(fmod(static_cast<double>(ui->scroll_rotate_x->value() + x * 1. / 100. + 180.), 360.) - 180);
    int shift_y = static_cast<int>(fmod(static_cast<double>(ui->scroll_rotate_y->value() + y * 1. / 100. + 180.), 360.) - 180);
    ui->scroll_rotate_x->setValue(shift_x);
    ui->scroll_rotate_y->setValue(shift_y);
}

void MainWindow::open_obj_file() {
    std::string s = file_name.toStdString();
    char *name = const_cast<char *>(s.c_str());

    if (ui->OGLWindow->file_opened)
        clear_obj(&ui->OGLWindow->obj);

    int status = parse_file(name, &ui->OGLWindow->obj);

    if (status) {
        ui->OGLWindow->file_opened = 0;
        return;
    }
    ui->OGLWindow->file_opened = 1;

    ui->lineEdit_vert_num->setText(QString::number(ui->OGLWindow->obj.vertices_count));
    ui->lineEdit_edges_num->setText(QString::number(ui->OGLWindow->obj.square_cnt * 4 + ui->OGLWindow->obj.triangle_cnt * 3));
}

void MainWindow::setWheelScale(int increase_scale) {
  int shift = ui->scroll_scale->value() + increase_scale;
  if (shift >= 1 && shift <= 200) onScrollScChanged(shift);
}

