#include <Dps310.h>
#include <math.h> 
  
  #define ml_second_per_Pa  2.6
  #define dt 0.072
  
  #define prs_mr 128
  #define prs_osr 4
  

  
  float pressure1;
  float pressure2;
  float offset1;
  float offset2;  
  float temperature1;
  float temperature2;
  float volume = 0;
  
  float dt_millis = 0;


// Dps310 Opject
Dps310 Dps310PressureSensor1 = Dps310();
Dps310 Dps310PressureSensor2 = Dps310();

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  
  Dps310PressureSensor1.begin(Wire); 
  Dps310PressureSensor2.begin(Wire, 0x76);

  (void)XMC_I2C_CH_SetBaudrate(XMC_I2C0_CH1, 400000u); // Change the i2c clock to 400KHz
   
  Dps310PressureSensor1.measureTempOnce(temperature1);
  Dps310PressureSensor1.measurePressureOnce(pressure1); offset1 = pressure1;
  Dps310PressureSensor2.measureTempOnce(temperature2);
  Dps310PressureSensor2.measurePressureOnce(pressure2); offset2 = pressure2;
  
//  Serial.println("Init complete!");
}

void loop()
{
  dt_millis = millis();
  // Get actual pressure values
    Dps310PressureSensor1.measureTempOnce(temperature1,2);
    //Serial.print("dt t1: ");Serial.print(millis()-dt_millis);Serial.print("\t"); 
    Dps310PressureSensor1.measurePressureOnce(pressure1,2); pressure1 -= offset1;
   // Serial.print("dt p1: ");Serial.print(millis()-dt_millis);Serial.print("\t");
    Dps310PressureSensor2.measureTempOnce(temperature2,2);
    //Serial.print("dt t2: ");Serial.print(millis()-dt_millis);Serial.print("\t"); 
    Dps310PressureSensor2.measurePressureOnce(pressure2,2); pressure2 -= offset2;
    // Serial.print("dt p2: ");Serial.print(millis()-dt_millis);Serial.println("\t"); 
    

 // calculate volume
 float temp = pressure1-pressure2;
    //if(temp >= 0)volume += log((abs(temp))+1);
    //if(temp <  0) volume -= log((abs(temp)+1));

    volume += temp;
    //volume += sqrt((pressure1-pressure2));//*dt*ml_second_per_Pa;
    

 //Display results    
//     Serial.print("dt: ");
//     Serial.print(millis()-dt_millis);
//     Serial.print(" ");
//     
//     Serial.print("Pressure1: ");
//     Serial.print(pressure1);
//     Serial.print(" ");
//    
//     Serial.print("Pressure2: ");
//     Serial.print(pressure2);
//     Serial.print(" ");

     Serial.print("dp:");
     Serial.print(pressure1-pressure2);
     Serial.print(" ");

     Serial.print("Volume:");
     Serial.println(volume);

     Serial.println("");
 
  //Wait some time
  //delay(10);
}
