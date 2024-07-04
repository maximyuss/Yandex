// https://contest.yandex.ru/contest/59539/problems/G
// This is the first, imperfect, but fast algorithm based on the Golden Ratio. 
// I would like to improve it.
#include <iostream>
#include <climits>

using namespace std;

int taskG(int x, int y, int p) {
    int step = 1,
        z = 0,
        res = INT_MAX,
        stepTry = 0,
        ty, tz;
    y -= x;
    if (y <= 0 && z <= 0) return step;
    z += p;
    while (x > 0 && z > 0) {
        ++step;
        ty = 0;
        tz = 0;
        // My attack
        if (y > 0 && (x >= 0.61803 * (y + z)) && step > stepTry) {
            // Destroy 
            ty = y;
            tz = x - y;
            int tmpX = x, tmpZ = z - tz, tmpS = step;
            tmpX -= tmpZ;
            while (tmpX > 0 && tmpZ > 0) {
                ++tmpS;
                tmpZ -= tmpX;
                tmpX -= tmpZ;
            }
            if (tmpZ <= 0) {
                if (res < INT_MAX && tmpS < res) {
                    res = tmpS;
                    break;
                }
                res = min(res, tmpS);
            }
            stepTry = step;
            --step;
            continue;
        }
        else {
            // Kill
            if (x > z) {
                tz = z;
                ty = x - z;
            }
            else
                tz = x;
            if (y > 0 && ty == 0 )
                if (res < INT_MAX)
                    break;
                else
                    return -1;
            y -= ty;
            z -= tz;
        }
        // Enemy attack
        x -= z;
        // Recrutment
        if (y > 0)
            z += p;
    }
    if (x == 0) return -1;
    return res;
}

int main() {
    int x, y, p;
    cin >> x >> y >> p;
    cout << taskG(x, y, p);
}
/*
    cout << taskG(10, 11, 15) << endl;  // 4
    cout << taskG(1, 2, 1) << endl;     //-1
    cout << taskG(1, 1, 1) << endl;     // 1
    cout << taskG(5, 8, 5) << endl;     // 4
    cout << taskG(25, 200, 10) << endl; // 13
    cout << taskG(250, 500, 225) << endl; // 7
    cout << taskG(250, 500, 230) << endl; // 8
    cout << taskG(250, 500, 249) << endl; // 101
    cout << taskG(250, 500, 187) << endl; // 4
    cout << taskG(250, 500, 234) << endl; // 10
    cout << taskG(250, 500, 218) << endl; // 6
*/
