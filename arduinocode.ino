#include <QTRSensors.h>//Murat Bay
#define NUM_SENSORS 6 // Kullanýlacak olan pin sayýsý
#define NUM_SAMPLES_PER_SENSOR 4
#define EMITTER_PIN QTR_NO_EMITTER_PIN

QTRSensorsRC qtrrc((unsigned char[]) { 2, 3, 4, 5, 6, 7}, //Sensör giriþ pinlerimizi belirliyoruz.
NUM_SENSORS, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

int ena=8; //PWM için enable pin giriþ pini tanýmlanýr
int in1=9; //Motor1 için (+) pin giriþ pini tanýmlanýr
int in2=10; //Motor1 için (-) pin giriþ pini tanýmlanýr
int in3=11; //Motor2 için (+) pin giriþ pini tanýmlanýr
int in4=12; //Motor2 için (-) pin giriþ pini tanýmlanýr
int enb=13; //PWM için enable pin giriþ pini tanýmlanýr
void setup()
{
delay(500);
Serial.begin(9600);
delay(1000);

pinMode(ena,INPUT);
pinMode(in1,INPUT);
pinMode(in2,OUTPUT);
pinMode(enb,OUTPUT);
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
}

void loop()
{
qtrrc.read(sensorValues); //Sensör deðeri okuma fonksiyonu


Serial.print(sensorValues[0]);
Serial.print("\t");
Serial.print(sensorValues[1]); /* Tüm sensörlerin deðerlerini ekrana yazdýrmak için ayrý ayrý sensör deðerleri seri port üzerinde ekrana yazdýrýyoruz.*/
Serial.print("\t");
Serial.print(sensorValues[2]);
Serial.print("\t");
Serial.print(sensorValues[3]);
Serial.print("\t");
Serial.print(sensorValues[4]);
Serial.print("\t");
Serial.print(sensorValues[5]);
Serial.print("\t");
Serial.println();


if (sensorValues[0] > 250 || sensorValues[1] > 250)
{
analogWrite(enb,255);
digitalWrite(in3,HIGH);
analogWrite(ena,0);
digitalWrite(in1,LOW);

}

else if (sensorValues[5] > 250 || sensorValues[4] > 250)
{
analogWrite(enb,0); //Sol
digitalWrite(in3,LOW);
analogWrite(ena,255); 
digitalWrite(in1,HIGH);
}

else if( sensorValues[2] > 250 || sensorValues[3] > 250 ) 
{
digitalWrite(in3,HIGH); //Sol ileri
analogWrite(enb,255);
digitalWrite(in1,HIGH); //Sag ileri
analogWrite(ena,255);
}

else 
{
analogWrite(enb,0); //Sol
digitalWrite(in3,LOW);
digitalWrite(in4,LOW);
analogWrite(ena,0); 
digitalWrite(in1,LOW);
digitalWrite(in2,LOW);
}


}