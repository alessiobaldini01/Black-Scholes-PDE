#include "complete.h"

namespace ensiie
{
	void Complete::coefficients_computation()
	{
		std::vector<double> alpha(N_ + 1), beta(N_ + 1), gamma(N_ + 1);

		double sigma_sqr = sigma_ * sigma_;

		for (int i = 0; i <= N_; i++)
		{
			double i_sqr = i * i;

			alpha[i] = (dt_ / 4) * ((sigma_sqr * i_sqr) - (r_ * i));
		
			beta[i] = (-dt_ / 2) * ((sigma_sqr * i_sqr) + r_);
		
			gamma[i] = (dt_ / 4) * ((sigma_sqr * i_sqr) + (r_ * i));
		}

		alpha_ = alpha;
		beta_ = beta;
		gamma_ = gamma;
	}

	void Complete::lu_factorization()
	{
		std::vector<double> low(N_ + 1, 0), up(N_ + 1, 0);

		for (int i = 0; i <= N_; i++)
		{
			if (i == 0)
			{
				up[i] = 1 - beta_[i];
				low[i] = 0;
			}
			else
			{
				low[i] = -(alpha_[i]) / up[i - 1];
				up[i] = (1 - beta_[i]) + low[i] * (gamma_[i-1]);
			}
		}

		low_ = low;
		up_ = up;
	}

	Complete::Complete(double T, double r, double sigma, double K, double L, double M, double N) : Data(T, r, sigma, K, L, M, N)
	{
		coefficients_computation();
		lu_factorization();
	}

	Complete::Complete(const Data& d) : Data(d)
	{
		coefficients_computation();
		lu_factorization();
	}

	std::vector<double> Complete::get_alpha() const
	{
		return alpha_;
	}

	std::vector<double> Complete::get_beta() const
	{
		return beta_;
	}

	std::vector<double> Complete::get_gamma() const
	{
		return gamma_;
	}

	std::vector<double> Complete::get_low() const
	{
		return low_;
	}

	std::vector<double> Complete::get_up() const
	{
		return up_;
	}
}