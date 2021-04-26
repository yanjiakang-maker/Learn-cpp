#include <iostream>
#include <vector>

using namespace std;

vector<int> spiralOrder(vector<vector<int>>& matrix) {
    //��ȡm��n��ֵ
    int m = matrix.size();
    int n = matrix[0].size();
    vector<int> result;

    //�����������ұ߽�
    int up(0), down(m - 1), left(0), right(n - 1);
    //��ʼ����
    while (1) {
        //��������
        for (int i = left; i <= right; i++) {
            result.push_back(matrix[up][i]);
        }
        if (++up > down)
            break;
        //���ϵ���
        for (int i = up; i <= down; i++) {
            result.push_back(matrix[i][right]);
        }
        if (--right < left)
            break;
        //��������
        for (int i = right; i >= left; i--) {
            result.push_back(matrix[down][i]);
        }
        if (--down >= up)
            break;
        //��������
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