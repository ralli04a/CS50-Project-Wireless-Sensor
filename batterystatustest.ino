/*
prints the voltage on analog pin to the serial port and light up LEDs
Do not connect more than 5 volts directly to an Arduino pin.
This is meant to check battery status as an inturrupt. I plan to modify
it so the voltage divider is only drawing energy while the inturrupt is active
*/

const float referenceVolts = 5.0; // the default reference on a 5-volt board
//const float referenceVolts = 3.3; // use this for a 3.3-volt board

#define R1 = 3000.0 // value for a maximum voltage of 20 volts, see note below
#define R2 = 1000.0 
/* 
R1 is the resistor value before the voltage divide read point
R2 is the resistor value after the voltage divide read point
below is the ideal ratios to use:
For 9v battery use 5:4 ratio for R1:R2. LED's are set for 9v battery
20v would be a 3:1 ratio
15v would be a 2:1 ratio
*/
float Vout;
float ResRatio = (R1+R2)/(R2);

//Define LED Pins
const int GREEN = 9;
const int YELLOW = 10;
const int RED = 11;
const int blink = 13;

void setup()
{
	Serial.begin(9600);
	pinMode(GREEN, OUTPUT); 
	pinMode(YELLOW, OUTPUT);
	pinMode(RED, OUTPUT);
	pinMode(blink, OUTPUT);
	digitalWrite(RED, HIGH);
	delay(500);
	digitalWrite(YELLOW, HIGH);
	delay(500);
	digitalWrite(GREEN, HIGH);
	delay(1000);
	digitalWrite(GREEN, LOW); 
	digitalWrite(YELLOW, LOW); 
	digitalWrite(RED, LOW); 
	attachInterrupt(0, batstat, RISING); // Interrupt Pin 0 is digital pin 2 on UNO
}

void loop()
{
	digitalWrite(blink, HIGH); //whatever the program is
	delay(500);
        digitalWrite(blink, LOW);
	delay(500);
}

void batstat()
{
  digitalWrite(blink,LOW);
  float Vout = analogRead(A0)*(referenceVolts/1023.0); // read the value from the sensor
  float volts = resRatio * Vout; // Calculate the total voltage from the volt divider
	Serial.println(volts); // print the value in volts

/*
Set voltage values for the discharge of the battery you are using.
This is set for a 9v battery
*/

	if (volts > 8.0) {
		digitalWrite(GREEN, HIGH);
        digitalWrite(YELLOW, LOW);
        digitalWrite(RED, LOW);
	}
	else if ((volts <= 8.0) && (volts >= 7.5)) {
		digitalWrite(YELLOW, HIGH);
        digitalWrite(GREEN, LOW);
        digitalWrite(RED, LOW);
	}
	else if ((volts < 7.5) && (volts >= 7.0)) {
		digitalWrite(RED, HIGH);
        digitalWrite(GREEN, LOW);
        digitalWrite(YELLOW, LOW);
	}
	else (volts < 7.0); {
		digitalWrite(RED, HIGH);
		digitalWrite(GREEN, HIGH); //Indicate critically Low
        digitalWrite(YELLOW, LOW);
	}
}