#pragma once

#include <thread>

#include <QObject>
#include <QDebug>

#include "opencv2/opencv.hpp"

#include <model/Scene.h>

using namespace freemapper;
using namespace cv;

class CameraCapture : public QObject
{
  Q_OBJECT
  Q_PROPERTY(Scene::Ptr scene READ scene NOTIFY sceneChanged)
  Q_PROPERTY(QImage     image READ image NOTIFY imageChanged)

signals:
  void sceneChanged();
  void imageChanged();

public:
  Q_INVOKABLE void capture();

  const Scene::Ptr  scene() { return m_scene; }
  const QImage      image() { return m_image; }

private:
  Scene::Ptr  m_scene;
  QImage      m_image;

  std::unique_ptr<std::thread> m_thread = nullptr;

  // ...
  void gray();

  // Apply Gauss blurry filter
  void gauss();

  // Apply Canny's edge detection
  void canny();

};


