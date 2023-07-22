//set pins
int SER_Pin = 4;    //pin 14 on the 75HC595
int RCLK_Pin = 5;   //pin 12 on the 75HC595
int SRCLK_Pin = 6;  //pin 11 on the 75HC595
int BUTTON_Pin = 7; // button pin
int BUZZER_Pin = 3;  // buzzer pin

//game option
int min_waarde = 200;
int max_waarde = 250;
int start_delay = 5;
bool CANstart;

//config
#define number_of_74hc595s 5
#define numOfRegisterPins number_of_74hc595s * 8

boolean registers[numOfRegisterPins];
int Randomwaarde;
int del;

void setup() {
  Serial.begin(9600);
  pinMode(SER_Pin, OUTPUT);
  pinMode(RCLK_Pin, OUTPUT);
  pinMode(SRCLK_Pin, OUTPUT);
  pinMode(BUZZER_Pin, OUTPUT);
  pinMode(BUTTON_Pin, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(BUTTON_Pin) == LOW){ //functions based off of button pulling input pin LOW
    CANstart = true;
    startGame();
  }
  
  if(CANstart){
    for (int x=0; x<=36; x++){
      if (del <= Randomwaarde){
         //digitalWrite(BUZZER_Pin,HIGH);
         setRegisterPin(x, HIGH);
         updateShiftRegister();
         delay(del);
         //digitalWrite(BUZZER_Pin,LOW);
         if(!(del >= Randomwaarde)){
           setRegisterPin(x, LOW);
           updateShiftRegister();
         }
         del = del +1;
     }
    }
  }
  
}

void updateShiftRegister(){
   digitalWrite(RCLK_Pin, LOW);
   for(int i = numOfRegisterPins - 1; i >=  0; i--){
     digitalWrite(SRCLK_Pin, LOW);
     int val = registers[i];
     digitalWrite(SER_Pin, val);
     digitalWrite(SRCLK_Pin, HIGH);
   }
  digitalWrite(RCLK_Pin, HIGH);
}

void clearShiftRegisters(){
 for(int i = numOfRegisterPins - 1; i >=  0; i--){
   registers[i] = LOW;
 }
}

void setRegisterPin(int index, int value){
 registers[index] = value;
}

void startGame(){
  Randomwaarde = random(min_waarde,max_waarde);
  del = start_delay;
  clearShiftRegisters();
  updateShiftRegister();
}
