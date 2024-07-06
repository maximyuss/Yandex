// https://contest.yandex.ru/contest/59539/problems/H/
// The first version, a complex and confusing but correct solution

#include <iostream>
#include <vector>
using namespace std;

bool taskH(int l, int x1, int v1, int x2, int v2, double& res) {
    vector <double> ress;
    double tmp;
    // case 0 x1=x2
    if (x1 == x2) {
        res = 0;
        return true;
    }
    if (v1 == 0 && v2 == 0)
        return false;
    // Normalization values
    if (v1 > 0 && v2 > 0) {
        
    }
    if (v1 < 0 && v2 < 0) {
        v1 = -v1;
        v2 = -v2;
        x1 = l - x1;
        x2 = l - x2;
    }
    // case 1 One point
    if ((v2 - v1) != 0) {
        tmp = (double)(x1 - x2) / (v2 - v1);
        if (tmp > 0) ress.push_back(tmp);
    }

    // case 2 Symmetrical points
    if ((v2 + v1) != 0) {
        tmp = (double)(l - x1 - x2) / (v1 + v2);
        if (tmp > 0) ress.push_back(tmp);
    }

    if (ress.empty()) {
        // case 3 Points after several circles
        double 
            diffX = x1 - x2,
            diffV = v2 - v1;
        int multiL = l;
        if (diffV != 0) {
            for (size_t i = 0; i < 10000; i++) {
                tmp = (double)(multiL + diffX) / diffV;
                if (tmp > 0) {
                    ress.push_back(tmp);
                    break;
                }
                tmp = (double)(multiL - diffX) / (-diffV);
                if (tmp > 0) {
                    ress.push_back(tmp);
                    break;
                }
                multiL += l;
            }
        }
        // case 4 Points after several circles
        diffX = x1 + x2;
        diffV = v2 + v1;
        if (diffV != 0) {
            for (size_t i = 0; i < 10000; i++) {
                tmp = (double)(multiL - diffX) / diffV;
                if (tmp > 0) {
                    ress.push_back(tmp);
                    break;
                }
                multiL += l;
            }
        }
    }
    if (!ress.empty()) {
        tmp = ress[0];
        for (auto e : ress)
            if (e < tmp)
                tmp = e;
        res = tmp;
        return true;
    }
    return false;
}
int main() {
    int l, x1, v1, x2, v2;
    double res = 0;
    cin >> l >> x1 >> v1 >> x2 >> v2;

    if (taskH(l, x1, v1, x2, v2, res)) {
        cout << "YES" << endl;
        printf("%.10lf", res);
    } else
        cout << "NO" << endl;
}
/*
6 3 1 1 1 - 1
12 8 10 5 20 - 0.3
5 0 0 1 2 - 2
10 7 -3 1 4 - 0.8571428571
94 76 0 76 0 - 0
938712409 11003268 0 278188417 0
72 20 -38121735 66 288888467 - 0.0000000795
615143346 79387687 -80123649 306422480 -80123649 - 2.4075923389
948744004 861724643 848773505 584154450 730556189 - 0.2859497398
977345779 636176199 0 165786447 815181433 - 0.2151461330
82 42 -354891707 42 -354891707 - 0
956390104 549514100 7 315097830 -7
*/
