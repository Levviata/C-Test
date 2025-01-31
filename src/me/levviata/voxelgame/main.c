#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window = NULL; // the window where our rendering takes place in (and game also, its a window duh)
static SDL_Renderer *renderer = NULL; // the variable where we will mash shit-in to print a beautiful or disfigured picture (WHEN we actually tell the GPU to render it)
static SDL_Texture* texture = NULL;

static int texture_width = 0, texture_height = 0;

static const char appname[32] = "Voxel Game";
static const char version[32] = "v0.0.0";
static const char appIdentifier[32] = "me.levviata.voxelgame";

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_Surface* surface = NULL;
    char* bmp_path = NULL;

    // set our basic metadata, todo: expand later
    SDL_SetAppMetadata(appname, version, appIdentifier); 
        
    // Initalize subsystems, these can be manually closed with SDL_QuitSubSystem().
    // For when we close our app we use SDL_QuitSubSystem() for each subsystem and then SDL_Quit() for recleanup (as far as I know)
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    
    /* Create the window and the renderer! */
    if (!SDL_CreateWindowAndRenderer(appname, 800, 600, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    /*
    SDL_asprintf(&bmp_path, "%stexture.bmp", SDL_GetBasePath());  /* allocate a string of the full file path 

    surface = SDL_LoadBMP(bmp_path);
    if (!surface) {
        SDL_Log("Couldn't load bitmap: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_free(bmp_path);  /* done with this, the file is loaded.

    texture_width = surface->w;
    texture_height = surface->h;

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        SDL_Log("Couldn't create static texture: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_DestroySurface(surface);  /* done with this, the texture has a copy of the pixels now.
    */
    return SDL_APP_CONTINUE;
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_KEY_DOWN ||
        event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    return SDL_APP_CONTINUE;
}

void render()
{
    #define vertLen 3
    SDL_Vertex vert[vertLen];

    // center
    vert[0].position.x = 400;
    vert[0].position.y = 150;
    vert[0].color.r = 1.0;
    vert[0].color.g = 0.0;
    vert[0].color.b = 0.0;
    vert[0].color.a = 1.0;

    // left
    vert[1].position.x = 200;
    vert[1].position.y = 450;
    vert[1].color.r = 0.0;
    vert[1].color.g = 0.0;
    vert[1].color.b = 1.0;
    vert[1].color.a = 1.0;

    // right
    vert[2].position.x = 600;
    vert[2].position.y = 450;
    vert[2].color.r = 0.0;
    vert[2].color.g = 1.0;
    vert[2].color.b = 0.0;
    vert[2].color.a = 1.0;

    /*
    SDL_FRect dst_rect;

    SDL_RenderClear(renderer); // Clear the canvas/render screen

    /* center this one.
    dst_rect.x = ((float)(800 - texture_width)) / 2.0f;
    dst_rect.y = ((float)(600 - texture_height)) / 2.0f;
    dst_rect.w = (float)texture_width;
    dst_rect.h = (float)texture_height;
    SDL_RenderTexture(renderer, texture, NULL, &dst_rect);

    //SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    //processInput();
    //update();
    render();

    return SDL_APP_CONTINUE;
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    SDL_DestroyTexture(texture); // Destroy texture
    /* Seems like SDL destroys our render and window on app quit automatically? Either way leave this as is just in case. */
    SDL_DestroyRenderer(renderer); // Destroy render 
    SDL_DestroyWindow(window); // Destroy window

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}

