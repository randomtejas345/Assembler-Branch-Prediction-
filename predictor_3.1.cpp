#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

int flag = 1;
int is_branch = 0;
int is_pos = 0;
int total = 0;
int always_taken = 0;
int always_not_taken = 0;
int hit_1 = 0;
int miss_1 = 0;
int hit_2 = 0;
int miss_2 = 0;


map<string, pair<int, vector<int>>> BTB;

void single_bit(string pc, string temp_word, int Taken) {
    if (BTB[pc].second.back() != Taken) {
        miss_1++;
    } else {
        hit_1++;
    }
}

void double_bit(string pc, string temp_word, int Taken) {
    int size = BTB[pc].second.size();
    int last = BTB[pc].second[size - 1];
    if (size > 1) {
        int second_last = BTB[pc].second[size - 2];
        if ((last == Taken && second_last == Taken) || (last != Taken && second_last == Taken)) {
            hit_2++;
        } else {
            miss_2++;
        }
    } else {
        if (BTB[pc].second.back() != Taken) {
            hit_2++;
        } else {
            miss_2++;
        }
    }
}
int count=0;
int main() {
    printf("1> wikison_test_Lab\n");
    printf("2> sqrt_test_Lab\n");
    printf("3> Recursion_test_Lab\n");
    printf("4> recursion_test_Lab\n");
    printf("5> qsort_test_Lab\n");
    printf("6> Fact_test_Lab_test_Lab\n");
    printf("7> Bubbel_test_Lab\n");
    printf("8> Sample_test_Lab\n");
    int num_files = 8; // Number of files to scan
    vector<string> filenames; // Vector to store filenames
    for (int i = 1; i <= num_files; ++i) {
        filenames.push_back("code" + to_string(i) + ".asm"); // Add filenames to vector
    }

    // Prompt user to select a file
    cout << "Enter the number of the file you want to scan (1-" << num_files << "): ";
    int file_number;
    cin >> file_number;

    if (file_number < 1 || file_number > num_files) {
        cout << "Invalid file number. Exiting..." << endl;
        return 1;
    }

    string filename = filenames[file_number - 1]; // Get selected filename

    string text;
    ifstream Myfile(filename);
    if (!Myfile.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return 1;
    }

    while (getline(Myfile, text)) {
        if (!text.empty()) {
            stringstream ss(text);
            string temp_word;
            string pc;
            vector<int> history;
            while (getline(ss, temp_word, ' ')) {
                if (temp_word.substr(0, 2) == "0x" && flag == 1) {
                    flag = 1 - flag;
                    pc = temp_word;
                }
                if (temp_word == "pc") {
                    is_branch = 1;
                }
                if (temp_word.find('+') != string::npos) {
                    is_pos = 1;
                }
            }
            int label;
            int Taken;

            if (is_branch) {
                label = stoi(temp_word);
                total++;
                if (label == 4 && is_pos == 1) {
                    Taken = 0;
                    always_not_taken++;
                } else {
                    Taken = 1;
                    always_taken++;
                }

                if (BTB.find(pc) != BTB.end()) {
                    single_bit(pc, temp_word, Taken);
                    double_bit(pc, temp_word, Taken);
                } else {
                    history.push_back(Taken);
                    BTB[pc] = {label, history};
                }

                BTB[pc].second.push_back(Taken);
            }

            flag = 1;
            is_branch = 0;
        }
    }

    float accuracy_always_taken = always_taken * 100.0 / total;
    float accuracy_always_not_taken = always_not_taken * 100.0 / total;
    float accuracy1 = hit_1 * 100.0 / (hit_1 + miss_1);
    float accuracy2 = hit_2 * 100.0 / (hit_2 + miss_2);

    cout << "Accuracy (Always Taken): " << accuracy_always_taken << " %" << endl;
    cout << "Accuracy (Always Not Taken): " << accuracy_always_not_taken << " %" << endl;
    cout << "Accuracy (Single Bit Predictor): " << accuracy1 << " %" << endl;
    cout << "Accuracy (Two Bit Predictor): " << accuracy2 << " %" << endl;

    return 0;
}
