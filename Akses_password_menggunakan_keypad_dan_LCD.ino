#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

#define Password_lenght 8

const int signalPin = 13;

char Data [Password_lenght];
char Master [Password_lenght] = "#";

byte data_count = 0, master_count = 0; //Set awal dari data counting

char customKey;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);



void setup() {
  // put your setup code here, to run once:
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  pinMode (signalPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor (0,0);
  lcd.print ("Masukan Password");
  customKey = customKeypad.getKey();
  if (customKey){
    Data[data_count] = customKey; 
    lcd.setCursor(data_count,1); 
    lcd.print(Data[data_count]); 
    data_count++; 
    }
  if (data_count == Password_lenght-1){
    lcd.clear();
  }
  if (!strcmp (Data,Master)){
    lcd.print (" Password Benar");
    digitalWrite (signalPin, HIGH);
    delay (3000);
    digitalWrite (signalPin, LOW);
  }
  else {
    lcd.print (" Password Salah");
    delay (400);
  }

  lcd.clear();
  clearData();

}

void clearData (){
  while (data_count !=0){ //Ini adalah program untuk digunakan pada seluruh besar array 
    Data[data_count--] =0; //Membersihkan array untuk data yang baru
  }
  return;
}
