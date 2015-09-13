/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#include "font.h"
#include "sdl.h"
#include "variables.h"

using namespace std;

BitmapFont::BitmapFont(){
    /**Initialize the variables:*/
    bitmap_font_texture=NULL;
    w=0;
    h=0;
    newLine=0;
    space=0;
}

void BitmapFont::build_font(string font_location){
    bitmap_font_texture=load_texture(font_location);
    /**Set the texture dimensions:*/
    w=256*SCALE;
    h=256*SCALE;
    /**Set the cell dimensions:*/
    int cellW=w/16;
    int cellH=h/16;
    int currentChar=0;/**The current character we are setting.*/
    for(int rows=0;rows<16;rows++){/**Go through the cell rows.*/
        for(int cols=0;cols<16;cols++){/**Go through the cell columns.*/
            /**Set the character offset:*/
            chars[currentChar].x=cellW*cols;
            chars[currentChar].y=cellH*rows;
            /**Set the dimensions of the character:*/
            chars[currentChar].w=cellW;
            chars[currentChar].h=cellH;
            currentChar++;/**Go to the next character.*/
        }
    }
    space=cellW/4;/**Calculate space.*/
    newLine=cellH/1.05;
}

void BitmapFont::show(int x,int y,string text,int font_color){
    int X=x,Y=y;/**Temporary offsets.*/
    for(int show=0;text[show]!='\0';show++){/**Go through the text.*/
        if(text[show]==' '){/**If the character is a space.*/
            X+=space;/**Move over.*/
        }
        else if(text[show]=='\n'){/**If the current character is a newline.*/
            Y+=newLine;/**Move down.*/
            X=x;/**Move back.*/
        }
        else{
            int ascii=(unsigned char)text[show];/**Get the ASCII value of the character.*/
            render_texture(X,Y,w,h,bitmap_font_texture,&chars[ascii],font_color);/**Show the character.*/
            X+=chars[ascii].w+1;/**Move over the width of the character with one pixel of padding.*/
        }
    }
}
