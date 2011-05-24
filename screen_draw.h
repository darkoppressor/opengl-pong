/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#ifndef screen_draw_h
#define screen_draw_h

#include <string>

/**For some draw functions (currently draw_city(), draw(), and draw_main_menu()), there is no call to SDL_Flip() at the end. This is because that particular screen may sometimes have dialog boxes
displayed over it, and the call to SDL_Flip() is located at the end of them instead. This means that you must be sure to add a call to SDL_Flip() after any other
call to the function. In other words, when calling the function without it being followed by a draw_dialog function, be sure to add the call to SDL_Flip() after it yourself.*/

void draw();

#endif
