#include "utils.h"
#include <time.h>

double gettime () {
	struct timespec ts;
	clock_gettime ( CLOCK_MONOTONIC, &ts);
	return ts.tv_sec*1e0 + ts.tv_nsec*1e-9;
}

void * engine_routine ( void * args)
{
	targ_t * a = (targ_t *) args;
	int quit_f = *(a->quit_f),
		moved_f = 0,
		jumped_f = 0,
		w_updated_f = 0;

	double	t1 = gettime(),
			t2 = 0.0f;
	a->t_level = (SDL_Texture *) a->m_main->c_texture;
	a->t_char = (SDL_Texture *) a->c_main->c_texture;
	
	int bool = 1;
	
	do
	{
		// TIMER
		t2 = gettime();
		if ( t2 - t1 < 1e-1)	continue;

		pthread_mutex_lock( a->m_stdout);
		quit_f = *(a->quit_f);
		moved_f = *(a->moved_f);
		w_updated_f = *(a->w_updated_f);
		jumped_f = *(a->jumped_f);
		pthread_mutex_unlock( a->m_stdout);

		int i = a->c_main->x,
			j = a->c_main->y,
			ret = 0;

			// FALLING
			if ( a->m_main->c_string[(j+1) * a->m_main->w + i] == ' ')
			{
				pthread_mutex_lock( a->m_stdout);
				*a->y = (*a->y + 1) % S_BOX;
				if ( *a->y == 0)	a->c_main->y++;
				pthread_mutex_unlock( a->m_stdout);
				ret = ret || 1;
			}

			// MOVING
			if ( moved_f)
			{
				ret = ret || 1;
				(*a->x) += *a->dx;
				if ( abs(*a->x) == S_BOX)
				{
					pthread_mutex_lock( a->m_stdout);
					*(a->moved_f) = 0;
					a->c_main->x += *a->dx;
					*a->x = 0;
					pthread_mutex_unlock( a->m_stdout);
				}
			}

			if ( ret)
			{
				*a->w_updated_f = 1;
				t1 = gettime();
			}
		//~ }
	} while (!quit_f);
	
	return NULL;
}
