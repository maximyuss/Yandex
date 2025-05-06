// https://contest.yandex.ru/contest/74967/problems/F/
#include <iostream>
#include <vector>
#include <cstdint> 
using namespace std;

const int MAX_N = 1000;
static uint64_t XY[MAX_N][(MAX_N + 63) / 64],
    YZ[MAX_N][(MAX_N + 63) / 64],
    XZ[MAX_N][(MAX_N + 63) / 64];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    int cntBlock = (n + 63) / 64;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < cntBlock; ++j) {
            XY[i][j] = YZ[i][j] = XZ[i][j] = 0;
        }
    }
    for (int i = 0; i < k; ++i) {
        int x, y, z;
        cin >> x >> y >> z;
        --x; --y; --z;

        int xBlock = y / 64, yBlock = z / 64, zBlock = z / 64;
        int xBit = y % 64, yBit = z % 64, zBit = z % 64;

        XY[x][xBlock] |= 1ULL << xBit;
        YZ[y][yBlock] |= 1ULL << yBit;
        XZ[x][zBlock] |= 1ULL << zBit;
    }

    vector<uint64_t> fullMask(cntBlock);
    for (int i = 0; i < cntBlock; ++i) {
        if (i == cntBlock - 1 && n % 64 != 0)
            fullMask[i] = (1ULL << (n % 64)) - 1;
        else
            fullMask[i] = ~0ULL;
    }

    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < n; ++y) {
            int xBlock = y / 64;
            int xBit = y % 64;
            if (XY[x][xBlock] & (1ULL << xBit)) 
                continue;

            for (int j = 0; j < cntBlock; ++j) {
                uint64_t combined = YZ[y][j] | XZ[x][j];
                if (combined == fullMask[j]) continue;

                uint64_t freeMask = ~combined & fullMask[j];
                for (int bit = 0; bit < 64; ++bit) {
                    if (freeMask & (1ULL << bit)) {
                        int z = j * 64 + bit;
                        if (z < n) {
                            cout << "NO\n" << ++x << " " << ++y << " " << ++z << "\n";
                            return 0;
                        }
                    }
                }
            }
        }
    }
    cout << "YES\n";
    return 0;
}
