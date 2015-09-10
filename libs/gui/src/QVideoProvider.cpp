#include "QVideoProvider.h"

#include <math.h>

#include "opencv2/video/video.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <model/Scene.h>

// --------------------------------------------------------------------------------------------------------------------

QVideoProvider::QVideoProvider()
  : QQuickImageProvider( QQuickImageProvider::Pixmap )
{
  //  if(!cap.isOpened())  // check if we succeeded
  //    return -1;
}

// --------------------------------------------------------------------------------------------------------------------

QPixmap QVideoProvider::requestPixmap( const QString &id, QSize *size, const QSize &requestedSize )
{
  VideoCapture capture(1);
  Mat frame;
  Mat converted;

  capture >> frame; // get a new frame from camera
  cvtColor( frame, converted, COLOR_BGR2GRAY );

  freemapper::Scene original{ converted };
  //original.gauss();
  original.canny();

  return QPixmap::fromImage( original.qImage() );
}

