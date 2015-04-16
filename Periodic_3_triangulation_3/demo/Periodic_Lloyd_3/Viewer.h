#ifndef VIEWER_H
#define VIEWER_H

#include "Scene.h"
#include <QGLViewer/qglviewer.h>
#include <QOpenGLFunctions_3_3_Core>
#include <QGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QGLBuffer>
#include <QOpenGLShaderProgram>


class Viewer : public QGLViewer, QOpenGLFunctions_3_3_Core {

  typedef qglviewer::Vec Vec;

  Q_OBJECT

  CGAL::Timer timer;
  Scene* scene;

  int nr_of_facets;
public:
  Viewer(QWidget* parent)
    : QGLViewer(parent)
  {}

  void setScene(Scene* scene_)
  {
    scene = scene_;
  }

  void init();
  void clear();

public:
  void draw();


public slots :
  void changed();
  void sceneChanged();
  void render_video();
  
signals:
  void valueChanged(int i);

private:
  Vec next_around_circle(const float& phi, const Vec& pos, const Vec& ori);

      int vertexLocation[3];
      int mvpLocation[3];
      int colorLocation[3];


      std::vector<float> pos_points;
      std::vector<float> pos_lines;
      std::vector<float> pos_8lines2D;
      std::vector<float> pos_8lines;


      QGLBuffer buffers[4];
      QOpenGLVertexArrayObject vao[4];
      QOpenGLShaderProgram rendering_program;
      void initialize_buffers();
      void compute_elements();
      void attrib_buffers(QGLViewer*);
      void compile_shaders();
};

#endif
