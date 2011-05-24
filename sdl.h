/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#ifndef sdl_h
#define sdl_h

#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_opengl.h>

#include "font.h"

GLuint surface_to_texture(SDL_Surface* optimized_image);

SDL_Surface *load_image(std::string filename);

GLuint load_texture(std::string filename);

/**x offset, y offset, source surface, destination surface, clipping SDL_Rect, change offsets to center source surface somewhere?*/
void render_texture(float x,float y,float h,float w,GLuint source,SDL_Rect* texture_clip,int font_color);

bool init_GL();/**Initialize all of the OpenGL specific stuff.*/

bool init();/**Initialize all of the SDL stuff.*/

bool load_files();

void clean_up();

#endif
