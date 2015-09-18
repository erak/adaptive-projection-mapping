#include "Projection.h"

#include <math.h>

#include <SFML/Graphics.hpp>

namespace freemapper {

Projection::~Projection()
{
  off();
}

// --------------------------------------------------------------------------------------------------------------------

void Projection::on()
{
  setEnabled( true );

  auto thread = new std::thread( [this] () {

    // Antialiased shapes
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(640, 480), "freemapper::projection", sf::Style::Default, settings);

    // run the program as long as the window is open
    while( m_enabled && window.isOpen() )
    {
      // check all the window's events that were triggered since the last iteration of the loop
      sf::Event event;
      while (window.pollEvent(event))
      {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
          window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        sf::ConvexShape shape;

        // resize it to 5 points
        shape.setPointCount(5);

        // define the points
        shape.setPoint(0, sf::Vector2f(5, 5));
        shape.setPoint(1, sf::Vector2f(150, 10));
        shape.setPoint(2, sf::Vector2f(120, 90));
        shape.setPoint(3, sf::Vector2f(30, 100));
        shape.setPoint(4, sf::Vector2f(5, 50));

        shape.setFillColor(sf::Color::Green);

        shape.setOutlineThickness(2.0);
        shape.setOutlineColor(sf::Color::White);

        window.draw(shape);

        // end the current frame
        window.display();
    }

    // If projection window was closed, notify QML to alter UI
    setEnabled( false );

  });
  m_thread.reset( thread );
}

// --------------------------------------------------------------------------------------------------------------------

void Projection::off()
{
  setEnabled( false );

  if ( !!m_thread ) {
    m_thread.get()->join();
  }
  m_thread.release();
}

// --------------------------------------------------------------------------------------------------------------------

void Projection::setEnabled( const bool &enabled )
{
  m_enabled = enabled;
  enabledChanged();
}

// --------------------------------------------------------------------------------------------------------------------

void Projection::setScene( const Scene::Ptr &scene )
{
  m_scene = scene;
  sceneChanged();
}


} // namespace freemapper
