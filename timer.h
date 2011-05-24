/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#ifndef timer_h
#define timer_h

class Timer{
    private:
    Uint32 start_ticks;/**The clock time when the timer started.*/
    Uint32 paused_ticks;/**The ticks stored when the timer was paused.*/
    /**Timer status.*/
    bool paused;
    bool started;
    public:
    Timer();/**Initializes variables.*/
    /**The various clock actions.*/
    void start();
    void stop();
    void pause();
    void unpause();
    Uint32 get_ticks();/**Get the timer's time.*/
    /**Checks the status of the timer.*/
    bool is_started();
    bool is_paused();
};

#endif
