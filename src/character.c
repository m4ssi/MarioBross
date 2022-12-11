#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "character.h"

characater_t readCharacterString ( char * filename)
{
	
	FILE * f = fopen ( filename, "r");

	char buf[128];
	int h = 0, w = 0;
	fgets ( buf, 128, f);
	sscanf ( buf, "[%d|%d]", &h, &w);
	
	char * c_string = (char *) malloc ( (h * w) * sizeof ( char));
	for (int i = 0; i < h; i++)
		fgets ( buf, 128, f),	memcpy ( c_string + (i * w), buf, w * sizeof(char));
	
	fclose ( f);
	

	
	return (characater_t) { .c_string = c_string, .w = w, .h = h, .c_texture = NULL};
}

characater_t * setCharacterDyn ( characater_t c)
{
	characater_t * ptr = (characater_t *) malloc ( sizeof (characater_t));
	
	ptr->c_string = c.c_string;
	ptr->w = c.w;
	ptr->h = c.h;
	ptr->c_texture = c.c_texture;
	
	return ptr;
}


void freeCharacter ( characater_t * c, void(*freeTexture)(void*))
{
	free ( c->c_string);
	freeTexture ( c->c_texture);
}
