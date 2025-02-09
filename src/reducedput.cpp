#include "reducedput.h"

namespace ensiie
{
	ReducedPut::ReducedPut(double T, double r, double sigma, double K, double L, double M, double N) : Reduced(T, r, sigma, K, L, M, N) {};
	ReducedPut::ReducedPut(const Data& d) : Reduced(d) {};

	void ReducedPut::pricing()
	{
		/// In the methods the matrix prices has the form prices[raws j],[columns i]
		std::vector<std::vector<double>> prices(N_ + 1, std::vector<double>(M_ + 1));
		std::vector<double> b(N_ + 1);
		std::vector<double> y(N_ + 1);

		/// Terminal condition for t=T
		for (int j = 0; j <= N_; j++)
		{
			prices[j][0] = std::max(0.0, exp(0.5 * (f_ - 1) * l_changed_[j]) - exp(0.5 * (f_ + 1) * l_changed_[j]));
		}

		/// Iterative solution of the matrix prices by column
		for (int i = 1; i <= M_; i++) 
		{
			/// Solution to the problem Ly=b, comuting b and then y
			for (int j = 0; j <= N_; j++)
			{
				if (j == 0)
				{
					b[j] = prices[j][i - 1];
					y[j] = b[j];
				}
				else
				{
					b[j] = prices[j][i - 1];
					y[j] = b[j] - low_[j] * y[j - 1];
				}
			}

			/// Solution to the problem Ux=y
			for (int j = N_; j >=0; j--)
			{
				if (j == N_)
				{
					prices[j][i] = y[j] / up_[j];
				}
				else
				{
					prices[j][i] = (y[j] + theta_ * prices[j + 1][i]) / up_[j];
				}
			}
		}

		/// Extraction of the column of the matrix corresponding to P_tilda(0, s)
		std::vector<double> price(N_ + 1);
		std::vector<double> correct_price(N_ + 1);
		for (int i = 0; i <= N_; i++)
		{
			price[i] = prices[i][0];
		}

		///Changing of the price vector with real prices
		correct_price = price_transformation(price);

		this->price_ = correct_price;
	}

	std::vector<double> ReducedPut::get_price() const
	{
		return price_;
	}
}