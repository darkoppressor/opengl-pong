/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#ifndef font_h
#define font_h

#include <SDL.h>
#include <string>
#include <SDL_opengl.h>

class BitmapFont{
    private:
    GLuint bitmap_font_texture;/**The font surface.*/
    int w,h;/**The width and height of the entire texture.*/
    SDL_Rect chars[256];/**The individual characters in the surface.*/
    int newLine,space;/**Spacing variables*/

    public:
    BitmapFont();/**The default constructor.*/
    void build_font(std::string font_location);/**Generates the font.*/
    void show(int x,int y,std::string text,int font_color);/**Shows the text.*/
};

#endif
