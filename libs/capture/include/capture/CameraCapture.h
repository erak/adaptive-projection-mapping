#pragma once

#include <thread>
#include <mutex>

#include <QObject>
#include <QDebug>

#include "opencv2/opencv.hpp"

#include <model/Scene.h>

namespace freemapper {

using namespace cv;

class CameraCapture : public QObject
{
  Q_OBJECT
  Q_PROPERTY(Scene*     scene READ scene NOTIFY sceneChanged)
  Q_PROPERTY(QImage     image READ image NOTIFY imageChanged)

signals:
  void sceneChanged();
  void imageChanged();

public:
  Q_INVOKABLE void capture();

  CameraCapture();

  Scene*            scene();
  const QImage      image();

private:
  Scene::Ptr  m_scene;
  QImage      m_image;

  std::mutex  _scene_mtx;
  std::mutex  _image_mtx;

  std::unique_ptr<std::thread> m_thread = nullptr;
};

} // namespace freemapper
