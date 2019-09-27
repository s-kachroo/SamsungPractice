#include <iostream>
using namespace std;

int lengthOfString(char *str){
    int len = 0, i = 0;
    while(str[i] != '\0'){
        len++;
        i++;
    }
    return len;
}

void mergeAplha(char *str){
    int lenString = lengthOfString(str);
    int hash[26] = {0};

    for(int i=0; i<lenString; i++){
        char letter = str[i];
        i++;

        int temp = 0;
        while(i<lenString && str[i] >= '0' && str[i] <= '9'){
            temp = (temp * 10) + (str[i]-'0');
            i++;
        }
        i--;
        
        hash[letter - 'a'] += temp; 
    }

    for(int i=0; i<26; i++){
        if(hash[i] != 0){
            char temp = i + 'a';
            cout << temp << " " << hash[i] << " ";
        }
    }

}

int main() {
    char s[100];
    cin >> s;
    mergeAplha(s);
    return 0;
}
