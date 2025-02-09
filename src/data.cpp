#include "data.h"

namespace ensiie
{

	void Data::discretize()
	{

		dt_ = T_ / M_;
		ds_ = L_ / N_;

		std::vector<double> t(M_ + 1);
		std::vector<double> l(N_ + 1);

		for (int i = 0; i <= M_; i++)
		{
			t[i] = i * dt_;
		}

		for (int i = 0; i <= N_; i++)
		{
			l[i] = i * ds_;
		}

		t_ = t;
		l_ = l;
	}

	Data::Data(double T, double r, double sigma, double K, double L, double M, double N)
	{

		// Excpetion for negative values
		if (T < 0 || r < 0 || sigma < 0 || K < 0 || L < 0 || M < 0 || N < 0)
		{
			throw std::invalid_argument("Values must be non-negative");
		}
		// Exception for null number of steps
		else if (M == 0 || N == 0 || sigma == 0 || K == 0)
		{
			throw std::invalid_argument("M, N, sigma and K must be positive");
		}
		else
		{
			T_ = T;
			r_ = r;
			sigma_ = sigma;
			K_ = K;
			L_ = L;
			M_ = M;
			N_ = N;

			discretize();
		}
	}

	double Data::get_T() const
	{
		return T_;
	};

	double Data::get_r() const 
	{
		return r_;
	}

	double Data::get_sigma() const
	{
		return sigma_;
	}

	double Data::get_K() const
	{
		return K_;
	}

	double Data::get_L() const
	{
		return L_;
	}

	double Data::get_M() const
	{
		return M_;
	}

	double Data::get_N() const
	{
		return N_;
	}

	double Data::get_dt() const
	{
		return dt_;
	}

	double Data::get_ds() const
	{
		return ds_;
	}

	std::vector<double> Data::get_t() const
	{
		return t_;
	}

	std::vector<double> Data::get_l() const
	{
		return l_;
	}
}