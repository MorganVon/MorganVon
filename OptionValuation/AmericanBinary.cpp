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

// struct AmericanPath_Dot{
//     double EU_Val, US_Val;
//     int tau, process;
// };

// void UpgradeLastValue(double &ans, double spot, double stk, double ir, double up_rate, string cp) {

// }

void UpdateUSPremium(vector<double> &Premium, vector<double> SpotList, double stk, string cp, 
    double up, double r) {
    
    if (Premium.size() > 1){
        vector<double> max_list, last_spot;
        for (int i = 0; i < Premium.size(); i++) {
            double Intri = max((cp == "c" ? 1 : -1) * (SpotList[i] - stk), 0.0);
            max_list.push_back(max(Premium[i], Intri));
        }

        double dn = 1 / up;
        double p = (1 + r - dn) / (up - dn);
        double q = (up - 1 - r) / (up - dn);
        Premium.clear();
        for (int i = 0; i < max_list.size() - 1; i++) {
            Premium.push_back((max_list[i] * p + max_list[i+1] * q) / (1 + r));
            last_spot.push_back(SpotList[i] * dn);
            // cout << Premium[i] << " : " << last_spot[i] << endl;
        }
        UpdateUSPremium(Premium, last_spot, stk, cp, up, r);
    }
}

int main() {
    double ans, spot = 100, strike = 100, ir = 0.025, up = 1.25;
    string cp = "c";
    int term = 3;

    double maxSpot = spot * pow(up, term), minSpot = spot / pow(up, term);
    vector<double> FinalSpot, Intrinsic;
    for (double x = maxSpot; x >= minSpot; x /= (up * up)){
        FinalSpot.push_back(x);
        double Intri = max((cp == "c" ? 1 : -1) * (x - strike), 0.0);
        Intrinsic.push_back(Intri);
        // cout << x << " : " << Intri << endl;
    }
    UpdateUSPremium(Intrinsic, FinalSpot, strike, cp, up, ir);
    ans = Intrinsic[0];
    cout << ans << endl;

    return 0;
}