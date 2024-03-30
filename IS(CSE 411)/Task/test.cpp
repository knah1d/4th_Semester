#include<bits/stdc++.h>

using namespace std;

string newkey[5][5];
int main() {

    unordered_set<char>seenChars;
    bool nbol = true;
    bool flag = true;
    string ukey = "ABCDEFKLM";
    int i, j, k = 0, vi, vj;
    for(i = 0; i<5 && nbol; i++) {
        for(j = 0; j<5; j++) {
           if(k<ukey.length()) {
                newkey[i][j] = ukey[k];
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
    cout<<alpha;
    int l = 0;
    for(i = vi; i<5; i++) {
        for(j = vj; j<5; j++) {

                newkey[i][j] = alpha[l];
                l++;
            }
        }

    for(int i = 0; i<5; i++) {
        for(int j=0; j<5; j++) {
            cout<<newkey[i][j];
        }
    }




}
