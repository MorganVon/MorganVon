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

void GetTheNextValue(double &ans, double max_spot, double spot, double up, int n, int step) {
    max_spot = max(max_spot, spot);
    if (step == n) {

        ans += max(max_spot - spot, 0.0);
    } else {
        GetTheNextValue(ans, max_spot, spot * up, up, n, step + 1);
        GetTheNextValue(ans, max_spot, spot / up, up, n, step + 1);
    }
}

double LookBackOption(double spot, double up, double r, int n){
    double ans = 0;
    GetTheNextValue(ans, spot, spot, up, n, 0);
    ans /= (pow(2, n) * pow(1 + r, n));
    return ans;
}

int main() {
    double spot = 4.0;
    double up = 2.0;
    double r = 0.25;
    int n = 3;

    double a = LookBackOption(spot, up, r, n);
    cout << a;

    return 0;
}
