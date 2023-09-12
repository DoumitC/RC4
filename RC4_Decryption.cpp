// RC4_Decryption.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cctype> // for isspace and ispunct
#include <sstream>
#include <iomanip>

using namespace std;

string FileInput(string filename) {
    ifstream FileIn;
    FileIn.open(filename);
    string TextIn = "";

    string temp = "";
    while (getline(FileIn, temp)) {
        unsigned long num = stoul(temp, nullptr, 16);
        TextIn += num; // append each line to the string
    }
    FileIn.close();
    return TextIn;
}

int* KSA(string key) {
    static int S[256];
    int j = 0;

    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
    int temp;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key.size()]) % 256;

        // Swap values
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
    //cout << size(S) << endl;

    return S;
}

string PRGA(string Text, int* S) {
    string OUTPUT = "";
    int i = 0;
    int j = 0;
    int temp;
    for (int z = 0; z < Text.size(); z++) {
        OUTPUT += " ";
    }
    for (int z = 0; z < 3072; z++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        // Swap values
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        char t = (S[(S[i] + S[j]) % 256]);
    }
    for (int z = 0; z < Text.size(); z++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        // Swap values
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        char t = (S[(S[i] + S[j]) % 256]);


        OUTPUT[z] = t ^ Text[z];

    }

    return OUTPUT;
}

void FileOutput(string filename, string Text) {
    ofstream FileOut;
    FileOut.open(filename);
    FileOut << Text;
    FileOut.close();
}




int main()
{
    string Key = "Key";
    cout << "Enter key: ";
    cin >> Key;
    int* S = KSA(Key);
    string EncryptedText = FileInput("encrypt2.txt");
    cout << EncryptedText << endl << endl;
    string DecryptedText = PRGA(EncryptedText, S);
    cout << DecryptedText << endl;
    FileOutput("Decrypted.txt", DecryptedText);
}

