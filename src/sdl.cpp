#include "sdl.h"
#include <stdexcept>
#include <iostream>
#include <algorithm> 

namespace ensiie {

    SDL::SDL(const std::string& title, int width, int height) : window(nullptr), renderer(nullptr), screenWidth(width), screenHeight(height) 
    {
        // Initialize the SDL video subsystem
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            throw std::runtime_error("Error during SDL initialization: " + std::string(SDL_GetError()));
        }

        // Creates the window
        window = SDL_CreateWindow(title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_SHOWN);
        if (!window) {
            throw std::runtime_error("Impossible to create the window: " + std::string(SDL_GetError()));
        }

        //Creates the render
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!renderer) {
            SDL_DestroyWindow(window);
            throw std::runtime_error("Impossible to create the renderer: " + std::string(SDL_GetError()));
        }
    }

    SDL::~SDL() 
    {
        // Destroy the render
        SDL_DestroyRenderer(renderer);

        // Destroy the window
        SDL_DestroyWindow(window);

        // Quit SDL subsystem
        SDL_Quit();
    }

    void SDL::clearScreen() 
    {
        // Sets to white the colour of the draw
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        // Clear the screen
        SDL_RenderClear(renderer);
    }

    void SDL::drawAxes() 
    {
        // Set the color of the axis to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // X Axis on the bottom of the window
        SDL_RenderDrawLine(renderer, 0, screenHeight - 20, screenWidth, screenHeight - 20);

        // Y Axis on the left side of the window
        SDL_RenderDrawLine(renderer, 50, 0, 50, screenHeight);
    }

    void SDL::drawGraph_red(const std::vector<double>& values)
    {
        // Ensure the vector has at least two points
        if (values.size() < 2) {
            throw std::invalid_argument("The vector must contain at least two points to draw a graph.");
        }

        // Sets the draw color to red
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // Find the maximum and minimum values in the vector
        double maxValue = *std::max_element(values.begin(), values.end());
        double minValue = *std::min_element(values.begin(), values.end());

        // Handle the case where all values are identical
        if (maxValue == minValue) {
            throw std::runtime_error("Cannot draw graph: all values are identical.");
        }

        // Calculate the step size for the X axis
        double xStep = static_cast<double>(screenWidth - 100) / (values.size() - 1);

        // Calculate the scaling factor for the Y axis
        double yScale = static_cast<double>(screenHeight - 40) / (maxValue - minValue);

        // Draw the graph
        for (size_t i = 0; i < values.size() - 1; ++i)
        {
            double x1 = 50 + i * xStep;
            double y1 = screenHeight - 20 - (values[i] - minValue) * yScale;

            double x2 = 50 + (i + 1) * xStep;
            double y2 = screenHeight - 20 - (values[i + 1] - minValue) * yScale;

            // Draw the line
            SDL_RenderDrawLine(renderer, static_cast<int>(x1), static_cast<int>(y1),
                static_cast<int>(x2), static_cast<int>(y2));
        }
    }

    void SDL::drawGraph_green(const std::vector<double>& values)
    {
        // Ensure the vector has at least two points
        if (values.size() < 2) {
            throw std::invalid_argument("The vector must contain at least two points to draw a graph.");
        }

        // Sets the draw color to red
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

        // Find the maximum and minimum values in the vector
        double maxValue = *std::max_element(values.begin(), values.end());
        double minValue = *std::min_element(values.begin(), values.end());

        // Handle the case where all values are identical
        if (maxValue == minValue) {
            throw std::runtime_error("Cannot draw graph: all values are identical.");
        }

        // Calculate the step size for the X axis
        double xStep = static_cast<double>(screenWidth - 100) / (values.size() - 1);

        // Calculate the scaling factor for the Y axis
        double yScale = static_cast<double>(screenHeight - 40) / (maxValue - minValue);

        // Draw the graph
        for (size_t i = 0; i < values.size() - 1; ++i)
        {
            double x1 = 50 + i * xStep;
            double y1 = screenHeight - 20 - (values[i] - minValue) * yScale;

            double x2 = 50 + (i + 1) * xStep;
            double y2 = screenHeight - 20 - (values[i + 1] - minValue) * yScale;

            // Draw the line
            SDL_RenderDrawLine(renderer, static_cast<int>(x1), static_cast<int>(y1),
                static_cast<int>(x2), static_cast<int>(y2));
        }
    }


    void SDL::updateScreen() 
    {
        // Present the rendered content on the screen
        SDL_RenderPresent(renderer);
    }

    void SDL::waitForClose() 
    {
        bool running = true;
        SDL_Event event;

        // The cycle stops SDL from running when catch the event "Close the window"
        while (running) 
        {
            while (SDL_PollEvent(&event)) 
            {
                if (event.type == SDL_QUIT) 
                {
                    running = false;
                }
            }
        }
    }

}

