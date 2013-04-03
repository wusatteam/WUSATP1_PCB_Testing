int A_PRES = 0;
int A_TEMP1 = 2;
int A_TEMP2 = 1;

int pres=0,temp1=0,temp2=0;
int mpres=0,mtemp1=0,mtemp2=0;

void setup() {
  //  analogueReference(DEFAULT);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  digitalWrite(A0,LOW);
  digitalWrite(A1,LOW);
  digitalWrite(A2,LOW);
  
  Serial.begin(9600);
  while(!Serial){
  }

  Serial.println("Ready");
}

void loop() {
  pres=analogRead(A_PRES);
  delay(100);
  temp1=analogRead(A_TEMP1);
  delay(100);
  temp2=analogRead(A_TEMP2);

  mpres=map(pres,0,1024,0,5000);
  mtemp1=map(temp1,0,1024,0,5000);
  mtemp2=map(temp2,0,1024,0,5000);

  Serial.print("PRES: ");
  Serial.println(mpres,DEC);
  Serial.print("TEMP1: ");
  Serial.println(mtemp1,DEC);
  Serial.print("TEMP2: ");
  Serial.println(mtemp2,DEC);
  delay(1000);
}





