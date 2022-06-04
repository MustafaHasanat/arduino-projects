int X;  int Y;
float t;              float f = 0;
float water = 0;      float total = 0;
float leters = 0;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

void loop() {
  X = pulseIn(A0, HIGH);
  Y = pulseIn(A0, LOW);
  t = X + Y;           f = 1000000/t;    
  water = f/7.5;       leters = water/60;


  if(isinf(f)){ Serial.print(total); }
  else{ 
      total = total + leters;
      Serial.print(total);}
  Serial.print(" ");
  
  delay(1500);
  
}
