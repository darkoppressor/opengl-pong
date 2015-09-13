/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#ifndef paddle_h
#define paddle_h

#include <SDL.h>

#include "timer.h"

class Paddle{
    private:
    Timer ai_check;
    public:
    Paddle(float get_x,float get_y,bool get_human);
    void handle_input();
    void move(Uint32 delta_ticks);
    void handle_events();
    void show();
    float x,y,w,h;
    int move_state;
    bool human;
};

#endif
