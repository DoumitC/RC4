// RC4_Encryption.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cctype> // for isspace and ispunct
#include <sstream>
#include <iomanip>

using namespace std;

//Reads File to string and returns that string
string FileInput(string filename) {
    ifstream FileIn;
    FileIn.open(filename);
    string TextIn = "";

    string temp = "";
    while (getline(FileIn, temp)) {
        TextIn += temp; // append each line to the string
    }
    FileIn.close();
    return TextIn;
}

void FileOutput(string filename, string Text) {
    ofstream FileOut;
    FileOut.open(filename);
    FileOut <<Text;
    FileOut.close();
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

string PRGA(string Text, int *S) {
    string OUTPUT = "";
    int i = 0;
    int j = 0;
    int temp;
    for (int z = 0; z < Text.size(); z++) {
        OUTPUT += " ";
    }
    for(int z = 0; z< Text.size(); z++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        // Swap values
        temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        unsigned char c = (S[(S[i] + S[j]) % 256]);
        OUTPUT[z] = c ^ Text[z];

    }

    return OUTPUT;
}

string intToHex(int num) {
    stringstream stream;
    stream << hex << setw(2) << setfill('0') << num;
    return stream.str();
}

int main()
{

    int* S = KSA("Key");
    
    string EncryptedTxt = PRGA(FileInput("rc4input.txt"), S);
    
    cout << FileInput("rc4input.txt") << endl << endl << endl;
    
    cout << endl << endl << endl;
    cout  <<EncryptedTxt << endl << endl << endl;
    
    string HexTxt = "";
    for (int i = 0; i < EncryptedTxt.size(); i++) {
        HexTxt += intToHex(EncryptedTxt[i]);
        HexTxt += "\n";
        //cout << HexTxt << endl;
    }

    cout << endl << endl << endl;
    //cout << HexTxt << endl << endl << endl;
    FileOutput("Encrypted.txt", HexTxt);

    
}

