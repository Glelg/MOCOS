#include "main.h"

complex<double> i(0, 1);
// степень двух
int power(int n)
{
	int x = 1;
	if (n > 0)
	{
		x = power(n - 1);
		x = x * 2;
	}
	return x;
}

int ind_inv(int x, int n)
{
	int tmp = 0;
	for (int i = n; i > 0; i--)
	{
		tmp += x % 2 * power(i - 1);
		x /= 2;
	}
	return tmp;
}

vector<complex<double>> BPF(vector<complex<double>> X)
{
	int N = X.size();
	int n = log(double(N)) / log(2.0);
	vector<complex<double>> tmp_X;
	for (int k = 0; k < X.size(); k++)
	{
		tmp_X.push_back(X[ind_inv(k, n)]);
	}

	X = tmp_X;

	for (int k = 1; k <= n; k++)
	{
		for (int j = 0; j < power(n - k); j++)
		{
			for (int l = 0; l < power(k - 1); l++)
			{
				complex<double> w;
				complex<double> tmp;

				w = exp(-2 * M_PI * l/ power(k) * i);
				
				tmp = X[j * power(k) + l] + w * X[j * power(k) + l + power(k - 1)];
				X[power(k - 1) + j * power(k) + l] = X[j * power(k) + l] - w * X[j * power(k) + l + power(k - 1)];
				X[j*power(k)+l] = tmp;
			}
		}
	}

	for (int k = 0; k < N; k++)
	{
		X[k] /= sqrt(double(N));
	}
	return X;
}

vector<complex<double>> OBPF(vector<complex<double>> X)
{
	int N = X.size();
	int n = log(double(N)) / log(2.0);
	vector<complex<double>> tmp_X;
	for (int k = 0; k < X.size(); k++)
	{
		tmp_X.push_back(X[ind_inv(k, n)]);
	}

	X = tmp_X;

	for (int k = 1; k <= n; k++)
	{
		for (int j = 0; j < power(n - k); j++)
		{
			for (int l = 0; l < power(k - 1); l++)
			{
				complex<double> w;
				complex<double> tmp;

				w = exp(2 * M_PI * l / power(k) * i);

				tmp = X[j * power(k) + l] + w * X[j * power(k) + l + power(k - 1)];
				X[power(k - 1) + j * power(k) + l] = X[j * power(k) + l] - w * X[j * power(k) + l + power(k - 1)];
				X[j * power(k) + l] = tmp;
			}
		}
	}

	for (int k = 0; k < N; k++)
	{
		X[k] /= sqrt(double(N));
	}
	return X;
}