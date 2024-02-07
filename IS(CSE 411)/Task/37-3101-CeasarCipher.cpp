#include <bits/stdc++.h>

using namespace std;

string encrypt(const string& str, int key) {
    string result = "";

    for (char ch : str) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            //cout<<static_cast<int>((ch - base + key) % 26)<<endl;
            result += static_cast<char>((ch - base + key) % 26 + base);
        } else {
            result += ch;
        }
    }

    return result;
}

string decrypt(const string& message, int key) {

    return encrypt(message, 26 - key);
}

int main() {
    string message;
    int key;
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
