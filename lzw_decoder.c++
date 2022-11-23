#include <map>
#include <iostream>
#include <list>

using namespace std;

string decoder(list<int> message);

int main(){
    list<int> messageToEncode = {97,98,256,256};
    cout<<decoder(messageToEncode)<<endl;
}

string getString(char c){
    string s(1,c);
    return s;
}

string decoder(list<int> message){

    map<int,string> dictionary;
    int size = 256;

    for(int i=0; i<256; i++){
        dictionary.insert(pair<int,string>(i,getString(char(i)) ) );
    }

    string chars = getString(char(message.front()) );
    message.pop_front();
    string result = chars;

    list<int> :: iterator iter;
    for(iter = message.begin(); iter != message.end(); iter++){
        string entry = (dictionary.count(*iter))?
            dictionary.at(*iter) : chars + chars[0];
        result += entry;
        dictionary.insert(pair<int,string>(size++,chars+entry[0]) );
        chars = entry;
    }

    return result;
}