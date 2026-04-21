#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// -------- LCD --------
LiquidCrystal_I2C lcd1(0x27, 16, 2);
LiquidCrystal_I2C lcd2(0x23, 16, 2);

// -------- BUTTONS --------
int p1Pins[3] = {2, 3, 4};
int p2Pins[3] = {5, 6, 7,};

// -------- BUZZER --------
int buzzer = 9;

// -------- POWER LED --------
int p1LED = 10;
int p2LED = 11;

// -------- GAME STATE --------
int p1Choice = -1;
int p2Choice = -1;

int p1Health = 5;
int p2Health = 5;

// -------- POWER SYSTEM --------
int p1Streak = 0;
int p2Streak = 0;

bool p1PowerReady = false;
bool p2PowerReady = false;

bool gameOver = false;

// =============================================
void showPlayers(String p1, String p2) {
  lcd1.clear(); lcd1.setCursor(0, 0); lcd1.print(p1);
  lcd2.clear(); lcd2.setCursor(0, 0); lcd2.print(p2);
}

// =============================================
// SOUND
// =============================================
void soundClick(){ tone(buzzer,800,40); }
void soundWin(){ tone(buzzer,1200,200); }
void soundLose(){ tone(buzzer,400,200); }
void soundDraw(){ tone(buzzer,700,150); }

void soundClash(){
  tone(buzzer,600,60); delay(70);
  tone(buzzer,900,80);
}

void soundPowerUp(){
  tone(buzzer,600,80); delay(80);
  tone(buzzer,900,80); delay(80);
  tone(buzzer,1300,150);
}

// =============================================
// PLAYER 1 SWAP
// =============================================
int remapP1(int c){
  if(c==0) return 2;
  if(c==2) return 0;
  return 1;
}

// =============================================
// GAME LOGIC
// =============================================
int getResult(int p1,int p2){
  if(p1==p2)return 0;
  if((p1==1&&p2==2)||(p1==0&&p2==1)||(p1==2&&p2==0))return 1;
  return -1;
}

// =============================================
void resetGame(){
  p1Health=9; p2Health=9;
  p1Streak=0; p2Streak=0;
  p1PowerReady=false; p2PowerReady=false;
  p1Choice=-1; p2Choice=-1;
  gameOver=false;

  digitalWrite(p1LED,LOW);
  digitalWrite(p2LED,LOW);

  showPlayers("Clash of Olympus","Clash of Olympus");
  delay(1200);
  showPlayers("Choose Power","Choose Power");
}

// =============================================
void setup(){
  Wire.begin();
  lcd1.init(); lcd1.backlight();
  lcd2.init(); lcd2.backlight();

  pinMode(p1LED,OUTPUT);
  pinMode(p2LED,OUTPUT);

  for(int i=0;i<3;i++){
    pinMode(p1Pins[i],INPUT_PULLUP);
    pinMode(p2Pins[i],INPUT_PULLUP);
  }

  showPlayers("Clash of Olympus","Clash of Olympus");
  delay(1200);
  showPlayers("Choose Power","Choose Power");
}

// =============================================
void loop(){

  if(gameOver){
    showPlayers("Restart","Restart");
    delay(1500);
    resetGame();
    return;
  }

  // INPUT
  if(p1Choice==-1){
    for(int i=0;i<3;i++){
      if(digitalRead(p1Pins[i])==LOW){
        p1Choice=i;
        soundClick();
        delay(120);
      }
    }
  }

  if(p2Choice==-1){
    for(int i=0;i<3;i++){
      if(digitalRead(p2Pins[i])==LOW){
        p2Choice=i;
        soundClick();
        delay(120);
      }
    }
  }

  // RESOLVE
  if(p1Choice!=-1 && p2Choice!=-1){

    soundClash();
    int result = getResult(remapP1(p1Choice), p2Choice);

    // -------- DRAW --------
    if(result==0){
      p1Streak=0; p2Streak=0;
      showPlayers("DRAW","DRAW");
      delay(600);
      showPlayers("POWER STAYS","POWER STAYS");
      soundDraw();
    }

    // -------- P1 WINS --------
    else if(result==1){

      if(p1PowerReady){
        p1Health++;
        p2Health--;
        p1PowerReady=false;
        digitalWrite(p1LED,LOW);

        showPlayers("DOUBLE HIT","DOUBLE HIT");
        delay(700);
      }
      else if(p2PowerReady){
        p2PowerReady=false;
        digitalWrite(p2LED,LOW);

        showPlayers("POWER BLOCKED","POWER BLOCKED");
        delay(700);
      }
      else{
        p2Health--;
      }

      p1Streak++;
      p2Streak=0;

      if(p1Streak==2){
        p1PowerReady=true;
        digitalWrite(p1LED,HIGH);
        p1Streak=0;

        showPlayers("ATHENAS FAVOUR","");
        soundPowerUp();
        delay(700);
      }

      showPlayers("VICTORY","DEFEAT");
      soundWin();
    }

    // -------- P2 WINS --------
    else{

      if(p2PowerReady){
        p2Health++;
        p1Health--;
        p2PowerReady=false;
        digitalWrite(p2LED,LOW);

        showPlayers("DOUBLE HIT","DOUBLE HIT");
        delay(700);
      }
      else if(p1PowerReady){
        p1PowerReady=false;
        digitalWrite(p1LED,LOW);

        showPlayers("POWER BLOCKED","POWER BLOCKED");
        delay(700);
      }
      else{
        p1Health--;
      }

      p2Streak++;
      p1Streak=0;

      if(p2Streak==2){
        p2PowerReady=true;
        digitalWrite(p2LED,HIGH);
        p2Streak=0;

        showPlayers("","ATHENAS FAVOUR");
        soundPowerUp();
        delay(700);
      }

      showPlayers("DEFEAT","VICTORY");
      soundLose();
    }

    delay(800);
    showPlayers("YOU:"+String(p1Health)+" ENEMY:"+String(p2Health)+"  ","YOU:"+String(p2Health)+" ENEMY:"+String(p1Health));
    delay(1200);

    if(p1Health<=0 || p2Health<=0){

      if(p1Health>p2Health){
        showPlayers("CHAMPION","DEFEATED");
      }else{
        showPlayers("DEFEATED","CHAMPION");
      }

      delay(1500);
      gameOver=true;
      return;
    }

    p1Choice=-1;
    p2Choice=-1;
    showPlayers("Choose Power","Choose Power");
  }
}
