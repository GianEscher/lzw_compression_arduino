int mystr[10];
int receiverCounter = 0;

void setup()
{
  pinMode(2,INPUT);
  Serial.begin(115200);
}

void loop()
{
  if(Serial.available()>0){
  	if(digitalRead(2)==HIGH){
    	mystr[receiverCounter] = Serial.read() + 1000;

    }else{
    	mystr[receiverCounter] = Serial.read();
    }
    Serial.println(mystr[receiverCounter]);
    receiverCounter++;
    delay(100);
  }
}