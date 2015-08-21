#include "Projection.h"

#include <math.h>

#include <SFML/Graphics.hpp>

// --------------------------------------------------------------------------------------------------------------------

void Projection::on()
{
  m_running = true;

  auto thread = new std::thread( [this] () {

    // Antialiased shapes
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(640, 480), "freemapper::projection", sf::Style::Default, settings);

    // run the program as long as the window is open
    while( m_running && window.isOpen() )
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

        // Draw vertices
        // create an array of 3 vertices that define a triangle primitive
        sf::VertexArray shape(sf::LinesStrip, 3);

        // define the position of the triangle's points
        shape[0].position = sf::Vector2f(10, 10);
        shape[1].position = sf::Vector2f(100, 10);
        shape[2].position = sf::Vector2f(100, 100);

        // set the shape color to green
        shape[0].color = sf::Color::Red;
        shape[1].color = sf::Color::Red;
        shape[2].color = sf::Color::Green;

        window.draw(shape);

        // end the current frame
        window.display();
    }
  });
  m_thread.reset( thread );
}

// --------------------------------------------------------------------------------------------------------------------

void Projection::off()
{
  m_running = false;

  if ( !!m_thread ) {
    m_thread.get()->join();
  }
  m_thread.release();
}

// --------------------------------------------------------------------------------------------------------------------

void Projection::onOff()
{
  if ( !m_running ) {
    on();
  } else {
    off();
  }
}


//} // namespace freemapper
