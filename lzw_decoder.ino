const int compressorSize = 100;

const int BUFFER_SIZE = compressorSize;
char buf[BUFFER_SIZE];

int receiver[compressorSize];
//int resultIndex = 0;//serves to keep track of which index to add results
int receiverCounter = 0;//counter used to keep track of received symbols

int indexToAdd = 0;//int code representing the symbol to be added to result, or just the index of a symbol found in the dictio
    
String dictionary[compressorSize];
int dictioIndex = 0;//serves to keep track of which dictio index to add custom symbol entries

void setup(){
  pinMode(2,OUTPUT);
  
  Serial.begin(115200);
  //Serial.println("insira a mensagem");
}

void loop(){
    
  	if(Serial.available()>0){
  	if(digitalRead(2)==HIGH){
    	receiver[receiverCounter] = Serial.read() + 1000;

    }else{
    	receiver[receiverCounter] = Serial.read();
    }
    //Serial.println(receiver[receiverCounter]);
    receiverCounter++;
    delay(100);
    }
    
    String chars = "";
    chars[0] = (char) receiver[0];
    String result = chars;

    for(int i = 0; i <= receiverCounter; i++){

      String entry = "";

        if(receiver[i]<=255){

          //here we are sure that its about a 1 byte char, that means, a symbol that belongs to ASCII8
          entry = (char) receiver[i];

        }else if(receiver[i]>255){

          //we cant say for sure that a 2+ bytes symbol is present on lzw custom dictio, so we must test it ONLY IN THE CUSTOM SYMBOL ARRAY
          
          if( (receiver[i]-1000) <=dictioIndex){

              for(int j = 0; j<dictioIndex; j++){
                if((receiver[i]-1000)==j){
                  entry = dictionary[j];
                  break;
                }
              }

          }else{
            entry = chars + chars[0];
          }
        }

        result += entry;
        dictionary[dictioIndex] = chars+entry[0];
        dictioIndex++;
        chars = entry;
    }

    Serial.println(result);
 
}
 

    
    




