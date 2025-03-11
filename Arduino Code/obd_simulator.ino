#include <CAN.h> // the OBD2 library depends on the CAN library
#include <OBD2.h>



void setup() {
  Serial.begin(9600); // Initializes serial communication with a baud rate of 9600
  while (!Serial);    // Waits until the serial connection is established

  Serial.println(F("OBD2 data printer"));
  Serial.println(F("Type 'start' to begin or 'stop' to end printing data."));
  Serial.println(F("Type 'clear' to clear DTCs."));
  


  // Attempt to connect to the OBD-II CAN bus
  while (true) {
    Serial.print(F("Attempting to connect to OBD2 CAN bus ... "));

    if (!OBD2.begin()) {              // Checks connection
      Serial.println(F("failed!"));
      delay(1000);                    // Waits before retrying
    } else {
      Serial.println(F("success"));
      break;
    }
  }
Serial.println("Attempting to detect ECU module...");
EcuModule moduleType = OBD2.detectEcuModule();

  Serial.println();
  Serial.print("VIN = ");
  Serial.println(OBD2.vinRead());   //Calls vinRead function from the OBD2 library, to read VIN (Vehicle Identification Number based on Mode 09)
  Serial.print("ECU Name = ");
  Serial.println(OBD2.ecuNameRead());
  Serial.println();

}


void loop() {
  // Check if any data is available in the Serial buffer
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');          // Read the command until a newline
    command.trim();                                         // Remove any leading/trailing whitespace

    // Check for start/stop commands
        if (command.equalsIgnoreCase("start")) {
          running = true;                               // Set running variable to true
          Serial.println(F("Started printing data."));
        } else if (command.equalsIgnoreCase("stop")) {
          running = false;                              // Set running variable to true
          Serial.println(F("Stopped printing data."));
        } else if (command.equalsIgnoreCase("clear")) {
          if (OBD2.clearAllStoredDTC()) {               //Calls the clearAllStoredDTC function from the OBD2 library to clear the DTCs
            Serial.println(F("DTCs cleared successfully"));
          } else {
            Serial.println(F("Failed to clear DTCs"));
          }
        }else if (command.equalsIgnoreCase("dtc")) {
      byte dtcData[12];                                   // Size adjustment according to the expected amount of DTC data
      int dtcLength = OBD2.getDTC(dtcData, 12);
      
      if (dtcLength != 0) {
        //Serial.print("DTCs: ");
        for (int i = 0; i < dtcLength; i += 2) {
          uint16_t dtc = (dtcData[i] << 8) | dtcData[i + 1];            // Combination of 2 bytes in a DTC code
          Serial.print(dtc, HEX);                                       // Print the DTC in hexadecimal format
          Serial.print(" ");
        }
        Serial.println();
      } else {
        Serial.println("No DTCs available");
      }
    }

  }

// Process PIDs only if running is true
      if (running) {
        for (int pid = 0; pid < 96; pid++) {
          processPid(pid);
        }
    Serial.println();               // Blank line for better readability
    delay(1000);                    // Reduced latency for more frequent updates
                  }


                  
} //void loop ends here

void processPid(int pid) {
  if (!OBD2.pidSupported(pid)) {                // Check if the PID is supported
    return;                                     // Omission of unsupported PIDs
  }

  Serial.print(OBD2.pidName(pid));
  Serial.print(F(" = "));

  if (OBD2.pidValueRaw(pid)) {
    unsigned long pidRawValue = OBD2.pidReadRaw(pid);
    Serial.print(F("0x"));
    Serial.print(pidRawValue, HEX);
  } else {
    float pidValue = OBD2.pidRead(pid);
    if (isnan(pidValue)) {
      Serial.print("error");
    } else {
      Serial.print(pidValue);
      Serial.print(F(" "));
      Serial.print(OBD2.pidUnits(pid));
    }
  }

  delay(500);
  Serial.println();                       // New line after each PID output
}









/*


//=============================================================
//this code below , can also print the raw data simultaneously with the calculated values that are printed by the above code 

#include <CAN.h> // the OBD2 library depends on the CAN library
#include <OBD2.h>

bool running = false; // Variable to control data printing

void setup() {
  Serial.begin(9600); // Initializes serial communication with a baud rate of 9600
  while (!Serial);    // Waits until the serial connection is established

  Serial.println(F("OBD2 data printer"));
  Serial.println(F("Type 'start' to begin or 'stop' to end printing data."));
  Serial.println(F("Type 'clear' to clear DTCs."));

  // Attempt to connect to the OBD-II CAN bus
  while (true) {
    Serial.print(F("Attempting to connect to OBD2 CAN bus ... "));

    if (!OBD2.begin()) { // Checks connection
      Serial.println(F("failed!"));
      delay(1000); // Waits before retrying
    } else {
      Serial.println(F("success"));
      break;
    }
  }

  Serial.println();
  Serial.print("VIN = ");
  Serial.println(OBD2.vinRead());
  Serial.print("ECU Name = ");
  Serial.println(OBD2.ecuNameRead());
  Serial.println();
}

void loop() {
  // Check if any data is available in the Serial buffer
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n'); // Read the command until a newline
    command.trim(); // Remove any leading/trailing whitespace

    // Check for start/stop commands
    if (command.equalsIgnoreCase("start")) {
      running = true; // Set running to true
      Serial.println(F("Started printing data."));
    } else if (command.equalsIgnoreCase("stop")) {
      running = false; // Set running to false
      Serial.println(F("Stopped printing data."));
    } else if (command.equalsIgnoreCase("clear")) {
      if (OBD2.clearAllStoredDTC()) {
        Serial.println(F("DTCs cleared successfully"));
      } else {
        Serial.println(F("Failed to clear DTCs"));
      }
    }
  }

  // Only process PIDs if running is true
  if (running) {
    for (int pid = 0; pid < 96; pid++) {
      processPid(pid);
    }
    Serial.println(); // Empty line for readability
    delay(1000); // Reduced delay for more frequent updates
  }
}

void processPid(int pid) {
  if (!OBD2.pidSupported(pid)) { // Check if PID is supported
    return; // Skip unsupported PIDs
  }

  Serial.print(OBD2.pidName(pid));
  Serial.print(F(" = "));

  if (OBD2.pidValueRaw(pid)) {
    unsigned long pidRawValue = OBD2.pidReadRaw(pid);
    Serial.print(F("0x"));
    Serial.print(pidRawValue, HEX);
    Serial.print(F(" (Raw)"));
  } else {
    float pidValue = OBD2.pidRead(pid);
    if (isnan(pidValue)) {
      Serial.print("error");
    } else {
      Serial.print(pidValue);
      Serial.print(F(" "));
      Serial.print(OBD2.pidUnits(pid));
      Serial.print(F(" (Calculated)"));
    }
  }

  // Print the raw data
  Serial.print(F(" Raw Data: "));
  unsigned long pidRawValue = OBD2.pidReadRaw(pid);
  for (int i = 0; i < 4; i++) {
    Serial.print((pidRawValue >> (8 * (3 - i))) & 0xFF, HEX);
    Serial.print(F(" "));
  }

  delay(500);
  Serial.println(); // New line after each PID output
}
*/



