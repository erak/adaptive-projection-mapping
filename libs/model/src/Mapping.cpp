#include "Mapping.h"

namespace freemapper {

Mapping::Mapping( QObject *parent )
  : QObject( parent )
{
  ConvexShape shape = demoShape();

  _shapes = std::make_shared< Shapes >( Shapes{} );
  _shapes.get()->insert( std::make_pair( 1, shape ));
}

// --------------------------------------------------------------------------------------------------------------------

sf::ConvexShape Mapping::demoShape() const
{
  ConvexShape shape;

  // resize it to 5 points
  shape.setPointCount(5);

  // define the points
  shape.setPoint(0, Vector2f(5, 5));
  shape.setPoint(1, Vector2f(150, 10));
  shape.setPoint(2, Vector2f(120, 90));
  shape.setPoint(3, Vector2f(30, 100));
  shape.setPoint(4, Vector2f(5, 50));

  shape.setFillColor(Color::Red);

  return shape;
}

} // namespace freemapper
