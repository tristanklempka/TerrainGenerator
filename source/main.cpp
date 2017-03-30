#define GLM_FORCE_RADIANS

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <SFML/OpenGL.hpp>

#include "display.hpp"
#include "mesh.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "transform.hpp"
#include "camera.hpp"
#include "light.hpp"
#include "terrain.hpp"

#include <iostream>

static const int DISPLAY_WIDTH = 1024;
static const int DISPLAY_HEIGHT = 768;
static const sf::Time TIME_PER_FRAME = sf::seconds(1.f/60.f);

int main()
{
  Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Terrain Generator");
  Terrain terrain("../resource/terrain_heightmap.png");
  Texture texture("../resource/debug.jpg");
  Shader shader("../resource/basicShader");
  Camera camera(glm::vec3(256.0f/2.0f, 256.0f/2.0f, -8.0f), 70.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.1f, 500.0f);  
  Transform transform;
  Light light(glm::vec3(256.0f/2.0f, 256.0f/2.0f, 10.0f));
  

  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  
  bool isRunning = true;
  while(isRunning)
    {
      timeSinceLastUpdate += clock.restart();
      while(timeSinceLastUpdate > TIME_PER_FRAME)
	{
	  timeSinceLastUpdate -= TIME_PER_FRAME;
	  sf::Event event;
	  while(display.PollEvent(event))
	    {
	      if(event.type == sf::Event::Closed)
		isRunning = false;
	      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		camera.MoveForward(0.5f);
	      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		camera.MoveBackward(0.5f);
	      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		camera.MoveRight(0.5f);
	      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		camera.MoveLeft(0.5f);
	      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		camera.Pitch(-0.5f);
	      if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		camera.Pitch(0.5f);
	      if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		camera.RotateZ(-0.8f);
	      if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		camera.RotateZ(0.8f);
	    }
	}
      

      display.Clear(0, 0, 0, 1.0f);
      texture.Bind();
      shader.Bind();
      shader.Update(transform, camera, light);
      
      terrain.Draw();
      
      display.Show();
    }

  return EXIT_SUCCESS;
}
