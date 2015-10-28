#pragma once

#include <thread>
#include <utility>

#include <QObject>

#include <SFML/Graphics.hpp>

namespace freemapper {

using namespace sf;

class Mapping : public QObject
{
  Q_OBJECT

public:
  using Ptr       = std::shared_ptr< Mapping >;
  using Shapes    = std::map< int, ConvexShape >;
  using ShapesPtr = std::shared_ptr< Shapes >;

  Mapping();
  Mapping( const sf::Color& color );

  ShapesPtr shapes() const { return _shapes; }

private:
  ShapesPtr _shapes;

  ConvexShape demoShape() const;
};

} // namespace freemapper

