#include "glview.h"

#include "parser.h"

glView::glView(QWidget* parent) : QOpenGLWidget(parent) {
  x_move = 0;
  y_move = 0;
  z_move = 0;
  x_rotate = 0;
  y_rotate = 0;
  z_rotate = 0;
  scale_change = 0;
  flag_solid_dotted_line = false;
  flag_projection = false;
  value_background_color = 1;
  value_line_color = 1;
  value_vertex_type = 1;
  value_vertex_color = 1;
  custom_vertex_size = 1;
  custom_line_size = 1;
  flag_background_color = true;
  flag_centering = false;
}

glView::~glView() { free_matrix(&figure); }

void glView::initializeGL() {
  set_background_color();
  glEnable(GL_DEPTH_TEST);
}
void glView::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void glView::paintGL() {
  if (flag_centering) {
    centering();
  }
  if (flag_projection) {
    set_projection();
  }
  if (flag_background_color) {
    set_background_color();
  }
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (int i = 0; i < figure.number_of_vertex * 3; ++i) {
    figure.matrix_of_vertex[i] = figure.matrix_of_vertex_origin[i];
  }
  if (x_rotate) {
    rotate_for_asix_x(x_rotate);
  }
  if (y_rotate) {
    rotate_for_asix_y(y_rotate);
  }
  if (z_rotate) {
    rotate_for_asix_z(z_rotate);
  }

  if (x_move) {
    move_for_asix_x(x_move);
  }
  if (y_move) {
    move_for_asix_y(y_move);
  }
  if (z_move) {
    move_for_asix_z(z_move);
  }

  if (scale_change) {
    scaling();
  }

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  draw_figure();
}

void glView::set_projection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  float view = 5 * (figure.z_max / (2 * tan(60.0 * M_PI / 180 / 2)));
  if (value_projection) {
    glOrtho(figure.x_min * 2.5, figure.x_max * 2.5, figure.y_min * 2.5,
            figure.y_max * 2.5, view, 5000);
  } else {
    glFrustum(figure.x_min * 1.25, figure.x_max * 1.25, figure.y_min * 1.25,
              figure.y_max * 1.25, view, 5000);
  }
  glTranslated(0, 0, -view * 2);
  flag_projection = false;
}

void glView::draw_figure() {
  if (figure.load_result == 1) {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glVertexPointer(3, GL_FLOAT, 0, figure.matrix_of_vertex);
    glEnableClientState(GL_VERTEX_ARRAY);

    glLineStipple(1, 0x00FF);
    glLineWidth(custom_line_size);
    if (flag_solid_dotted_line) {
      glEnable(GL_LINE_STIPPLE);
    }
    if (value_line_color) {
      set_line_color();
    }
    glDrawElements(GL_LINES, figure.number_of_faces_all * 2, GL_UNSIGNED_INT,
                   figure.matrix_of_index);
    glDisable(GL_LINE_STIPPLE);

    if (value_vertex_type != 1 && custom_vertex_size != 0) {
      if (value_vertex_type == 2)
        glEnable(GL_POINT_SMOOTH);
      else
        glDisable(GL_POINT_SMOOTH);
      set_vertex_size();
      set_vertex_color();
      glDrawArrays(GL_POINTS, 0, figure.number_of_vertex);
    }

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_DEPTH_TEST);
  }
}

void glView::set_background_color() {
  if (value_background_color == 1) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  } else if (value_background_color == 2) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  } else if (value_background_color == 3) {
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  } else if (value_background_color == 4) {
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  } else if (value_background_color == 5) {
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
  }
  flag_background_color = false;
}

void glView::set_line_color() {
  if (value_line_color == 1) {
    glColor3f(1.0f, 1.0f, 1.0f);
  } else if (value_line_color == 2) {
    glColor3f(0.0f, 0.0f, 0.0f);
  } else if (value_line_color == 3) {
    glColor3f(1.0f, 0.0f, 0.0f);
  } else if (value_line_color == 4) {
    glColor3f(0.0f, 0.0f, 1.0f);
  } else if (value_line_color == 5) {
    glColor3f(0.0f, 1.0f, 0.0f);
  }
}

void glView::set_vertex_color() {
  if (value_vertex_color == 1) {
    glColor3f(0.0f, 0.0f, 0.0f);
  } else if (value_vertex_color == 2) {
    glColor3f(1.0f, 1.0f, 1.0f);
  } else if (value_vertex_color == 3) {
    glColor3f(1.0f, 0.0f, 0.0f);
  } else if (value_vertex_color == 4) {
    glColor3f(0.0f, 0.0f, 1.0f);
  } else if (value_vertex_color == 5) {
    glColor3f(0.0f, 1.0f, 0.0f);
  }
}

void glView::set_vertex_size() { glPointSize(custom_vertex_size); }

void glView::set_vertex_type() {
  if (value_vertex_type == 2) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, figure.matrix_of_vertex_origin);
    glDrawArrays(GL_POINTS, 0, figure.number_of_vertex * 3);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void glView::centering() {
  centr_x = figure.x_min + (figure.x_max - figure.x_min) / 2;
  centr_y = figure.y_min + (figure.y_max - figure.y_min) / 2;
  centr_z = figure.z_min + (figure.z_max - figure.z_min) / 2;
  move_model(figure.matrix_of_vertex_origin, 0, figure.number_of_vertex * 3,
             -centr_x);
  move_model(figure.matrix_of_vertex_origin, 1, figure.number_of_vertex * 3,
             -centr_y);
  move_model(figure.matrix_of_vertex_origin, 2, figure.number_of_vertex * 3,
             -centr_z);
  flag_centering = false;
  figure.x_min -= centr_x;
  figure.x_max -= centr_x;
  figure.y_min -= centr_y;
  figure.y_max -= centr_y;
  figure.z_min -= centr_z;
  figure.z_max -= centr_z;
  double diagonal_x = std::sqrt(std::pow(figure.x_max - figure.x_min, 2));
  double diagonal_y = std::sqrt(std::pow(figure.y_max - figure.y_min, 2));
  double diagonal_z = std::sqrt(std::pow(figure.z_max - figure.z_min, 2));
  scaleFactor_x = diagonal_x / 100.0;
  scaleFactor_y = diagonal_y / 100.0;
  scaleFactor_z = diagonal_z / 100.0;
}

void glView::scaling() {
  scale_model(figure.matrix_of_vertex, figure.number_of_vertex * 3,
              scale_change);
}

void glView::open_obj() {
  if (!FileName.isEmpty()) {
    free_matrix(&figure);
    QByteArray ba = FileName.toLocal8Bit();
    char* name_of_file = ba.data();
    open_file(name_of_file, &figure);
    flag_centering = true;
    flag_projection = true;
    update();
  }
  emit set_counts(figure.number_of_vertex, figure.number_of_faces_all);
}

void glView::move_for_asix_x(double value) {
  move_model(figure.matrix_of_vertex, 0, figure.number_of_vertex * 3,
             value * scaleFactor_x);
}

void glView::move_for_asix_y(double value) {
  move_model(figure.matrix_of_vertex, 1, figure.number_of_vertex * 3,
             value * scaleFactor_y);
}

void glView::move_for_asix_z(double value) {
  move_model(figure.matrix_of_vertex, 2, figure.number_of_vertex * 3,
             value * scaleFactor_z);
}

void glView::update_figure() { update(); }

void glView::rotate_for_asix_x(double value) {
  rotation_by_ox(figure.matrix_of_vertex, figure.number_of_vertex, value);
}

void glView::rotate_for_asix_y(double value) {
  rotation_by_oy(figure.matrix_of_vertex, figure.number_of_vertex, value);
}

void glView::rotate_for_asix_z(double value) {
  rotation_by_oz(figure.matrix_of_vertex, figure.number_of_vertex, value);
}

bool glView::saveImage(const QString& fileName, const QString& format) {
  makeCurrent();  // setting the current OpenGL context
  QSize size = this->size();
  int width = size.width();
  int height = size.height();
  QOpenGLFramebufferObject fbo(width, height);  // creating a frame buffer
  fbo.bind();                                   // making it current
  paintGL();                                    // draw a scene into it
  QImage image = fbo.toImage();  // getting an image from the frame buffer
  return image.save(
      fileName,
      format.toStdString().c_str());  // saving the image to a file
}
