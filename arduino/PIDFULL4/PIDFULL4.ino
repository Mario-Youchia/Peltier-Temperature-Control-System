#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include<math.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2  //sensor data bus
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#define MotorDirectionA 4
#define MotorSpeedA 3
#define MotorDirectionB 7
#define MotorSpeedB 5
LiquidCrystal_I2C lcd(0x27, 20, 4);
int SpeedValA;
int SpeedValB;
float kp = 1.15;
float ki = 80.1;
float kd = -0.00239;
float Ti = kp / ki;
float Td = kd / kp;
float Ts = 0.00826;
float set_temp = 25;
float beta = kp * Td / Ts;
float alpha = kp * Ts / Ti;
float ek = 0;
float ek_1 = 0;
float pk_1 = 0;
float read_temp;
float sk = 0;
float yk = 0;
float wk, pk, qk, uk;
float val;
float Vmax = 12;

float Read_AD_temp() {
  sensors.requestTemperatures();
  read_temp = float(sensors.getTempCByIndex(0));
  yk = read_temp;
  Serial.println(read_temp);
  return yk;
}
float V2PWM (float V, float Vmax) {
  float PWMval = float (255 * abs(V) / Vmax);
  if (PWMval > 255) {
    PWMval = 255;
  }
  if (V > 0) {
    digitalWrite(MotorDirectionA, HIGH);
    digitalWrite(MotorDirectionB, LOW);
  }
  return PWMval;
}

void timer2_init()
{
  // set up timer with prescaler = 1024
  TCCR1A |= (1 << CS02) | (1 << CS00);

  // initialize counter time .01 s
  TCNT1 = 157;
}
void setup() {
  Serial.begin(9600);
  sensors.begin();
  // Timer1 initialization
  cli();                          //Disable all interrupts
  // initialize timer
  timer2_init();
  sei();   // enable global interrupts

  pinMode(MotorDirectionA, OUTPUT);
  pinMode(MotorSpeedA, OUTPUT);
  pinMode(MotorDirectionB, OUTPUT);
  pinMode(MotorSpeedB, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("CurrTemp=");
  lcd.print(Read_AD_temp());
  lcd.print((char)223);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("ReqTemp=");
  // Initially they are equal
  lcd.print(Read_AD_temp());
  lcd.print((char)223);
  lcd.print("C");
}
ISR(TIMER1_COMPA_vect)
{
  sk = 155 - set_temp;
  yk = Read_AD_temp();
  ek = sk - yk;
  wk = kp * ek;
  qk = beta * (ek - ek_1);
  pk = alpha * ek + pk_1;
  val = wk + qk + pk;
  Serial.println(val);
  if (val > Vmax) {
    val = Vmax;
  }
  if ((val < 0) || (ek < 0)) {
    val = 0;
  }
  //Convert V into PWM => PD output, Peltier input
  uk = V2PWM(val, Vmax);
  analogWrite(MotorSpeedA, uk);
  analogWrite(MotorSpeedB, uk);
  Serial.print("\t");
  Serial.println(uk);
  Serial.print("\t");
  Serial.println(val);
  Serial.print("\t");
  Serial.println(ek);
  pk_1 = pk;
  ek_1 = ek;
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(MotorDirectionA, HIGH);
  //digitalWrite(MotorDirectionB, LOW);

  lcd.setCursor(0, 0);
  lcd.print("CurrTemp=");
  lcd.print(Read_AD_temp());
  lcd.print((char)223);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("ReqTemp=");
  lcd.print(set_temp);
  lcd.print((char)223);
  lcd.print("C");
}
