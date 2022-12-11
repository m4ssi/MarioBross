#include "utils.h"
#include "display.h"


targ_t init_arg_t ( SDL_Window * win, SDL_Renderer * rend, char * f_character, char * f_map)
{
	SDL_Window   * w = win == NULL ? SDL_CreateWindow(	W_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W_WIDTH, W_HEIGHT,	SDL_WINDOW_SHOWN) : win;
	SDL_Renderer * r = rend == NULL ? SDL_CreateRenderer ( w, -1, SDL_RENDERER_ACCELERATED) : rend;

	SDL_Texture	 * background = SDL_CreateTexture ( r, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, W_WIDTH, W_HEIGHT);
	SDL_Rect s_bg = { .x = 0, .y = 0, .w = W_WIDTH, .h = W_HEIGHT};
	SDL_SetRenderTarget ( r, background);
	SDL_SetRenderDrawColor ( r, 0x00, 0x89, 0xFF, 0xFF);
	SDL_RenderFillRect ( r, &s_bg);
	SDL_SetRenderTarget ( r, NULL);
	
	
	characater_t m_char= readCharacterString ( f_character);
	m_char.c_texture = getCharacterTexture ( r, m_char.c_string, m_char.h, m_char.w);

	map_t m_map = readCharacterString ( f_map);
	m_map.c_texture = getMapTexture ( r, m_map.c_string, m_map.h, m_map.w, S_BOX, S_BOX);

	targ_t a = 
		{
			.c_main			= setCharacterDyn ( m_char),
			.m_main			= setCharacterDyn ( m_map),
			.x 				= malloc ( sizeof ( int)), 
			.y 				= malloc ( sizeof ( int)), 
			.dx 				= malloc ( sizeof ( int)), 
			.dy 				= malloc ( sizeof ( int)), 
			.moved_f		= malloc ( sizeof ( int)), 
			.jumped_f		= malloc ( sizeof ( int)), 
			.quit_f			= malloc ( sizeof ( int)), 
			.w_updated_f	= malloc ( sizeof ( int)), 
			.w 				= w,
			.r 				= r, 
			.t_char 		= NULL, 
			.t_level		= NULL,
			.t_background	= background
		};
	return a;
}

void free_targ_t ( targ_t a)
{
	free ( a.x);
	free ( a.y);
	free ( a.dx);
	free ( a.dy);
	free ( a.w_updated_f);
	free ( a.moved_f);
	free ( a.jumped_f);
	free ( a.quit_f);

	freeCharacter ( a.c_main, SDL_DestroyTexture);
	
	//~ SDL_DestroyTexture ( a.t_char);
	SDL_DestroyTexture ( a.t_level);
	SDL_DestroyTexture ( a.t_background);
	SDL_DestroyRenderer ( a.r);	
	SDL_DestroyWindow( a.w);	
}
