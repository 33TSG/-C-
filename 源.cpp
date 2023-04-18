#include <iostream>
#include <iomanip>
using namespace std;

const int MAXN = 1 << 10; // 棋盘最大大小为2^10*2^10

int board[MAXN][MAXN]; // 记录棋盘状态
int tile = 0; // 骨牌编号

void chessboard(int tr, int tc, int dr, int dc, int size) {
    if (size == 1) return;
    int t = ++tile;
    int s = size / 2;

    if (dr < tr + s and dc < tc + s)  // Case 1
        chessboard(tr, tc, dr, dc, s);
    else {
        board[tr + s - 1][tc + s - 1] = t;
        chessboard(tr, tc, tr + s - 1, tc + s - 1, s);
    }

    if (dr < tr + s and dc >= tc + s) // Case 2
        chessboard(tr, tc + s, dr, dc, s);
    else {
        board[tr + s - 1][tc + s] = t;
        chessboard(tr, tc + s, tr + s - 1, tc + s, s);
    }

    if (dr >= tr + s and dc < tc + s) // Case 3
        chessboard(tr + s, tc, dr, dc, s);
    else {
        board[tr + s][tc + s - 1] = t;
        chessboard(tr + s, tc, tr + s, tc + s - 1, s);
    }

    if (dr >= tr + s and dc >= tc + s) // Case 4
        chessboard(tr + s, tc + s, dr, dc, s);
    else {
        board[tr + s][tc + s] = t;
        chessboard(tr + s, tc + s, tr + s, tc + s, s);
    }

}

int main() {
    int k, x, y;
    cout << "输入k的值：";
    cin >> k;
    cout << "输入特殊方格的坐标x, y坐标值：";
    cin >> x >> y;                                      // 输入棋盘大小以及空缺位置
    board[x][y] = -1;                                   // 标记空缺位置为-1
    chessboard(0, 0, x, y, 1 << k);  // 计算所有格子的骨牌编号
    cout << "要求的棋盘如下：" << endl;
    for (int i = (1 << k) - 1; i >= 0; --i) {
        for (int j = 0; j < (1 << k); ++j) {
            if (board[i][j] == -1) {
                cout << left << setw(3) << " ";                    // 输出空缺位置
            } else {
                cout << left << setw(3) << board[i][j];
            }
        }
        cout << endl ;
    }
    return 0;
}
