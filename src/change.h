#pragma once
#include "data.h"
#include <cmath>

namespace ensiie
{
	/**
	 * @class Change
	 * 
	 * @brief Class representing a transformation of variables to determine those to be used to 
	 * dtermine the transformed PDE solution to the otpion pricing.
	 *
	 * The `Change` class inherits from the `Data` class and is responsible for performing
	 * transformation of prices and time vectors.
	 */
	class Change : public Data
	{
	protected:
		double f_; /**< Parameter to execute variable's change.*/
		double dt_changed_; /**< Changed time step.*/
		double ds_changed_; /**< Changed underlying asset's price step.*/
		std::vector<double> t_changed_;
		std::vector<double> l_changed_;

		/**
		 * @brief Performs the time transformation.
		 *
		 * This function calculates the time transformation `t` based on volatility
		 * and maturity, and stores the results in `t_changed_` and `dt_changed_`.
		 */
		void t_transformation();

		/**
		 * @brief Performs the price transformation.
		 *
		 * This function calculates the price transformation `l` based on the parameter `K`
		 * and stores the results in `l_changed_` and `ds_changed_`.
		 */
		void l_transformation();

		/**
		* @brief Transforms the t=0 price vector.
		*
		* @param v The price vector to be transformed.
		* @return A vector containing the transformed prices.
		*
		* This function applies a transformation to the prices obtained by the changed PDE using 
		* a formula based on `f_` and `l_changed_`, returning a vector with the corrected prices.
		*/
		std::vector<double> price_transformation(const std::vector<double>& v);

	public:

		/**
		* @brief Constructs a Change object using financial parameters.
		*
		* Initializes the financial parameters for the option pricing model and
		* calculates transofrmation of time and underlying asset's price.
		*
		* @param T Time to maturity (in years)
		* @param r Market Risk-free interest rate
		* @param sigma Volatility of the underlying asset
		* @param K Strike price of the option
		* @param L Maximum value of the underlying asset
		* @param M Number of time steps
		* @param N Number of price steps
		*/
		Change(double T, double r, double sigma, double K, double L, double M, double N);

		/**
		* @brief Constructs a Reduced object using an existing Data object.
		 *
		 * This constructor initializes the model using an existing `Data` object
		 * and calculates change of variables.
		 *
		 * @param d A `Data` object containing the financial parameters for the model
		*/
		Change(const Data& d);

		/**
		 * @brief Gets the transformed time values.
		 *
		 * @return A vector containing the transformed time values.
		 */
		std::vector<double> get_t_changed() const;

		/**
		 * @brief Gets the transformed price values.
		 *
		 * @return A vector containing the transformed asset's price values.
		 */
		std::vector<double> get_l_changed() const;

		/**
		 * @brief Gets the time variation step.
		 *
		 * @return The time variation step.
		 */
		double get_dt_changed() const;

		/**
		 * @brief Gets the price variation.
		 *
		 * @return The price variation value.
		 */
		double get_ds_changed() const;

		/**
		 * @brief Gets the f parameter.
		 *
		 * @return The f parameter value.
		 */
		double get_f() const;
	};
}