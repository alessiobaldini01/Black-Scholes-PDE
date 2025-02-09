#pragma once
#include "change.h"
#include <algorithm>

namespace ensiie
{
	/**
	 * @class Reduced
	 * @brief A base abstract class for solving financial models using implicit finite differences methods.
	 *
	 * The `Reduced` class extends the `Data` and 'Change' classes and serves as an abstract base for solving
	 * the modified partial differential equations (PDEs) related to call and put options pricing.
	 * It provides the structure and common functionality for subclasses, involved in deterining prices
	 * for call and put options, computing coefficient used in implicit finite differences schemes,
	 * performing LU factorization of the coefficients' matrix, and providing access to the computed values.
	 *
	 * @details
	 * This abstract class includes the method for LU factorization for efficient solving of tridiagonal systems.
	 *
	 * Subclasses derived from `Reduced` implement the specific algorithm of the PDE solver, including
	 * terminal condition, to get the modified european call and put option pricing.
	 *
	 * The class can be initialized via direct parameter input or using an existing `Data` object.
	 *
	 * @note This class cannot be instantiated directly due to its abstract nature.
	 */
	class Reduced : public Change
	{
	protected:
		double theta_; /**< Parameter to solve the linear system.*/
		std::vector<double> low_;
		std::vector<double> up_;

		/**
		 * @brief Performs LU factorization of the system's matrix for implicit finite differences scheme.
		 *
		 * This method calculates the lower (low) and upper (up) matrices, which are
		 * used to solve the system of equations iteratively.
		 */
		void lu_factorization();

	public:

		/**
		* @brief Constructs a Reduced object using financial parameters.
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
		Reduced(double T, double r, double sigma, double K, double L, double M, double N);

		/**
		* @brief Constructs a Reduced object using an existing Data object.
		 *
		 * This constructor initializes the model using an existing `Data` object
		 * and calculates change of variables, parameters and LU factorization.
		 *
		 * @param d A `Data` object containing the financial parameters for the model
		*/
		Reduced(const Data& d);

		/**
		 * @brief Pure virtual function to compute the price of the option.
		 *
		 * This is a pure virtual function that is implemented by its derived class.
		 *
		 * It defines the computation of Modified Call and Put options prices.
		 * The specific implementation will based on different terminal conditions.
		 *
		 * @note Since this is a pure virtual function, `Complete` cannot be instantiated directly.
		 */
		virtual void pricing() = 0;

		/**
		 * @brief Gets the theta coefficient for the implicit finite differences scheme.
		 * @return A double with the theta coefficient.
		 */
		double get_theta() const;

		/**
		 * @brief Gets the lower matrix values of coefficients' matrix
		 * from the LU factorization.
		 *
		 * @return A vector of lower matrix values (low).
		 */
		std::vector<double> get_low() const;

		/**
		 * @brief Gets the upper matrix values of coefficients' matrix
		 * from the LU factorization.
		 *
		 * @return A vector of upper matrix values (up).
		 */
		std::vector<double> get_up() const;
	};
}