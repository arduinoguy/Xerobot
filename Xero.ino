#include<SD.h>
#include<LiquidCrystal.h>

LiquidCrystal lcd(A15, A14, A13, A12, A11, A10);
File card;
byte set=0;
byte out=0;
void setup()
{
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  lcd.begin(16,2);
  SD.begin(10);
  attachInterrupt(0,clearset,RISING);
  attachInterrupt(2,trainset,RISING);
  attachInterrupt(1,repeatset,RISING);

 
}

void trainset()
{ if(set==0)
 { set=1;
  card=SD.open("xerobot.txt",FILE_WRITE);
  lcd.clear();
  lcd.print("Training mode");
 }
  else
  {lcd.clear();
   lcd.print("Xerobot");
  set=0;
  card.close();
  }
}

void repeatset()
{ if(set==0)
{ 
  card=SD.open("xerobot.txt");
  set=2;
  lcd.clear();
  lcd.print("Repeat mode");
}
  else{
    lcd.clear();
    lcd.print("Xerobot");
    card.close();
  set=0;
}
}

void clearset()
{ 
  lcd.clear();
  lcd.print("File Cleared");
  SD.remove("Xerobot.txt");
  delay(5000);
  lcd.clear();
  lcd.print("Xerobot");
}

void train()
{
  DDRF=0x00;
  byte value=PINF;
  card.write(value);
  delay(50);
}

void repeat()
{ 
  DDRF=0xff;
  char value;
  
  
    for(byte count=7;count>=0&&(value=card.read())!=EOF;count--)
    {
      byte x=value-'0';
      out=(out<<1)|x;
     
      
    }
   PORTF=out;
   if(value=EOF)
   {
     card.seek(0);
   }
   delay(50);
   // Serial.println(out,BIN);
}
  
    
  





void loop()
{
    
 while(set==1)
{ train();}

while(set==2)
{repeat();}
}





