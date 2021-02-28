// Karel Renaldi / 13519180 / K-04 / Tucil Stima 2
#include <bits/stdc++.h>
using namespace std;

// Global variabel
int semester = 0;

void split(string const &str, const char *delim, vector<string> &out)
{
    char *token = strtok(const_cast<char *>(str.c_str()), delim);
    while (token != nullptr)
    {
        out.push_back(string(token));
        token = strtok(nullptr, delim);
    }
}

string convert_roman_numeral(int &number)
{
    int standard_numeral[] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
    string roman_numeral[] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};

    int remainder = number, curr_pointer = 12; // roman_numeral (arr size - 1)
    string res = "";

    while (remainder > 0)
    {
        int div_result = remainder / standard_numeral[curr_pointer];
        while (div_result--)
            res += roman_numeral[curr_pointer];
        remainder = remainder % standard_numeral[curr_pointer];
        curr_pointer--;
    }

    return res;
}

void create_graph(string filename, unordered_map<string, int> &vertices_degree_in, unordered_map<string, unordered_set<string>> &graph)
{
    string text;
    ifstream file(filename);

    while (getline(file, text))
    {
        vector<string> parse_text;
        unordered_set<string> vertices;

        text.pop_back();
        split(text, ", ", parse_text);

        graph.insert({parse_text[0], vertices});

        for (int i = 1; i < parse_text.size(); i++)
            graph[parse_text[0]].insert(parse_text[i]);
    }

    for (auto adj : graph)
        vertices_degree_in[adj.first] = adj.second.size();
}

void topological_sort(unordered_map<string, int> &vertices_degree_in, unordered_map<string, unordered_set<string>> &graph)
{
    vector<string> erase_key;

    semester++;
    cout << "Semester " << convert_roman_numeral(semester) << " : ";
    for (auto vertices = vertices_degree_in.begin(); vertices != vertices_degree_in.end(); vertices++)
    {
        if (vertices->second == 0)
        {
            erase_key.push_back(vertices->first);
            cout << vertices->first << ", ";
        }
    }
    cout << "\b\b"
         << " " << endl;

    // Decrease
    for (string key : erase_key)
    {
        vertices_degree_in.erase(key);
        for (auto adj : graph)
            if (adj.first != key && adj.second.count(key) != 0)
                vertices_degree_in[adj.first]--;
    }

    // Recursive
    if (vertices_degree_in.size() != 0)
        topological_sort(vertices_degree_in, graph);
}

int main()
{
    unordered_map<string, int> vertices_degree_in;
    unordered_map<string, unordered_set<string>> graph;
    string filename, path = "../test/";

    cout << "============== WELCOME TO SUPREMO PLAN APPLICATION ==============" << endl
         << endl;

    cout << "Masukkan nama file: ";
    cin >> filename;
    cout << endl;

    // Parsing text to graph
    create_graph(path + filename, vertices_degree_in, graph);

    clock_t start = clock();
    double duration;

    // Implement topological sort algorithm
    topological_sort(vertices_degree_in, graph);

    duration = (clock() - start) / (double)CLOCKS_PER_SEC;

    cout << endl
         << "Time : " << duration << "s";

    return 0;
}