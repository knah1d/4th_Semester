#include <bits/stdc++.h>
#include <cstring>
#include "aes.h"
using namespace std;

void output(unsigned char *data, int size)
{
    for (int index = 0; index < size; index++)
    {
        cout << hex << (int)data[index];
        cout << " ";
    }
    cout << endl;
}

void AESDecryption(unsigned char *cipher, unsigned char *expandedKey, unsigned char *plainText)
{
    unsigned char *state = new unsigned char[16];

    for (int i = 0; i < 16; ++i)
        state[i] = cipher[i] ^ expandedKey[160 + i];

    for (int rounds = 9; rounds > 0; rounds--)
    {
        inverseByteSubShiftRow(state);
        int counter = 0;
        int loc = 16 * rounds;
        while (counter < 16)
        {
            state[counter] ^= expandedKey[loc];
            loc++;
            counter++;
        }
        inverseMixedColumn(state);
    }

    inverseByteSubShiftRow(state);
    for (int i = 0; i < 16; i++)
        plainText[i] = state[i] ^ expandedKey[i];

    delete[] state;
}

int main()
{
    string msgstr;
    ifstream infile;
    infile.open("ciphertext.txt", ios::in | ios::binary);
    getline(infile, msgstr); 
    infile.close();

    char *msg = new char[msgstr.size() + 1];

    strcpy(msg, msgstr.c_str());

    int n = strlen((const char *)msg);

    unsigned char Key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x99, 0x89, 0xcf, 0xab, 0x12};
    unsigned char *expandedKey = keyExpansion(Key);
    unsigned char *cipher = new unsigned char[n];
    
    for (int i = 0; i < n; i++)
    {
        cipher[i] = (unsigned char)msg[i];
    }
    int messageLen = strlen((const char *)cipher);

    delete[] msg;

    unsigned char *decrypted = new unsigned char[messageLen];

    for (int i = 0; i < messageLen; i += 16)
    {
        AESDecryption(cipher + i, expandedKey, decrypted + i);
    }

    cout << "\nDecrypted Ciphertext: ";
    output(decrypted, messageLen);
    cout << endl;

    cout << "Decrypted Ciphertext: ";
    cout << decrypted << endl << endl;

    delete[] decrypted;
    delete[] expandedKey;
    delete[] cipher;
}
