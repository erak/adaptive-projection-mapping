#include <thread>

#include <QObject>
#include <QDebug>

#include "opencv2/opencv.hpp"

#include <model/Scene.h>

using namespace freemapper;
using namespace cv;

class Capture : public QObject
{
  Q_OBJECT

public slots:
  void capture();

public:
  const std::shared_ptr<Scene> scene();

private:
  std::shared_ptr<Scene> m_scene;
};


