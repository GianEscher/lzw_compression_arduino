#include <map>
#include <list>


//remember that this line removes the need for using std:: before evr single
//std function written here
using namespace std;

int main(){


}

string getString(char c){
    string s(1,c);
    return s;
}
    

list<int> encoder(string message){

    map<string, int> dictionary;
    int size = 256;
    
    for(int i=0; i<256; i++){
        dictionary.insert(pair<string, int>(getString(char(i)),i));
    }

    string foundChars = "";
    static list<int> result;
    for(auto c: message){

        string charsToAdd = foundChars + c;

        if(dictionary.count(charsToAdd) == 1){
            foundChars = charsToAdd;
        }else{
            result.push_back(dictionary[foundChars]);
            dictionary.insert(pair<string,int>(charsToAdd,size++));
            foundChars = c;
        }
    }

    if (foundChars.compare("") != 0){
        result.push_back(dictionary[foundChars]);
    }

    return result;
}



