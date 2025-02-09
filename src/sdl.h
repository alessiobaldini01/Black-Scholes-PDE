#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>

namespace ensiie {

    /**
     * @class SDL
     * 
     * @brief A class to manage the SDL window and render put and call prices.
     *
     * This class provides functionalities to create an SDL window, render graphical elements (axes and graphs),
     * and manage events for the window. It includes methods for clearing the screen, drawing axes, drawing graphs,
     * updating the screen, and handling window close events.
     */
    class SDL 
    {

        SDL_Window* window; /**< Pointer to the SDL window. */
        SDL_Renderer* renderer; /**< Pointer to the SDL renderer. */
        int screenWidth; /**< Width of the window. */
        int screenHeight; /**< Height of the window. */

    public:
       
        /**
        * @brief Constructs the SDL object and initializes the SDL video subsystem.
        *
        * This constructor creates an SDL window with the specified title and dimensions and sets up the renderer.
        * If any SDL function call fails, an exception is thrown.
        *
        * @param title The title of the SDL window.
        * @param width The width of the SDL window.
        * @param height The height of the SDL window.
        * @throws std::runtime_error If SDL initialization, window creation, or renderer creation fails.
        */
        SDL(const std::string& title, int width, int height);

        /**
         * @brief Destructor to clean up SDL resources.
         *
         * This destructor destroys the SDL renderer and window and calls SDL_Quit to clean up the SDL library.
         */
        ~SDL();

        /**
         * @brief Clears the screen with a white background.
         *
         * This method sets the drawing color to white and clears the renderer’s target, essentially clearing the screen.
         */
        void clearScreen();

        /**
        * @brief Draws the axes on the screen.
        *
        * This method draws the X and Y axes on the screen. The X axis is drawn along the bottom of the window,
        * and the Y axis is drawn along the left side.
        */
        void drawAxes();

        /**
         * @brief Draws a graph on the screen based on the provided values.
         *
         * This method plots a graph by drawing lines between data points. The graph is scaled according to the screen size
         * and the range of the data. The graph is drawn in red color.
         *
         * @param values A vector containing the data points to be plotted on the graph.
         */
        void drawGraph_red(const std::vector<double>& values);

        /**
         * @brief Draws a graph on the screen based on the provided values.
         *
         * This method plots a graph by drawing lines between data points. The graph is scaled according to the screen size
         * and the range of the data. The graph is drawn in green color.
         *
         * @param values A vector containing the data points to be plotted on the graph.
         */
        void drawGraph_green(const std::vector<double>& values);

        /**
         * @brief Updates the screen with the rendered content.
         *
         * This method presents the rendered content to the screen. It is called to update the window after drawing operations.
         */
        void updateScreen();

        /**
         * @brief Waits for the user to close the window.
         *
         * This method enters a loop that listens for SDL events, and the window will stay open until the user closes it.
         * Once the user closes the window, the loop terminates.
         */
        void waitForClose();
    };
}
