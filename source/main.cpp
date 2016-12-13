#include <iostream>
#include <GL/glew.h>
#include "Display.hpp"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

int main()
{
  Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Terrain Generator");
  
  SDL_Event e;
  bool isRunning = true;
  while(isRunning)
    {
      while(SDL_PollEvent(&e))
	{
	  if(e.type == SDL_QUIT)
	    isRunning = false;
	}
      display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
      display.SwapBuffers();
      SDL_Delay(1);
    }

  return EXIT_SUCCESS;
}