#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

// 🔹 розбиття на речення
vector<string> splitSentences(const string& text) {
    vector<string> sentences;
    string current;

    for (char c : text) {
        current += c;
        if (c == '.' || c == '!' || c == '?') {
            sentences.push_back(current);
            current.clear();
        }
    }
    return sentences;
}

// 🔹 отримання слів (без isalpha — працює з укр)
vector<string> getWords(const string& sentence) {
    vector<string> words;
    string word;

    for (char c : sentence) {
        if (c != ' ' && c != '.' && c != ',' && c != '!' && c != '?' && c != ':' && c != ';') {
            word += c;
        }
        else {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        }
    }

    if (!word.empty())
        words.push_back(word);

    return words;
}

// 🔹 перевірка спільних слів
bool hasCommonWords(const string& s1, const string& s2) {
    vector<string> w1 = getWords(s1);
    vector<string> w2 = getWords(s2);

    set<string> set1(w1.begin(), w1.end());

    int count = 0;

    for (auto& w : w2) {
        if (set1.count(w)) {
            count++;
            if (count >= 2)
                return true;
        }
    }
    return false;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin.is_open()) {
        cout << "ERROR: input.txt not found\n";
        return 1;
    }

    string text, line;

    while (getline(fin, line)) {
        text += line + " ";
    }

    vector<string> sentences = splitSentences(text);

    vector<string> result;

    for (int i = 0; i < sentences.size(); i++) {
        for (int j = i + 1; j < sentences.size(); j++) {
            if (hasCommonWords(sentences[i], sentences[j])) {
                result.push_back(sentences[i]);
                result.push_back(sentences[j]);
            }
        }
    }

    if (result.empty()) {
        if (!sentences.empty())
            fout << sentences[0];
    }
    else {
        for (auto& s : result)
            fout << s << endl;
    }

    fin.close();
    fout.close();

    cout << "Done. Check output.txt\n";

    return 0;
}