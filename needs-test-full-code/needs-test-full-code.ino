#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

//ZEOLITES////
int slider = 0;
int colorRInit = 0;
int colorGInit = 255;
int colorZeoR = 0;
int colorZeoG = 255;
int z;
int ZEOPIN = 3;
int numZeoPix = 16;
int targetZeoPix = 0;
int zeoCool = 255;

//HMC
int force = 0;
int colorHmcR = 0;
int colorHmcG = 255;
int h;
int HMCPIN = 4;
int numHmcPix = 4;

//FIRE/////
int buttonFirePin = 53;
int buttonFireState = 0;
int f;
int FIREPIN = 5;
int numFirePix = 6;
int targetFirePix = 7;
int fireLoopNum = 0;


//SOLAR PANELS////
int photo = 0;
int solarMapped = 0;
int s;
int SOLARPIN = 6;
int numSolPix = 5;

//GREENHOUSE//
int numGreenhousePix = 11;
int GREENHOUSEPIN = 7;
int buttonGreenhouse = 52;
int buttonGreenhouseState = 0;
int g;
int gbright;
int greenFade;

//RADIATORS//
int numRadiatorPix = 30;
int RADIATORPIN = 8;
int buttonRadiators = 50;
int buttonRadiatorsState = 0;
int r;
int target1Row = 0;
int target2Row = 19;
int target3Row = 20;
int radiatorRow1 = 0;
int radiatorRow2 = 19;
int radiatorRow3 = 20;
int radiatorLoopNum = 0;

//WATER RECYCLING AND ELECTROLYSIS//
int numDirtyPix = 8;
int DIRTYPIN = 9;
int numWaterPix = 4;
int WATERPIN = 10;
int numAirPix = 4;
int AIRPIN = 11;
int a, w, d;
int buttonWater = 48;
int buttonAir = 47;
int buttonWaterState = 0;
int buttonAirState = 0;

//On and Off button
boolean isOn = false;
int buttonOn = 49;
int buttonOnState = 0;

Adafruit_NeoPixel zeoStrip(numZeoPix, ZEOPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel hmcStrip(numHmcPix, HMCPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel fireStrip(numFirePix, FIREPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel solarStrip(numSolPix, SOLARPIN, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel greenhouseStrip(numGreenhousePix, GREENHOUSEPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel radiatorStrip(numRadiatorPix, RADIATORPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel waterStrip(numWaterPix, WATERPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel dirtyStrip(numDirtyPix, DIRTYPIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel airStrip(numAirPix, AIRPIN, NEO_GRB + NEO_KHZ800);



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  zeoStrip.begin();
   hmcStrip.begin();
  pinMode(buttonFirePin, INPUT);
  fireStrip.begin();
  solarStrip.begin();
  radiatorStrip.begin();
  greenhouseStrip.begin();
  waterStrip.begin();
  dirtyStrip.begin();
  airStrip.begin();
  pinMode(buttonGreenhouse, INPUT);
  pinMode(buttonRadiators, INPUT);
  pinMode(buttonWater, INPUT);
  pinMode(buttonAir, INPUT);
  pinMode(buttonOn, INPUT);
}

void loop() {
  zeoStrip.clear();
  slider = analogRead(A0);
  hmcStrip.clear();
  force = analogRead(A1);
  fireStrip.clear();
  buttonFireState = digitalRead(buttonFirePin);
  buttonGreenhouseState = digitalRead(buttonGreenhouse);
  buttonRadiatorsState = digitalRead(buttonRadiators);
  buttonWaterState = digitalRead(buttonWater);
  buttonAirState = digitalRead(buttonAir);
  buttonOnState = digitalRead(buttonOn);
  photo = analogRead(A3);
  solarMapped = map(photo, 350, 650, 0, numSolPix);
//  Serial.println(photo);
//  Serial.print(force);
//  Serial.print(" ");
//  Serial.println("");

  if(buttonOnState == HIGH){
    isOn = !isOn;
  }
  
  if(isOn){
    zeoLoop();
    hmcLoop();
    fireloop();
    solarLoop();
    greenhouseLoop();
    radiatorLoop();
    WRELoop();
  }
  else{
    fullClear();
  }
  

// This sends the updated pixel color to the hardware.
   zeoStrip.show(); 
   hmcStrip.show(); 
   fireStrip.show();
   solarStrip.show();
   greenhouseStrip.show();
   radiatorStrip.show();
   dirtyStrip.show();
   airStrip.show();
   waterStrip.show();

   delay(200);
}

 /////////////////////////////
  ////////ZEO LOGIC //////////
  /////////////////////////////
void zeoLoop(){
  if (slider > 900){
    fullZeoReset();
    for(z=0; z<numZeoPix; z++){
        // red
        zeoStrip.setPixelColor(z, zeoCool, 0, 0); 
     }

     if (zeoCool != 0) {zeoCool -= 5;}
     else {zeoCool = 0;}
  }

  else{

    changeZeoColor();
    zeoCool = 255;
  
     if(colorZeoR==255){
        zeoReset();
        targetZeoPix +=4;
     }
    if(targetZeoPix == numZeoPix){
      for(z=0; z<numZeoPix; z++){
        // red
        zeoStrip.setPixelColor(z, 255, 0, 0); 
     }
    }
    else {  
       //for less than target pix -> be red
       // for targetPix -> turn red
       //for more than targetPix be green
       for(z=0; z<targetZeoPix; z++){
          // red
          zeoStrip.setPixelColor(z, 255, 0, 0); 
       }
      //transition
      for(z=targetZeoPix; z<targetZeoPix+4; z++){
             zeoStrip.setPixelColor(z, colorZeoR, colorZeoG, 0);
      }
       
       for(z=targetZeoPix+4; z<numZeoPix; z++){
        //green
        zeoStrip.setPixelColor(z, 0, 255, 0);
       }
      }   
  }
}

void changeZeoColor(){
   if (colorZeoR < 255){
    colorZeoR += 1;
    colorZeoG -= 1;
   }
}

void zeoReset(){
  colorZeoR = colorRInit;
  colorZeoG = colorGInit;
}

void fullZeoReset(){
  zeoReset();
  targetZeoPix = 0;
}


/////////////////////////////
////////HMC LOGIC //////////
/////////////////////////////
void hmcLoop(){
    if (force > 100){
      hmcReset();
    }
    changeHmcColor();
    for(h=0; h<numHmcPix; h++){
      hmcStrip.setPixelColor(h, colorHmcR, colorHmcG, 0); 
    }
    
}

void changeHmcColor(){
   if (colorHmcR < 255){
    colorHmcR += 1;
    colorHmcG -= 1;
   }
}

void hmcReset(){
  colorHmcR = colorRInit;
  colorHmcG = colorGInit;
}

/////////////////////////////
////////FIRE LOGIC //////////
/////////////////////////////
void fireloop(){
   //button logic 
    if(buttonFireState == HIGH) {
      //turn light off
      fireStrip.setPixelColor(targetFirePix, 0, 0, 0);
      fireStrip.show();
      targetFirePix = numFirePix + 1;
    }
    if(targetFirePix == numFirePix +1){
        //create a delay
        if(fireLoopNum == 300){
           targetFirePix = random(0,numFirePix);
          fireLoopNum = 0;
        }
       else{
        fireLoopNum += 1;
       }
    }
    //orange
    fireStrip.setPixelColor(targetFirePix, 255, 60, 0);
}

void fireReset(){
  targetFirePix = numFirePix + 1;
}


/////////////////////////////
////////Solar LOGIC //////////
/////////////////////////////
void solarLoop(){
   for(s=0; s<solarMapped; s++){
     // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      solarStrip.setPixelColor(s, 255, 60, 0); // orange!
    }
   for(s=solarMapped; s<numSolPix; s++) {
      solarStrip.setPixelColor(s, 0, 0, 0);    // turn off all pixels after value displayed
   }

}

//////GREENHOUSE/////
void greenhouseLoop(){
   if (buttonGreenhouseState == HIGH){
    greenFade = random(1, 10);
    for(g=0; g<numGreenhousePix; g++) {
      gbright = 255;
      greenhouseStrip.setPixelColor(g,gbright,0,gbright);
    }
   }
   if (buttonGreenhouseState == LOW){
//    for(gbright=255; gbright>=0; gbright--){
      for(g=0; g<numGreenhousePix; g++) {
        greenhouseStrip.setPixelColor(g,gbright,0,gbright);
      }
//    }
    if (gbright > 0){
      gbright -= greenFade;
    }
    if(gbright < 0){
      gbright = 0;
    }
   }
}

/////RADIATORS/////
void radiatorLoop(){
   if (buttonRadiatorsState == HIGH){
    for(r=0; r<numRadiatorPix; r++){
      radiatorReset();
      radiatorStrip.setPixelColor(r,0,0,0);
    }
   }
   if (buttonRadiatorsState == LOW){
    if(target1Row != radiatorRow2){
      //row 1
      for(r=radiatorRow1; r<target1Row; r++){
        radiatorStrip.setPixelColor(r,255,0,0);
      }
      //row 2
      for(r=radiatorRow2; r>target2Row; r--){
        radiatorStrip.setPixelColor(r,255,0,0);
      }
      //row 2
      for(r=radiatorRow3; r<target3Row; r++){
        radiatorStrip.setPixelColor(r,255,0,0);
      }
    }
    else{
      for(r=0; r<numRadiatorPix; r++){
        radiatorStrip.setPixelColor(r,255,0,0);
      }
    }


   if(radiatorLoopNum == 20){
      target1Row += 1;
      target2Row -= 1;
      target3Row += 1;
      radiatorLoopNum = 0;
    }
     else{
      radiatorLoopNum += 1;
     }
   }
}

void radiatorReset(){
  target1Row = radiatorRow1;
  target2Row = radiatorRow2;
  target3Row = radiatorRow3;
}

//WRE LOGIC
  bool dirtyUp = true;
  int dirtyLoopNum = 0;
  int dirtyTarget = 0;
 bool waterUp = false;
 int waterTarget = numWaterPix;
  int waterLoopNum = 0;
 bool airUp = false;
int airTarget = numAirPix;
  int airLoopNum = 0;
  int wreTimer =20;
 
 void WRELoop(){
  if(buttonAirState == HIGH){
    airUp = true;
    airLoopNum = 0;
    dirtyGoDown();

  }
  //air logic
  //air goes down, unless pressed it goes up
  if(airUp){
    if(airLoopNum == wreTimer && airTarget != numAirPix){
      airLoopNum = 0;
      airTarget ++;
      dirtyGoDown();
    }
    if(airTarget == numAirPix){
      airUp = false;
    }
  }
  else{
    if(airLoopNum == wreTimer && airTarget != 0){
      airLoopNum = 0;
      airTarget --;
    }
  }
  Serial.print(airLoopNum);
  Serial.print(" ");
  Serial.print(airTarget);
  Serial.print(" ");
  Serial.println(airUp);
  for(a=0; a<airTarget; a++){
    airStrip.setPixelColor(a, 255, 255, 255);
  }
  for(a=airTarget; a<numAirPix; a++){
    airStrip.setPixelColor(a, 0, 0, 0);
  }
  //airLoopNum ++;
  
//water goes up sequentially
if(buttonWaterState == HIGH){
    waterUp = true;
    dirtyGoDown();
    waterLoopNum = 0;
  }
  //water goes down, unless pressed it goes up
  if(waterUp){
    if(waterLoopNum == wreTimer && waterTarget != numWaterPix){
      waterLoopNum = 0;
      waterTarget ++;
    }
    if(waterTarget == numWaterPix){
      waterUp = false;
    }
  }
  else{
    if(waterLoopNum == wreTimer && waterTarget != 0){
      waterLoopNum = 0;
      waterTarget --;
    }
  }
  
  for(w=0; w<waterTarget; w++){
    waterStrip.setPixelColor(w, 0, 0, 255);
  }
  for(w=waterTarget; w<numWaterPix; w++){
    waterStrip.setPixelColor(w, 0, 0, 0);
  }
  waterLoopNum ++;



  //always slowly moves up
  if(dirtyUp){ 
    if(dirtyLoopNum == wreTimer && dirtyTarget != numDirtyPix){
      dirtyTarget += 1;
      dirtyLoopNum = 0;
    } 
  }
  
  else{
    if(dirtyLoopNum == wreTimer){
      dirtyTarget -= 1;
      dirtyLoopNum = 0;
    }
    if(dirtyTarget == 0){
      dirtyUp = true;
    }
  }
   for(d=0; d<dirtyTarget; d++){
      dirtyStrip.setPixelColor(d, 102, 51, 0);
    }
    for(d=dirtyTarget; d<numDirtyPix; d++){
      dirtyStrip.setPixelColor(d, 0, 0, 0); 
    }
    dirtyLoopNum++;
    airLoopNum++;
}

void dirtyGoDown(){
  dirtyUp = false;
  dirtyLoopNum = 0;
 // dirtyTarget = numDirtyPix;
}

void wreReset(){
  dirtyUp = true;
  dirtyLoopNum = 0;
  dirtyTarget = 0;
  airLoopNum = 0;
  waterLoopNum = 0;
  airTarget = numAirPix;
  waterTarget = numWaterPix;
  waterUp = false;
  airUp = false;
}

void fullClear(){
  hmcReset();
  fullZeoReset();
  fireReset();
  radiatorReset();
  wreReset();
  //zeo
   for(z=0; z<numZeoPix; z++){
        zeoStrip.setPixelColor(z, 0, 0, 0); 
   }
  //hmc
 for(h=0; h<numHmcPix; h++){
    hmcStrip.setPixelColor(h, 0, 0, 0); 
  }
  //fire
  for(f=0; f<numFirePix; f++){
    fireStrip.setPixelColor(f, 0, 0, 0);
  }
  //solar
  for(s=0; s<numSolPix; s++) {
      solarStrip.setPixelColor(s, 0, 0, 0);
   }
  //greenhouse
  for(g=0; g<numGreenhousePix; g++) {
    greenhouseStrip.setPixelColor(g,0,0,0);
  }
  //radiators
  for(r=0; r<numRadiatorPix; r++){
      radiatorStrip.setPixelColor(r,0,0,0);
   }

   //wreloop
  for(a=0; a<numAirPix; a++){
    airStrip.setPixelColor(a, 0, 0, 0);
  }
  for(w=0; w<numWaterPix; w++){
    waterStrip.setPixelColor(w, 0, 0, 0);
  }
  for(d=0; d<numDirtyPix; d++){
    dirtyStrip.setPixelColor(d, 0, 0, 0);
  }
}
