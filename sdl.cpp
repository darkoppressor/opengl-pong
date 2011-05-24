/* Copyright (c) 2011 Kevin Wells */
/* OpenGL Pong may be freely redistributed.  See license for details. */

#include <SDL_mixer.h>

#include "sdl.h"
#include "variables.h"

using namespace std;

GLuint surface_to_texture(SDL_Surface* optimized_image){
    GLuint texture;
    GLenum texture_format;
    GLint nOfColors;
    nOfColors=optimized_image->format->BytesPerPixel;
    if(nOfColors==4){/**If the image contains an alpha channel.*/
        if(optimized_image->format->Rmask==0x000000ff){
            texture_format=GL_RGBA;
        }
        else{
            texture_format=GL_BGRA;
        }
    }
    else if(nOfColors==3){/**If the image contains no alpha channel.*/
        if(optimized_image->format->Rmask==0x000000ff){
            texture_format=GL_RGB;
        }
        else{
            texture_format=GL_BGR;
        }
    }
    else{
        printf("Warning: the loaded image is not truecolor... this will probably break\n");
        //Do something about this.
    }
    glGenTextures(1,&texture);/**Have OpenGL generate a texture object handle for us.*/
    glBindTexture(GL_TEXTURE_2D,texture);/**Bind the texture object.*/
    /**Set the texture's properties:*/
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    /**Edit the texture object's image data using the information SDL_Surface gives us:*/
    glTexImage2D(GL_TEXTURE_2D,0,nOfColors,optimized_image->w,optimized_image->h,0,texture_format,GL_UNSIGNED_BYTE,optimized_image->pixels);
    return texture;
}

SDL_Surface *load_image(string filename){
    SDL_Surface* loaded_image=NULL;/**Temporary storage for the image being loaded.*/
    SDL_Surface* optimized_image=NULL;/**The optimized image that will be used.*/
    loaded_image=IMG_Load(filename.c_str());/**Load the image.*/
    if(loaded_image != NULL){/**Make sure nothing went wrong loading the image.*/
        optimized_image=SDL_DisplayFormatAlpha(loaded_image);/**Create the optimized image.*/
        SDL_FreeSurface(loaded_image);/**Free the old surface.*/
    }
    return optimized_image;
}

/**Call this when loading image files to be used as textures throughout the program:*/
GLuint load_texture(string filename){
    SDL_Surface* temp_surface=load_image(filename);
    GLuint temp_texture=surface_to_texture(temp_surface);
    SDL_FreeSurface(temp_surface);
    return temp_texture;
}

/**x offset, y offset, source texture, clipping SDL_Rect, centered on the x-axis?*/
void render_texture(float x,float y,float w,float h,GLuint source,SDL_Rect* texture_clip=NULL,int font_color=0){
    glBindTexture(GL_TEXTURE_2D,source);/**Bind the source texture.*/
    glTranslatef(x,y,0);/**Move to the offset of the image we want to place.*/
    /**Set the font colors.*/
    if(font_color==1){/**If we want white font.*/
        glColor4f(1.0,1.0,1.0,1.0);
    }
    else if(font_color==2){/**If we want black font.*/
        glColor4f(0.0,0.0,0.0,1.0);
    }
    else{/**Otherwise, make the color full white. This also allows whatever colors and alpha you want for images.*/
        glColor4f(1.0,1.0,1.0,1.0);
    }
    glBegin(GL_QUADS);/**Start quad.*/
        /**Apply the texture to the screen:*/
        if(texture_clip!=NULL){/**If we are clipping a sprite sheet:*/
            glTexCoord2f((texture_clip->x)/w,(texture_clip->y+texture_clip->h)/h);/**Bottom left corner.*/                  glVertex3f(0,texture_clip->h,0);/**Bottom left corner.*/
            glTexCoord2f((texture_clip->x+texture_clip->w)/w,(texture_clip->y+texture_clip->h)/h);/**Bottom right corner.*/ glVertex3f(texture_clip->w,texture_clip->h,0);/**Bottom right corner.*/
            glTexCoord2f((texture_clip->x+texture_clip->w)/w,(texture_clip->y)/h);/**Top right corner.*/                    glVertex3f(texture_clip->w,0,0);/**Top right corner.*/
            glTexCoord2f((texture_clip->x)/w,(texture_clip->y)/h);/**Top left corner.*/                                     glVertex3f(0,0,0);/**Top left corner.*/
        }
        else{/**If we are just rendering a full texture:*/
            glTexCoord2i(0,0); glVertex3f(0,0,0);
            glTexCoord2i(1,0); glVertex3f(w,0,0);
            glTexCoord2i(1,1); glVertex3f(w,h,0);
            glTexCoord2i(0,1); glVertex3f(0,h,0);
        }
    glEnd();/**End quad.*/
    glLoadIdentity();/**Reset.*/
}

bool init_GL(){
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(0,.63,0,0);/**Set clear color.*/
    glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
    /**Set projection:*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0,-1,1);
    /**Initialize modelview matrix:*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(glGetError()!=GL_NO_ERROR){/**If there were any errors.*/
        return false;
    }
    return true;/**If everything initialized successfully, we are good to go!*/
}

/**Here we initialize all of the SDL stuff.*/
bool init(){
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1){/**Initialize all of the standard SDL stuff, and return false if it did not initialize properly.*/
        printf("Unable to init SDL: %s\n",SDL_GetError());
        return false;
    }

    ///fprintf(stderr,"Whoa! Test!",SDL_GetError());

    /**Set OpenGL attributes:*/
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    /**Set up the screen:*/
    screen=SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_OPENGL|SDL_HWSURFACE);
    if(!screen){/**Return false if the screen could not be set up.*/
        printf("Unable to set video mode: %s\n",SDL_GetError());
        return false;
    }
    /**Initialize OpenGL*/
    if(init_GL()==false){
        return false;
    }
    if(Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096)==-1){/**Start up the audio system.*/
        return false;
    }
    SDL_WM_SetCaption("OpenGL Pong",NULL);/**Set the window caption.*/
    SDL_ShowCursor(1);/**Show the mouse cursor.*/
    return true;
}

bool load_files(){
    /**Load the textures:*/
    paddle=load_texture("data/images/paddle.png");
    ball=load_texture("data/images/ball.png");

    /**Load the music and sound effects:*/
    music=Mix_LoadMUS("data/music/background.ogg");
    beep_paddle=Mix_LoadWAV("data/sounds/beep1.wav");
    beep_wall=Mix_LoadWAV("data/sounds/beep2.wav");
    score=Mix_LoadWAV("data/sounds/score.wav");

    /**Load the font:*/
    font.build_font("data/images/bitmap_font.png");

    return true;
}

void clean_up(){
    while(!Mix_FadeOutMusic(1000) && Mix_PlayingMusic()){
        SDL_Delay(100);
    }
    Mix_HaltMusic();

    Mix_FreeMusic(music);
    Mix_FreeChunk(beep_paddle);
    Mix_FreeChunk(beep_wall);
    Mix_FreeChunk(score);

    glDeleteTextures(1,&paddle);
    glDeleteTextures(1,&ball);


    Mix_CloseAudio();
    SDL_Quit();
    printf("Exited cleanly!\n");
}
