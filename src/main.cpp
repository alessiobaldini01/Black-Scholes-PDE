#define SDL_MAIN_HANDLED
#include "completecall.h"
#include "completeput.h"
#include "reducedcall.h"
#include "reducedput.h"
#include "sdl.h"
#include <iostream>
#include <cstdlib>

using namespace ensiie;

int main(int argc, char* argv[])
{
    // Unused parameters in the main function (just to avoid compiler warnings)
    (void)argc;
    (void)argv;

    try {

        // Initialization of input parameters for option pricing
        double T = 1.0;     ///< Time to maturity
        double r = 0.1;     ///< Risk-free interest rate
        double sigma = 0.1; ///< Volatility of the asset
        double K = 100;     ///< Strike price
        double L = 300;     ///< Asset price grid length
        double M = 1000;    ///< Number of time steps
        double N = 1000;    ///< Number of price points

        // Creating the Data object that holds all option pricing parameters
        Data d(T, r, sigma, K, L, M, N);

        // Creating instances for different option pricing methods (Complete and Reduced methods)
        CompletePut cp(d);   ///< Complete Put option pricing
        CompleteCall cc(d);  ///< Complete Call option pricing
        ReducedPut rp(d);    ///< Reduced Put option pricing
        ReducedCall rc(d);   ///< Reduced Call option pricing

        // Pricing the options using different methods
        cp.pricing();        ///< Pricing Complete Put option
        cc.pricing();        ///< Pricing Complete Call option
        rp.pricing();        ///< Pricing Reduced Put option
        rc.pricing();        ///< Pricing Reduced Call option

        // Retrieving the computed option prices
        std::vector<double> cput = cp.get_price();   ///< Prices for Complete Put options
        std::vector<double> ccall = cc.get_price();  ///< Prices for Complete Call options
        std::vector<double> rput = rp.get_price();   ///< Prices for Reduced Put options
        std::vector<double> rcall = rc.get_price();  ///< Prices for Reduced Call options

        // Arrays to store the differences between the two pricing methods (Complete and Reduced)
        std::vector<double> difference_call(N + 1);  ///< Difference for Call options
        std::vector<double> difference_put(N + 1);   ///< Difference for Put options

        // Printing the prices for each option type
        for (int i = 0; i <= N; i++)
        {
            std::cout << "price complete Put " << i << " = " << cput[i] << std::endl;
        }
        
        for (int i = 0; i <= N; i++)
        {
            std::cout << "price complete Call " << i << " = " << ccall[i] << std::endl;
        }
        
        for (int i = 0; i <= N; i++)
        {
            std::cout << "price reduced Put " << i << " = " << rput[i] << std::endl;
        }
        
        for (int i = 0; i <= N; i++)
        {
            std::cout << "price reduced Call " << i << " = " << rcall[i] << std::endl;
        }
        
        // Computing the differences between the two pricing methods
        for (int i = 0; i <= N; i++)
        {
            difference_call[i] = ccall[i] - rcall[i];
        }

        for (int i = 0; i <= N; i++)
        {
            difference_put[i] = cput[i] - rput[i];
        }

        // Information for the user about the upcoming graphs
        std::cout << "To visualize the next graph, close the windows manually" << std::endl;
        std::cout << "All the graph are presented in the following order:" << std::endl;
        std::cout << "- P(0,s) and P_tilda(0,s)" << std::endl;
        std::cout << "- difference between the two methods' results for Put" << std::endl;
        std::cout << "- C(0,s) and C_tilda(0,s)" << std::endl;
        std::cout << "- difference between the two methods' results for Call" << std::endl;

        // Setting up the window size for graphical output
        const int Screen_Width = 800;
        const int Screen_Height = 600;
    
        // Creating a graph window to visualize the results
        SDL graph("P(0, s)/C(0,s) = red, P_tilda(0,s)/C_tilda(0,s) = green", Screen_Width, Screen_Height);
        
        // Graph 1: Plotting the prices of Complete Put and Reduced Put
        graph.clearScreen();
        graph.drawAxes();
        graph.drawGraph_red(cput);   ///< Drawing the Complete Put prices in red
        graph.drawGraph_green(rput); ///< Drawing the Reduced Put prices in green
        graph.updateScreen();
        graph.waitForClose(); // Wait for user to close the window

        // Graph 2: Plotting the difference between Complete and Reduced Put
        graph.clearScreen();
        graph.drawAxes();
        graph.drawGraph_red(difference_put); ///< Drawing the difference for Put prices in red
        graph.updateScreen();
        graph.waitForClose();

        // Graph 3: Plotting the prices of Complete Call and Reduced Call
        graph.clearScreen();
        graph.drawAxes();
        graph.drawGraph_red(ccall);   ///< Drawing the Complete Call prices in red
        graph.drawGraph_green(rcall); ///< Drawing the Reduced Call prices in green
        graph.updateScreen();
        graph.waitForClose();

        // Graph 4: Plotting the difference between Complete and Reduced Call
        graph.clearScreen();
        graph.drawAxes();
        graph.drawGraph_red(difference_call); ///< Drawing the difference for Call prices in red
        graph.updateScreen();
        graph.waitForClose();
    }

    catch (const std::exception& e) 
    {
        std::cerr << "Error: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
   
    return 0;
}
