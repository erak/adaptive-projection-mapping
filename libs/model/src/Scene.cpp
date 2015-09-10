#include "Scene.h"

#include <math.h>

using namespace cv;

namespace freemapper {

// --------------------------------------------------------------------------------------------------------------------

Scene::Scene()
{

}

// --------------------------------------------------------------------------------------------------------------------

Scene::Scene( Mat matrix )
  : _matrix( matrix )
{

}

// --------------------------------------------------------------------------------------------------------------------

void Scene::gray()
{
  cvtColor( _matrix, _matrix, COLOR_BGR2GRAY );
}

// --------------------------------------------------------------------------------------------------------------------

void Scene::gauss()
{
  GaussianBlur( _matrix, _matrix, Size(3,3), 5.0, 5.0);
}

// --------------------------------------------------------------------------------------------------------------------

void Scene::canny()
{
  // Increasing the 3rd parameter leds to less detected shapes. Shorter / smaller edges seems to be sorted out.
  Canny( _matrix, _matrix, 0, 120, 3);
}

// --------------------------------------------------------------------------------------------------------------------

void Scene::drawShape( const Shape &shape )
{
  for( auto point: shape )
  {
    _matrix.at<uchar>( point ) = 0;
  }
}

// --------------------------------------------------------------------------------------------------------------------

QImage Scene::qImage()
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
