# https://contest.yandex.ru/contest/59539/problems/D/
# 5-1D

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Shifts table, 0: Rook, 1 : Bishop
const vector<vector<int>>
    di{ {0, 0, 1, -1}, {1, 1, -1, -1} },
    dj{ {1, -1, 0, 0}, {1, -1, 1, -1} };

void input(vector<string>& board) {
    string line;
    board.emplace_back(string(10, '#'));
    while (getline(cin, line))
        board.emplace_back('#' + line.substr(0, 8) + '#');
    board.emplace_back(string(10, '#'));
}

int main() {
    vector<string> board;
    input(board);
    size_t res = 64;
    for (size_t i = 1; i < 9; i++)
        for (size_t j = 1; j < 9; j++)
            if (board[i][j] == 'R' or board[i][j] == 'B') {
                res--;
                for (size_t shift = 0; shift < 4; shift++) {
                    char figure = (board[i][j] == 'R' ? 0 : 1);
                    size_t tmpI = i + di[figure][shift], tmpJ = j + dj[figure][shift];
                    while (board[tmpI][tmpJ] == '*' or board[tmpI][tmpJ] == '.') {
                        if (board[tmpI][tmpJ] == '*') {
                            board[tmpI][tmpJ] = '.';
                            res--;
                        }
                        tmpI += di[figure][shift];
                        tmpJ += dj[figure][shift];
                    }
                }
            }
    cout << res;
}
