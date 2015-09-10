#pragma once

#include <QQuickImageProvider>
#include <QString>
#include <QPixmap>

#include "opencv2/opencv.hpp"

using namespace cv;

class QVideoProvider : public QQuickImageProvider
{
public:
  QVideoProvider();

  QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize);

private:
  int WIDTH = 640;
  int HEIGHT = 480;
};
