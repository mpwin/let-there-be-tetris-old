#include <cstdlib>
#include <ctime>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SDL.h>

#include "board.h"
#include "tetromino.h"

int main(int argc, char ** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow(
        "Tetris",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024,
        768,
        SDL_WINDOW_OPENGL
    );
    SDL_Surface *screen = SDL_GetWindowSurface(window);

    SDL_GL_CreateContext(window);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0f, 24.0f, -2.0f, 22.0f, 0.0f, 1.0f);

    srand(time(NULL));

    Board board;
    board.instantiate_tetromino();

    int current_time, last_time = 0;

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_DOWN:
                            board.process_tetromino_down();
                            break;
                        case SDLK_ESCAPE:
                            running = false;
                            break;
                        case SDLK_LEFT:
                            board.process_tetromino_left();
                            break;
                        case SDLK_RIGHT:
                            board.process_tetromino_right();
                            break;
                        case SDLK_UP:
                            board.process_tetromino_rotate();
                            break;
                        default:
                            break;
                    }
                    break;
                }
                default:
                    break;
            }
        }

        current_time = SDL_GetTicks();
        if (current_time > last_time + 750)
        {
            board.process_tetromino_down();
            last_time = current_time;
        }

        glClear(GL_COLOR_BUFFER_BIT);
        board.draw();
        SDL_GL_SwapWindow(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
