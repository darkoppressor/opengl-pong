/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#ifndef ball_h
#define ball_h

#include <SDL.h>

class Ball{
    private:
    public:
    Ball();
    void move(Uint32 delta_ticks);
    void handle_events();
    void show();
    float x,y,w,h,x_vel,y_vel;
};

#endif
