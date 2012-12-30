//
// Button polling
//

// The pins used:
const int out_FAN = 3; // PWM pin FAN
const int out_BTN_TP = 5; // PWM Front LED
const int out_BTN_BT = 6; // PWM Front LED
const int out_LED_R = 11; // PWM pin R LED
const int out_LED_G = 10; // PWM pin G LED
const int out_LED_B = 9; // PWM pin B LED
const int front_btn = A0; // digital input front button
const int rear_pot = A1;  // Analog input pin that the potentiometer is attached to

// Global Variables
int FAN = 200;
int LED_R = 255;
int LED_G = 0;
int LED_B = 0;
int LED_BTN_TP = 255;
int LED_BTN_BT = 255;
int i = 1;
int j = 0;
int k = 0;
int delay_time = 75;
int currentSine = 0;
int pushEffect = 0;
int buttonState;
int prevState;
int zeroCross;

int newValues[6];

void setup() {
    pinMode(front_btn, INPUT);
    pinMode(out_LED_R, OUTPUT);
    pinMode(out_LED_G, OUTPUT);
    pinMode(out_LED_B, OUTPUT);
    pinMode(out_BTN_TP, OUTPUT);
    pinMode(out_BTN_BT, OUTPUT);
    pinMode(out_FAN, OUTPUT);
}

void loop(){
    buttonState = digitalRead(front_btn);
    if(prevState != buttonState)
    {
      prevState = buttonState;
      if(buttonState == HIGH)
      {
        i++;  //button pressed     
        k=0;
        zeroCross=0;
      }
    }
    else digitalWrite(out_BTN_BT,LOW);
  
    if(i==10) i=1;
    currentSine = getSine(j); //(0 <= j <= 81)
    if (k>100 && j==0) zeroCross = 1;        //detect zero crosse to sync with sinewave
    if (k<250 && zeroCross == 0) pushEffect = getSine(k+41);  //generate afterglow
    else pushEffect = currentSine;
    
    getValues(i);
    analogWrite(out_FAN,newValues[0]);
    analogWrite(out_LED_R,newValues[1]);
    analogWrite(out_LED_G,newValues[2]);
    analogWrite(out_LED_B,newValues[3]);
    analogWrite(out_BTN_TP,newValues[4]);
    analogWrite(out_BTN_BT,newValues[5]);
    
    j++;
    if (k<250) k++;
    if (j>100) j=0;

    delay(delay_time);
}

void getValues(int selector){
  if(selector == 1) {
    newValues[0] = 100;            //FAN
    newValues[1] = currentSine;    //R
    newValues[2] = 0;              //G
    newValues[3] = 0;              //B
    newValues[4] = currentSine;    //TOP LED
    newValues[5] = pushEffect;    //BOTTOM LED
    return;
  }
  if(selector == 2) {
    newValues[0] = 180;
    newValues[1] = currentSine;
    newValues[2] = 0;
    newValues[3] = 0;
    newValues[4] = currentSine;
    newValues[5] = pushEffect;
    return;
  }  
  if(selector == 3) {
    newValues[0] = 255;
    newValues[1] = currentSine;
    newValues[2] = 0;
    newValues[3] = 0;
    newValues[4] = currentSine;
    newValues[5] = pushEffect;
    return;
  }
  if(selector == 4){
    newValues[0] = 100;
    newValues[1] = currentSine;
    newValues[2] = currentSine;
    newValues[3] = currentSine;
    newValues[4] = currentSine;
    newValues[5] = pushEffect;
    return;
  }
  if(selector == 5){
    newValues[0] = 180;
    newValues[1] = currentSine;
    newValues[2] = currentSine;
    newValues[3] = currentSine;
    newValues[4] = currentSine;
    newValues[5] = pushEffect;
    return;
  }
  if(selector == 6){
    newValues[0] = 255;
    newValues[1] = currentSine;
    newValues[2] = currentSine;
    newValues[3] = currentSine;
    newValues[4] = currentSine;
    newValues[5] = pushEffect;
    return;
  }
  if(selector == 7){
    newValues[0] = 180;
    newValues[1] = 255;
    newValues[2] = 0;
    newValues[3] = 0;
    newValues[4] = currentSine;
    newValues[5] = pushEffect;
    return;
  }
  if(selector == 8){
    newValues[0] = 180;
    newValues[1] = 255;
    newValues[2] = 255;
    newValues[3] = 255;
    newValues[4] = currentSine;
    newValues[5] = pushEffect;
    return;
  }
  if(selector == 9){
    newValues[0] = 0;
    newValues[1] = 0;
    newValues[2] = 0;
    newValues[3] = 0;
    if (k<70)
    {
      newValues[4] = pushEffect;    //fade out
      newValues[5] = pushEffect;
    }
    else
    {
      newValues[4] = 0;             //keep off
      newValues[5] = 0; 
    }
    return;
  }
  else{
    newValues[0] = 180;
    newValues[1] = 0;
    newValues[2] = 0;
    newValues[3] = 0;
    newValues[4] = currentSine;
    newValues[5] = pushEffect;
    return;
  }
}

int getSine(int x){
  if(x==	0	) return(	1	);
  if(x==	1	) return(	1	);
  if(x==	2	) return(	2	);
  if(x==	3	) return(	3	);
  if(x==	4	) return(	5	);
  if(x==	5	) return(	8	);
  if(x==	6	) return(	11	);
  if(x==	7	) return(	15	);
  if(x==	8	) return(	20	);
  if(x==	9	) return(	25	);
  if(x==	10	) return(	30	);
  if(x==	11	) return(	36	);
  if(x==	12	) return(	43	);
  if(x==	13	) return(	49	);
  if(x==	14	) return(	56	);
  if(x==	15	) return(	64	);
  if(x==	16	) return(	72	);
  if(x==	17	) return(	80	);
  if(x==	18	) return(	88	);
  if(x==	19	) return(	97	);
  if(x==	20	) return(	105	);
  if(x==	21	) return(	114	);
  if(x==	22	) return(	123	);
  if(x==	23	) return(	132	);
  if(x==	24	) return(	141	);
  if(x==	25	) return(	150	);
  if(x==	26	) return(	158	);
  if(x==	27	) return(	167	);
  if(x==	28	) return(	175	);
  if(x==	29	) return(	183	);
  if(x==	30	) return(	191	);
  if(x==	31	) return(	199	);
  if(x==	32	) return(	206	);
  if(x==	33	) return(	212	);
  if(x==	34	) return(	219	);
  if(x==	35	) return(	225	);
  if(x==	36	) return(	230	);
  if(x==	37	) return(	235	);
  if(x==	38	) return(	240	);
  if(x==	39	) return(	244	);
  if(x==	40	) return(	247	);
  if(x==	41	) return(	250	);
  if(x==	42	) return(	247	);
  if(x==	43	) return(	244	);
  if(x==	44	) return(	240	);
  if(x==	45	) return(	235	);
  if(x==	46	) return(	230	);
  if(x==	47	) return(	225	);
  if(x==	48	) return(	219	);
  if(x==	49	) return(	212	);
  if(x==	50	) return(	206	);
  if(x==	51	) return(	199	);
  if(x==	52	) return(	191	);
  if(x==	53	) return(	183	);
  if(x==	54	) return(	175	);
  if(x==	55	) return(	167	);
  if(x==	56	) return(	158	);
  if(x==	57	) return(	150	);
  if(x==	58	) return(	141	);
  if(x==	59	) return(	132	);
  if(x==	60	) return(	123	);
  if(x==	61	) return(	114	);
  if(x==	62	) return(	105	);
  if(x==	63	) return(	97	);
  if(x==	64	) return(	88	);
  if(x==	65	) return(	80	);
  if(x==	66	) return(	72	);
  if(x==	67	) return(	64	);
  if(x==	68	) return(	56	);
  if(x==	69	) return(	49	);
  if(x==	70	) return(	43	);
  if(x==	71	) return(	36	);
  if(x==	72	) return(	30	);
  if(x==	73	) return(	25	);
  if(x==	74	) return(	20	);
  if(x==	75	) return(	15	);
  if(x==	76	) return(	11	);
  if(x==	77	) return(	8	);
  if(x==	78	) return(	5	);
  if(x==	79	) return(	3	);
  if(x==	80	) return(	2	);
  if(x==	81	) return(	1	);
  if(x>	        81	) return(	0	);
}
