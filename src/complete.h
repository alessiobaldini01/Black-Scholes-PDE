#pragma once
#include "data.h"
#include <algorithm>
#include <cmath>

namespace ensiie
{
	/**
	 * @class Complete
	 * @brief A base abstract class for solving financial models using Crank-Nicolson methods.
	 *
	 * The `Complete` class extends the `Data` class and serves as an abstract base for solving
	 * partial differential equations (PDEs) related to call and put options pricing.
	 * It provides the structure and common functionality for subclasses, involved in deterining prices 
	 * for call and put optiont, computing coefficients used in Crank-Nicolson schemes, 
	 * performing LU factorization of the coefficients' matrix, and providing access to the computed values.
	 *
	 * @details
	 * This abstract class includes methods for:
	 * - Calculation of the coefficients (`alpha`, `beta`, `gamma`) for Crank-Nicolson methods.
	 * - LU factorization for efficient solving of tridiagonal systems.
	 *
	 * Subclasses derived from `Complete` implement the specific algorithm of the PDE solver, including
	 * boundary conditions, to get the european call and put option pricing.
	 *
	 * The class can be initialized via direct parameter input or using an existing `Data` object.
	 *
	 * @note This class cannot be instantiated directly due to its abstract nature.
	 */
	class Complete : public Data
	{
	protected:
		std::vector<double> alpha_;
		std::vector<double> beta_;
		std::vector<double> gamma_;
		std::vector<double> low_;
		std::vector<double> up_;

		/**
		 * @brief Computes the coefficients (alpha, beta, gamma) for the Crank-Nicolson scheme.
		 *
		 * These coefficients are used in the matrix representation of the problem.
		 * The computation is based on the model parameters and discretization values.
		 */
		void coefficients_computation();

		/**
		 * @brief Performs LU factorization of the system's matrix for Crank-Nicholson scheme.
		 *
		 * This method calculates the lower (low) and upper (up) matrices, which are
		 * used to solve the system of equations iteratively.
		 */
		void lu_factorization();

	public:

		/**
		 * @brief Constructs a Complete object with the given parameters.
		 *
		 * This constructor initializes the base `Data` class and computes
		 * the coefficients and LU factorization.
		 *
		 * @param T Total time to maturity (in years).
		 * @param r Risk-free interest rate.
		 * @param sigma Volatility of the underlying asset.
		 * @param K Strike price.
		 * @param L Maximum asset price for discretization.
		 * @param M Number of time steps.
		 * @param N Number of space steps.
		 */
		Complete(double T, double r, double sigma, double K, double L, double M, double N);
		
		/**
		 * @brief Constructs a Complete object using an existing Data object.
		 *
		 * This constructor takes the parameters from an existing `Data` object
		 * and computes the coefficients and LU factorization.
		 * 
		 * Note: The `Data` object `d` is not copied; its values are used to initialize 
		 * the base class `Data` members. Therefore, the member of the class 'Data'
		 * exists only once in memory, shared between the `Data` and `Complete` objects.
		 * 
		 * @param d A `Data` object to initialize the base class.
		 */
		Complete(const Data& d);

		/**
		 * @brief Pure virtual function to compute the price of the option.
		 *
		 * This is a pure virtual function that is implemented by its derived class.
		 * 
		 * It defines the computation of Call and Put options price.
		 * The specific implementation will based on different boundary conditions.
		 *
		 * @note Since this is a pure virtual function, `Complete` cannot be instantiated directly.
		 */
		virtual void pricing() = 0;

		/**
		 * @brief Gets the alpha coefficients for the Crank_Nicolson scheme.
		 * @return A vector of alpha coefficients.
		 */
		std::vector<double> get_alpha() const;

		/**
		 * @brief Gets the beta coefficients for the Crank_Nicolson scheme.
		 * @return A vector of beta coefficients.
		 */
		std::vector<double> get_beta() const;

		/**
		 * @brief Gets the gamma coefficients for the Crank_Nicolson scheme.
		 * @return A vector of gamma coefficients.
		 */
		std::vector<double> get_gamma() const;

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