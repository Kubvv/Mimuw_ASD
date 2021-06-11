#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> field;
vector<vector<int>> oneDimMax;
vector<vector<int>> oneDimMin;
vector<vector<int>> twoDimMax;
vector<vector<int>> twoDimMin;

int minIgnoreZero(int x, int y)
{
    if (x == 0 || y == 0)
    {
        return max(x, y);
    }
    else
    {
        return min(x, y);
    }
}

void createOneDimTrees(int arrNum, int index, int left, int right)
{
    if (left == right)
    {
        oneDimMax[arrNum][index] = field[arrNum][left];
        oneDimMin[arrNum][index] = field[arrNum][left];
    }
    else
    {
        int mid = (left + right) / 2;
        createOneDimTrees(arrNum, 2 * index + 1, left, mid);
        createOneDimTrees(arrNum, 2 * index + 2, mid + 1, right);
        oneDimMax[arrNum][index] = max(oneDimMax[arrNum][2 * index + 1], oneDimMax[arrNum][2 * index + 2]);
        oneDimMin[arrNum][index] = minIgnoreZero(oneDimMin[arrNum][2 * index + 1], oneDimMin[arrNum][2 * index + 2]);
    }
}

void createTwoDimTrees(int index, int left, int right, int size) {
    if (left == right)
    {
        twoDimMax[index] = oneDimMax[left];
        twoDimMin[index] = oneDimMin[left];
    }
    else 
    {
        twoDimMax[index].resize(size);
        twoDimMin[index].resize(size);
        int mid = (left + right) / 2;

        createTwoDimTrees(2 * index + 1, left, mid, size);
        createTwoDimTrees(2 * index + 2, mid + 1, right, size);

        for (size_t i = 0; i < twoDimMax[index].size(); i++)
        {
            twoDimMax[index][i] = max(twoDimMax[2 * index + 1][i], twoDimMax[2 * index + 2][i]);
            twoDimMin[index][i] = minIgnoreZero(twoDimMin[2 * index + 1][i], twoDimMin[2 * index + 2][i]);
        }
    }
}

pair<int, int> findMinMaxOneDim(int tabNum, int index, int left, int right, int y1, int y2)
{
    if (y1 > right || y2 < left)
    {
        return make_pair(0, 0);
    }
    if (left >= y1 && right <= y2)
    {
        return make_pair(twoDimMax[tabNum][index], twoDimMin[tabNum][index]);
    }

    int mid = (left + right) / 2;
    pair<int, int> leftAnswer = findMinMaxOneDim(tabNum, 2 * index + 1, left, mid, y1, y2);
    pair<int, int> rightAnswer = findMinMaxOneDim(tabNum, 2 * index + 2, mid + 1, right, y1, y2);

    pair<int, int> result;
    result.first = max(leftAnswer.first, rightAnswer.first);
    result.second = minIgnoreZero(leftAnswer.second, rightAnswer.second);

    return result;
}

pair<int, int> findMinMaxDif(int index, int left, int right, int x1, int y1, int x2, int y2, int rIndexOfSubTree)
{
    if (left > x2 || right < x1)
    {
        return make_pair(0, 0);
    }
    if (left >= x1 && right <= x2)
    {
        return findMinMaxOneDim(index, 0, 0, rIndexOfSubTree, y1, y2);
    }

    int mid = (left + right) / 2;
    pair<int, int> leftAnswer = findMinMaxDif(2 * index + 1, left, mid, x1, y1, x2, y2, rIndexOfSubTree);
    pair<int, int> rightAnswer = findMinMaxDif(2 * index + 2, mid + 1, right, x1, y1, x2, y2, rIndexOfSubTree);

    pair<int, int> result;
    result.first = max(leftAnswer.first, rightAnswer.first);
    result.second = minIgnoreZero(leftAnswer.second, rightAnswer.second);

    return result;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, k;
    cin >> n >> m >> k;

    field.resize(n);
    oneDimMax.resize(n);
    oneDimMin.resize(n);

    int mSize = 1;
    int nSize = 1;

    while (m > mSize) mSize *= 2;
    mSize = mSize * 2 - 1;

    while (n > nSize) nSize *= 2;
    nSize = nSize * 2 - 1;

    twoDimMax.resize(nSize);
    twoDimMin.resize(nSize);

    for (int i = 0; i < n; i++)
    {
        field[i].resize(m);
        oneDimMax[i].resize(mSize);
        oneDimMin[i].resize(mSize);

        for (int j = 0; j < m; j++)
        {
            cin >> field[i][j];
        }

        createOneDimTrees(i, 0, 0, m - 1);
    }

    createTwoDimTrees(0, 0, n-1, mSize);
    
    pair<int, int> result;
    int x1, x2, y1, y2;

    for (int i = 0; i < k; i++)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        result = findMinMaxDif(0, 0, n - 1, x1, y1, x2, y2, m - 1);
        cout << result.first - result.second << '\n';
    }

    return 0;
}