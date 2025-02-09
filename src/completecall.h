#pragma once
#include "complete.h"

namespace ensiie 
{
	/**
	* @class CompleteCall
	* 
	* @brief A class to calculate and store the price of a European call option
	* using Crank-Nicolson method to solve the Black-Scholes PDE.
	*
	* This class is derived from the `Complete` class and implements the specific
	* pricing algorithm for a European call option, including the computation of
	* boundary conditions and the solution of the PDE using LU factorization.
	*/
	class CompleteCall : public Complete
	{
		/** @brief A vector to store the prices of the call option at time 0 and different time steps */
		std::vector<double> price_;

	public:

		/**
		* @brief Constructs a CompleteCall object using financial parameters.
		*
		* Initializes the financial parameters for the option pricing model and
		* calculates the coefficients and LU factorization.
		*
		* @param T Time to maturity (in years)
		* @param r Market Risk-free interest rate
		* @param sigma Volatility of the underlying asset
		* @param K Strike price of the option
		* @param L Maximum value of the underlying asset
		* @param M Number of time steps
		* @param N Number of price steps
		*/
		CompleteCall(double T, double r, double sigma, double K, double L, double M, double N);

		/**
		 * @brief Constructs a CompleteCall object using an existing Data object.
		 *
		 * This constructor initializes the model using an existing `Data` object
		 * and calculates the coefficients and LU factorization.
		 *
		 * @param d A `Data` object containing the financial parameters for the model
		 */
		CompleteCall(const Data& d);

		/**
		 * @brief Computes the price of the European call option using the Crank-Nicolson method.
		 *
		 * This method uses boundary conditions, LU factorization, and a system of equations
		 * to solve for the price of the European call option over a grid of time and price steps.
		 */
		void pricing() override;

		/**
		 * @brief Retrieves the computed prices of the call option C(0, s), which are prices 
		 * at time 0 for each level of underlying price s.
		 *
		 * @return A vector containing the prices of the call option at time 0.
		 */
		std::vector<double> get_price() const;
	};
}