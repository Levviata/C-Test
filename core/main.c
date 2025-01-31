#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

static SDL_Window *window = NULL; // the window where our rendering takes place in (and game also, its a window duh)
static SDL_Renderer *renderer = NULL; // the variable where we will mash shit-in to print a beautiful or disfigured picture (when we actually tell the GPU to render it)
static SDL_Texture *bitmapTexture = NULL; // a bit map (or a map of bits?) of our texture
static SDL_Surface *bitmapSurface = NULL; // the surface where we lay / render our texture

static const char appname[32] = "Voxel Game";
static const char version[32] = "v0.0.0";
static const char appIdentifier[32] = "me.levviata.voxelgame";

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    // set our basic metadata, todo: expand later
    SDL_SetAppMetadata(appname, version, appIdentifier); 

    /* Create the window */
    if (!SDL_CreateWindowAndRenderer(appname, 800, 600, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window and renderer: %s\n", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Initalize subsystems, these can be manually closed with SDL_QuitSubSystem().
    // For when we close our app we use SDL_QuitSubSystem() for each subsystem and then SDL_Quit() for a re recleanup (as far as I know)
    SDL_InitSubSystem(SDL_INIT_VIDEO);

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


    /*
    const char *message = "Hello World!";
    int w = 0, h = 0;
    float x, y;
    const float scale = 2.0f;

    /* Center the message and scale it up 
    SDL_GetRenderOutputSize(renderer, &w, &h);
    SDL_SetRenderScale(renderer, scale, scale);
    x = ((w / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * SDL_strlen(message)) / 2;
    y = ((h / scale) - SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE) / 2;

    /* Draw the message
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDebugText(renderer, x, y, message);
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
    SDL_DestroyRenderer(renderer); // Destroy render 1st
    SDL_DestroyWindow(window); // Destroy window 2nd
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
}

