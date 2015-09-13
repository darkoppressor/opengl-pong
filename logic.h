/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#ifndef logic_h
#define logic_h

#include <SDL.h>

void movement(Uint32 delta_ticks);

void hit_detection();

bool check_collision(int a_x,int a_y,int a_w,int a_h,int b_x,int b_y,int b_w,int b_h);

#endif
