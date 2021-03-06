#ifndef APPLICATION_H
#define APPLICATION_H

#include <iostream>
#include <sstream>

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "display.hpp"
#include "camera.hpp"
#include "terrain.hpp"
#include "light.hpp"
#include "shader.hpp"
#include "texture.hpp"

class Application
{
public:
  Application();
  void                	run();

private:
  void                	processInputs();
  void                	update(sf::Time elapsedTime);
  void                	updateStatistics(sf::Time elapsedTime);
  void 				  	render();

private:
  static const int 	  	DISPLAY_WIDTH = 1024;
  static const int 	  	DISPLAY_HEIGHT = 768;
  static const sf::Time TIME_PER_FRAME;

  Display    			m_display;
  Camera				m_camera;
  Terrain				m_terrain;
  Texture				m_texture;
  Shader				m_shader;
};

#endif // APPLICATION_H
