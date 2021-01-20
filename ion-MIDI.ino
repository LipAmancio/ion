/*
 * MIDIUSB_test.ino
 *
 * Created: 4/6/2015 10:47:08 AM
 * Author: gurbrinder grewal
 * Modified by Arduino LLC (2015)
 */ 

#include "MIDIUSB.h"

  #define Green A2     //Pino botao verde  
  #define Red A1     //Pino botao vermelho
  #define Yellow A0   //Pino botao amarelo
  #define Blue A8     //Pino botao azul
  #define Orange A9  //Pino botao laranja

  #define Strm_up  16  //Pino botão "para cima" da palheta (Strum) 
  #define Strm_dw 10   //Pino botão "para baixo" da palheta (Strum)

  const int Nbut = 5;
  int Pbut[Nbut] = {A2, A1, A0, A8, A9};
  int note[Nbut] = {48, 52, 55, 62, 64};
  int butCS[Nbut] = {1};
  int butPS[Nbut] = {0};
  int strmQr[Nbut] = {0};

  int i;
  int Sflg = 0;
  int N;
  long int debTime[Nbut+1];
  int debDelay = 40;
  

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void setup() {

  pinMode (Strm_up, INPUT_PULLUP);
  pinMode (Strm_dw, INPUT_PULLUP);
  
  for (i = 0; i < Nbut; i++){
    pinMode(Pbut[i], INPUT_PULLUP);
  }
}


void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void loop() {
  
  for (i = 0; i < Nbut; i++){
    butCS[i] = digitalRead(Pbut[i]);
  
    if ((millis() - debTime[i]) > debDelay){
    
      if(butPS[i] != butCS[i]){
        debTime[i] = millis();
        
      }
    }
  }
  //////////////////////////////////////////////
  //estrutura de gravação///////////////////////

  if ((Sflg == 1) && (digitalRead(Strm_up)) && (digitalRead(Strm_dw)) )
  Sflg = 0;
  
  for (i = 0; i < Nbut; i++){
    
    if(butPS[i] != butCS[i]){
      if(butPS[i] != LOW) {   
        strmQr[i] = 1;
        //MidiUSB.flush();
      }
      if(butPS[i] == LOW){
        noteOff(0, note[i], 80);  // Channel 0, middle C, normal velocity
        strmQr[i] = 0;
        //MidiUSB.flush();
      }
      butPS[i] = butCS[i];
      MidiUSB.flush();
    }  
    
  }
  if ((millis() - debTime[5]) > debDelay){
    if ((Sflg == 0) && ((!digitalRead(Strm_up)) || (!digitalRead(Strm_dw)))){
      Sflg = 1;
      debTime[5] = millis();
      for (i = 0; i < Nbut; i++){
        if (strmQr[i] == 1){
          noteOn(0, note[i], 80);
        }
      }
      MidiUSB.flush(); 
    }
  }
///////////////////////////////////////////////////
}
