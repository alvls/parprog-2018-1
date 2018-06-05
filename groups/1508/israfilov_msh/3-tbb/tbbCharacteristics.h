#include <vector>
#include "tbb\tbb.h"

using std::vector;
using std::make_pair;
using std::pair;

using namespace tbb;

typedef vector<pair<double, double> > vecP;

typedef vector<pair<double, double> > vecP;

class tbbCharacteristics {
	const vecP p;
	double res, tmp, leftBorder, m;
public:
	explicit tbbCharacteristics(vecP& _vec, double _res, double _leftBorder, double _m) : 
		p(_vec), res(_res), leftBorder(_leftBorder), m(_m) {}

	tbbCharacteristics(const tbbCharacteristics& c, split) : p(c.p), res(c.res), leftBorder(c.leftBorder) {}

	void operator() (const blocked_range<int>& r) {
		int begin = r.begin(), end = r.end();

		for (int i = begin; i != end; i++) {			
			tmp = m * (p[i + 1].first - p[i].first) + (pow(p[i + 1].second - p[i].second, 2) /
				(m * (p[i + 1].first - p[i].first))) - 2 * (p[i + 1].second + p[i].second);
			if (res < tmp)
			{
				res = tmp;
				leftBorder = i;
			}
		}
	}

	void join(const tbbCharacteristics& tbbChar) {
		if (res < tbbChar.res) {
			res = tbbChar.res;
			leftBorder = tbbChar.leftBorder;
		}
	}

	double getRes() {
		return res;
	}

	double getBorder() {
		return leftBorder;
	}
};