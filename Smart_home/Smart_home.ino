#define BLYNK_TEMPLATE_ID "**********"
#define BLYNK_DEVICE_NAME "*************"
#define BLYNK_AUTH_TOKEN "***************"

#include<SPI.h>
#include<Ethernet.h>
#include<BlynkSimpleEthernet.h>
#include<Wire.h>
#include<LiquidCrystal_I2C.h>

#include"main.h"
#include"temperature_system.h"
#include"serial_tank.h"

char auth[]=BLYNK_AUTH_TOKEN;
bool heater_sw,inlet_sw,outlet_sw;
unsigned int tank_volume;

BlynkTimer timer;

LiquidCrystal_I2C lcd(0x27,16,2);
BLYNK_WRITE(COOLER_V_PIN) {
  int value=param.asInt();
  if(value) {
    cooler_control(ON);
    lcd.setCursor(7, 0);
    lcd.print("CLR ON ");
  } else {
    cooler_control(OFF);
    lcd.setCursor(7, 0);
    lcd.print("CLR OFF");
  }
}
BLYNK_WRITE(HEATER_V_PIN) {
  heater_sw=param.asInt();
  if(heater_sw) {
    heater_control(ON);
    lcd.setCursor(7, 0);
    lcd.print("HTR ON ");
  } else {
    heater_control(OFF);
    lcd.setCursor(7, 0);
    lcd.print("HTR OFF");
  }
}
BLYNK_WRITE(INLET_V_PIN) {
  inlet_sw= param.asInt();
  if(inlet_sw){
    enable_inlet();
    lcd.setCursor(7, 1);
    lcd.print("INFL ON ");
  } else {
    disable_inlet();
    lcd.setCursor(7, 1);
    lcd.print("INFL OFF");
  }
}
BLYNK_WRITE(OUTLET_V_PIN) {
  outlet_sw= param.asInt();
  if(outlet_sw){
    enable_outlet();
    lcd.setCursor(7, 1);
    lcd.print("OUFL ON ");
  } else {
    disable_outlet();
    lcd.setCursor(7, 1);
    lcd.print("OUFL OFF");
  }
}
void update_temperature_reading(){
  Blynk.virtualWrite(TEMPERATURE_GAUGE,read_temperature());
  Blynk.virtualWrite(WATER_VOL_GAUGE,volume());
}
void handle_temp(void) {
  
  if((read_temperature() > (float)35)&& heater_sw){
    heater_sw=OFF;
    heater_control(OFF);
    lcd.setCursor(7, 0);
    lcd.print("HTR OFF");
    Blynk.virtualWrite(BLYNK_TERMINAL_V_PIN,"Temperature is above 35 degree Celsius\n");
    Blynk.virtualWrite(BLYNK_TERMINAL_V_PIN,"Turning OFF the heater\n");
    Blynk.virtualWrite(HEATER_V_PIN,OFF);
  }
}
void handle_tank(void) {
  if((tank_volume <2000)&& (inlet_sw==OFF)) {
      enable_inlet();
      lcd.setCursor(7, 1);
      lcd.print("INFL ON ");
      inlet_sw=ON;
      Blynk.virtualWrite(INLET_V_PIN,ON);
      Blynk.virtualWrite(BLYNK_TERMINAL_V_PIN,"Water volume is less than 2000 litres\n");
    Blynk.virtualWrite(BLYNK_TERMINAL_V_PIN,"Turning ON the inlet valve\n");

  }
  if((tank_volume ==3000)&& (inlet_sw==ON)) {
      disable_inlet();
      lcd.setCursor(7, 1);
      lcd.print("INFL OFF");
      inlet_sw=OFF;
      Blynk.virtualWrite(INLET_V_PIN,OFF);
      Blynk.virtualWrite(BLYNK_TERMINAL_V_PIN,"Tank is Full\n");
    Blynk.virtualWrite(BLYNK_TERMINAL_V_PIN,"Turning OFF the inlet valve\n");

  }
}
void setup() {
  // put your setup code here, to run once:
  Blynk.begin(auth);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.home();
  init_temperature_system();
  lcd.setCursor(0, 0);
  lcd.print("T=");
  lcd.setCursor(0, 1);
  lcd.print("V=");
  init_serial_tank();
  timer.setInterval(500L,update_temperature_reading);
}

void loop() {
  lcd.setCursor(2, 0);
  String temperature;
  temperature=String(read_temperature(),2);
  lcd.print(temperature);

  tank_volume=volume();
  lcd.setCursor(2,1);
  lcd.print(tank_volume);
  handle_temp();
  handle_tank();
  Blynk.run();
  timer.run();

}