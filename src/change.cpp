#include "change.h"

namespace ensiie
{
	void Change::t_transformation()
	{
		double sigma_sqr = sigma_ * sigma_;
		double dtau;
		std::vector<double> tau(M_ + 1);

		for (int i = 0; i <= M_; i++)
		{
			tau[M_ - i] = 0.5 * sigma_sqr * (T_ - t_[i]);
		}

		dtau = 0.5* sigma_sqr * dt_;

		t_changed_ = tau;
		dt_changed_ = dtau;
	}

	void Change::l_transformation()
	{
		double dx;
		std::vector<double> x(N_ + 1, 0);

		for (int i = 1; i <= N_; i++)
		{
			x[i] = std::log(l_[i] / K_);
		}

		///This aproximation is done as it's not possible to transform S=0
		x[0] = x[1]; 

		dx = (x[N_] - x[1]) / (N_ - 1);

		l_changed_ = x;
		ds_changed_ = dx;
	}

	std::vector<double> Change::price_transformation(const std::vector<double>& v)
	{
		std::vector<double> correct_price(N_ + 1);
		std::vector<double> coefficient(N_ + 1);

		///It's taken into account just the change of variable for the final time
		for (int i = 0; i <= N_; i++)
		{
			coefficient[i] = K_ * exp(-0.5 * (f_ - 1) * l_changed_[i]);
			correct_price[i] = v[i] * coefficient[i];
		}

		return correct_price;
	};

	Change::Change(double T, double r, double sigma, double K, double L, double M, double N) : Data(T, r, sigma, K, L, M, N)
	{
		t_transformation();
		l_transformation();
		f_ = 2 * r / (sigma * sigma);
	}

	Change::Change(const Data& d) : Data(d)
	{
		t_transformation();
		l_transformation();
		f_ = 2 * r_ / (sigma_ * sigma_);
	}

	std::vector<double> Change::get_t_changed() const
	{
		return t_changed_;
	}

	std::vector<double> Change::get_l_changed() const
	{
		return l_changed_;
	}

	double Change::get_dt_changed() const
	{
		return dt_changed_;
	}

	double Change::get_ds_changed() const
	{
		return ds_changed_;
	}

	double Change::get_f() const
	{
		return f_;
	}
}