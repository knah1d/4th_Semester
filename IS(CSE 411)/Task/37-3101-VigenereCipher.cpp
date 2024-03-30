#include <bits/stdc++.h>

using namespace std;

string encrypt(const string& str, string& key) {
    int i = 0;
    string result = "";
    int length = key.size();
    for (char ch : str) {
        if (isalpha(ch)) {
            char base1 = isupper(ch) ? 'A' : 'a';
            char base2 = isupper(key[i % length]) ? 'A' : 'a';
            result += static_cast<char>((ch - base1 + key[i % length] - base2) % 26 + base1);
            i++;
        }
        else {
            result += ch;
        }
    }

    return result;
}

string decrypt(const string& message, string& key) {

    int i = 0;
    string result = "";
    int length = key.size();
    for (char ch : message) {
        if (isalpha(ch)) {
            char base1 = isupper(ch) ? 'A' : 'a';
            char base2 = isupper(key[i % length]) ? 'A' : 'a';
            int val = key[i % length] - base2;
            result += static_cast<char>((ch - base1 + 26 - val) % 26 + base1);
            i++;
        }
        else {
            result += ch;
        }
    }

    return result;
}

int main() {
    string message;
    string key;
    int choice;

    while (true) {
        cout << "1. Encrypt\n2. Decrypt\n0. Exit\nEnter your choice: ";
        cin >> choice;

        if (choice == 0) {
            cout<<"Exiting..."<<endl;
            break;
        }

        string result;
        switch (choice) {
            case 1:
                cout << "Enter the Plaintext: ";
                cin.ignore();
                getline(cin, message);
                cout << "Enter the key value: ";
                cin >> key;
                result = encrypt(message, key);
                cout << "Ciphertext: " << result <<"\n"<<endl;
                break;

            case 2:
                cout << "Enter the Ciphertext: ";
                cin.ignore();
                getline(cin, message);
                cout << "Enter the key value: ";
                cin >> key;
                result = decrypt(message, key);
                cout << "Plaintext: " << result <<"\n"<<endl;
                break;

            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
