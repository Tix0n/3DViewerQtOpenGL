#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QMainWindow>
#include <QPoint>
#include <QSettings>
#include <QSignalMapper>
#include <QString>
#include <QTimer>
#include <cmath>

#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
  @brief MainWindow class.
It contains class member definitions such as constructor, destructor methods,
slots, and signals. The class contains variables for saving and loading
settings, signal mappers for matching actions to specific IDs, a timer, and
image objects for creating animated GIFs. Also in this class, various slots are
defined that are called during user interaction events with the interface, such
as changing the values ​​of spinboxes for moving, rotating and scaling
objects, choosing the type of projection and line color, setting the background
color, etc.
*/
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
    @brief Class constructor.
    @param parent the reference to parent object.
  */
  MainWindow(QWidget* parent = nullptr);
  /**
    @brief Class destructor.
  */
  ~MainWindow();
  /**
    @brief This feature saves application settings to a QSettings* settings. The
    code starts by saving the title of the main window, and then saves all other
    settings, which include settings for projection, line style, background
    color, line color, vertex color, vertex type, vertex size, and line size.
    The settings object is used to save the settings. This allows you to restore
    the previously saved settings the next time you start the application.
  */
  void save_settings();
  /**
    @brief The function restores the previous settings of the application when
    it is launched, so that the user can continue working with the application
    exactly where he left off the last time.
  */
  void load_settings();

 private:
  Ui::MainWindow* ui;  ///< Pointer to a class generated from the user interface
                       ///< file mainwindow.ui using the Qt Designer tool.
  QSettings* settings;  ///< Object for storing application settings.
  QSignalMapper*
      signalMapper_back_color;  ///< Pointer that is used to bind signals from
                                ///< the main window's background color picker
                                ///< widgets to a procedure that changes the
                                ///< background color.
  QSignalMapper*
      signalMapper_line_color;  ///< Pointer that is used to bind signals from
                                ///< the main window's line color picker widgets
                                ///< to a procedure that changes the line color.
  QSignalMapper*
      signalMapper_vertex_type;  ///< Pointer that is used to bind signals from
                                 ///< the main window's type of vertices to a
                                 ///< procedure that changes the type of
                                 ///< vertices.
  QSignalMapper*
      signalMapper_vertex_size;  ///< Pointer that is used to bind signals from
                                 ///< the main window's size of vertices to a
                                 ///< procedure that changes the size of
                                 ///< vertices.
  QSignalMapper*
      signalMapper_vertex_color;  ///< Pointer that is used to bind signals from
                                  ///< the main window's vertices color picker
                                  ///< widgets to a procedure that changes the
                                  ///< vertices color.
  int time;  ///< Variable to keep track of the number of frames added to the
             ///< GIF animation.
  QString gif_Path;  ///< Path to saved GIF file.
  QTimer* timer;  ///< Value is used to generate a signal every 100 milliseconds
                  ///< (0.1 seconds) that calls the save_gif() slot. After 50
                  ///< signal generations (5 seconds elapsed), the timer stops.
  QGifImage*
      gif;  ///< Pointer to an object of the QGifImage class, which is intended
            ///< for creating, storing and displaying a GIF animation.
  QImage image;  ///< Object that is used to store the image.

 public slots:
  /**
    @brief Sets the values ​​of the number of vertices and edges in the
    corresponding fields of the user interface.
    @param vertex_count count of vertisices
    @param line_count count of lines
  */
  void set_counts(int vertex_count, int line_count);

 private slots:
  /**
    @brief This is a handler slot that is called when you click on the "Open"
    menu item in the main application window.
  */
  void on_actionopen_triggered();
  /**
    @brief Changes the position of the object along the x-axis.
    @param arg1 value to set the x-coordinate.
  */
  void on_move_x_spinbox_valueChanged(double arg1);
  /**
    @brief Changes the position of the object along the y-axis
    @param arg1 value to set the y-coordinate.
  */
  void on_move_y_spinbox_valueChanged(double arg1);
  /**
    @brief Changes the position of the object along the z-axis
    @param arg1 value to set the z-coordinate
  */
  void on_move_z_spinbox_valueChanged(double arg1);
  /**
    @brief Rotate the object along the x-axis
    @param arg1 value in degrees by which you want to rotate the model along the
    x-axis
  */
  void on_rotate_x_spinbox_valueChanged(double arg1);
  /**
    @brief Rotate the object along the y-axis
    @param arg1 value in degrees by which you want to rotate the model along the
    y-axis
  */
  void on_rotate_y_spinbox_valueChanged(double arg1);
  /**
    @brief Rotate the object along the z-axis
    @param arg1 value in degrees by which you want to rotate the model along the
    z-axis
  */
  void on_rotate_z_spinbox_valueChanged(double arg1);
  /**
    @brief Changes the scale of the model.
    @param arg1 value to change the scale of the model.
  */
  void on_scaling_butt_valueChanged(double arg1);
  /**
    @brief Checks if the flag for drawing solid lines is set and updates the
    model.
  */
  void on_solid_line_triggered();
  /**
    @brief Checks if the flag for drawing dotted lines is set and updates the
    model.
  */
  void on_dotted_line_triggered();
  /**
    @brief Checks if the flag for drawing model in parallel projection is set
    and updates the model.
  */
  void on_parallel_projection_triggered();
  /**
    @brief Checks if the flag for drawing model in central projection is set and
    updates the model.
  */
  void on_central_projection_triggered();

  /**
    @brief The function sets the flags for each background color and redraws the
    model with the selected color.
    @param id value of background color.
  */
  void action_background_triggered(int id);
  /**
    @brief Create QSignalMapper object and associates triggered() signals from
    background color selection menu items with it.
  */
  void setupMenuActions_back_color();

  /**
    @brief The function sets the flags for each line color and redraws the model
    with the selected color.
    @param id value of line color.
  */
  void action_line_triggered(int id);
  /**
    @brief Create QSignalMapper object and associates triggered() signals from
    line color selection menu items with it.
  */
  void setupMenuActions_line_color();

  /**
    @brief Create QSignalMapper object and associates triggered() signals from
    verteces type selection menu items with it.
  */
  void setupMenuActions_vertex_type();
  /**
    @brief The function sets the flags for each verteces type  and redraws the
    model with the selected type.
    @param id value of verteces type.
  */
  void action_vertex_triggered(int id);

  /**
    @brief Create QSignalMapper object and associates triggered() signals from
    verteces color selection menu items with it.
  */
  void setupMenuActions_vertex_color();
  /**
    @brief The function sets the flags for each verteces color and redraws the
    model with the selected color.
    @param id value of verteces color.
  */
  void action_vertex_color_triggered(int id);

  /**
    @brief Is responsible for saving the image in BMP format.
  */
  void on_action_bmp_triggered();
  /**
    @brief Is responsible for saving the image in JPEG format.
  */
  void on_action_jpeg_triggered();

  /**
    @brief Is responsible for starting the screen recording in GIF format.
  */
  void on_start_screencast_clicked();
  /**
    @brief is responsible for save in GIF format.
  */
  void save_gif();

  /**
    @brief Change verteces size.
    @param value verteces size.
  */
  void on_custom_vertex_size_valueChanged(int value);
  /**
    @brief Change line size.
    @param value line size.
  */
  void on_custom_line_size_valueChanged(int value);

 signals:
  /**
    @brief Signal to open .obj file.
  */
  void openobj();
};

#endif  // MAINWINDOW_H
