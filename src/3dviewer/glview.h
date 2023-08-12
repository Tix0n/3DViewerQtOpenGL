#ifndef GLVIEW_H
#define GLVIEW_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <iostream>
using namespace std;

#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>
#include <QtWidgets/QWidget>

extern "C" {
#include "parser.h"
}

extern "C" {
#include "affine_transform.h"
}

/**
  @brief Class for working with QWidget
  The main task of the class is to visualize the model
*/
class glView : public QOpenGLWidget {
  Q_OBJECT
 public:
  /**
    @brief Class constructor.
    @param paren the reference to parent object.
  */
  glView(QWidget* parent = nullptr);
  /**
    @brief Class destructor.
  */
  ~glView();
  /**
    @brief The widget redrawing.
  */
  void update_figure();
  /**
    @brief Save file in bmp or jpeg format.
    @param fileName name of the file to save.
    @param format format of the file to save: bmp or jpeg.
    @return true if the file was saved, false if the file could not be saved.
  */
  bool saveImage(const QString& fileName, const QString& format);
  QString FileName = NULL;  ///< The file name.
  float x_move,             ///< The value to move the model along the x-axis.
      y_move,               ///< The value to move the model along the y-axis.
      z_move;               ///< The value to move the model along the z-axis.
  float x_rotate,           ///< The value to rotate the model along the x-axis.
      y_rotate,             ///< The value to rotate the model along the y-axis.
      z_rotate;             ///< The value to rotate the model along the z-axis.
  float scale_change;       ///< The value to scale the model.
  bool flag_solid_dotted_line;  ///< Flag for using dashed lines to draw lines,
                                ///< false - solid line, true - dotted line.
  int value_projection;  ///< The value for selection projection type: 0 -
                         ///< central projection, 1 - parallel projection.
  bool flag_projection = false;  ///< The flag indicating that the projection
                                 ///< matrix needs to be set.
  int value_background_color;    ///< The value for choose background color: 1 -
                                 ///< black, 2 - white, 3 - red , 4 - blue, 5 -
                                 ///< green.
  bool flag_background_color;    ///< The flag indicating that the background
                                 ///< color needs to be set.
  int value_line_color;    ///< The value for choose line color: 1 - white, 2 -
                           ///< black, 3 - red , 4 - blue, 5 - green.
  int value_vertex_type;   ///< The value for vertex type selection: 1 - no
                           ///< vertex, 2 - circle vertex , 3- square vertex.
  int custom_vertex_size;  ///< The value for custom vertex size: 0 - no vertex,
                           ///< 30 - max vertex size.
  int custom_line_size;  ///< The value for custom line size: 1 - min line size,
                         ///< 10 - max line size.
  int value_vertex_color;  ///< The value for choose vertex color: 1 - black, 2
                           ///< - white, 3 - red , 4 - blue, 5 - green.

 private:
  /**
    @brief function called at initialization glView.
  */
  void initializeGL() override;
  /**
    @brief Setting the size of the output area.
    @param w width output area
    @param h height output area
  */
  void resizeGL(int w, int h) override;
  /**
    @brief The widget drawing.
  */
  void paintGL() override;
  /**
    @brief The model drawing.
  */
  void draw_figure();
  /**
    @brief Setting the projection of the model: parallel or central.
  */
  void set_projection();
  /**
    @brief Place the model in the center of the area.
  */
  void centering();
  /**
    @brief Setting model size.
  */
  void scaling();
  /**
    @brief Setting the background color.
  */
  void set_background_color();
  /**
    @brief Setting the line color.
  */
  void set_line_color();
  /**
    @brief Setting the type of verteces.
  */
  void set_vertex_type();
  /**
    @brief Setting the size of verteces.
  */
  void set_vertex_size();
  /**
    @brief Setting the color of verteces.
  */
  void set_vertex_color();
  /**
    @brief The moving the model along the x-axis.
    @param value value to move the model.
  */
  void move_for_asix_x(double value);
  /**
    @brief The moving the model along the y-axis.
    @param value value to move the model.
  */
  void move_for_asix_y(double value);
  /**
    @brief The moving the model along the z-axis.
    @param value value to move the model.
  */
  void move_for_asix_z(double value);
  /**
    @brief The rotation the model along the x-axis.
    @param value value to rotate the model.
  */
  void rotate_for_asix_x(double value);
  /**
    @brief The rotation the model along the y-axis.
    @param value value to rotate the model
  */
  void rotate_for_asix_y(double value);
  /**
    @brief The rotation the model along the z-axis.
    @param value value to rotate the model.
  */
  void rotate_for_asix_z(double value);
  struct info_figure figure = {
      0, 0, NULL, NULL, 0,     0,
      0, 0, 0,    0,    false, NULL};  ///< The information about the model.
  bool flag_centering;  ///< The flag indicating that the model needs to be
                        ///< centered.
  float centr_x =
            0.0,  ///< The value of the center of the model along the x-axis.
      centr_y =
          0.0,  ///< The value of the center of the model along the y-axis.
      centr_z =
          0.0;  ///< The value of the center of the model along the z-axis.
  double scaleFactor_x,  ///< The coefficient for moving the model along the
                         ///< x-axis.
      scaleFactor_y,  ///< The coefficient for moving the model along the y-axis
      scaleFactor_z;  ///< The coefficient for moving the model along the z-axis

 public slots:
  /**
    @brief Slot to open .obj file.
  */
  void open_obj();

 signals:
  /**
    @brief Signal to transmit the number of vertices and the number of lines.
    @param vertex_count The number of model vertices.
    @param line_count The number of model lines.
  */
  void set_counts(int vertex_count, int line_count);
};

#endif  // GLVIEW_H
