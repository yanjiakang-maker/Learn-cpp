#include <iostream>
#include <vector>

using namespace std;

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    //获取m和n的值
    int m = matrix.size();
    int n = matrix[0].size();
    vector<int> result;

    //定义上下左右边界
    int up(0), down(m - 1), left(0), right(n - 1);
    //开始遍历
    while (1) {
        //从左向右
        for (int i = left; i <= right; i++) {
            result.push_back(matrix[up][i]);
        }
        if (++up > down)
            break;
        //从上到下
        for (int i = up; i <= down; i++) {
            result.push_back(matrix[i][right]);
        }
        if (--right < left)
            break;
        //从右往左
        for (int i = right; i >= left; i--) {
            result.push_back(matrix[down][i]);
        }
        if (--down >= up)
            break;
        //从下往上
        for (int i = down; i >= up; i--) {
            result.push_back(matrix[i][left]);
        }
        if (++left >= right)
            break;
    }
    return result;
}


void test() {
    vector<vector<int>> v = { {2, 5, 8}, {4, 0, -1} };
    vector<int> result = spiralOrder(v);
    for (auto& e : result)
        cout << e << " ";
    cout << endl;
}


int main() {
    test();

    return 0;
}