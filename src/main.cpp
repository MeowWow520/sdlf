#define CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL3/SDL.h>



bool isgoing = true;
bool isLogFPS = false;
int FPS = 120;
SDL_Renderer *renderer;
SDL_Window *window;

bool scc(bool flag)
{
    if (flag) return flag;
    else SDL_Log("scc failed");
    return flag;
}

void InitSDL()
{
    scc(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO));
    window = SDL_CreateWindow("sdlf", 960, 800, SDL_WINDOW_RESIZABLE);
    renderer = SDL_CreateRenderer(window, NULL);
}

void HandleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case(SDL_EVENT_QUIT): {
                isgoing = false;
                SDL_Log("Recieving SDL_EVENT_QUIT, main loop quit");
                break;
            }
            default: break; 
        };
    }
}

void Updata()
{
    //TODO: you function
    return;
}

void Render()
{
    SDL_RenderPresent(renderer);
}

void Quit()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



int main(int argc, char* argv)
{
    (void)argc;
    (void)argv;
    std::cout << "Hello, SDL ez Freamwork\n";
    
    InitSDL();

    auto FrameTime = (1e9 / FPS);
    auto deltaTime = 0.0f;
    while(isgoing) 
    {
        auto StartTicks= SDL_GetTicksNS();

        HandleEvents();
        Updata();
        Render();

        auto EndTicks = SDL_GetTicksNS();  
        auto Diffent = EndTicks - StartTicks;
        if (Diffent <  FrameTime) {
            SDL_Delay((Uint32)((FrameTime - Diffent) / 1e6));
            deltaTime = (float)(FrameTime / 1e9);
        } else { deltaTime = (float)(Diffent / 1e9); }
        if (isLogFPS) SDL_Log("Current FPS: %f", 1 / deltaTime);
    }

    Quit();
    return 0;
}