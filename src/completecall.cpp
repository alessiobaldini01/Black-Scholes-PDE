#include "completecall.h"

namespace ensiie 
{
	CompleteCall::CompleteCall(double T, double r, double sigma, double K, double L, double M, double N) : Complete(T, r, sigma, K, L, M, N) {};
	CompleteCall::CompleteCall(const Data& d) : Complete(d) {};

	void CompleteCall::pricing()
	{
		// In the methods the matrix prices has the form prices[raws j],[columns i]
		std::vector<std::vector<double>> prices(N_ + 1, std::vector<double>(M_ + 1));
		std::vector<double> b(N_ + 1);
		std::vector<double> y(N_ + 1);
		
		// Boundary conditions for s=L
		for (int i = 0; i <= M_; i++)
		{
			prices[N_][i] = L_ - K_ * std::exp(-r_ * (T_ - t_[M_-i]));
		}
		
		// Boundary condition for t=T
		for (int j = 1; j < N_; j++)
		{
			prices[j][0] = std::max(0.0, l_[j] - K_);
		}

		// Boundary condition for s=0
		for (int i = 0; i <= M_; i++) 
		{
			prices[0][i] = 0;
		}

		// Iterative solution of the matrix prices by column
		for(int i = 1; i <= M_; i++){

			// Solution to the problem Ly=b, comuting b and then y
			for (int j = 0; j <= N_; j++)
			{
				if (j == 0)
				{
					b[j] = prices[j][i - 1] * (1 + beta_[j]) + prices[j + 1][i - 1] * gamma_[j];
					y[j] = b[j];
				}
				else if (j == N_)
				{
					b[j] = prices[j][i - 1] * (1 + beta_[j]) + prices[j - 1][i - 1] * alpha_[j];
					y[j] = b[j] - low_[j] * y[j - 1];
				}
				else
				{
					b[j] = prices[j][i - 1] * (1 + beta_[j]) + prices[j + 1][i - 1] * gamma_[j] + prices[j - 1][i - 1] * alpha_[j];
					y[j] = b[j] - low_[j] * y[j - 1];
				}
			}

			// Solution to the problem Ux=y
			for (int j = (N_ - 1); j > 0; j--) 
			{
				prices[j][i] = (y[j] + gamma_[j] * prices[j+1][i]) / up_[j];
			}
		}

		// Extraction of the column of the matrix corresponding to C(0, s)
		std::vector<double> price(N_ + 1);
		for (int i = 0; i <= N_; i++) 
		{
			price[i]=prices[i][M_];
		}

		this-> price_ = price;
	}

	std::vector<double> CompleteCall::get_price() const
	{
		return price_;
	}
}