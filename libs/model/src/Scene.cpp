#include "Scene.h"

#include <math.h>

using namespace cv;

namespace freemapper {

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

// --------------------------------------------------------------------------------------------------------------------

Mapping::Ptr Scene::createMapping() const
{
  return std::make_shared< Mapping >( new Mapping() );
}

// --------------------------------------------------------------------------------------------------------------------

void Scene::setMatrix( const Mat &matrix )
{
  _matrix = matrix;
  _mapping = createMapping();

  mappingChanged();
}

// --------------------------------------------------------------------------------------------------------------------


} // namespace freemapper
