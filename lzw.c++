#include <map>
#include <list>


//remember that this line removes the need for using std:: before evr single
//std function written here
using namespace std;

int main(){
    map<int, char> dictionary;
    int size = 256;
    
    for(int i=0; i<256; i++){
        dictionary.insert(pair<int, char>(i, char(i)));
    }
}

int *encoder(string message){

    list<int> result;
    for(auto c: message){
        
    }
    return 0;
}



