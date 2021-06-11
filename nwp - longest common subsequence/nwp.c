#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> kSubMax[20];
vector<int> a;
vector<int> b;
int areZeros[20];

int maximalNoZero(int x, int y)
{
    if (x == 0 || y == 0)
    {
        return 0;
    }
    else
    {
        return max(x, y);
    }
}

int minimalNoZero(int x, int y)
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


void createFirstTab()
{
    if (a[0] == b[0])
    {
        kSubMax[0][0][0] = a[0];
    }
    for (unsigned int i = 1; i < a.size(); i++)
    {
        kSubMax[0][0][i] = minimalNoZero((a[i] == b[0]) * a[i], kSubMax[0][0][i - 1]);
    }
    for (unsigned int j = 1; j < b.size(); j++)
    {
        kSubMax[0][j][0] = minimalNoZero((b[j] == a[0]) * a[0], kSubMax[0][j - 1][0]);
    }
    for (unsigned int i = 1; i < a.size(); i++)
    {
        for (unsigned int j = 1; j < b.size(); j++)
        {
            kSubMax[0][j][i] = minimalNoZero(minimalNoZero(kSubMax[0][j - 1][i], kSubMax[0][j][i - 1]), a[i] * (a[i] == b[j]));
            if (areZeros[0] && kSubMax[0][j][i] > 0)
            {
                areZeros[0] = false;
            }
        }
    }
}

void insertElement(int tabNum, int c, int i, int j)
{
    int lowestNeighbour = minimalNoZero(kSubMax[tabNum][j - 1][i], kSubMax[tabNum][j][i - 1]);
    int maxPrev = maximalNoZero(kSubMax[tabNum - 1][j - 1][i - 1], (a[i] == b[j] && a[i] >= kSubMax[tabNum - 1][j - 1][i - 1] - c) * a[i]);
    kSubMax[tabNum][j][i] = minimalNoZero(lowestNeighbour, maxPrev);
}

void createTabNumTab(int tabNum, int c)
{
    for (unsigned int i = 1; i < a.size(); i++)
    {
        for (unsigned int j = 1; j < b.size(); j++)
        {
            insertElement(tabNum, c, i, j);
            if (areZeros[tabNum] && kSubMax[tabNum][j][i] > 0)
            {
                areZeros[tabNum] = false;
            }
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    int m;
    int c;
    int k = 20;
    int j = 0;
    cin >> n;
    cin >> m;
    cin >> c;
    if (n == 0 || m == 0)
    {
        cout << 0 << endl;
    }
    else
    {
        a.resize(n);
        b.resize(m);
        vector<int> temp(n);
        for (int i = 0; i < 20; i++)
        {
            kSubMax[i].resize(m);
            for (int l = 0; l < m; l++)
            {
                kSubMax[i][l] = temp;
            }
            areZeros[i] = true;
        }
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        for (int i = 0; i < m; i++)
        {
            cin >> b[i];
        }

        createFirstTab();

        while (j < k && !areZeros[j])
        {
            j++;
            if (j < k)
            {
                createTabNumTab(j, c);
            }
        }

        cout << j << '\n';
    }

    return 0;
}