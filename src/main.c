#include "utils.h"
#include "renderer.h"
#include "engine.h"


void gameLoopEvent ( targ_t * s)
{
	do
	{
		int d = 0;

		SDL_Event e;
		while ( SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_QUIT:
					pthread_mutex_lock (s->m_stdout);
					*(s->quit_f) = 1;
					pthread_mutex_unlock (s->m_stdout);
					break;
				case SDL_KEYUP:
					if ( e.key.keysym.sym == SDLK_d)		d = 1;
					if ( e.key.keysym.sym == SDLK_z)		d = 2;
					if ( e.key.keysym.sym == SDLK_q)		d = 3;

					if ( e.key.keysym.sym == SDLK_w)
					{
						pthread_mutex_lock (s->m_stdout);
						*(s->quit_f) = 1;
						pthread_mutex_unlock (s->m_stdout);
					}
					break;
			}
			if ( d)
			{
				pthread_mutex_lock ( s->m_stdout);

				d = 2 - d;
				(*(s->dx)) = 0 + d;
				if (d)	(*(s->moved_f)) = 1;
				else	(*(s->jumped_f)) = 1;
				
				SDL_Log ("BILAN : P.x(%d).y (%d) | GLOB.x(%d).y(%d)", s->c_main->x, s->c_main->y, *s->x, *s->y);
				pthread_mutex_unlock ( s->m_stdout);
			}
			break;
		}

	}	
	while ( !(*(s->quit_f)));
}

int main(int argc, char* args[]) 
{
	SDL_Init(SDL_INIT_VIDEO);

	pthread_t t_display, t_engine;

	pthread_mutex_t m;
	pthread_mutex_init ( &m, NULL);
	
	targ_t a = init_arg_t( NULL, NULL, "res/mario.perso", "lvl/level01_01.bross");
	a.m_stdout = &m;
	a.c_main->x = 0 * S_BOX;
	a.c_main->y = 0 * S_BOX;
	*(a.dx) = 0;
	*(a.dy) = 0;
	*(a.x) = 0;
	*(a.y) = 0;
	*(a.quit_f) = 0;
	*(a.w_updated_f) = 1;


	pthread_create ( &t_display, NULL, display_routine, (void*) &a);
	pthread_create ( &t_engine, NULL, engine_routine, (void*) &a);

	gameLoopEvent ( &a);
	
	pthread_join ( t_engine, NULL);
	pthread_join ( t_display, NULL);
	
	pthread_mutex_destroy ( &m);
	free_targ_t ( a);
	
	SDL_Quit();	
	return 0;
}
