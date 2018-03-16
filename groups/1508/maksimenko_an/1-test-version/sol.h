#include <string>

void MergeSorting(int l, int r, double* &x, int &count) {
	if (r == l)
		return;
	if (r - l == 1) {
		if (x[r] < x[l])
			std::swap(x[r], x[l]);
		return;
	}
	int m = (r + l) / 2;
	MergeSorting(l, m, x, count);
	MergeSorting(m + 1, r, x, count);
	double* buf;
	buf = new double[count];
	int xl = l;
	int xr = m + 1;
	int cur = 0;
	while (r - l + 1 != cur) {
		if (xl > m)
			buf[cur++] = x[xr++];
		else if (xr > r)
			buf[cur++] = x[xl++];
		else if (x[xl] > x[xr])
			buf[cur++] = x[xr++];
		else buf[cur++] = x[xl++];

	}
	for (int i = 0; i < cur; i++)
		x[i + l] = buf[i];
	delete[] buf;
}