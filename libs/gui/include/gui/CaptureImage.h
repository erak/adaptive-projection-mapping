#pragma once

#include <QObject>
#include <QQuickPaintedItem>
#include <QString>
#include <QPixmap>
#include <QPainter>

#include "opencv2/opencv.hpp"

namespace freemapper {

class CaptureImage : public QQuickPaintedItem
{
  Q_OBJECT
  Q_PROPERTY(QImage image READ image() WRITE setImage NOTIFY imageChanged)

signals:
  void imageChanged();

public:
  QImage image() const { return m_image; }
  void setImage( const QImage & );

  void paint( QPainter *painter );

private:
  int WIDTH = 640;
  int HEIGHT = 480;

  QImage m_image;
};

} // namespace freemapper
