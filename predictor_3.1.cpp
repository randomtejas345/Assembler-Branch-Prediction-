#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <map>

using namespace std;

int tester = 0;
long flag = 1;
long flag_2 = 1;
long is_branch = 0;
long is_pos = 0;
long total = 0;
long always_taken = 0;
long always_not_taken = 0;
long hit_1 = 0;
long miss_1 = 0;
long hit_2 = 0;
long miss_2 = 0;

map<string, pair<long, vector<long>>> BTBonebit;
map<string, pair<long, vector<long>>> BTBtwobit;

string last_instruction = "";

unsigned int hexToDecimal(const string &hexString) {
    unsigned int decimalValue;
    stringstream ss;
    ss << hex << hexString;
    ss >> decimalValue;
    return decimalValue;
}

void single_bit(string pc, string temp_word, long Taken) {
    if (BTBonebit[pc].second.back() != Taken) {
        miss_1++;
    } else {
        hit_1++;
    }
    BTBonebit[pc].second.push_back(Taken);
}

void double_bit(string pc, string temp_word, long Taken) {
    long size = BTBtwobit[pc].second.size();
    long last = BTBtwobit[pc].second[size - 1];
    long second_last = BTBtwobit[pc].second[size - 2];
    if ((last == 1 && second_last == 1 && Taken == 1) || (second_last == 0 && last == 0 && Taken == 0)) {
        hit_2++;
    } else if ((last == 1 && second_last == 0 && Taken == 0) || (second_last == 1 && last == 0 && Taken == 1)) {
        hit_2++;
    } else {
        miss_2++;
    }
    BTBtwobit[pc].second.push_back(Taken);
}

long count = 0;
int main() {
      printf("1> wikison_test_Lab\n");
    printf("2> sqrt_test_Lab\n");
    printf("3> Recursion_test_Lab\n");
    printf("4> recursion_test_Lab\n");
    printf("5> qsort_test_Lab\n");
    printf("6> Fact_test_Lab_test_Lab\n");
    printf("7> Bubbel_test_Lab\n");
    printf("8> Sample_test_Lab\n");
    // Prompt user to select a file
    cout << "Enter the number of the file you want to scan (1-8): ";
    int file_number;
    cin >> file_number;

    if (file_number < 1 || file_number > 8) {
        cout << "Invalid file number. Exiting..." << endl;
        return 1;
    }

    string filename = "code" + to_string(file_number) + ".asm"; // Construct filename

    string text;
    ifstream Myfile(filename);
    if (!Myfile.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return 1;
    }

    while (getline(Myfile, text)) {
        string temp = text;
        text = last_instruction;
        if (!text.empty()) {
            stringstream ss(text);
            stringstream ss2(temp);
            string temp_word;
            string temp_word_2;
            string pc;
            string pc_present;
            vector<long> history;
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
            while (getline(ss2, temp_word_2, ' ')) {
                if (temp_word_2.substr(0, 2) == "0x" && flag_2 == 1) {
                    flag_2 = 1 - flag_2;
                    pc_present = temp_word_2;
                }
            }

            long label;
            long Taken;

            if (is_branch && temp.find("core") != string::npos) {
                label = stol(temp_word);

                uint32_t dec_last_pc = stoll(pc, nullptr, 16);
                uint32_t res;
                if (is_pos) {
                    res = dec_last_pc + label;
                } else {
                    res = dec_last_pc - label;
                }

                uint32_t dec_curr = stoll(pc_present, nullptr, 16);
                total++;
                if (dec_curr != res) {
                    Taken = 0;
                    always_not_taken++;
                } else {
                    Taken = 1;
                    always_taken++;
                }

                if (BTBonebit.find(pc) != BTBonebit.end()) {
                    single_bit(pc, temp_word, Taken);
                    double_bit(pc, temp_word, Taken);
                } else {
                    history.push_back(Taken);
                    BTBonebit[pc] = {label, history};
                    BTBtwobit[pc] = {label, history};
                    BTBonebit[pc].second.push_back(1);
                    BTBtwobit[pc].second.push_back(0);
                    BTBtwobit[pc].second.push_back(0);
                }
            }
        }

        flag = 1;
        flag_2 = 1;
        is_branch = 0;
        is_pos = 0;

        last_instruction = temp;
    }

    float accuracy_always_taken = always_taken * 100.0 / total;
    float accuracy_always_not_taken = always_not_taken * 100.0 / total;
    float accuracy1 = hit_1 * 100.0 / (hit_1 + miss_1);
    float accuracy2 = hit_2 * 100.0 / (hit_2 + miss_2);

    cout << "Accuracy(Always Taken): " << accuracy_always_taken << " %" << endl;
    cout << "Accuracy(Always Not Taken): " << accuracy_always_not_taken << " %" << endl;
    cout << "Accuracy(Single bit): " << accuracy1 << " %" << endl;
    cout << "Accuracy(Two bit): " << accuracy2 << " %" << endl;

    return 0;
}
