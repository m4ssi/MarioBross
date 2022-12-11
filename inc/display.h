#ifndef _H_DISPLAY_
#define _H_DISPLAY_

#include <SDL2/SDL.h>


#define S_PIXEL 5
#define W_TOP	0
#define W_LEFT	0
#define S_BOX	20
#define W_WIDTH 1000
#define W_HEIGHT (15* S_BOX)
#define W_TITLE "Super Mario Bross - Beta"

SDL_Texture * getCharacterTexture ( SDL_Renderer * r, char * c_string, int h, int w);

SDL_Texture * getMapTexture ( SDL_Renderer * r, char * map, int h, int w, int box_w, int box_h);

void displayGameScreen ( SDL_Renderer * r, SDL_Texture * t_background, SDL_Texture * t_level, SDL_Texture * t_char, int x, int y, int w, int h);


#endif
