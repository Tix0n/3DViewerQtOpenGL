#include "mainwindow.h"

#include "glview.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  gif = NULL;
  timer = NULL;
  time = 0;
  ui->setupUi(this);

  settings = new QSettings("Channelle&Larraqan", "3d_viewer", this);
  load_settings();

  setupMenuActions_back_color();
  setupMenuActions_line_color();
  setupMenuActions_vertex_type();
  setupMenuActions_vertex_color();

  connect(this, &MainWindow::openobj, ui->widget, &glView::open_obj);
  connect(ui->widget, &glView::set_counts, this, &MainWindow::set_counts);

  connect(ui->solid_line, &QAction::triggered, this,
          &MainWindow::on_solid_line_triggered);
  connect(ui->dotted_line, &QAction::triggered, this,
          &MainWindow::on_dotted_line_triggered);

  connect(ui->parallel_projection, &QAction::triggered, this,
          &MainWindow::on_parallel_projection_triggered);
  connect(ui->central_projection, &QAction::triggered, this,
          &MainWindow::on_central_projection_triggered);
}

void MainWindow::on_actionopen_triggered() {
  QString filePath = NULL;
  filePath = QFileDialog::getOpenFileName(this, NULL, "/~", "OBJ (*.obj)");
  if (!filePath.isNull()) {
    ui->widget->FileName = filePath;
    QFileInfo fileInfo(filePath);
    QString file_Name = fileInfo.fileName();
    ui->name_file->setText(file_Name);
    ui->vertex_count->setText("0");
    ui->line_count->setText("0");
    ui->move_x_spinbox->setValue(0);
    ui->move_y_spinbox->setValue(0);
    ui->move_z_spinbox->setValue(0);
    ui->rotate_x_spinbox->setValue(0);
    ui->rotate_y_spinbox->setValue(0);
    ui->rotate_z_spinbox->setValue(0);
    ui->scaling_butt->setValue(1);
    emit openobj();
  }
}

void MainWindow::set_counts(int vertex, int lines) {
  ui->vertex_count->setText(QString::number(vertex));
  ui->line_count->setText(QString::number(lines));
}

void MainWindow::setupMenuActions_back_color() {
  signalMapper_back_color = new QSignalMapper(this);

  connect(ui->background_black, SIGNAL(triggered()), signalMapper_back_color,
          SLOT(map()));
  connect(ui->background_white, SIGNAL(triggered()), signalMapper_back_color,
          SLOT(map()));
  connect(ui->background_red, SIGNAL(triggered()), signalMapper_back_color,
          SLOT(map()));
  connect(ui->background_blue, SIGNAL(triggered()), signalMapper_back_color,
          SLOT(map()));
  connect(ui->background_green, SIGNAL(triggered()), signalMapper_back_color,
          SLOT(map()));

  signalMapper_back_color->setMapping(ui->background_black, 1);
  signalMapper_back_color->setMapping(ui->background_white, 2);
  signalMapper_back_color->setMapping(ui->background_red, 3);
  signalMapper_back_color->setMapping(ui->background_blue, 4);
  signalMapper_back_color->setMapping(ui->background_green, 5);

  connect(signalMapper_back_color, SIGNAL(mapped(int)), this,
          SLOT(action_background_triggered(int)));
}

void MainWindow::action_background_triggered(int id) {
  ui->background_black->setChecked(id == 1);
  ui->background_white->setChecked(id == 2);
  ui->background_red->setChecked(id == 3);
  ui->background_blue->setChecked(id == 4);
  ui->background_green->setChecked(id == 5);
  ui->widget->value_background_color = id;
  ui->widget->flag_background_color = true;
  ui->widget->update_figure();
}

void MainWindow::setupMenuActions_line_color() {
  signalMapper_line_color = new QSignalMapper(this);

  connect(ui->line_black, SIGNAL(triggered()), signalMapper_line_color,
          SLOT(map()));
  connect(ui->line_white, SIGNAL(triggered()), signalMapper_line_color,
          SLOT(map()));
  connect(ui->line_red, SIGNAL(triggered()), signalMapper_line_color,
          SLOT(map()));
  connect(ui->line_blue, SIGNAL(triggered()), signalMapper_line_color,
          SLOT(map()));
  connect(ui->line_green, SIGNAL(triggered()), signalMapper_line_color,
          SLOT(map()));

  signalMapper_line_color->setMapping(ui->line_black, 2);
  signalMapper_line_color->setMapping(ui->line_white, 1);
  signalMapper_line_color->setMapping(ui->line_red, 3);
  signalMapper_line_color->setMapping(ui->line_blue, 4);
  signalMapper_line_color->setMapping(ui->line_green, 5);

  connect(signalMapper_line_color, SIGNAL(mapped(int)), this,
          SLOT(action_line_triggered(int)));
}

void MainWindow::action_line_triggered(int id) {
  ui->line_white->setChecked(id == 1);
  ui->line_black->setChecked(id == 2);
  ui->line_red->setChecked(id == 3);
  ui->line_blue->setChecked(id == 4);
  ui->line_green->setChecked(id == 5);
  ui->widget->value_line_color = id;
  ui->widget->update_figure();
}

void MainWindow::setupMenuActions_vertex_type() {
  signalMapper_vertex_type = new QSignalMapper(this);

  connect(ui->no_vertex, SIGNAL(triggered()), signalMapper_vertex_type,
          SLOT(map()));
  connect(ui->vertex_circle, SIGNAL(triggered()), signalMapper_vertex_type,
          SLOT(map()));
  connect(ui->vertex_square, SIGNAL(triggered()), signalMapper_vertex_type,
          SLOT(map()));

  signalMapper_vertex_type->setMapping(ui->no_vertex, 1);
  signalMapper_vertex_type->setMapping(ui->vertex_circle, 2);
  signalMapper_vertex_type->setMapping(ui->vertex_square, 3);

  connect(signalMapper_vertex_type, SIGNAL(mapped(int)), this,
          SLOT(action_vertex_triggered(int)));
}

void MainWindow::action_vertex_triggered(int id) {
  ui->no_vertex->setChecked(id == 1);
  ui->vertex_circle->setChecked(id == 2);
  ui->vertex_square->setChecked(id == 3);
  ui->widget->value_vertex_type = id;
  ui->widget->update_figure();
}

void MainWindow::setupMenuActions_vertex_color() {
  signalMapper_vertex_color = new QSignalMapper(this);

  connect(ui->vertex_black, SIGNAL(triggered()), signalMapper_vertex_color,
          SLOT(map()));
  connect(ui->vertex_white, SIGNAL(triggered()), signalMapper_vertex_color,
          SLOT(map()));
  connect(ui->vertex_red, SIGNAL(triggered()), signalMapper_vertex_color,
          SLOT(map()));
  connect(ui->vertex_blue, SIGNAL(triggered()), signalMapper_vertex_color,
          SLOT(map()));
  connect(ui->vertex_green, SIGNAL(triggered()), signalMapper_vertex_color,
          SLOT(map()));

  signalMapper_vertex_color->setMapping(ui->vertex_black, 1);
  signalMapper_vertex_color->setMapping(ui->vertex_white, 2);
  signalMapper_vertex_color->setMapping(ui->vertex_red, 3);
  signalMapper_vertex_color->setMapping(ui->vertex_blue, 4);
  signalMapper_vertex_color->setMapping(ui->vertex_green, 5);

  connect(signalMapper_vertex_color, SIGNAL(mapped(int)), this,
          SLOT(action_vertex_color_triggered(int)));
}

void MainWindow::action_vertex_color_triggered(int id) {
  ui->vertex_black->setChecked(id == 1);
  ui->vertex_white->setChecked(id == 2);
  ui->vertex_red->setChecked(id == 3);
  ui->vertex_blue->setChecked(id == 4);
  ui->vertex_green->setChecked(id == 5);
  ui->widget->value_vertex_color = id;
  ui->widget->update_figure();
}

void MainWindow::on_move_x_spinbox_valueChanged(double arg) {
  ui->widget->x_move = arg;
  ui->widget->update_figure();
}

void MainWindow::on_move_y_spinbox_valueChanged(double arg) {
  ui->widget->y_move = arg;
  ui->widget->update_figure();
}

void MainWindow::on_move_z_spinbox_valueChanged(double arg) {
  ui->widget->z_move = arg;
  ui->widget->update_figure();
}

double radians(double degrees) {
  return degrees * 3.14159265358979323846 / 180.0;
}

void MainWindow::on_rotate_x_spinbox_valueChanged(double arg1) {
  ui->widget->x_rotate = radians(-arg1);
  ui->widget->update_figure();
}

void MainWindow::on_rotate_y_spinbox_valueChanged(double arg1) {
  ui->widget->y_rotate = radians(-arg1);
  ui->widget->update_figure();
}

void MainWindow::on_rotate_z_spinbox_valueChanged(double arg1) {
  ui->widget->z_rotate = radians(-arg1);
  ui->widget->update_figure();
}

void MainWindow::on_scaling_butt_valueChanged(double arg1) {
  ui->widget->scale_change = arg1;
  ui->widget->update_figure();
}

void MainWindow::on_solid_line_triggered() {
  if (!(ui->solid_line->isChecked())) {
    ui->solid_line->setChecked(true);
  }
  ui->dotted_line->setChecked(false);
  ui->widget->flag_solid_dotted_line = false;
  ui->widget->update_figure();
}

void MainWindow::on_dotted_line_triggered() {
  if (!(ui->dotted_line->isChecked())) {
    ui->dotted_line->setChecked(true);
  }
  ui->solid_line->setChecked(false);
  ui->widget->flag_solid_dotted_line = true;
  ui->widget->update_figure();
}

void MainWindow::on_parallel_projection_triggered() {
  if (!(ui->parallel_projection->isChecked())) {
    ui->parallel_projection->setChecked(true);
  }
  ui->central_projection->setChecked(false);
  ui->widget->value_projection = 0;
  ui->widget->flag_projection = true;
  ui->widget->update_figure();
}

void MainWindow::on_central_projection_triggered() {
  if (!(ui->central_projection->isChecked())) {
    ui->central_projection->setChecked(true);
  }
  ui->parallel_projection->setChecked(false);
  ui->widget->value_projection = 1;
  ui->widget->flag_projection = true;
  ui->widget->update_figure();
}

void MainWindow::on_action_bmp_triggered() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "",
                                                  tr("BMP (*.bmp)"));
  if (!fileName.isEmpty()) {
    QString format = "BMP";
    ui->widget->saveImage(fileName, format);
  }
}

void MainWindow::on_action_jpeg_triggered() {
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "",
                                                  tr("JPEG (*.jpeg)"));
  if (!fileName.isEmpty()) {
    QString format = "JPEG";
    ui->widget->saveImage(fileName, format);
  }
}

void MainWindow::on_start_screencast_clicked() {
  if (time == 0) {
    gif = new QGifImage;
    gif->setDefaultDelay(100);
    time = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(save_gif()));
    timer->start(100);
  }
}

void MainWindow::save_gif() {
  time++;
  image = ui->widget->grab().toImage();
  gif->addFrame(image, QPoint(0, 0));
  if (time == 50) {
    timer->stop();
    time = 0;
    disconnect(timer, SIGNAL(timeout()), this, SLOT(save_gif()));
    gif_Path = QFileDialog::getSaveFileName(this, NULL, NULL, "GIF (*.gif)");
    if (!gif_Path.isEmpty()) gif->save(gif_Path);
    delete gif;
    gif = NULL;
  }
}

void MainWindow::on_custom_vertex_size_valueChanged(int value) {
  ui->widget->custom_vertex_size = value;
  ui->widget->update_figure();
}

void MainWindow::on_custom_line_size_valueChanged(int value) {
  ui->widget->custom_line_size = value;
  ui->widget->update_figure();
}

MainWindow::~MainWindow() {
  save_settings();
  delete signalMapper_back_color;
  delete signalMapper_line_color;
  delete signalMapper_vertex_type;
  delete signalMapper_vertex_color;
  delete settings;
  if (gif != NULL) {
    delete gif;
  }
  if (timer != NULL) {
    delete timer;
  }
  delete ui;
}
void MainWindow::save_settings() {
  settings->setValue("title", windowTitle());

  settings->setValue("central_projection", ui->central_projection->isChecked());
  settings->setValue("parallel_projection",
                     ui->parallel_projection->isChecked());
  settings->setValue("value_projection", ui->widget->value_projection);

  settings->setValue("solid_line", ui->solid_line->isChecked());
  settings->setValue("dotted_line", ui->dotted_line->isChecked());
  settings->setValue("flag_solid_dotted_line",
                     ui->widget->flag_solid_dotted_line);

  settings->setValue("background_black", ui->background_black->isChecked());
  settings->setValue("background_white", ui->background_white->isChecked());
  settings->setValue("background_red", ui->background_red->isChecked());
  settings->setValue("background_blue", ui->background_blue->isChecked());
  settings->setValue("background_green", ui->background_green->isChecked());
  settings->setValue("value_background_color",
                     ui->widget->value_background_color);

  settings->setValue("line_black", ui->line_black->isChecked());
  settings->setValue("line_white", ui->line_white->isChecked());
  settings->setValue("line_red", ui->line_red->isChecked());
  settings->setValue("line_blue", ui->line_blue->isChecked());
  settings->setValue("line_green", ui->line_green->isChecked());
  settings->setValue("value_line_color", ui->widget->value_line_color);

  settings->setValue("vertex_black", ui->vertex_black->isChecked());
  settings->setValue("vertex_white", ui->vertex_white->isChecked());
  settings->setValue("vertex_red", ui->vertex_red->isChecked());
  settings->setValue("vertex_blue", ui->vertex_blue->isChecked());
  settings->setValue("vertex_green", ui->vertex_green->isChecked());
  settings->setValue("value_vertex_color", ui->widget->value_vertex_color);

  settings->setValue("no_vertex", ui->no_vertex->isChecked());
  settings->setValue("vertex_circle", ui->vertex_circle->isChecked());
  settings->setValue("vertex_square", ui->vertex_square->isChecked());
  settings->setValue("value_vertex_type", ui->widget->value_vertex_type);

  settings->setValue("custom_vertex_size", ui->widget->custom_vertex_size);
  settings->setValue("custom_line_size", ui->widget->custom_line_size);
}

void MainWindow::load_settings() {
  setWindowTitle(settings->value("title", "3d_viewer").toString());
  ui->central_projection->setChecked(
      settings->value("central_projection", true).toBool());
  ui->parallel_projection->setChecked(
      settings->value("parallel_projection", false).toBool());
  ui->widget->value_projection = settings->value("value_projection", 0).toInt();
  ;
  ui->widget->flag_projection = true;
  ui->solid_line->setChecked(settings->value("solid_line", true).toBool());
  ui->dotted_line->setChecked(settings->value("dotted_line", false).toBool());
  ui->widget->flag_solid_dotted_line =
      settings->value("flag_solid_dotted_line", false).toBool();
  ui->background_black->setChecked(
      settings->value("background_black", true).toBool());
  ui->background_white->setChecked(
      settings->value("background_white", false).toBool());
  ui->background_red->setChecked(
      settings->value("background_red", false).toBool());
  ui->background_blue->setChecked(
      settings->value("background_blue", false).toBool());
  ui->background_green->setChecked(
      settings->value("background_green", false).toBool());
  ui->widget->value_background_color =
      settings->value("value_background_color", 1).toInt();
  ui->line_black->setChecked(settings->value("line_black", false).toBool());
  ui->line_white->setChecked(settings->value("line_white", true).toBool());
  ui->line_red->setChecked(settings->value("line_red", false).toBool());
  ui->line_blue->setChecked(settings->value("line_blue", false).toBool());
  ui->line_green->setChecked(settings->value("line_green", false).toBool());
  ui->widget->value_line_color = settings->value("value_line_color", 1).toInt();
  ui->vertex_black->setChecked(settings->value("vertex_black", false).toBool());
  ui->vertex_white->setChecked(settings->value("vertex_white", true).toBool());
  ui->vertex_red->setChecked(settings->value("vertex_red", false).toBool());
  ui->vertex_blue->setChecked(settings->value("vertex_blue", false).toBool());
  ui->vertex_green->setChecked(settings->value("vertex_green", false).toBool());
  ui->widget->value_vertex_color =
      settings->value("value_vertex_color", 1).toInt();
  ui->no_vertex->setChecked(settings->value("no_vertex", true).toBool());
  ui->vertex_circle->setChecked(
      settings->value("vertex_circle", false).toBool());
  ui->vertex_square->setChecked(
      settings->value("vertex_square", false).toBool());
  ui->widget->value_vertex_type =
      settings->value("value_vertex_type", 1).toInt();
  ui->widget->custom_vertex_size =
      settings->value("custom_vertex_size", 1).toInt();
  ui->custom_vertex_size->setValue(ui->widget->custom_vertex_size);
  ui->widget->custom_line_size = settings->value("custom_line_size", 1).toInt();
  ui->custom_line_size->setValue(ui->widget->custom_line_size);
}
