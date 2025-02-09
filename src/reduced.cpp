#include "reduced.h"

namespace ensiie
{
	Reduced::Reduced(double T, double r, double sigma, double K, double L, double M, double N) : Change(T, r, sigma, K, L, M, N) 
	{
		theta_ = dt_changed_ / (2 * ds_changed_ * ds_changed_);
		lu_factorization();
	};

	Reduced::Reduced(const Data& d) : Change(d) 
	{
		theta_ = dt_changed_ / (2 * ds_changed_ * ds_changed_);
		lu_factorization();
	};

	void Reduced::lu_factorization()
	{
		std::vector<double> low(N_ + 1, 0), up(N_ + 1, 0);

		for (int i = 0; i <= N_; i++)
		{
			if (i == 0)
			{
				up[i] = 1 + 2 * theta_;
				low[i] = 0;
			}
			else
			{
				low[i] = -theta_ / up[i - 1];
				up[i] = (1 + 2 * theta_) + low[i] * theta_;
			}
		}

		low_ = low;
		up_ = up;
	}

	double Reduced::get_theta() const
	{
		return theta_;
	}

	std::vector<double> Reduced::get_low() const
	{
		return low_;
	}

	std::vector<double> Reduced::get_up() const
	{
		return up_;
	}
}