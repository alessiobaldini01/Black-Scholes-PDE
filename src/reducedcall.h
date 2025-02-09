#pragma once
#include "reduced.h"

namespace ensiie
{
	/**
	* @class ReducedCall
	*
	* @brief A class to calculate and store the price of a European call option
	* using implicit finite differences method to solve the modified Black-Scholes Heat Equation.
	*
	* This class is derived from the `Reduced` class and implements the specific
	* pricing algorithm for a European call option, including the computation of
	* terminal condition and the solution of the modified PDE using LU factorization.
	*/
	class ReducedCall : public Reduced
	{
		/** @brief A vector to store the prices of the reduced call option at time 0 and different time steps */
		std::vector<double> price_;

	public:

		/**
		* @brief Constructs a ReducedCall object using financial parameters.
		*
		* Initializes the financial parameters for the option pricing model and
		* calculates change of variables, parameters and LU factorization.
		*
		* @param T Time to maturity (in years)
		* @param r Market Risk-free interest rate
		* @param sigma Volatility of the underlying asset
		* @param K Strike price of the option
		* @param L Maximum value of the underlying asset
		* @param M Number of time steps
		* @param N Number of price steps
		*/
		ReducedCall(double T, double r, double sigma, double K, double L, double M, double N);
		
		/**
		* @brief Constructs a ReducedCall object using an existing Data object.
		 *
		 * This constructor initializes the model using an existing `Data` object
		 * and calculates change of variables, parameters and LU factorization.
		 *
		 * @param d A `Data` object containing the financial parameters for the model
		*/
		ReducedCall(const Data& d);

		/**
		 * @brief Computes the price of the European call option using the finite difference method
		 * on transformed PDE.
		 *
		 * This method uses terminal condition, LU factorization, and a system of equations
		 * to solve for the price of the European call option over a grid of time and price steps.
		 */
		void pricing() override;

		/**
		 * @brief Retrieves the computed prices of the put option P_tilda(0, s), which are prices
		 * at time 0 for each level of underlying price s.
		 *
		 * @return A vector containing the prices of the put option at time 0.
		 */
		std::vector<double> get_price() const;
	};
}