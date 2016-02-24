// 0-1 package problem
// Created by lg on 16-2-24.

#include <iostream>
#include <string.h>

using namespace std;

const int TSize = 3;
const int PSize = 5;
const int Min = 0x80000000;
int f[TSize + 1][PSize + 1];
int package_collocate(int *value, int *cost, int t_size, int p_size);

int main() {
    int values[4] = {0, 7, 5, 8};
    int costs[4] = {0, 2, 3, 4};
    int result = package_collocate(values, costs, TSize, PSize);
    int i = TSize, j = PSize;
    if (result > 0) {
        cout << endl;
        cout << "the opt value: " << result << endl;
        while (i--) {
            if (f[i][j] == (f[i - 1][j - costs[i]] + values[i])) {
                cout << i << ":" << "w = " << costs[i] << ", c = " << costs[i] << endl;
                j -= costs[i];
            }
        }
    } else {
        cout << "cannot find the opt value" << endl;
    }
    return 0;
}

//params: t_size: 物品数量； p_size: 背包大小
int package_collocate(int *value, int *cost, int t_size, int p_size) {
    memset(f, 0, sizeof(f));
    /*for (int i = 0; i <= t_size; i++)
        for (int j = 1; j <= p_size; j++) //此步骤是解决是否恰好满足背包容量，f[i][0]都为零
            f[i][j] = Min;         //若“恰好”满足背包容量，即正好装满背包，则加上此步骤，若不需要“恰好”，则初始化为0
    */
    for (int i = 1; i <= t_size; ++i) {
        for (int j = cost[i]; j <= p_size; ++j) {
            //状态转移方程：f[i][j]表示前i个values[]值放入背包时不同容量具有的价值，f[i][j]取前一个状态的最大值
            int i_not_push = f[i - 1][j];  //第i个物品不放入背包内的f[i][j]
            int i_push = f[i - 1][j - cost[i]] + value[i];  //第i个物品放入背包内f[i][j]
            f[i][j] = (i_not_push > i_push) ? i_not_push : i_push; //取量这种的较大值
            cout << "f[" << i << "][" << j << "] = " << f[i][j] << endl;
        }
    }
    return f[t_size][p_size];
}