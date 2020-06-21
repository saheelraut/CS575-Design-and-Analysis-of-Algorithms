#include <iostream>
#include <string>
#include <vector>
using namespace std;
int max(int a, int b)
{
    return a > b ? a : b;
}

int max(int a, int b, int c)
{
    return (max(a, b) > c) ? max(a, b) : c;
}

void longest_common_subsequence(vector<vector<int> > &lcs, string s1, string s2)
{
    int m = s1.length();
    int n = s2.length();

    for (int j = 0; j <= n; ++j)
    {
        lcs[0][j] = 0;
    }

    for (int i = 0; i <= m; ++i)
    {
        lcs[i][0] = 0;
    }

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            lcs[i + 1][j + 1] = lcs[i][j];
            if (s1[i] == s2[j])
            {
                lcs[i + 1][j + 1]++;
            }
            else
            {
                lcs[i + 1][j + 1] = max(lcs[i][j + 1], lcs[i + 1][j]);
            }
        }
    }
    cout << "Length of LCS: " << lcs[m][n] << endl;

    int i = m;
    int j = n;
    int index = lcs[m][n];
    string seq(lcs[m][n], ' ');
    while (i > 0 && j > 0)
    {
        if (s1[i - 1] == s2[j - 1])
        {
            seq[index - 1] = s1[i - 1];
            --index;
            --i;
            --j;
        }
        else if (lcs[i - 1][j] > lcs[i][j - 1])
        {
            --i;
        }
        else
        {
            --j;
        }
    }
    cout << "LCS : " << seq << endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3) //condition for input code
    {
        cout << "Wrong Input Count \n";
        cout << "Usage : ./lcs <string1> <string2>\n";
        return -1;
    }
    string string1, string2;
    string1 = argv[1];
    string2 = argv[2];
    if ((string1.length() < 100) && (string2.length() < 100)) // String length condition
    {
        vector<vector<int> > lcs(string1.length() + 1, vector<int>(string2.length() + 1));

        longest_common_subsequence(lcs, string1, string2);
        return 0;
    }
    else
    {
        cout << "String length more than 100";
        return -2;
    }
}