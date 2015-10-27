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
    while( _enabled && window.isOpen() )
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
\
        std::lock_guard<std::mutex> lock( _mapping_mutex );

        auto shapes = _mapping->shapes().get();
        sf::ConvexShape shape = shapes->at(1);

        window.draw(shape);

        // end the current frame
        window.display();
    }

    // If projection window was closed, notify QML to alter UI
    setEnabled( false );

  });
  _thread.reset( thread );
}

// --------------------------------------------------------------------------------------------------------------------

void Projection::off()
{
  setEnabled( false );

  if ( !!_thread ) {
    _thread.get()->join();
  }
  _thread.release();
}

// --------------------------------------------------------------------------------------------------------------------

void Projection::setEnabled( const bool &enabled )
{
  _enabled = enabled;
  enabledChanged();
}

// --------------------------------------------------------------------------------------------------------------------

void Projection::setScene( Scene *scene )
{
  std::lock_guard<std::mutex> lock( _mapping_mutex );
  std::cout << "Projection::setMapping" << std::endl;

  _mapping = scene->mapping();

  sceneChanged();
}


} // namespace freemapper
