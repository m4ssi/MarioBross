#include "display.h"

SDL_Texture * getCharacterTexture ( SDL_Renderer * r, char * c_string, int h, int w)
{
	SDL_Texture * t_m = SDL_CreateTexture ( r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w * S_PIXEL, h * S_PIXEL);
	SDL_SetTextureBlendMode(t_m, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget ( r, t_m);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			char c = c_string[ i * w + j];
			SDL_Rect hg = { .y = i * S_PIXEL, .x = j * S_PIXEL,.h = S_PIXEL, .w = S_PIXEL};
			if ( c == '*')	SDL_SetRenderDrawColor ( r, 0x00, 0x00, 0x00, 0);
			if ( c == 'R')	SDL_SetRenderDrawColor ( r, 0xFF, 0x00, 0x00, 0xFF);
			if ( c == 'W')	SDL_SetRenderDrawColor ( r, 0xF9, 0xE4, 0xB7, 0xFF);
			if ( c == 'D')	SDL_SetRenderDrawColor ( r, 0x00, 0x00, 0x00, 0xFF);
			if ( c == 'B')	SDL_SetRenderDrawColor ( r, 0x58, 0x29, 0x00, 0xFF);
			if ( c == 'C')	SDL_SetRenderDrawColor ( r, 0x00, 0x00, 0xFF, 0xFF);
			SDL_RenderFillRect ( r, &hg);
		}
	}
	
	SDL_SetRenderTarget ( r, NULL);
	return t_m;
}

SDL_Texture * getMapTexture ( SDL_Renderer * r, char * map, int h, int w, int box_w, int box_h)
{
	SDL_Texture * t_m = SDL_CreateTexture ( r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w * box_w, h * box_h);
	SDL_SetTextureBlendMode(t_m, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget ( r, t_m);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			SDL_Rect hg = { .y = i * box_h, .x = j * box_w, .h = box_h, .w = box_w};
			char c = map[i*w + j];
			if ( c == ' ')	SDL_SetRenderDrawColor ( r, 0xFF, 0xFF, 0xFF, 0);
			if ( c == 'P')	SDL_SetRenderDrawColor ( r, 0x00, 0xFF, 0x00, 0xFF);
			if ( c == 'B')	SDL_SetRenderDrawColor ( r, 0xFF, 0xAA, 0x00, 0xFF);
			if ( c == 'S')	SDL_SetRenderDrawColor ( r, 0x00, 0xFF, 0xAA, 0xFF);
			if ( c == 'R')	SDL_SetRenderDrawColor ( r, 0x58, 0x29, 0x00, 0xFF);
			if ( c == 'F')	SDL_SetRenderDrawColor ( r, 0xFF, 0x00, 0x00, 0xFF);
			SDL_RenderFillRect ( r, &hg);
		}
	}
	SDL_SetRenderTarget ( r, NULL);
	return t_m;
}

void displayGameScreen ( SDL_Renderer * r, SDL_Texture * t_background, SDL_Texture * t_level, SDL_Texture * t_char, int x, int y, int w, int h)
{
	SDL_Rect l_pos = { .x = 0, .y = 0, .w = W_WIDTH, .h = W_HEIGHT};	
	SDL_Rect l_src = { .x = 0, .y = 0, .w = W_WIDTH, .h = W_HEIGHT};	
	SDL_Rect p_pos = { .x = x, .y = y, .w = w, .h = h};	

	SDL_RenderCopy ( r, t_background, NULL, &l_pos);
	SDL_RenderCopy ( r, t_level, &l_src, &l_pos);
	SDL_RenderCopy ( r, t_char, NULL, &p_pos);
	SDL_RenderPresent ( r);	
}

