#include <bits/stdc++.h>
using namespace std;

inline bool eq(long long a, long long b) { return a == b; }
inline bool lt(long long a, long long b) { return a < b; }
inline bool le(long long a, long long b) { return a <= b; }
inline int sgn(long long x) { return eq(x, 0) ? 0 : (x < 0 ? -1 : 1); }

struct point {
	long long x,y;
	point(long long _x = 0, long long _y = 0) : x(_x), y(_y) {}
	point operator+(const point& p) const { return point(x+p.x, y+p.y); }
	point operator-(const point& p) const { return point(x-p.x, y-p.y); }
	point operator*(long long t) { return point(x*t, y*t); }
	// point operator/(long long t) { return point(x/t, y/t); }
	long long operator*(const point& p) const { return x*p.x + y*p.y; }
	long long operator%(const point& p) const { return x*p.y - y*p.x; }
	// long long squared_norm() { return *this * *this; }
	// bool operator==(const point& p) const { return eq(x, p.x) && eq(y, p.y); }
	bool operator<(const point& p) const { return eq(y, p.y) ? x < p.x : y < p.y; }
};

// ostream& operator<<(ostream& os, point p) {
// 	return os << "(" << p.x << ", " << p.y << ")";
// }

//a-b-c: -1 clockwise, 0 colliner, 1 counterclockwise
int ccw(point a, point b, point c) { return sgn((b-a) % (c-b)); }

bool cmp(pair<point, int> a, pair<point, int> b) {
	int dir = sgn(a.first % b.first);
	if (dir == 0)
		return a.second < b.second;
	return dir > 0;
}

//sorting point in points from 1st quadrant to 4th quadrant
void sortCircular(vector<pair<point, int>> &points) {
	vector<pair<point, int>> upper, lower;
	for(auto& e : points) {
		if(point() < e.first)
			upper.push_back(e);
		else
			lower.push_back(e);
	}
	sort(upper.begin(), upper.end(), cmp);
	sort(lower.begin(), lower.end(), cmp);
	for(int i = 0; i < (int) upper.size(); i++)
		points[i] = upper[i];
	for(int i = 0; i < (int) lower.size(); i++)
		points[i + upper.size()] = lower[i];
}

long long C(long long n, long long k){
	if(n < k || n < 0 || k < 0)
		return 0;
	long long res = 1;
	for(int i = n; i >= n-k+1; i--)
		res *= i;
	for(int i = 1; i <= k; i++)
		res /= i;
	return res;
}

int n;
vector<point> pt;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n;
	for(int i = 1; i <= n; i++) {
		long long x, y;
		cin >> x >> y;
		pt.emplace_back(x, y);
	}

	for(int i = 0; i < n; i++) {
		vector<pair<point, int>> pts;
		for(int j = 0; j < n; j++) {
			if (i == j)
				continue;
			pts.emplace_back(pt[j] - pt[i], j);
		}
		sortCircular(pts);
		int l = 0, r = 1, cur = 1;
		long long count = 0;
		for(l = 0; l < n; l++){
			cur--;
			while(sgn(pt[r] % pt[l]) < 0) {
				r++;
				cur++;
			}
			count += C(cur, 3); // count side
			// count += C(cur, 2) * (n - 2 - cur); // diagonal
		}
	}	

	long long ans = (5 * C(n, 5));
	ans -= count;
	cout << ans << "\n";

	return 0;
}