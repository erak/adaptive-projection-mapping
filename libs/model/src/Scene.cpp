#include "Scene.h"

#include <math.h>

using namespace cv;

namespace freemapper {

Scene::Scene()
{
  _mapping.reset( new Mapping() );
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
  Canny( _matrix, _matrix, 0, 40, 3);
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

void Scene::createMapping( const sf::Color &color )
{
  _mapping.reset( new Mapping() );
  //

  vector<vector<Point>> contours;
  vector<Vec4i> hierarchy;
  RNG rng( 12345 );

  findContours( _matrix, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  auto id = 0;
  for( auto &contour: contours )
  {
    auto index = 0;
    auto size = contour.size();

    ConvexShape shape;
    shape.setPointCount( size );
    shape.setFillColor( size < 50 ? sf::Color::Green : sf::Color::Yellow );
    shape.setOutlineThickness( 1.0f );
    shape.setOutlineColor( sf::Color::White );

    for( auto &point: contour )
    {
      shape.setPoint(index, Vector2f(point.x, point.y));
      index++;
    }

    _mapping->shapes()->insert( std::make_pair( id, shape ));
    id++;
  }

}

// --------------------------------------------------------------------------------------------------------------------

void Scene::setMatrix( const Mat &matrix )
{
  _matrix = matrix;
}

// --------------------------------------------------------------------------------------------------------------------


} // namespace freemapper
