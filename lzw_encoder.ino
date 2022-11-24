const int BUFFER_SIZE = 10;
char buf[BUFFER_SIZE];

void setup(){
  Serial.begin(9600);
  //Serial.println("insira a mensagem");
}

void loop(){
  if(Serial.available()>0){
    
  	int rlen = Serial.readBytesUntil('\n', buf, BUFFER_SIZE);
    encoder();
    Serial.println("Encoder should have been called atm...");
  }

    // prints the received data
    
    
    /*
    Serial.print("I received: ");
    for(int i = 0; i < rlen; i++)
      Serial.print(buf[i]);
  	}
  	*/
  
  	

    /*
    list <int> show = encoder(text);
    list <int> :: iterator iter;
    for(iter = show.begin(); iter != show.end(); iter++ ){
        Serial.println(*iter);
    }
    */
}

/*
string getString(char c){
    string s(1,c);
    return s;
}
 */   

void encoder(){

  //A BUFFER OF 100 BYTES ALLOWS MESSAGES OF 100 BYTES TO BE COMPRESSED
  //IF THERES NO COMPRESSION, THAT IS, IF ALL SYMBOLS IN THE MESSAGE ARE DIFFERENT, THEN THE LONGEST RESULT POSSIBLE HAS 100 BYTES
  //IN THIS CASE, EACH CONSECUTIVELY PAIR OF SYMBOLS WILL BE A NEW ENTRY TO THE CUSTOM LZW DICTIONARY
  //EXCEPT FOR THE FIRST SYMBOL READ, WE'LL HAVE A PAIR FOR EACH SYMBOL - THAT MEANS, A MAX NUMBER OF 99 LZW ENTRIES PER MESSAGE

  //IT WOULD BE NICE, THO, IF WE REUTILIZED ENTRIES FOR MORE THAN ONE BUFFER READ
  //KEEPING ENTRIES IS A GOOD IDEA, BUT IT COULD OCCUPY ALL OF OUR MEMORY IF ITS NOT DONE PROPERLY
  //HOW ABOUT 256 INDEXES? WHICH WILL START BEING REPLACED WHEN ALL OF THEM GET OCCUPIED BY A SYMBOL

  //THIS WAY, CODES WITH HIGH VARIATION RATES WILL FILL THE INDEXES QUICKLY, BUT WILL BE REPLACED AS QUICKLY THEY WERE FILLED
  //SINCE LZW USES REVERSE ENGINEERING OF THE ENCODING TO DECIPHER THE COMPRESSED MESSAGE ON THE DECODER PART, IT SHOULDNT
  //SHOW ANY PROBLEMS RELATED TO SYNCHRONIZING CODES ALONG REPETITIONS AND REPLACEMENTS

    //std::map<string, int> dictionary;
    
    //BUILDING ASCII "DICTIONARY"
    Serial.println("encoder called! rlen is: ");

    
    int result[100];
    int resultIndex = 0;//serves to keep track of which index to add results

    int indexToAdd = 0;//int code representing the symbol to be added to result, or just the index of a symbol found in the dictio
    
    String dictionary[518];
    int dictioIndex = 256;//serves to keep track of which dictio index to add custom symbol entries
    int size = 256;
    
    for(int i=0; i<256; i++){
        //dictionary.insert(pair<string, int>(getString(char(i)),i));
        dictionary[i] = (String) i;
    }
  
    //THE REMAING 256 INDEXES ARE RESERVED FOR CUSTOM LZW SYMBOLS

    String foundChars = "";
    //static list<int> result;
    for(int i = 0; i < 4; i++){

      	String charsToAdd = foundChars + buf[i];

        if(charsToAdd.length()==1){

          //here we are sure that its about a 1 byte char, that means, a symbol that belongs to ASCII8
          foundChars = charsToAdd;
          indexToAdd = (int) foundChars[0];

        }else if(charsToAdd.length()>1){

          //we cant say for sure that a 2+ bytes symbol is present on lzw custom dictio, so we must test it ONLY IN THE CUSTOM SYMBOL ARRAY
          for(int j = 256; j<518 ; j++){
            if(charsToAdd == dictionary[j]){
              foundChars = charsToAdd;
              indexToAdd = j;
              break;
            }
            if(i==517){//lets check if the searcher didnt found the charsToAdd until the last repetition -> if it doesnt, them we shall
            //add the new charsToAdd to the dictio and reset foundChars to the last symbol read

              result[resultIndex] = indexToAdd;
              dictionary[dictioIndex] = charsToAdd;
              foundChars = buf[i];

              resultIndex++;
              dictioIndex++;
            }
          }

        }
        
        /*
        if(dictionary.count(charsToAdd) == 1){
            foundChars = charsToAdd;
        }else{
            result.push_back(dictionary[foundChars]);
            dictionary.insert(pair<string,int>(charsToAdd,size++));
            foundChars = c;
        }
        */
    }

    if(foundChars.length()>0){
      result[resultIndex] = indexToAdd; //we dont need to reset resultIndex here, since it'll be declared again in the next encode() call
    }

    /*if (foundChars.compare("") != 0){
        result.push_back(dictionary[foundChars]);
    }

    return result;

    */

    for(int i: result){
      Serial.println(i);
    }
}



