const int SensorProximty = 9;

void setup()
{
  Serial.begin(9600);
  pinMode(SensorProximty, INPUT);
}

void loop()
{
  int hasil = digitalRead(SensorProximty);
  if(hasil == LOW)
  {
    Serial.println("Ada Halangan");
  }
  if(hasil == HIGH)
  {
    Serial.println("Aman, Tidak Ada Halangan");
  }
  delay(250);
}