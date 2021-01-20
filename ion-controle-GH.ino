#include <Keyboard.h>

#include <Mouse.h>

/*  Programa criado para contolar uma guitarra de guitar hero
 *  ou semelhantes, por meio de um Arduino Pro micro ou Leonardo
 *  Autor: Luis Felipe F. Amancio @lip_amancio
 */
//=-=-=-=-=-=- Bibliotecas =-=-=-=-=-=-=-=-
//#include <Mouse.h>

//#include <Keyboard.h>

//=-=-=-=-=-=-=-= Pinagem =-=-=-=-=-=-=-=-=

#define Green A2     //Pino botao verde  
#define Red A1     //Pino botao vermelho
#define Yellow A0   //Pino botao amarelo
#define Blue A8     //Pino botao azul
#define Orange A9  //Pino botao laranja

#define Strm_up  16  //Pino botão "para cima" da palheta (Strum) 
#define Strm_dw 10  //Pino botão "para baixo" da palheta (Strum)

#define strpwr 14    //Pino botão Star Power

//#define start 7   //Pino botão Start 

#define sldPin A3    //Pino Slider (Whammy)  

//=-=-=-=-=-=- Correspondencia =-=-=-=-=-=-
//Define os botões correspondentes do
//teclado para cada botão

#define K_Green  'q'  
#define K_Red    'w'
#define K_Yellow 'e'
#define K_Blue   'r'
#define K_Orange 't'

#define K_Up     'u'
#define K_Down   'd'

//#define K_Start  's'  //Backspace
#define K_StrPwr    'p'

//=-=-=-=-=-= Variaveis Globais =-=-=-=-=-=-

int sldMem = 0;
int sldValue = 0;
int sld = 0;
int flag = 0;

//=-=-=-=-=-=-= Inicialização =-=-=-=-=-=-=-

void setup() {

//=-=-=-=-= Declaração de Pinos =-=-=-=-=-=-
  pinMode (Green, INPUT_PULLUP);    
  pinMode (Red, INPUT_PULLUP);
  pinMode (Yellow, INPUT_PULLUP);
  pinMode (Blue, INPUT_PULLUP);
  pinMode (Orange, INPUT_PULLUP);

  pinMode (Strm_up, INPUT_PULLUP);
  pinMode (Strm_dw, INPUT_PULLUP);

//  pinMode (start, INPUT_PULLUP);
  pinMode (strpwr, INPUT_PULLUP);

  //pinMode (sldPin, INPUT);
}

//=-=-=-=-=-=-=-= Repetição =-=-=-=-=-=-=-=-=

void loop() {

   //sld = //analogRead (sldPin);
 
  if (sld%sldMem > 5){
    sldValue = sldMem - sld;
    Mouse.move (0, 0, sldValue*-3);
    sldMem = sld;
  }

  if (sldMem >= 1017) sldMem = sld;
    
  if (sldMem <= 6) sldMem = sld;

//=-=-=-=- Le os botões e ativa a tecla correspondente =-=-=-=-

  if (!digitalRead(Green)) Keyboard.press(K_Green); 
  if (digitalRead(Green))  Keyboard.release(K_Green);

  if (!digitalRead(Red)) Keyboard.press(K_Red); 
  if (digitalRead(Red))  Keyboard.release(K_Red);

  if (!digitalRead(Yellow)) Keyboard.press(K_Yellow); 
  if (digitalRead(Yellow))  Keyboard.release(K_Yellow);

  if (!digitalRead(Blue)) Keyboard.press(K_Blue); 
  if (digitalRead(Blue))  Keyboard.release(K_Blue);
  
  if (!digitalRead(Orange)) Keyboard.press(K_Orange); 
  if (digitalRead(Orange))  Keyboard.release(K_Orange);

  if (!digitalRead(Strm_up)) Keyboard.press(K_Up);
  if (digitalRead(Strm_up)) Keyboard.release(K_Up);

  if (!digitalRead(Strm_dw)) Keyboard.press(K_Down); 
  if (digitalRead(Strm_dw))  Keyboard.release(K_Down);
/*  
  if (!digitalRead(start)) Keyboard.press(K_Start); 
  if (digitalRead(start))  Keyboard.release(K_Start); 
*/
  
  if (!digitalRead(strpwr)) Keyboard.press(K_StrPwr); 
  if (digitalRead(strpwr))  Keyboard.release(K_StrPwr);
 
}
