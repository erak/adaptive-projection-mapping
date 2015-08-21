#include "Image.h"

#include <math.h>

using namespace cv;

namespace freemapper {

// --------------------------------------------------------------------------------------------------------------------

Image::Image()
{

}

// --------------------------------------------------------------------------------------------------------------------

Image::Image( Mat matrix )
  : _matrix( matrix )
{

}

// --------------------------------------------------------------------------------------------------------------------

void Image::gray()
{
  cvtColor( _matrix, _matrix, COLOR_BGR2GRAY );
}

// --------------------------------------------------------------------------------------------------------------------

void Image::gauss()
{
  GaussianBlur( _matrix, _matrix, Size(3,3), 5.0, 5.0);
}

// --------------------------------------------------------------------------------------------------------------------

void Image::canny()
{
  // Increasing the 3rd parameter leds to less detected shapes. Shorter / smaller edges seems to be sorted out.
  Canny( _matrix, _matrix, 0, 120, 3);
}

// --------------------------------------------------------------------------------------------------------------------

void Image::drawShape( const Shape &shape )
{
  for( auto point: shape )
  {
    _matrix.at<uchar>( point ) = 0;
  }
}

// --------------------------------------------------------------------------------------------------------------------

QImage Image::qImage()
{
  auto image = QImage( 640, 480, QImage::Format_RGB32 );

  for( int x = 0; x < image.width(); x++)
  {
    for( int y = 0; y < image.height(); y++)
    {
      auto pixel = _matrix.at<uchar>( cv::Point(x, y) );
      image.setPixel( QPoint( x, y ), qRgba(pixel, pixel, pixel, pixel) );
    }
  }
  return image;
}


} // namespace freemapper
