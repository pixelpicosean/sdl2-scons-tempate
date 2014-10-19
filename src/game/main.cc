#include <SDL2/SDL.h>

SDL_Window *g_pWindow = nullptr;
SDL_Renderer *g_pRenderer = nullptr;

bool g_bRunning = false;

bool init(const char *title, int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {
        g_pWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

        if (g_pWindow != nullptr) {
            g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        }
    }
    else {
        return false;
    }

    return true;
}

void handleEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                g_bRunning = false;
                break;
            default:
                break;
        }
    }
}

void update() {}

void render()
{
    // Set to black
    SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);

    // Clear window
    SDL_RenderClear(g_pRenderer);

    // Render to window
    SDL_RenderPresent(g_pRenderer);
}

void clean()
{
    SDL_DestroyWindow(g_pWindow);
    SDL_DestroyRenderer(g_pRenderer);

    SDL_Quit();
}

int main(int argc, char *argv[])
{
    if (init("Awesome Game", 640, 480)) {
        g_bRunning = true;
    }
    else {
        return -1;
    }

    while (g_bRunning) {
        handleEvents();
        update();
        render();
    }

    clean();

    return 0;
}
