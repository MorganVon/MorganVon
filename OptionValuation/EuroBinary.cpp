#include <string>
#include <map>
#include <set>
#include <vector>
#include <deque>
#include <math.h>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <functional>
using namespace std;

int combi(int n, int k) {
  if (n == k || k == 0) { return 1; }
  else { return combi(n - 1, k - 1) + combi(n - 1, k); }
}

double EuroBinary(double spot, double strike, double up, double r, int n,
  string cp) {
  double dn = 1 / up;
  double p = (1 + r - dn) / (up - dn);
  double q = (up - 1 - r) / (up - dn);

  double ans = 0;
  double Opt_Int = 0;
  for (int i = 0; i < n + 1; i++) {
    double Stk_Int = spot * pow(up, i) * pow(dn, n - i);
    if (cp == "c") { Opt_Int = max(Stk_Int - strike, 0.0); }
    else if (cp == "p") { Opt_Int = max(strike - Stk_Int, 0.0); }
    else { return 0.0; }
    // Opt_Int = max(strike - Stk_Int, 0.0);
    ans += Opt_Int * pow(p, i) * pow(q, n - i) * combi(n, i);
  }
  ans /= pow(1 + r, n);
  return ans;
}

int main() {
  double spot = 4.0;
  double strike = 5.0;
  double up = 2.0;
  double r = 0.25;
  int n = 3;
  string cp = "p";

  double a = EuroBinary(spot, strike, up, r, n, cp);
  cout << a;

  return 0;
}
