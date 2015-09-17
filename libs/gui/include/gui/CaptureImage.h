#pragma once

#include <QObject>
#include <QQuickPaintedItem>
#include <QString>
#include <QPixmap>
#include <QPainter>

#include "opencv2/opencv.hpp"

namespace freemapper {

using namespace cv;

class CaptureImage : public QQuickPaintedItem
{
  // Q_OBJECT
  // DO NOT INCLUDE QOBJECT MACRO (since it's included in QQuickPaintedItem)
  Q_PROPERTY(QImage image READ image WRITE setImage NOTIFY imageChanged)

signals:
  void imageChanged();

public:
  const QImage image() { return m_image; }
  void setImage( const QImage & );

  void paint( QPainter *painter );

private:
  int WIDTH = 640;
  int HEIGHT = 480;

  QImage m_image;
};

} // namespace freemapper
