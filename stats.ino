#include <LiquidCrystal.h>

// RS, EN, D4, D5, D6, D7
LiquidCrystal lcd(6, 7, 9, 10, 11, 12);

char buffer[32];
byte idx = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("waiting for data");
}

void loop() {
  if (Serial.available()) 
  {
    char c = Serial.read();

    if (c == '\n' || c == '\r') 
    {
      if (idx > 0) 
      {
        buffer[idx] = '\0';

        int cpu = 0, ram = 0, temp = 0;
        int parsed = sscanf(buffer, "%d,%d,%d", &cpu, &ram, &temp);

        if (parsed == 3) 
        {
          lcd.clear();
          lcd.setCursor(0, 0);

          lcd.print("CPU:");
          lcd.print(cpu);
          lcd.print("% ");

          lcd.print(temp);
          lcd.print("C");

          lcd.setCursor(0, 1);
          
          lcd.print("RAM:");
          lcd.print(ram);
          lcd.print("%");
        }
        idx = 0;
      }
    } 
    else 
      if (idx < 31) 
      {
        buffer[idx] = c;
        idx++;
      } 
      else 
        idx = 0;
  }
}