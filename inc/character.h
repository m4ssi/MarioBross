#ifndef _H_CHARACTER_
#define _H_CHARACTER_

typedef struct
{
	char * c_string;
	int w, h, x, y;
	
	void * c_texture;
	
} characater_t;

characater_t readCharacterString ( char * filename);

characater_t * setCharacterDyn ( characater_t c);

void freeCharacter ( characater_t * c, void(*freeTexture)(void*));
#endif
