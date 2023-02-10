int led=2;
int button=4;
int stateLED = LOW;
int lastButtonState = HIGH;   
unsigned long lastTime = 0;  
bool buttonState = HIGH; 
byte tapCounter,count;
bool flag; 
bool flag1, flag2;
long double presstime, releasetime;
unsigned long currentTime;
unsigned long endTime;
unsigned long duration;
const long onDuration=100;
const long offDuration=100;
int ledState=HIGH;
long rememberTime=0;


void setup() {
  Serial.begin(9600); 
  pinMode(button, INPUT_PULLUP); 
  pinMode(led, OUTPUT); 
}

//led blinking millies
void blinkts(){
 if(ledState==HIGH){
    if((millis()-rememberTime)>=onDuration){
    ledState=LOW;
    rememberTime=millis();
    }
  }
  else{
    if((millis()-rememberTime)>=offDuration){
      ledState=HIGH;
      rememberTime=millis();
    }
  }
  digitalWrite(led,ledState);
}
// 2nd blinking
void blinkts2(int blinkLEDInterval) {  
  unsigned long timeNow = millis();                                   
    if (timeNow - rememberTime > blinkLEDInterval) { 
      rememberTime = timeNow;                        
        if (stateLED == LOW)  {                                 
          stateLED = HIGH;                                           
          Serial.println("ON2");                                     
      } else  {      
          stateLED = LOW;                                       
          Serial.println("OFF2");                            
        } 
       digitalWrite(led, stateLED);            
    }
}

void btn_press(){  
  int reading = digitalRead(button);
   if (reading != lastButtonState) {
    // reset the debouncing timer
    lastTime = millis();
   }
   if ((millis() - lastTime) > 20) {    
     if (reading != buttonState) {
      buttonState = reading;
     }
   }
  
//when switch is pressed
 if (buttonState == 0 && flag2 == 0){
    presstime = millis();
    flag1 = 0;
    flag2 = 1;
    tapCounter++;
  //delay(10);
 }  
 if (buttonState == 1 && flag1 == 0){
    releasetime = millis(); 
    flag1 = 1;
    flag2 = 0;  
    //delay(10);
  }
  
  //when button long press
  if (flag == 0 && buttonState == HIGH){
    currentTime = millis();
    flag = 1;
  }
  if (flag == 1 && buttonState == LOW){
    endTime = millis();
    flag = 0;
    duration = endTime - currentTime;
 // Serial.println (duration);
  }

  //  main (led on off)
   if ((millis() - presstime) > 400){    
      while (tapCounter == 1){
        if (duration <= 1000){ 
          Serial.println("single tap");             
         blinkts();           
        }
        else{       
          Serial.println("led off");
          digitalWrite(led,LOW);             
        }
        reading = digitalRead(button);
         if(reading==HIGH){
            count++;
            !tapCounter==count;
            tapCounter=count;
          }
       }    
      while(tapCounter == 2 ){                                
        Serial.println("double Tap");  
       blinkts2(1000);  
        reading = digitalRead(button);
        if(reading==HIGH){
          count++;
          !tapCounter==count;
          tapCounter=count;
        }               
      }     
      while (tapCounter == 3){
        Serial.println("triple tap");     
         reading = digitalRead(button);
           if(reading==HIGH){
            count++;
            !tapCounter==count;
            tapCounter=count;
          } 
      }             
    tapCounter =0;
  }      
 lastButtonState = reading;
}

void loop() {
  btn_press();
}
