#include "ogl.h"

OGL::OGL(QWidget *parent) : QOpenGLWidget(parent) {
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
    timer.start(20);
}

OGL::~OGL() {
  QSettings mySettings("Viewer");

  mySettings.setValue("red", color_red);
  mySettings.setValue("green", color_green);
  mySettings.setValue("blue", color_blue);

  mySettings.setValue("line red", line_red);
  mySettings.setValue("line green", line_green);
  mySettings.setValue("line blue", line_blue);
  mySettings.setValue("line size", line_thickness);

  mySettings.setValue("vertice red", vert_red);
  mySettings.setValue("vertice green", vert_green);
  mySettings.setValue("vertice blue", vert_blue);
  mySettings.setValue("vertice size", vert_size);
  mySettings.setValue("vertice type", vert_type);

  mySettings.setValue("stripe", stripe);
  mySettings.setValue("projection", projection);

  if (file_opened)
    clear_obj(&obj);
}

void OGL::initializeGL() {
  scale_curr = scale = 1;

  x_rotate = x_rotate_curr = 0.;
  y_rotate = y_rotate_curr = 0.;
  z_rotate = z_rotate_curr = 0.;

  x_moved = x_moved_curr = 0.0;
  y_moved = y_moved_curr = 0.0;
  z_moved = z_moved_curr = 0.0;

  file_opened = 0;

  QSettings mySettings("Viewer");

  color_red = mySettings.value("red").toDouble();
  color_green = mySettings.value("green").toDouble();
  color_blue = mySettings.value("blue").toDouble();

  line_red = mySettings.value("line red").toDouble();
  line_green = mySettings.value("line green").toDouble();
  line_blue = mySettings.value("line blue").toDouble();
  line_thickness = mySettings.value("line size").toDouble();

  vert_red = mySettings.value("vertice red").toDouble();
  vert_green = mySettings.value("vertice green").toDouble();
  vert_blue = mySettings.value("vertice blue").toDouble();
  vert_size = mySettings.value("vertice size").toDouble();
  vert_type = (vert_form) mySettings.value("vertice type").toUInt();

  stripe = (stripe_type) mySettings.value("stripe").toUInt();
  projection = (project) mySettings.value("projection").toUInt();

  project_curr = (project) !projection;
  // glClearColor(color_red, color_green, color_blue, 1);
}

void OGL::paintGL() {
  glClearColor(color_red, color_green, color_blue, 0);
  if (file_opened) {
      update_view();

      translate_ox_object(&obj, x_moved - x_moved_curr);
      translate_oy_object(&obj, y_moved - y_moved_curr);
      translate_oz_object(&obj, z_moved - z_moved_curr);

//      rotate_ox_object(&obj, xRot - xRot_curr);
//      rotate_oy_object(&obj, yRot - yRot_curr);
//      rotate_oz_object(&obj, zRot - zRot_curr);

      rotate_ox_object(&obj, x_rotate - x_rotate_curr);
      rotate_oy_object(&obj, y_rotate - y_rotate_curr);
      rotate_oz_object(&obj, z_rotate - z_rotate_curr);

      xRot_curr = xRot;
      yRot_curr = yRot;
      zRot_curr = zRot;

      x_moved_curr = x_moved;
      y_moved_curr = y_moved;
      z_moved_curr = z_moved;

      x_rotate_curr = x_rotate;
      y_rotate_curr = y_rotate;
      z_rotate_curr = z_rotate;

      glEnableClientState(GL_VERTEX_ARRAY);
      glVertexPointer(3, GL_DOUBLE, 0, obj.vertices);

      if (vert_type != NONE) {
          glPointSize(vert_size);
          glColor3d(vert_red, vert_green, vert_blue);
          if (vert_type == CIRCLE) glEnable(GL_POINT_SMOOTH);
          if (vert_type == SQUARE) glDisable(GL_POINT_SMOOTH);
          glDrawElements(GL_POINTS, obj.triangle_cnt * 3, GL_UNSIGNED_INT, obj.facets_coor_triangle);
          glDrawElements(GL_POINTS, obj.square_cnt * 4, GL_UNSIGNED_INT, obj.facets_coor_square);
      }

      glLineWidth(line_thickness);
      glColor3d(line_red, line_green, line_blue);

      if (stripe) {
          glEnable(GL_LINE_STIPPLE);
          glLineStipple(1, 0x00F0);
      } else {
          glDisable(GL_LINE_STIPPLE);
      }

      glDrawElements(GL_LINE_LOOP, obj.triangle_cnt * 3, GL_UNSIGNED_INT, obj.facets_coor_triangle);
      glDrawElements(GL_LINE_LOOP, obj.square_cnt * 4, GL_UNSIGNED_INT, obj.facets_coor_square);
      glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void OGL::mousePressEvent(QMouseEvent* mo) {
   mPos = mo->pos();
}

void OGL::mouseMoveEvent(QMouseEvent* mo) {
  xRot = (mo->pos().y() - mPos.y());
  yRot = (mo->pos().x() - mPos.x());

  emit mouseTrigger(xRot, yRot);
}

void OGL::wheelEvent(QWheelEvent* event) {
  int increase_scale = event->angleDelta().y() < 0 ? -2 : 2;

  emit wheelTrigger(increase_scale);
}

void OGL::update_view() {
  if (scale != scale_curr) {
    do_scaling();
    scale_curr = scale;
  }
  if (project_curr != projection) {
    do_scaling();
  }
  project_curr = projection;
}

void OGL::do_scaling() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  if (projection == PERSEPCTIVE) {
    glFrustum(-1, 1, -1, 1, 2, 15);
    glTranslated(0, 0, -7);
  } else {
    glOrtho(-1, 1, -1, 1, 100, -100);
  }

  scale_object(&obj, scale / scale_curr);
}

