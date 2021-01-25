// Karel Renaldi / 13519180 / K-04 / Tucil Stima 1

#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

void getListWord(vector<string> &operands, string filename)
{
    ifstream file(filename);
    string input;

    while (file >> input)
        operands.push_back(input);

    operands.erase(operands.end() - 2);
    for (int i = 0; i < operands.size(); i++)
        if (operands[i].find('+') != string::npos)
            operands[i].pop_back();
}

void getListUniqueChars(vector<string> &words, vector<char> &uniqueChars)
{
    for (string word : words)
        for (char character : word)
            if (find(uniqueChars.begin(), uniqueChars.end(), character) == uniqueChars.end())
                uniqueChars.push_back(character);
}

void getListIdxNonZero(vector<int> &idxNotZero, vector<string> &words, vector<char> &uniqueChars)
{
    for (int i = 0; i < uniqueChars.size(); i++)
    {
        int j = 0;
        bool found = false;
        while (j < words.size() && !found)
        {
            if (words[j][0] == uniqueChars[i])
            {
                found = true;
                idxNotZero.push_back(i);
            }
            j++;
        }
    }
}

int getIndex(vector<char> &uniqueChars, char chr)
{
    auto position = find(uniqueChars.begin(), uniqueChars.end(), chr);
    if (position != uniqueChars.end())
        return position - uniqueChars.begin();
    else
        return -1;
}

bool nextPermutation(vector<int> &v)
{
    int i, j;

    i = v.size() - 1;

    // Find pivot index
    while (i > 0 && v[i - 1] >= v[i])
        i--;

    if (i == 0)
        return false;

    // find suffix element > pivot
    j = v.size() - 1;
    while (v[j] <= v[i - 1])
        j--;

    // swap element suffix > pivot with pivot
    swap(v[i - 1], v[j]);

    j = v.size() - 1;

    // reverse suffix array
    while (i < j)
    {
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
        i++;
        j--;
    }
    return true;
}

int getMaxNumberAtI(vector<int> v, int i)
{
    return 9 - (v.size() - 1) + i;
}

bool includeIdxNonZero(vector<int> &idxNotZero, vector<int> &v)
{
    int i = 0;
    bool found = false;

    while (i < idxNotZero.size() && !found)
    {
        if (v[idxNotZero[i]] == 0)
            found = true;
        i++;
    }

    return found;
}

int main()
{
    string filename;
    string path = "../test/";

    cout << "Masukkan nama file: ";
    cin >> filename;
    cout << endl;

    string fullPath = path + filename;

    bool solve = false;
    vector<string> words;
    vector<char> uniqueChars;
    vector<int> idxNotZero;

    getListWord(words, fullPath);

    time_point<system_clock> start, end;
    start = system_clock::now();

    getListUniqueChars(words, uniqueChars);
    getListIdxNonZero(idxNotZero, words, uniqueChars);

    // Initialize charnNum
    vector<int> charNum(uniqueChars.size()), wordNum(words.size());
    iota(charNum.begin(), charNum.end(), 0);

    int i = charNum.size() - 1;
    bool finish = false, solved = true;
    int test = 0;
    while (!finish)
    {
        vector<int> currentCharNum = charNum;
        do
        {
            int res = 0;
            for (int i = 0; i < words.size(); i++)
            {
                int temp = 0;
                for (int j = 0; j < words[i].size(); j++)
                {
                    int idx = getIndex(uniqueChars, words[i][j]);
                    temp += (int)(currentCharNum[idx] * pow(10.0, (float)(words[i].size() - j - 1)));
                }
                wordNum[i] = temp;
            }

            for (int i = 0; i < wordNum.size() - 1; i++)
                res += wordNum[i];

            if (res == wordNum.back())
            {
                if (!includeIdxNonZero(idxNotZero, currentCharNum))
                {
                    charNum = currentCharNum;
                    solved = true;
                    finish = true;
                }
            }
            test++;
        } while (nextPermutation(currentCharNum) && !finish);

        if (!finish)
        {
            if (charNum[i] + 1 <= getMaxNumberAtI(charNum, i))
                charNum[i]++;
            else
            {
                while (charNum[i] + 1 > getMaxNumberAtI(charNum, i) && i > 0)
                    i--;

                if (i != 0 || charNum[i] + 1 <= getMaxNumberAtI(charNum, i))
                {
                    charNum[i] += 1;
                    while (charNum[i] + 1 <= getMaxNumberAtI(charNum, i + 1) && i < charNum.size() - 1)
                    {
                        charNum[i + 1] = charNum[i] + 1;
                        i++;
                    }
                }
                else
                {
                    finish = true;
                }
            }
        }
    }

    // Output
    for (int i = 0; i < words.size(); i++)
    {
        cout << words[i] << endl;
        if (i == words.size() - 2)
            cout << "-------+" << endl;
    }
    cout << endl;

    if (solved)
    {
        for (int i = 0; i < words.size(); i++)
        {
            for (int j = 0; j < words[i].size(); j++)
            {
                int idx = getIndex(uniqueChars, words[i][j]);
                cout << charNum[idx];
            }
            cout << endl;
            if (i == words.size() - 2)
            {
                cout << "-------+" << endl;
            }
        }
    }
    else
    {
        cout << "Tidak ada solusi ditemukan" << endl;
    }

    cout << endl;

    end = system_clock::now();
    duration<double> elapsed_seconds = end - start;
    cout << "Waktu eksekusi: " << elapsed_seconds.count() << " "
         << "detik" << endl;
    cout << "Total test: " << test;
    return 0;
}