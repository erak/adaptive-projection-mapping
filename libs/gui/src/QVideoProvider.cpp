#include "QVideoProvider.h"

#include <math.h>

#include "opencv2/video/video.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <model/Image.h>

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

  freemapper::Image image{ converted };
  freemapper::Image original{ converted };

  //image.gray();
  image.gauss();
  image.canny();

  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;
  RNG rng( 12345 );
  findContours( image.matrix(), contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  std::cout << "Found " << contours.size() << " shapes." << std::endl;

  /// Draw contours
  //Mat drawing = Mat::zeros( image.matrix().size(), CV_8UC3 );
  //original.gray();

  for( int i = 0; i < contours.size(); i++ )
  {
    auto contour = contours[i];
    if( contour.size() > 1 )
    {
      Scalar color = Scalar( rng.uniform(0,255), rng.uniform(0,0), rng.uniform(0,0) );
      drawContours( original.matrix(), contours, i, color, 1, 8, hierarchy, 0, Point() );
    }
  }

  // imshow( "Result window", drawing );
  //for( auto contour: contours )
  //{
  //  out.drawShape( contour );
  //}

  return QPixmap::fromImage( original.qImage() );
}
