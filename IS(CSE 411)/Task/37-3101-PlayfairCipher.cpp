#include <bits/stdc++.h>
using namespace std;

const int SIZE = 5;

string generateKeyTable(const string& key) {
    string keyWithoutDuplicates;
    string newkey;


    for (char ch : key) {
        if (isalpha(ch) && keyWithoutDuplicates.find(ch) == string::npos) {
            keyWithoutDuplicates += toupper(ch);
        }
    }
    cout<<keyWithoutDuplicates<<endl;
    for (char ch : keyWithoutDuplicates) {
        newkey += ch;
    }


    for (char ch = 'A'; ch <= 'Z'; ++ch) {
        if (ch != 'J' && keyWithoutDuplicates.find(ch) == string::npos) {
            newkey += ch;
        }
    }

    return newkey;
}

void findPositions(const string& newkey, char ch, size_t& pos) {
    if (ch == 'J') {
        findPositions(newkey, 'I', pos);
    } else {
        pos = newkey.find(ch);
    }
}

string encryptDigraph(const string& newkey, char a, char b) {
    size_t pos1, pos2;
    findPositions(newkey, a, pos1);
    findPositions(newkey, b, pos2);

    size_t row1 = pos1 / SIZE;
    size_t col1 = pos1 % SIZE;
    size_t row2 = pos2 / SIZE;
    size_t col2 = pos2 % SIZE;


    if (row1 == row2) {
        return string(1, newkey[row1 * SIZE + (col1 + 1) % SIZE]) + newkey[row2 * SIZE + (col2 + 1) % SIZE];
    }

    else if (col1 == col2) {
        return string(1, newkey[((row1 + 1) % SIZE) * SIZE + col1]) + newkey[((row2 + 1) % SIZE) * SIZE + col2];
    }

    else {
        return string(1, newkey[row1 * SIZE + col2]) + newkey[row2 * SIZE + col1];
    }
}

string playfairEncrypt(const string& message, const string& key) {
    string newkey = generateKeyTable(key);


    string processedMessage;
    for (char ch : message) {
        if (isalpha(ch)) {
            ch = toupper(ch);
            if (ch == 'J') {
                ch = 'I';
            }
            processedMessage += ch;
        }
    }


    string encryptedMessage;
    for (size_t i = 0; i < processedMessage.length(); i += 2) {
        char a = processedMessage[i];
        char b = (i + 1 < processedMessage.length()) ? processedMessage[i + 1] : 'X';
        encryptedMessage += encryptDigraph(newkey, a, b);
    }

    return encryptedMessage;
}

int main() {

    string key, message;
    cout<<"Enter Plaintext: ";
    getline(cin, message);
    cout<<"Enter Keyword: ";
    cin>>key;

    string encryptedMessage = playfairEncrypt(message, key);

    cout << "Encrypted Message: " << encryptedMessage << endl;

    return 0;
}
