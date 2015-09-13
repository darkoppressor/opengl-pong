/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#include "logic.h"
#include "variables.h"
#include "paddle.h"

#include <SDL.h>

using namespace std;

void movement(Uint32 delta_ticks){
    for(int i=0;i<paddles.size();i++){
        paddles.at(i).move(delta_ticks);
    }
    for(int i=0;i<balls.size();i++){
        balls.at(i).move(delta_ticks);
    }
}

void hit_detection(){
    for(int i=0;i<paddles.size();i++){
        paddles.at(i).handle_events();
    }
    for(int i=0;i<balls.size();i++){
        balls.at(i).handle_events();
    }
}

bool check_collision(int a_x,int a_y,int a_w,int a_h,int b_x,int b_y,int b_w,int b_h){
    /**The sides of the rectangles.*/
    int left_a,left_b;
    int right_a,right_b;
    int top_a,top_b;
    int bottom_a,bottom_b;

    /**Calculate the sides of rect A.*/
    left_a=a_x;
    right_a=a_x + a_w;
    top_a=a_y;
    bottom_a=a_y + a_h;

    /**Calculate the sides of rect B.*/
    left_b=b_x;
    right_b=b_x + b_w;
    top_b=b_y;
    bottom_b=b_y + b_h;

    /**Check each side of a.  If it is found to be outside of b, these two squares are not colliding, so return false.*/
    if(bottom_a<=top_b){
        return false;
    }
    if(top_a>=bottom_b){
        return false;
    }
    if(right_a<=left_b){
        return false;
    }
    if(left_a>=right_b){
        return false;
    }

    /**If none of the sides from a are outside b.*/
    return true;
}
