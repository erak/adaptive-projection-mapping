#pragma once

#include <QQuickPaintedItem>
#include <QString>
#include <QPixmap>
#include <QPainter>

#include "opencv2/opencv.hpp"

namespace freemapper {

using namespace cv;

class CaptureImage : public QQuickPaintedItem
{
  // DO NOT INCLUDE QOBJECT MACRO (since it's included in QQuickPaintedItem)
signals:
  void imageChanged();

public:
  void paint( QPainter *painter );

private:
  int WIDTH = 640;
  int HEIGHT = 480;
};

} // namespace freemapper
