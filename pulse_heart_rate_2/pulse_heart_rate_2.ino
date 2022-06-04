#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

SoftwareSerial mine(3, 2);
DFRobotDFPlayerMini player;

int thr = 80;

int pulsePin = A0;             
int blinkPin = 3;            

volatile int BPM;              
volatile int Signal;               
volatile int IBI = 600;            
volatile boolean Pulse = false; 
volatile boolean QS = false;        

static boolean serialVisual = true;   

volatile int rate[10];                     
volatile unsigned long sampleCounter = 0;          
volatile unsigned long lastBeatTime = 0;       
volatile int P = 512;                 
volatile int T = 512;                    
volatile int thresh = 525;                
volatile int amp = 100;                   
volatile boolean firstBeat = true;       
volatile boolean secondBeat = false;

void setup()
{
  Serial.begin(115200); 
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  
  mine.begin(9600);
  while(!player.begin(mine)) {
     Serial.println("Connecting to DFPlayer Mini failed!");
     delay(2000);}
  Serial.println("OK");
  player.volume(30);
  
  pinMode(blinkPin,OUTPUT);        
              
  interruptSetup();                
}



void loop()
{
  serialOutput();  
  if (QS == true) // A Heartbeat Was Found
    { serialOutputWhenBeatHappens();    
      QS = false;  }
  delay(20);
}

void interruptSetup()
{     
  TCCR2A = 0x02;     
  TCCR2B = 0x06;     
  OCR2A = 0X7C;    
  TIMSK2 = 0x02;    
  sei();            
} 

void serialOutput()
{   
 if (serialVisual == true)
  {  arduinoSerialMonitorVisual('-', Signal); } 
 else
  { sendDataToSerial('S', Signal); }        
}

void serialOutputWhenBeatHappens()
{    
 if (serialVisual == true)
   {            
     Serial.print(" Heart-Beat Found "); 
     Serial.print("BPM: ");
     Serial.println(BPM);



   if(BPM > thr) {

     for(int i=0; i<3; i++){
       digitalWrite(8, HIGH);
       digitalWrite(9, LOW);
       delay(200);
       digitalWrite(9, HIGH);
       digitalWrite(8, LOW);
       delay(200);
     }
       digitalWrite(8, LOW);
       digitalWrite(9, LOW);

     player.play(1);
     delay(10000);
     Serial.println("finished !!!");
    } else { }


    
     
   }
 else
   {
     sendDataToSerial('B',BPM);  
     sendDataToSerial('Q',IBI); 
   }   
}

void arduinoSerialMonitorVisual(char symbol, int data )
{    
  const int sensorMin = 0;   
  const int sensorMax = 1024;   
  int sensorReading = data;
  int range = map(sensorReading, sensorMin, sensorMax, 0, 11);
}


void sendDataToSerial(char symbol, int data )
{
   Serial.print(symbol);
   Serial.println(data);                
}

ISR(TIMER2_COMPA_vect) 
{  
  cli();                                  
  Signal = analogRead(pulsePin);            
  sampleCounter += 2;                   
  int N = sampleCounter - lastBeatTime;     
                                            
  if(Signal < thresh && N > (IBI/5)*3)
    {      
      if (Signal < T) 
      {                        
        T = Signal; 
      }
    }

  if(Signal > thresh && Signal > P)
    { P = Signal; }             

  if (N > 250)
  {                                 
    if ( (Signal > thresh) && (Pulse == false) && (N > (IBI/5)*3) )
      { Pulse = true;                              
        digitalWrite(blinkPin,HIGH);               
        IBI = sampleCounter - lastBeatTime;        
        lastBeatTime = sampleCounter;               
  
        if(secondBeat)
        { secondBeat = false;                 
          for(int i=0; i<=9; i++)
          { rate[i] = IBI; }
        }
  
        if(firstBeat) 
        {                         
          firstBeat = false;                  
          secondBeat = true;                  
          sei();                              
          return;                             
        }   
     
      word runningTotal = 0;                 

      for(int i=0; i<=8; i++)
        { rate[i] = rate[i+1];                 
          runningTotal += rate[i];             
        }

      rate[9] = IBI;                       
      runningTotal += rate[9];              
      runningTotal /= 10;                  
      BPM = 60000/runningTotal;            
      QS = true;                     
    }                       
  }

  if (Signal < thresh && Pulse == true)
    { digitalWrite(blinkPin,LOW);          
      Pulse = false;               
      amp = P - T;                        
      thresh = amp/2 + T;             
      P = thresh;                          
      T = thresh;
    }

  if (N > 2500)
    { thresh = 512;                     
      P = 512;                         
      T = 512;                              
      lastBeatTime = sampleCounter;            
      firstBeat = true;                     
      secondBeat = false;                  
    }
  sei();                             
}
