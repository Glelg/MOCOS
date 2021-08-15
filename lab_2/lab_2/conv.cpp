#include "main.h"

vector<complex<double>> Dconv(vector<complex<double>> X, vector<complex<double>> Y)
{
	int N = X.size() + Y.size() - 1;
	X.resize(N);
	Y.resize(N);
	vector<complex<double>> U;
	for (int n = 0; n < N; n++)
	{
		complex<double> sum(0, 0);
		for (int k = 0; k <= n; k++)
		{
			sum += X[k] * Y[n - k];
		}
		U.push_back(sum);
	}
	return U;
}

vector<complex<double>> Bconv(vector<complex<double>> X, vector<complex<double>> Y)
{
	int N = power(int(log(double(2 * max(X.size(), Y.size()))) / log(2.0)));
	X.resize(N);
	Y.resize(N);
	vector<complex<double>> U;
	X = BPF(X);
	Y = BPF(Y);
	for (int n = 0; n < N; n++)
	{
		U.push_back(X[n] * Y[n] * sqrt(double(N)));
	}
	U = OBPF(U);
	return U;
}