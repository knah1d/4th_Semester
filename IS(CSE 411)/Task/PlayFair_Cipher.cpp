#include <bits/stdc++.h>
#define SIZE 5
using namespace std;

string newkey[5][5];
string unique_key(const string& key) {
    unordered_set<char>seenChars;
    string ukey;
    for(char ch : key) {
        if(seenChars.insert(ch).second)
            ukey += ch;

    }
    //cout<<ukey<<endl;
    return ukey;
}

void matrix(string& ukey) {

    unordered_set<char>seenChars;
    bool nbol = true;
    bool flag = true;

    int i, j, k = 0, vi, vj;
    for(i = 0; i<5 && nbol; i++) {
        for(j = 0; j<5; j++) {
           if(k<ukey.length()) {
                newkey[i][j] = toupper(ukey[k]);
                seenChars.insert(ukey[k]);
                vi = i;
                vj = j;
           }
           else {
                nbol = false;
                break;
           }
           k++;
        }
    }
    if(vj==4) {
        vi++;
        vj = 0;
    } else vj++;
    string alpha = "";
    //cout<<vi<<vj<<endl;
    for(char m = 'A'; m<='Z'; m++) {
        if(m != 'J' && seenChars.insert(m).second)
            alpha += m;
    }
    //cout<<alpha<<endl;
    int l = 0;
    for(i = vi; i<5; i++) {
        for(j = vj; j<5; j++) {

            newkey[i][j] = alpha[l];
            l++;
            //cout<<i<<j<<endl;
        }
        vj = 0;
    }
    for(int i = 0; i<5; i++) {
        for(int j = 0; j<5; j++) {
            cout<<newkey[i][j]<<" ";
        }
        cout<<endl;
    }
}

void pm(string& message) {
    int j = message.size();
    for (size_t i = 0; i < j; ++i) {
        char ch = toupper(message[i]);
        message[i] = ch;
        if (i + 1 < j && ch == toupper(message[i + 1])) {
        message[i+1] = 'X';
        i++;
        }
    }
    if(j%2) message+='X';
}

void findPositions(char ch, size_t& pos) {
    if (ch == 'J') {
        findPositions('I', pos);
    } else {
        for(int i = 0; i<5; i++) {
//            pos = newkey[i].find(ch);
        }
    }
}


int main() {
    string message;
    string key, ukey, newkey;
    int choice;
    bool flag = true;

    while (flag) {
        cout << "1. Encrypt\n2. Decrypt\n0. Exit\nEnter your choice: ";
        cin >> choice;

        string result;
        switch (choice) {
            case 1:
                cout << "Enter the Plaintext: ";
                cin.ignore();
                getline(cin, message);
                cout << "Enter the key value: ";
                cin >> key;
                pm(message);
                cout<<message<<endl;
                ukey = unique_key(key);
                //cout<<ukey<<endl;
                //newkey = matrix(ukey);
                matrix(ukey);
                //result = encrypt(message);
                cout << "Ciphertext: " << result <<"\n"<<endl;
                break;

            case 2:
                cout << "Enter the Ciphertext: ";
                cin.ignore();
                getline(cin, message);
                cout << "Enter the key value: ";
                cin >> key;
//                result = decrypt(message, key);
                cout << "Plaintext: " << result <<"\n"<<endl;
                break;

            case 0:
                flag = false;
                cout<<"Exiting..."<<endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
