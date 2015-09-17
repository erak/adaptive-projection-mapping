#include "CaptureImage.h"

#include <math.h>

#include "opencv2/video/video.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <model/Scene.h>

namespace freemapper {

// --------------------------------------------------------------------------------------------------------------------

void CaptureImage::paint( QPainter *painter )
{
  //  if(!cap.isOpened())  // check if we succeeded
  //    return -1;
  VideoCapture capture(0);
  Mat frame;
  Mat converted;

  capture >> frame; // get a new frame from camera
  cvtColor( frame, converted, COLOR_BGR2GRAY );

  freemapper::Scene original{ converted };
  original.gauss();
  original.canny();

  painter->drawImage( QPointF(0.0f,0.0f), original.qImage() );
}

} // namespace freemapper
