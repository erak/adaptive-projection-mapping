#include "CaptureImage.h"

#include <math.h>

#include <QPainter>

#include "opencv2/video/video.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <model/Scene.h>

namespace freemapper {

void CaptureImage::setImage( const QImage &image )
{
  m_image = image;
  update();
  imageChanged();
}

// --------------------------------------------------------------------------------------------------------------------

void CaptureImage::paint( QPainter *painter )
{
  painter->drawImage( QPointF(0.0f,0.0f), m_image );
}

} // namespace freemapper
