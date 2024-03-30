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

void AESEncryption(unsigned char *plainText, unsigned char *expandedKey, unsigned char *cipher)
{
    unsigned char *state = new unsigned char[16];

    // Initial add round
    for (int i = 0; i < 16; ++i)
    {
        state[i] = plainText[i] ^ expandedKey[i];
    }

    // 9 rounds begin
    for (int rounds = 1; rounds < 10; rounds++)
    {
        byteSubShiftRow(state);
        mixColumns(state);
        int counter = 0;
        int loc = rounds * 16;
        while (counter < 16)
        {
            state[counter] ^= expandedKey[loc];
            loc++;
            counter++;
        }
    }

    // 10th round
    byteSubShiftRow(state);
    for (int i = 0; i < 16; i++)
    {
        cipher[i] = state[i] ^ expandedKey[i + 160];
    }
    delete[] state;
}

int main()
{

    ifstream inputFile("plaintext.txt");

    char plainText[200];
    inputFile.getline(plainText, sizeof(plainText));
    // cin.getline(plainText, sizeof(plainText));
    cout << "Plaintext: " << plainText << endl << endl;
    inputFile.close();

    unsigned char Key[16] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x99, 0x89, 0xcf, 0xab, 0x12};
    unsigned char *expandedKey = keyExpansion(Key);

    int originalLen = strlen((const char *)plainText);

    int paddedMessageLen = originalLen;

    if ((paddedMessageLen % 16) != 0)
    {
        paddedMessageLen = (paddedMessageLen / 16 + 1) * 16;
    }

    unsigned char *paddedMessage = new unsigned char[paddedMessageLen];
    for (int i = 0; i < paddedMessageLen; i++)
    {
        if (i >= originalLen)
        {
            paddedMessage[i] = 0;
        }
        else
        {
            paddedMessage[i] = plainText[i];
        }
    }

    unsigned char *cipher = new unsigned char[paddedMessageLen];

    for (int i = 0; i < paddedMessageLen; i += 16)
    {
        AESEncryption(paddedMessage + i, expandedKey, cipher + i);
    }

    cout << "Encrypted Plaintext: ";
    output(cipher, paddedMessageLen);
    cout << endl << endl;

    ofstream outfile("ciphertext.txt");
    outfile << cipher;
    outfile.close();

    delete[] expandedKey;
    delete[] cipher;
    delete[] paddedMessage;
}