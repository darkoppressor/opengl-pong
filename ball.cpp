/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#include "ball.h"
#include "variables.h"
#include "sdl.h"
#include "logic.h"
#include "random_number_generator.h"

using namespace std;

Ball::Ball(){
    w=BALL_WIDTH;
    h=BALL_HEIGHT;
    x_vel=random_range(150*SCALE,200*SCALE);
    int i=random_range(0,1);
    if(i==0){
        x_vel*=-1;
    }
    y_vel=random_range(150*SCALE,200*SCALE);
    x=SCREEN_WIDTH/2;
    if(last_score==0){
        y=10*SCALE;
    }
    if(last_score==1){
        y=(SCREEN_HEIGHT-BALL_HEIGHT-10)*SCALE;
        y_vel*=-1;
    }
}

void Ball::move(Uint32 delta_ticks){
    x+=x_vel * (delta_ticks/1000.0f);
    y+=y_vel * (delta_ticks/1000.0f);
}

void Ball::handle_events(){
    /**Keep the ball in bounds:*/
    if(x<0){/**If the ball hits the left wall.*/
        Mix_PlayChannel(-1,beep_wall,0);
        x=0;
        x_vel*=-1;
    }
    else if(x+w>SCREEN_WIDTH){/**If the ball hits the right wall.*/
       Mix_PlayChannel(-1,beep_wall,0);
        x=SCREEN_WIDTH-w;
        x_vel*=-1;
    }
    /**Did the ball go off screen?*/
    if(y+h/2<0 || y+h/2>SCREEN_HEIGHT){/**If the ball went off the screen.*/
        Mix_PlayChannel(-1,score,0);
        if(y+h/2<0){
            score_1++;/**Player 1 scores!*/
            last_score=1;
        }
        if(y+h/2>SCREEN_HEIGHT){
            score_2++;/**Player 2 scores!*/
            last_score=0;
        }
        /**Reset the ball:*/
        x_vel=random_range(150*SCALE,200*SCALE);
        int i=random_range(0,1);
        if(i==0){
            x_vel*=-1;
        }
        y_vel=random_range(150*SCALE,200*SCALE);
        x=SCREEN_WIDTH/2;
        if(last_score==0){
            y=10*SCALE;
        }
        if(last_score==1){
            y=(SCREEN_HEIGHT-BALL_HEIGHT-10)*SCALE;
            y_vel*=-1;
        }
    }
    /**Check for collision with the paddles.*/
    for(int i=0;i<paddles.size();i++){
        if(y_vel<0, check_collision(x,y,w,h,paddles.at(i).x,paddles.at(i).y,paddles.at(i).w,paddles.at(i).h) && y+h>=paddles.at(i).y+paddles.at(i).h){/**If the ball is traveling upwards and collides with a top paddle, and is not already too high.*/
                Mix_PlayChannel(-1,beep_paddle,0);
                y_vel*=-1;
                y_vel+=random_range(-10*SCALE,10*SCALE);
                x_vel+=random_range(-10*SCALE,10*SCALE);
                if(paddles.at(i).move_state==1){/**If the paddle was moving left.*/
                    x_vel-=random_range(10*SCALE,15*SCALE);
                }
                if(paddles.at(i).move_state==2){/**If the paddle was moving right.*/
                    x_vel+=random_range(10*SCALE,15*SCALE);
                }
                if(x_vel<0 && x>=(paddles.at(i).x+paddles.at(i).w-10*SCALE)){/**If the ball is going left and hits the far right side of the paddle.*/
                    x_vel*=-1;
                    y_vel+=random_range(40*SCALE,50*SCALE);
                    x_vel+=random_range(40*SCALE,50*SCALE);
                }
                if(x_vel>0 && x+w<=(paddles.at(i).x+10*SCALE)){/**If the ball is going right and hits the far left side of the paddle.*/
                    x_vel*=-1;
                    y_vel+=random_range(40*SCALE,50*SCALE);
                    x_vel+=random_range(40*SCALE,50*SCALE);
                }
                y=paddles.at(i).y+paddles.at(i).h;/**Set the ball just below the paddle.*/
        }
        if(y_vel>0 && check_collision(x,y,w,h,paddles.at(i).x,paddles.at(i).y,paddles.at(i).w,paddles.at(i).h) && y<=paddles.at(i).y){/**If the ball is traveling downwards and collides with a bottom paddle, and is not already too low.*/
                Mix_PlayChannel(-1,beep_paddle,0);
                y_vel*=-1;
                y_vel+=random_range(-10*SCALE,10*SCALE);
                x_vel+=random_range(-10*SCALE,10*SCALE);
                if(paddles.at(i).move_state==1){/**If the paddle was moving left.*/
                    x_vel-=random_range(10*SCALE,15*SCALE);
                }
                if(paddles.at(i).move_state==2){/**If the paddle was moving right.*/
                    x_vel+=random_range(10*SCALE,15*SCALE);
                }
                if(x_vel<0 && x>=(paddles.at(i).x+paddles.at(i).w-10*SCALE)){/**If the ball is going left and hits the far right side of the paddle.*/
                    x_vel*=-1;
                    y_vel-=random_range(40*SCALE,50*SCALE);
                    x_vel-=random_range(40*SCALE,50*SCALE);
                }
                if(x_vel>0 && x+w<=(paddles.at(i).x+10*SCALE)){/**If the ball is going right and hits the far left side of the paddle.*/
                    x_vel*=-1;
                    y_vel-=random_range(40*SCALE,50*SCALE);
                    x_vel-=random_range(40*SCALE,50*SCALE);
                }
                y=paddles.at(i).y-h;/**Set the ball just above the paddle.*/
        }
    }
}

void Ball::show(){
    render_texture(x,y,w,h,ball,NULL,WHITE);
}
