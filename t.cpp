#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main()
{
    vector<int> arr = { 3, 4, 9, 100};
    int target = 99;

    vector<int>::iterator result = find(arr.begin(), arr.end(), target); //查找target
    int index = distance(arr.begin(), result);

    cout << "target索引为:" << index << endl;

    system("pause");
}
