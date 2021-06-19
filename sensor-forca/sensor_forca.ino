
int fsrPin[5] = {0,1,2,3,4};
int i = 0;
int values = 0;

long fsrReading[5] =     {0,0,0,0,0}; // the analog reading from the FSR resistor divider
long fsrVoltage[5] =     {0,0,0,0,0}; // the analog reading converted to voltage
long fsrResistance[5]  = {0,0,0,0,0}; // The voltage converted to resistance, can be very big so make "long"
long fsrConductance[5] = {0,0,0,0,0};
long fsrForce[5] =       {0,0,0,0,0}; // Finally, the resistance converted to force

void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
    // Serial.println( " ============ " );
  
    for(i=0; i<3 ;i++){
      fsrReading[i] = analogRead(fsrPin[i]);
      
      /*
      Serial.print(i);
      Serial.print(" - Analog reading = ");
      Serial.println(fsrReading[i]);
      */
      
    }
    // Serial.println( " ============ " );

    int values = 0;
    for( i = 0; i<3; i++ ){
      if(fsrReading[i] > 10) { 
        values = values + 1;
      }
    }
    /*
    Serial.println( " values:  " );
    Serial.print(values);
    */
    
  if(values >= 2){
    Serial.write('g'); // goku
  }else if( fsrReading[0] > fsrReading[1] && fsrReading[0] > fsrReading[2]  ){
    Serial.write('w') ; // weak
  } else if( fsrReading[1] > fsrReading[0] && fsrReading[1] > fsrReading[2]  ){
    Serial.write('s') ; // strong
  }else if ( fsrReading[2] > fsrReading[0] && fsrReading[2] > fsrReading[1]  ){
    Serial.write('h') ; // hulk
  }
  
  delay(100);
}
