#include <string>
#include <iostream>
using namespace std;
void permute(const string & str);
void permute(const string & str, int low, int high );

void permute( const string & str ){
    size_t high = 1;
    for(size_t i = 1; i<= str.length(); i++){
        high = high * i;
    }
    permute(str, 0, static_cast<int>(high));
};

void permute(const string & str, int low, int high ){ //function should repeat str.length! times
    if(low < high){
        int length = str.length(); //length of str
        int modLow = low%length;  //mod of low, used to determine what two letters to swap
        cout << str << endl;
        low++; //increase to make sure function will end
        string newstr = str;
         //swap each character with the next char ex = abc -> acb -> cba -> etc in this pattern
        if((modLow) == ((length-1)%length)){ //swap end of string with zero, unique case
            swap(newstr[0], newstr[modLow]);
        } else { //default case
            swap(newstr[modLow], newstr[modLow+1]);
        }
        permute(newstr, low, high);
    }
};