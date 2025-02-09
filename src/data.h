#pragma once
#include <vector>
#include <stdexcept>

namespace ensiie
{
	/**
	* @class Data
	* @brief Contains all the data needed to solve the Black-Scholes pde.
	* 
	* It also discretize the domain in time and asset value. 
	*/
	class Data
	{
	protected:
		double T_; /**< Time to maturity.*/
		double r_; /**< Market risk-free interest rate.*/
		double sigma_; /**< Underlying asset volatility.*/
		double K_; /**< Strike price of the option.*/
		double L_; /**< Underlying asset maximum price.*/
		double M_; /**< Number of steps in time discretization.*/
		double N_; /**< Number of steps in asset price discretization.*/
		double dt_; /**< Lenght of the step in time.*/
		double ds_; /**< Lenght of the step in asset's value.*/
		std::vector<double> t_; /**< Discretized time vector.*/
		std::vector<double> l_; /**< Discretized asset price vector.*/

		/**
		 * @brief Discretizes the time and space domains based on the parameters of the model.
		 *
		 * This method calculates the time step (`dt_`) and space step (`ds_`)
		 * and fills the vectors `t_` and `l_` with the discretized values.
		 */
		void discretize();
		
	public:
		/**
		 * @brief Constructs a Data object with the specified parameters.
		 * 
		 * Initializes the parameters of the model and calls the `discretize()` method 
		 * to set up the time and space discretization.
		 * 
		 * @param T Total time to maturity (in years).
		 * @param r Market risk-free interest rate.
		 * @param sigma Volatility of the underlying asset.
		 * @param K Strike price of the option.
		 * @param L Maximum asset price considered in the model.
		 * @param M Number of time steps in the discretization.
		 * @param N Number of asset price steps in the discretization.
		 *
		 * @throws std::invalid_argument If any parameter is negative, or if `M` or `N` is zero.
		 */
		Data(double T, double r, double sigma, double K, double L, double M, double N);

		/**
		 * @brief Gets the total time to maturity.
		 * @return Total time to maturity (T).
		 */
		double get_T() const;

		/**
		 * @brief Gets the market risk-free interest rate.
		 * @return Market risk-free interest rate (r).
		 */
		double get_r() const;

		/**
		 * @brief Gets the volatility of the underlying asset.
		 * @return Volatility (sigma).
		 */
		double get_sigma() const;

		/**
		 * @brief Gets the strike price of the option.
		 * @return Strike price (K).
		 */
		double get_K() const;

		/**
		 * @brief Gets the maximum asset price considered in the model.
		 * @return Maximum asset price (L).
		 */
		double get_L() const;

		/**
		 * @brief Gets the number of time steps in the discretization.
		 * @return Number of time steps (M).
		 */
		double get_M() const;

		/**
		 * @brief Gets the number of asset price steps in the discretization.
		 * @return Number of asset price steps (N).
		 */
		double get_N() const;

		/**
		* @brief Gets the time step size.
		* @return Time step size (dt).
		*/
		double get_dt() const;

		/**
		 * @brief Gets the asset price step size.
		 * @return Asset price step size (ds).
		 */
		double get_ds() const;

		/**
		 * @brief Gets the discretized time vector.
		 * @return Discretized time vector (t).
		 */
		std::vector<double> get_t() const;

		/**
		 * @brief Gets the discretized asset price vector.
		 * @return Discretized asset price vector (l).
		 */
		std::vector<double> get_l() const;

	};
}