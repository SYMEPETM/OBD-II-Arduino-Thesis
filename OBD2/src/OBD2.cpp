#include <math.h>               //provides declarations for various mathematical functions (example: sqrt,sine,cos etc.)

#ifdef __AVR__                  //it restricts the typedef only to Arduino boards (Uno,Mega,Leonardo etc.)
#include <avr/pgmspace.h>       //if we are using an AVR board, this line includes another header, which provides functions and macros specified to the AVR architecture
#else                           //if AVR is not defined, this part of the block gets executed
#define PROGMEM                 //this macro is used elsewhere inside the code, in order to indicate that a variable or function argument, points to the data stored in the program memory
#endif                          // the end of ifdef

#include <CAN.h>            

#include "OBD2.h"

#include "DTC_codes.h"




/*
//const char: this part defines a constant array of characters. the keyword const, ensures that the contents of the array cannot be modified after the initialization

//PID_NAME_0x00: this is the name given to the character array

//[]: this declares the array itself. the square brackets specify that it is an array which could hold multiple characters

//PROGMEM: 1.a macro which was defined in the beginning of the code. 
//         2.Storing constant strings like menu items or error messages in flash memory frees up valuable RAM for program execution and variable storage
//         3.The program memory on most microcontrollers is read-only. This means the strings stored there cannot be accidentally modified during program execution,  protecting the integrity of your code
*/



const char PID_NAME_0x00[] PROGMEM = "PIDs supported [01 - 20]";
const char PID_NAME_0x01[] PROGMEM = "Monitor status since DTCs cleared";
const char PID_NAME_0x02[] PROGMEM = "Freeze DTC";
const char PID_NAME_0x03[] PROGMEM = "Fuel system status";        //this line creates a constant character array named PID_NAME_0x03 (which represents the OBD-II PID code 0x03) and stores the descriptive text "Fuel system status" within it
const char PID_NAME_0x04[] PROGMEM = "Calculated engine load";      //the amount of air the engine is consuming per minute
const char PID_NAME_0x05[] PROGMEM = "Engine coolant temperature";
const char PID_NAME_0x06[] PROGMEM = "Short term fuel trim — Bank 1";
const char PID_NAME_0x07[] PROGMEM = "Long term fuel trim — Bank 1";
const char PID_NAME_0x08[] PROGMEM = "Short term fuel trim — Bank 2";
const char PID_NAME_0x09[] PROGMEM = "Long term fuel trim — Bank 2";
const char PID_NAME_0x0a[] PROGMEM = "Fuel pressure";
const char PID_NAME_0x0b[] PROGMEM = "Intake manifold absolute pressure";
const char PID_NAME_0x0c[] PROGMEM = "Engine RPM";
const char PID_NAME_0x0d[] PROGMEM = "Vehicle speed";
const char PID_NAME_0x0e[] PROGMEM = "Timing advance";
const char PID_NAME_0x0f[] PROGMEM = "Intake air temperature";
const char PID_NAME_0x10[] PROGMEM = "MAF air flow rate";
const char PID_NAME_0x11[] PROGMEM = "Throttle position";
const char PID_NAME_0x12[] PROGMEM = "Commanded secondary air status";
const char PID_NAME_0x13[] PROGMEM = "Oxygen sensors present (in 2 banks)";
const char PID_NAME_0x14[] PROGMEM = "Oxygen Sensor 1 - Short term fuel trim";
const char PID_NAME_0x15[] PROGMEM = "Oxygen Sensor 2 - Short term fuel trim";
const char PID_NAME_0x16[] PROGMEM = "Oxygen Sensor 3 - Short term fuel trim";
const char PID_NAME_0x17[] PROGMEM = "Oxygen Sensor 4 - Short term fuel trim";
const char PID_NAME_0x18[] PROGMEM = "Oxygen Sensor 5 - Short term fuel trim";
const char PID_NAME_0x19[] PROGMEM = "Oxygen Sensor 6 - Short term fuel trim";
const char PID_NAME_0x1a[] PROGMEM = "Oxygen Sensor 7 - Short term fuel trim";
const char PID_NAME_0x1b[] PROGMEM = "Oxygen Sensor 8 - Short term fuel trim";
const char PID_NAME_0x1c[] PROGMEM = "OBD standards this vehicle conforms to";
const char PID_NAME_0x1d[] PROGMEM = "Oxygen sensors present (in 4 banks)";
const char PID_NAME_0x1e[] PROGMEM = "Auxiliary input status";
const char PID_NAME_0x1f[] PROGMEM = "Run time since engine start";
  //here we have the end of the first 20 PIDs


const char PID_NAME_0x20[] PROGMEM = "PIDs supported [21 - 40]";
const char PID_NAME_0x21[] PROGMEM = "Distance traveled with malfunction indicator lamp (MIL) on";
const char PID_NAME_0x22[] PROGMEM = "Fuel Rail Pressure (relative to manifold vacuum)";
const char PID_NAME_0x23[] PROGMEM = "Fuel Rail Gauge Pressure (diesel, or gasoline direct injection)";
const char PID_NAME_0x24[] PROGMEM = "Oxygen Sensor 1 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x25[] PROGMEM = "Oxygen Sensor 2 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x26[] PROGMEM = "Oxygen Sensor 3 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x27[] PROGMEM = "Oxygen Sensor 4 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x28[] PROGMEM = "Oxygen Sensor 5 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x29[] PROGMEM = "Oxygen Sensor 6 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x2a[] PROGMEM = "Oxygen Sensor 7 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x2b[] PROGMEM = "Oxygen Sensor 8 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x2c[] PROGMEM = "Commanded EGR";
const char PID_NAME_0x2d[] PROGMEM = "EGR Error";
const char PID_NAME_0x2e[] PROGMEM = "Commanded evaporative purge";
const char PID_NAME_0x2f[] PROGMEM = "Fuel Tank Level Input";
const char PID_NAME_0x30[] PROGMEM = "Warm-ups since codes cleared";
const char PID_NAME_0x31[] PROGMEM = "Distance traveled since codes cleared";
const char PID_NAME_0x32[] PROGMEM = "Evap. System Vapor Pressure";
const char PID_NAME_0x33[] PROGMEM = "Absolute Barometric Pressure";
const char PID_NAME_0x34[] PROGMEM = "Oxygen Sensor 1 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x35[] PROGMEM = "Oxygen Sensor 2 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x36[] PROGMEM = "Oxygen Sensor 3 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x37[] PROGMEM = "Oxygen Sensor 4 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x38[] PROGMEM = "Oxygen Sensor 5 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x39[] PROGMEM = "Oxygen Sensor 6 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x3a[] PROGMEM = "Oxygen Sensor 7 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x3b[] PROGMEM = "Oxygen Sensor 8 - Fuel–Air Equivalence Ratio";
const char PID_NAME_0x3c[] PROGMEM = "Catalyst Temperature: Bank 1, Sensor 1";
const char PID_NAME_0x3d[] PROGMEM = "Catalyst Temperature: Bank 2, Sensor 1";
const char PID_NAME_0x3e[] PROGMEM = "Catalyst Temperature: Bank 1, Sensor 2";
const char PID_NAME_0x3f[] PROGMEM = "Catalyst Temperature: Bank 2, Sensor 2";


const char PID_NAME_0x40[] PROGMEM = "PIDs supported [41 - 60]";
const char PID_NAME_0x41[] PROGMEM = "Monitor status this drive cycle";
const char PID_NAME_0x42[] PROGMEM = "Control module voltage";
const char PID_NAME_0x43[] PROGMEM = "Absolute load value";
const char PID_NAME_0x44[] PROGMEM = "Fuel–Air commanded equivalence ratio";
const char PID_NAME_0x45[] PROGMEM = "Relative throttle position";
const char PID_NAME_0x46[] PROGMEM = "Ambient air temperature";
const char PID_NAME_0x47[] PROGMEM = "Absolute throttle position B";
const char PID_NAME_0x48[] PROGMEM = "Absolute throttle position C";
const char PID_NAME_0x49[] PROGMEM = "Absolute throttle position D";
const char PID_NAME_0x4a[] PROGMEM = "Absolute throttle position E";
const char PID_NAME_0x4b[] PROGMEM = "Absolute throttle position F";
const char PID_NAME_0x4c[] PROGMEM = "Commanded throttle actuator";
const char PID_NAME_0x4d[] PROGMEM = "Time run with MIL on";
const char PID_NAME_0x4e[] PROGMEM = "Time since trouble codes cleared";
const char PID_NAME_0x4f[] PROGMEM = "Maximum value for Fuel–Air equivalence ratio, oxygen sensor voltage, oxygen sensor current, and intake manifold absolute pressure";
const char PID_NAME_0x50[] PROGMEM = "Maximum value for air flow rate from mass air flow sensor";
const char PID_NAME_0x51[] PROGMEM = "Fuel Type";
const char PID_NAME_0x52[] PROGMEM = "Ethanol fuel percentage";
const char PID_NAME_0x53[] PROGMEM = "Absolute Evap system Vapor Pressure";
const char PID_NAME_0x54[] PROGMEM = "Evap system vapor pressure";
const char PID_NAME_0x55[] PROGMEM = "Short term secondary oxygen sensor trim";
const char PID_NAME_0x56[] PROGMEM = "Long term secondary oxygen sensor trim";
const char PID_NAME_0x57[] PROGMEM = "Short term secondary oxygen sensor trim";
const char PID_NAME_0x58[] PROGMEM = "Long term secondary oxygen sensor trim";
const char PID_NAME_0x59[] PROGMEM = "Fuel rail absolute pressure";
const char PID_NAME_0x5a[] PROGMEM = "Relative accelerator pedal position";
const char PID_NAME_0x5b[] PROGMEM = "Hybrid battery pack remaining life";
const char PID_NAME_0x5c[] PROGMEM = "Engine oil temperature";
const char PID_NAME_0x5d[] PROGMEM = "Fuel injection timing";
const char PID_NAME_0x5e[] PROGMEM = "Engine fuel rate";
const char PID_NAME_0x5f[] PROGMEM = "Emission requirements to which vehicle is designed";

/* it specifies that each element in the array is a constant pointer to a constant character. 
this means that the strings pointed to by the pointers cannot be modified, 
nor can the pointers themselves be changed to point the different strings
*/


/*the code defines an array PID_NAME_MAPPER that contains pointers to constant strings.
 these strings are stored in the program memory (flash) to save SRAM*/


const char* const PID_NAME_MAPPER[] PROGMEM = {                 
  PID_NAME_0x00,
  PID_NAME_0x01,
  PID_NAME_0x02,
  PID_NAME_0x03,
  PID_NAME_0x04,
  PID_NAME_0x05,
  PID_NAME_0x06,
  PID_NAME_0x07,
  PID_NAME_0x08,
  PID_NAME_0x09,
  PID_NAME_0x0a,
  PID_NAME_0x0b,
  PID_NAME_0x0c,
  PID_NAME_0x0d,
  PID_NAME_0x0e,
  PID_NAME_0x0f,
  PID_NAME_0x10,
  PID_NAME_0x11,
  PID_NAME_0x12,
  PID_NAME_0x13,
  PID_NAME_0x14,
  PID_NAME_0x15,
  PID_NAME_0x16,
  PID_NAME_0x17,
  PID_NAME_0x18,
  PID_NAME_0x19,
  PID_NAME_0x1a,
  PID_NAME_0x1b,
  PID_NAME_0x1c,
  PID_NAME_0x1d,
  PID_NAME_0x1e,
  PID_NAME_0x1f,
  PID_NAME_0x20,
  PID_NAME_0x21,
  PID_NAME_0x22,
  PID_NAME_0x23,
  PID_NAME_0x24,
  PID_NAME_0x25,
  PID_NAME_0x26,
  PID_NAME_0x27,
  PID_NAME_0x28,
  PID_NAME_0x29,
  PID_NAME_0x2a,
  PID_NAME_0x2b,
  PID_NAME_0x2c,
  PID_NAME_0x2d,
  PID_NAME_0x2e,
  PID_NAME_0x2f,
  PID_NAME_0x30,
  PID_NAME_0x31,
  PID_NAME_0x32,
  PID_NAME_0x33,
  PID_NAME_0x34,
  PID_NAME_0x35,
  PID_NAME_0x36,
  PID_NAME_0x37,
  PID_NAME_0x38,
  PID_NAME_0x39,
  PID_NAME_0x3a,
  PID_NAME_0x3b,
  PID_NAME_0x3c,
  PID_NAME_0x3d,
  PID_NAME_0x3e,
  PID_NAME_0x3f,
  PID_NAME_0x40,
  PID_NAME_0x41,
  PID_NAME_0x42,
  PID_NAME_0x43,
  PID_NAME_0x44,
  PID_NAME_0x45,
  PID_NAME_0x46,
  PID_NAME_0x47,
  PID_NAME_0x48,
  PID_NAME_0x49,
  PID_NAME_0x4a,
  PID_NAME_0x4b,
  PID_NAME_0x4c,
  PID_NAME_0x4d,
  PID_NAME_0x4e,
  PID_NAME_0x4f,
  PID_NAME_0x50,
  PID_NAME_0x51,
  PID_NAME_0x52,
  PID_NAME_0x53,
  PID_NAME_0x54,
  PID_NAME_0x55,
  PID_NAME_0x56,
  PID_NAME_0x57,
  PID_NAME_0x58,
  PID_NAME_0x59,
  PID_NAME_0x5a,
  PID_NAME_0x5b,
  PID_NAME_0x5c,
  PID_NAME_0x5d,
  PID_NAME_0x5e,
  PID_NAME_0x5f,
};


//Measurement Units

const char PERCENTAGE[] PROGMEM = "%";
const char KPA[] PROGMEM = "kPa";
const char PA[] PROGMEM = "Pa";
const char RPM[] PROGMEM = "rpm";
const char KPH[] PROGMEM = "km/h";
const char DEGREES_BEFORE_TDC[] PROGMEM = "° before TDC";
const char GRAMS_PER_SECOND[] PROGMEM = "grams/sec";
const char SECONDS[] PROGMEM = "seconds";
const char RATIO[] PROGMEM = "ratio";
const char COUNT[] PROGMEM = "count";
const char KM[] PROGMEM = "km";
const char VOLTS[] PROGMEM = "V";
const char MINUTES[] PROGMEM = "minutes";
const char GPS[] PROGMEM = "g/s";
const char DEGREES[] PROGMEM = "°";
const char DEGREES_CELCIUS[] PROGMEM = "°C";
const char LPH[] PROGMEM = "L/h";

const char* const PID_UNIT_MAPPER[] PROGMEM = {
  NULL,
  NULL,
  NULL,
  NULL,
  PERCENTAGE,             //PID:04 "calculated engine load" has percentage as a measurement unit
  DEGREES_CELCIUS,        //PID:05 "Engine coolant temperature" has degrees of Celsius as a measurement unit
  PERCENTAGE,             //PIDs:06-09 have degrees of percentage as a measurement unit 
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,             
  KPA,                   //PID:0A "Fuel pressure (gauge pressure)" has kPa as a measurement unit
  KPA,                   //PID:0B "	Intake manifold absolute pressure" with kPa
  RPM,
  KPH,
  DEGREES_BEFORE_TDC,
  DEGREES_CELCIUS,
  GRAMS_PER_SECOND,       //Mass Air Flow sensor (MAF)
  PERCENTAGE,             //Throttle position
  NULL,
  NULL,
  PERCENTAGE,             //PIDs 14-1B "Oxygen Sensor"
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  NULL,
  NULL,
  NULL,
  SECONDS,              //PID:1F "Run Time since engine start"
  NULL,
  KM,                   //PID:21 "Distance traveled with malfunction indicator lamp(MIL) on"
  KPA,                  //PID:22 "Fuel Rail Pressure(relative to manifold vacuum)"
  KPA,                  //PID:23 "Fuel Rail Gauge Pressure(diesel or gasoline direct injection)"
  RATIO,                //PID:24-2B "Oxygen Sensor1-8"
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,           //PID:2F "Fuel tank level input"
    COUNT,              //PID:30 "Warm-ups since codes cleared"
    KM,                 //PID:31 "Distance travelled since codes where cleared"
  PA,
  KPA,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  RATIO,
  DEGREES_CELCIUS,          //PID:3C-3F "Catalyst Converter Bank"
  DEGREES_CELCIUS,
  DEGREES_CELCIUS,
  DEGREES_CELCIUS,
  NULL,
  NULL,
  VOLTS,                    //PID:42 "Control Module Voltage"
  PERCENTAGE,               //PID:43 "Absolute load value"
  RATIO,
  PERCENTAGE,               //PID:45 "Relative Throttle position"
  DEGREES_CELCIUS,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  MINUTES,            //PID:4D "Time run with MIL on"
  MINUTES,            //PID:4E "Time since trouble codes cleared"
  NULL,
  GPS,
  NULL,
  PERCENTAGE,
  KPA,
  PA,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  PERCENTAGE,
  KPA,
  PERCENTAGE,       //PID:5A "Relative Accelerator Pedal Position"
  PERCENTAGE,
  DEGREES_CELCIUS,  //PID:5C "Engine Oil Temperature"
  DEGREES,          //PID:5D "Fuel Injection Timing"
  LPH,              //PID:5E "Engine Fuel Rate"
  NULL,
};

OBD2Class::OBD2Class() :
  _responseTimeout(OBD2_DEFAULT_TIMEOUT),
  _lastPidResponseMillis(0)

{
  memset(_supportedPids, 0x00, sizeof(_supportedPids));
      pinMode(DTC_BUTTON_PIN, INPUT_PULLUP); // Set the DTC button pin as input with internal pull-up

}

OBD2Class::~OBD2Class()
{
}



const uint32_t standardIds[] = {0x7E0, 0x7E1, 0x7E2};
const uint32_t extendedIds[] = {0x18DAF110, 0x18DAF118, 0x18DAF128};        //1st element: ECM module, 2nd element: TCM module, 3rd element: ABS module


//Final used function

int OBD2Class::begin() {
  // Initialize CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    return 0; // Initialization failed
  }

  // Clear supported PIDs array
  memset(_supportedPids, 0x00, sizeof(_supportedPids));
  _useExtendedAddressing = false;

  // Allow user to set preferred module
  setPreferredModule();

  // Attempt to communicate with the selected module
  if (supportedPidsRead()) {
    return 1; // Successfully read PIDs from the selected module
  }

  // If the preferred module fails, try the fallback logic
  // Reset and try standard addressing for the default ECM
  CAN.filter(0x7e8); // Set filter for standard address

  if (!supportedPidsRead()) {
    // Switch to extended addressing and try the selected module again
    _useExtendedAddressing = true;
    switch (_currentModule) {
      case 0:
        CAN.filterExtended(extendedIds[0]); // ECM
        break;
      case 1:
        CAN.filterExtended(extendedIds[1]); // TCM
        break;
      case 2:
        CAN.filterExtended(extendedIds[2]); // ABS
        break;
      default:
        CAN.filterExtended(extendedIds[0]); // Default to ECM if invalid
        break;
    }
    
    if (supportedPidsRead()) {
      return 1; // Successfully read PIDs from the extended module
    }
    
  }

  return 0; // No modules found
}



int OBD2Class::setPreferredModule() {
  Serial.println("Enter the module name (ECM, TCM, ABS):");
  
  // Wait for user input
  while (!Serial.available());
  String moduleInput = Serial.readStringUntil('\n'); // Read input until newline

  // Convert to uppercase for easier matching
  moduleInput.toUpperCase();

  if (moduleInput == "ECM" && CAN.filterExtended(0x18DAF110)) {
    _currentModule = 0;
    //_useExtendedAddressing = true; // Set extended addressing for ECM
     // Filter for ECM using extended ID
  } else if (moduleInput == "TCM") {
    _currentModule = 1;
   // _useExtendedAddressing = true; // Set extended addressing for TCM
    CAN.filterExtended(0x18DAF118); // Filter for TCM using extended ID
  } else if (moduleInput == "ABS") {
    _currentModule = 2;
   // _useExtendedAddressing = true; // Set extended addressing for ABS
    CAN.filterExtended(0x18DAF128); // Filter for ABS using extended ID
  } else {
    Serial.println("Invalid module name. Defaulting to ECM.");
    _currentModule = 0; // Default to ECM
   // _useExtendedAddressing = true; // Set extended addressing for ECM
    CAN.filterExtended(0x18DAF110); // Default filter for ECM using extended ID
  }

  return _currentModule; // Return the current module
}



void OBD2Class::end()
{
  CAN.end();
}

bool OBD2Class::pidSupported(uint8_t pid)
{
  if (pid == 0) {
    return true;
  }

  return (_supportedPids[(pid - 1) / 0x20] & ((1UL << (31 - ((pid - 1) % 32))))) ? true : false;
}

bool OBD2Class::pidValueRaw(uint8_t pid)
{
  switch(pid) {
    case PIDS_SUPPORT_01_20: // raw
    case MONITOR_STATUS_SINCE_DTCS_CLEARED: // raw
    case FREEZE_DTC: // raw
    case PIDS_SUPPORT_21_40: // raw
    case PIDS_SUPPORT_41_60: // raw
    case MONITOR_STATUS_THIS_DRIVE_CYCLE: // raw
    case FUEL_SYSTEM_STATUS: // raw
    case COMMANDED_SECONDARY_AIR_STATUS: // raw 
    case OBD_STANDARDS_THIS_VEHICLE_CONFORMS_TO: // raw
    case OXYGEN_SENSORS_PRESENT_IN_2_BANKS: // raw
    case OXYGEN_SENSORS_PRESENT_IN_4_BANKS: // raw
    case AUXILIARY_INPUT_STATUS: // raw
    case FUEL_TYPE: // raw
    case EMISSION_REQUIREMENT_TO_WHICH_VEHICLE_IS_DESIGNED: // raw
      return true;

    default:
      return (pid > 0x5f);
  }
}

//function to retrieve the name of a PID (Parameteter ID)
String OBD2Class::pidName(uint8_t pid)
{
    //if the PID is out of the expected range, return "Unknown"
  if (pid > 0x5f) {
    return "Unknown";
  }

#ifdef __AVR__
// Retrieve the PID name from program memory (PROGMEM) for AVR-based microcontrollers
  const char* pgmName = pgm_read_ptr(&PID_NAME_MAPPER[pid]);
  String name;

  //check if the retrieved pointer is valid
  if (pgmName != NULL) {
    while (char c = pgm_read_byte(pgmName++)) {
      name += c;
    }
  }

  return name;
#else
  // Directly return the PID name from the PID_NAME_MAPPER array for non-AVR architectures

  return PID_NAME_MAPPER[pid];
#endif
}

// Function to retrieve the units associated with a given PID

String OBD2Class::pidUnits(uint8_t pid)
{
  if (pid > 0x5f) {
    return "";
  }

#ifdef __AVR__
  const char* pgmUnits = pgm_read_ptr(&PID_UNIT_MAPPER[pid]);
  String units;

  if (pgmUnits != NULL) {
    while (char c = pgm_read_byte(pgmUnits++)) {
      units += c;
    }
  }

  return units;
#else
  return PID_UNIT_MAPPER[pid];
#endif
}

float OBD2Class::pidRead(uint8_t pid)
{
  if (!pidSupported(pid)) {
    return NAN;
  }
 // Define macro shortcuts for easier access to the response bytes

  #define A value[0]
  #define B value[1]
  #define C value[2]
  #define D value[3]
  uint8_t value[4]; // Array to store the response bytes from the vehicle


    // Attempt to read the PID data from Mode 01 (live data request)

  if (!pidRead(0x01, pid, &value, sizeof(value))) {
    return NAN;
  }


  //information was obtained from the website:https://en.wikipedia.org/wiki/OBD-II_PIDs
  switch (pid) {
    default:
    case PIDS_SUPPORT_01_20: // raw
    case MONITOR_STATUS_SINCE_DTCS_CLEARED: // raw
    case FREEZE_DTC: // raw
    case PIDS_SUPPORT_21_40: // raw
    case PIDS_SUPPORT_41_60: // raw
    case MONITOR_STATUS_THIS_DRIVE_CYCLE: // raw
      // NOTE: return value can lose precision!
      return ((uint32_t)A << 24 | (uint32_t)B << 16 | (uint32_t)C << 8 | (uint32_t)D);

      /*uint32_t: This specifies the resulting data type, which is a 32-bit unsigned integer.
       (uint32_t)A << 24: it shifts the bits in A 24 positions to the left.
       Since A likely holds an 8-bit value (1 byte), shifting it 24 positions effectively moves it to the leftmost byte positions in the resulting 32-bit integer*/

    case FUEL_SYSTEM_STATUS: // raw
    case DISTANCE_TRAVELED_WITH_MIL_ON:
    case DISTANCE_TRAVELED_SINCE_CODES_CLEARED:
    case TIME_RUN_WITH_MIL_ON:
    case TIME_SINCE_TROUBLE_CODES_CLEARED:
      return (A * 256.0 + B);


    case RUN_TIME_SINCE_ENGINE_START:
      return ((uint32_t)A << 8 | (uint32_t)B); // Return runtime in seconds

    case CALCULATED_ENGINE_LOAD:
    case THROTTLE_POSITION:
    case COMMANDED_EGR:
    case COMMANDED_EVAPORATIVE_PURGE:
    case FUEL_TANK_LEVEL_INPUT:
    case RELATIVE_THROTTLE_POSITION:
    case ABSOLUTE_THROTTLE_POSITION_B:
    case ABSOLUTE_THROTTLE_POSITION_C:
    case ABSOLUTE_THROTTLE_POSITION_D:
    case ABSOLUTE_THROTTLE_POSITION_E:
    case ABSOLUTE_THROTTLE_POSITION_F:
    case COMMANDED_THROTTLE_ACTUATOR:
    case ETHANOL_FUEL_PERCENTAGE:
    case RELATIVE_ACCELERATOR_PEDAL_POSITTION:
    case HYBRID_BATTERY_PACK_REMAINING_LIFE:
      return (A / 2.55);

    case COMMANDED_SECONDARY_AIR_STATUS: // raw
    case OBD_STANDARDS_THIS_VEHICLE_CONFORMS_TO: // raw
    case OXYGEN_SENSORS_PRESENT_IN_2_BANKS: // raw
    case OXYGEN_SENSORS_PRESENT_IN_4_BANKS: // raw
    case AUXILIARY_INPUT_STATUS: // raw
    case FUEL_TYPE: // raw
    case EMISSION_REQUIREMENT_TO_WHICH_VEHICLE_IS_DESIGNED: // raw
      return (A);

    case OXYGEN_SENSOR_1_SHORT_TERM_FUEL_TRIM:
    case OXYGEN_SENSOR_2_SHORT_TERM_FUEL_TRIM:
    case OXYGEN_SENSOR_3_SHORT_TERM_FUEL_TRIM:
    case OXYGEN_SENSOR_4_SHORT_TERM_FUEL_TRIM:
    case OXYGEN_SENSOR_5_SHORT_TERM_FUEL_TRIM:
    case OXYGEN_SENSOR_6_SHORT_TERM_FUEL_TRIM:
    case OXYGEN_SENSOR_7_SHORT_TERM_FUEL_TRIM:
    case OXYGEN_SENSOR_8_SHORT_TERM_FUEL_TRIM:
      return ((A - 128) / 1.28);
      break;

    case ENGINE_COOLANT_TEMPERATURE:
    case AIR_INTAKE_TEMPERATURE:
    case AMBIENT_AIR_TEMPERATURE:
    case ENGINE_OIL_TEMPERATURE:
      return (A - 40.0);

    case SHORT_TERM_FUEL_TRIM_BANK_1:
    case LONG_TERM_FUEL_TRIM_BANK_1:
    case SHORT_TERM_FUEL_TRIM_BANK_2:
    case LONG_TERM_FUEL_TRIM_BANK_2:
    case EGR_ERROR:
      return ((A / 1.28) - 100.0);

    case FUEL_PRESSURE:
      return (A * 3.0);

    case INTAKE_MANIFOLD_ABSOLUTE_PRESSURE:
    case VEHICLE_SPEED:
    case WARM_UPS_SINCE_CODES_CLEARED:
    case ABSOLULTE_BAROMETRIC_PRESSURE:
      return (A);

    case ENGINE_RPM:
      return ((A * 256.0 + B) / 4.0);

    case TIMING_ADVANCE:
      return ((A / 2.0) - 64.0);

    case MAF_AIR_FLOW_RATE:
      return ((A * 256.0 + B) / 100.0);

    case FUEL_RAIL_PRESSURE:
      return ((A * 256.0 + B) * 0.079);

    case FUEL_RAIL_GAUGE_PRESSURE:
    case FUEL_RAIL_ABSOLUTE_PRESSURE:
      return ((A * 256.0 + B) * 10.0);

    case OXYGEN_SENSOR_1_FUEL_AIR_EQUIVALENCE_RATIO:
    case OXYGEN_SENSOR_2_FUEL_AIR_EQUIVALENCE_RATIO:
    case OXYGEN_SENSOR_3_FUEL_AIR_EQUIVALENCE_RATIO:
    case OXYGEN_SENSOR_4_FUEL_AIR_EQUIVALENCE_RATIO:
    case OXYGEN_SENSOR_5_FUEL_AIR_EQUIVALENCE_RATIO:
    case OXYGEN_SENSOR_6_FUEL_AIR_EQUIVALENCE_RATIO:
    case OXYGEN_SENSOR_7_FUEL_AIR_EQUIVALENCE_RATIO:
    case OXYGEN_SENSOR_8_FUEL_AIR_EQUIVALENCE_RATIO:
    case 0x34:
    case 0x35:
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x39:
    case 0x3a:
    case 0x3b:
      return (((A * 256.0 + B) * 2.0) / 65536.0);

    case EVAP_SYSTEM_VAPOR_PRESSURE:
      return (((int16_t)(A * 256.0 + B)) / 4.0);

    case CATALYST_TEMPERATURE_BANK_1_SENSOR_1:
    case CATALYST_TEMPERATURE_BANK_2_SENSOR_1:
    case CATALYST_TEMPERATURE_BANK_1_SENSOR_2:
    case CATALYST_TEMPERATURE_BANK_2_SENSOR_2:
      return (((A * 256.0 + B) / 10.0) - 40.0);

    case CONTROL_MODULE_VOLTAGE:
      return ((A * 256.0 + B) / 1000.0);

    case ABSOLUTE_LOAD_VALUE:
      return ((A * 256.0 + B) / 2.55);

    case FUEL_AIR_COMMANDED_EQUIVALENCE_RATE:
      return (2.0 * (A * 256.0 + B) / 65536.0);

    case ABSOLUTE_EVAP_SYSTEM_VAPOR_PRESSURE:
      return ((A * 256.0 + B) / 200.0);

    case 0x54:
      return ((A * 256.0 + B) - 32767.0);

    case FUEL_INJECTION_TIMING:
      return (((A * 256.0 + B) / 128.0) - 210.0);

    case ENGINE_FUEL_RATE:
      return ((A * 256.0 + B) / 20.0);
  }
}

/* the function is pidRead,
0x09,0x02: these are the hex values which represent a specific PID code to be read
17: is the expected byte length*/

String OBD2Class::vinRead()
{
  char vin[18];

  memset(vin, 0x00, sizeof(vin));

  if (!pidRead(0x09, 0x02, vin, 17)) {  
    // failed
    return "";
  }

  return vin;
}

uint32_t OBD2Class::pidReadRaw(uint8_t pid)
{
  if (!pidSupported(pid)) {   //at first it checks if the  provided pid is supported .if it doesn't then it returns 0(failure)
    return 0;
  }

  #define A value[0]
  #define B value[1]
  #define C value[2]
  #define D value[3]
  uint8_t value[4];

  if (!pidRead(0x01, pid, &value, sizeof(value))) {
    return 0;
  }

  switch (pid) {
    case COMMANDED_SECONDARY_AIR_STATUS:
    case OBD_STANDARDS_THIS_VEHICLE_CONFORMS_TO:
    case OXYGEN_SENSORS_PRESENT_IN_2_BANKS:
    case OXYGEN_SENSORS_PRESENT_IN_4_BANKS:
    case AUXILIARY_INPUT_STATUS:
    case FUEL_TYPE:
    case EMISSION_REQUIREMENT_TO_WHICH_VEHICLE_IS_DESIGNED:
      return (A);

    case FUEL_SYSTEM_STATUS:
      return ((uint32_t)A << 8 | (uint32_t)B);

    default:
      return ((uint32_t)A << 24 | (uint32_t)B << 16 | (uint32_t)C << 8 | (uint32_t)D);    //the default case returns all 4 bytes (A,B,C,D) combined using left shifts, in order to create a 32-bit value from all four bytes
  }
}

String OBD2Class::ecuNameRead()
{
  char ecuName[21];

  memset(ecuName, 0x00, sizeof(ecuName));

  if (!pidRead(0x09, 0x0a, ecuName, 20)) {
    // Failed
    return "";
  }

  return ecuName;
}

void OBD2Class::setTimeout(unsigned long timeout)
{
  _responseTimeout = timeout;
}

int OBD2Class::supportedPidsRead()
{
  for (int pid = 0x00; pid < 0xe0; pid += 0x20) {
    uint8_t value[4];

    if (pidRead(0x01, pid, value, sizeof(value)) != 4) {
      return 0;
    }

    #define A value[0]
    #define B value[1]
    #define C value[2]
    #define D value[3]
    _supportedPids[pid / 0x20] = ((uint32_t)A << 24 | (uint32_t)B << 16 | (uint32_t)C << 8 | (uint32_t)D << 0);

    if ((_supportedPids[pid / 0x20] & 0x00000001) == 0x00000000) {
      // no more
      break;
    }
  }

  return 1;
}

int OBD2Class::clearAllStoredDTC()
{
    //Function which clears the Stored Diagnostic Trouble Codes (DTCs)

    // make sure at least 60 ms have passed since the last response
    unsigned long lastResponseDelta = millis() - _lastPidResponseMillis;
    if (lastResponseDelta < 60) {
        delay(60 - lastResponseDelta);
    }

    for (int retries = 10; retries > 0; retries--) {
        if (_useExtendedAddressing) {
            CAN.beginExtendedPacket(0x18db33f1, 8);
        } else {
            CAN.beginPacket(0x7df, 8);
        }
        CAN.write(0x01); // number of additional bytes
        CAN.write(0x04); // Mode / Service 4, for clearing DTC
        if (CAN.endPacket()) {
            // send success
            break;
        } else if (retries <= 1) {
            return 0;
        }
    }

    return 1;
}

int OBD2Class::pidRead(uint8_t mode, uint8_t pid, void* data, int length)
{
  // make sure at least 60 ms have passed since the last response
  unsigned long lastResponseDelta = millis() - _lastPidResponseMillis;
  if (lastResponseDelta < 60) {
    delay(60 - lastResponseDelta);
  }

  for (int retries = 10; retries > 0; retries--) {
    if (_useExtendedAddressing) {
      CAN.beginExtendedPacket(0x18db33f1, 8);
    } else {
      CAN.beginPacket(0x7df, 8);
    }
    CAN.write(0x02); // number of additional bytes
    CAN.write(mode);
    CAN.write(pid);
    if (CAN.endPacket()) {
      // send success
      break;
    } else if (retries <= 1) {
      return 0;
    }
  }

  bool splitResponse = (length > 5);

  for (unsigned long start = millis(); (millis() - start) < _responseTimeout;) {
    if (CAN.parsePacket() != 0 &&
          (splitResponse ? (CAN.read() == 0x10 && CAN.read()) : CAN.read()) &&
          (CAN.read() == (mode | 0x40) && CAN.read() == pid)) {

      _lastPidResponseMillis = millis();

      // got a response
      if (!splitResponse) {
        return CAN.readBytes((uint8_t*)data, length);
      }

      int read = CAN.readBytes((uint8_t*)data, 3);

      for (int i = 0; read < length; i++) {
        delay(60);

        // send the request for the next chunk
        if (_useExtendedAddressing) {
          CAN.beginExtendedPacket(0x18db33f1, 8);
        } else {
          CAN.beginPacket(0x7df, 8);
        }
        CAN.write(0x30);
        CAN.endPacket();

        // wait for response
        while (CAN.parsePacket() == 0 ||
               CAN.read() != (0x21 + i)); // correct sequence number

        while (CAN.available()) {
          ((uint8_t*)data)[read++] = CAN.read();
        }
      }

      _lastPidResponseMillis = millis();

      return read;
    }
  }

  return 0;
}


//Trying to receive DTC codes in raw form
int OBD2Class::testDTC(String* &dtcCodes) {
  Serial.println("Starting testDTC function...");

  // Read raw PID 0x03 (request for stored DTCs)
  uint32_t dtcData = pidReadRaw(0x02);

  // Check if the response is valid
  if (dtcData != 0) {
    Serial.println("PID read successful.");

    // Since DTC codes are typically 2 bytes each, break down the response into DTC codes
    int dtcCount = dtcData / 2; // Assuming dtcData contains 2-byte DTC codes
    Serial.print("Number of DTCs: ");
    Serial.println(dtcCount, DEC);

    // Allocate memory for storing the DTC codes
    dtcCodes = new String[dtcCount];
    Serial.println("Allocated memory for DTC codes.");

    // Process each DTC from the response
    for (int i = 0; i < dtcCount; i++) {
      // Extract the two bytes for each DTC code
      byte firstByte = (dtcData >> (8 * (2 * i))) & 0xFF;
      byte secondByte = (dtcData >> (8 * (2 * i + 1))) & 0xFF;

      Serial.print("Processing DTC bytes: ");
      Serial.print(firstByte, HEX);
      Serial.print(" ");
      Serial.println(secondByte, HEX);

      String dtcCode;

      // Identify the DTC category based on the first 2 bits of the first byte
      switch (firstByte >> 6) {
        case 0: dtcCode += "P"; break; // Powertrain
        case 1: dtcCode += "C"; break; // Chassis
        case 2: dtcCode += "B"; break; // Body
        case 3: dtcCode += "U"; break; // Network
      }

      // Construct the DTC code using the bits from the first and second bytes
      dtcCode += String((firstByte >> 4) & 0x03, DEC);  // Next two bits (binary to decimal)
      dtcCode += String(firstByte & 0x0F, HEX);         // Last four bits of the first byte (hex)
      dtcCode += String(secondByte >> 4, HEX);          // First four bits of the second byte (hex)
      dtcCode += String(secondByte & 0x0F, HEX);        // Last four bits of the second byte (hex)

      // Store the DTC code in the array
      dtcCodes[i] = dtcCode;

      Serial.print("DTC Code ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(dtcCode);
    }

    Serial.println("All DTC codes processed successfully.");
    return dtcCount; // Return the number of DTC codes found
  } else {
    Serial.println("PID read failed. No DTC codes found.");
  }

  return 0; // Return 0 if no DTC codes are found
}



//Testing DTC code 
// Read DTC codes
int OBD2Class::readDTC(uint16_t* dtcCodes, byte maxCodes) {
  Serial.println("Starting readDTC function...");

  // Send a request for service mode 07
  uint8_t mode = 0x07; // Service mode 07
  uint8_t pid = 0x00; // PID 00 (no specific PID required for service mode 07)

  // Make sure at least 60 ms have passed since the last response
  unsigned long lastResponseDelta = millis() - _lastPidResponseMillis;
  if (lastResponseDelta < 60) {
    delay(60 - lastResponseDelta);
  }

  for (int retries = 10; retries > 0; retries--) {
    if (_useExtendedAddressing) {
      CAN.beginExtendedPacket(0x18db33f1, 8);
    } else {
      CAN.beginPacket(0x7df, 8);
    }
    CAN.write(0x02); // Number of additional bytes
    CAN.write(mode);
    CAN.write(pid);
    if (CAN.endPacket()) {
      // Send success
      break;
    } else if (retries <= 1) {
      Serial.println("Failed to send DTC request");
      return 0;
    }
  }

  byte numDTCs = 0;

  for (unsigned long start = millis(); (millis() - start) < _responseTimeout;) {
     if (CAN.available() > 0) {
         Serial.println("Packet available, parsing...");
         int packetLength = CAN.parsePacket();
         Serial.print("Packet length: ");
      Serial.println(packetLength);
         if (packetLength != 0) {
            Serial.print("Received a CAN packet: ");
            for (int i = 0; i < packetLength; i++) {
            Serial.print(CAN.read(), HEX);
            Serial.print("waiting");
            Serial.print(" ");
      }
      Serial.println();

      //byte packetLength = CAN.parsePacket();
      Serial.print("Packet length: ");
      Serial.println(packetLength);

      byte* packetData = new byte[packetLength];
      CAN.readBytes(packetData, packetLength);

      Serial.print("Packet data: ");
      for (int i = 0; i < packetLength; i++) {
        Serial.print(packetData[i], HEX);
        Serial.print(" ");
      }
      Serial.println();

      if (numDTCs == 0) {
        Serial.println("No response received");
      }

      delete[] packetData;
    }
  }
  } //  if (CAN.available() > 0) ends here
  return numDTCs;
}

// Check MIL (Check Engine Light) status
int OBD2Class::isMILOn() {
    // Read the button status
    bool buttonStatus = digitalRead(DTC_BUTTON_PIN);

    // Print the raw value read from the DTC button pin
    Serial.print("Raw button value: ");
    Serial.println(buttonStatus);

    // Print the MIL status
    Serial.print("MIL status: ");
    
    // For pull-up configuration:
    if (buttonStatus == LOW) { // Check if the button is pressed
        Serial.println("Pressed");
        return LOW; // Return LOW when the button is pressed
    } else {
        Serial.println("Not pressed");
        return HIGH; // Return HIGH when the button is not pressed
    }
}


// Get the number of stored DTC codes
byte OBD2Class::getNumberOfDTCs() {
    // Ensure at least 60 ms have passed since the last response
    unsigned long lastResponseDelta = millis() - _lastPidResponseMillis;
    if (lastResponseDelta < 60) {
        delay(60 - lastResponseDelta);
    }

    // Check if PID 0x01 is supported
    if (!pidSupported(MONITOR_STATUS_SINCE_DTCS_CLEARED)) {
        Serial.println("PID 0x01 not supported.");
        return 0;
    }

    uint8_t value[4];
    if (pidRead(0x01, MONITOR_STATUS_SINCE_DTCS_CLEARED, &value, sizeof(value)) != 4) {
        Serial.println("Failed to read PID 0x01.");
        return 0;
    }

    _lastPidResponseMillis = millis();

    // Number of DTCs is in bits 0-6 of byte A
    byte numDTCs = value[0] & 0x7F;
    Serial.print("Number of DTCs: ");
    Serial.println(numDTCs);

    return numDTCs;
}


// Perform DTC check (blocking)
void OBD2Class ::performDTCCheck()
{
    Serial.println("Performing DTC check...");

    uint16_t dtcCodes[10]; // Adjust the array size as needed
    byte numDTCs = OBD2.readDTC(dtcCodes, 10);

    if (numDTCs > 0)
    {
        Serial.println("Current DTCs found: ");
        for (int i = 0; i < numDTCs; i++)
        {
            Serial.println(dtcCodes[i], HEX);
        }
        delay(10000); // Wait for 10 seconds
    }
    else
    {
        Serial.println("No DTC codes found.");
    }
}


//latest-working version- pidReadCustom function

int OBD2Class::pidReadCustom(uint8_t mode, uint8_t pid, void* data, int length) {
    // Ensure at least 60 ms have passed since the last response
    unsigned long lastResponseDelta = millis() - _lastPidResponseMillis;
    if (lastResponseDelta < 60) {
        delay(60 - lastResponseDelta);
    }


    Serial.println("Sending PID request...");
 
    sendPidRequest(mode, pid);  // Send the request and handle retries


     // Reset DTC variables before handling a new module
    int numDTCs = 0;  // Reset the DTC count for a fresh response


    // Check which module is currently connected and handle accordingly
    if (_currentModule == 0) {  // ECM module
        Serial.println("Connected to ECM module. Handling multiframe response...");
        // Implement multiframe handling logic specific to ECM here
        // For example, you might need to read multiple frames until the end of the response
    } else if (_currentModule == 1) {  // TCM module
        Serial.println("Connected to TCM module.");
        // Handle TCM response here if necessary
    } else if (_currentModule == 2) {  // ABS module
        Serial.println("Connected to ABS module.");
        // Handle ABS response here if necessary
    } else {
        Serial.println("Unknown module connected.");
    }

   
    // Wait for the response and parse it
    return waitForResponse(mode);
}



//latest-working version- sendPidRequest function
// Function to send the PID request

void OBD2Class::sendPidRequest(uint8_t mode, uint8_t pid) {
    // Try sending the CAN packet with retries
    for (int retries = 10; retries > 0; retries--) {
        Serial.print("Attempt ");
        Serial.println(11 - retries);

        if (_useExtendedAddressing) {
            Serial.println("Using extended addressing");
            CAN.beginExtendedPacket(0x18db33f1, 8);
        } else {
            Serial.println("Using standard addressing");
            CAN.beginPacket(0x7df, 8);
        }

        CAN.write(0x02);  // Number of additional bytes
        CAN.write(mode);  // Send the mode

        CAN.write(pid);  // Send the PID (if needed for the mode)

        if (CAN.endPacket()) {
            Serial.println("Packet sent successfully.");
            break;
        } else if (retries <= 1) {
            Serial.println("Failed to send packet after retries.");
            return;
        } else {
            Serial.println("Failed to send packet. Retrying...");
        }
    }
}


//waitForResponse function
//Final Completed/Tested Version
int OBD2Class::waitForResponse(uint8_t mode) {
    int numDTCs = 0;  // Initialize the number of DTCs to 0
    uint8_t receivedBytes[64];  // Buffer to store response
    int index = 0;

    // Wait for the response from the vehicle
    for (unsigned long start = millis(); (millis() - start) < _responseTimeout;) {
        if (CAN.parsePacket() != 0) {
            Serial.println("Received a CAN packet.");

            // Read the packet ID and capture the response data
            uint32_t packetId = CAN.packetId();
            index = 0;

            // Store initial bytes in receivedBytes
            while (CAN.available() && index < 64) {
                receivedBytes[index++] = CAN.read();
                Serial.print("Byte received: 0x");
                Serial.println(receivedBytes[index - 1], HEX);
            }
    

            // Check if it's a multi-frame message
            if (receivedBytes[0] == 0x10) { 
                // Handle Mode 03 multi-frame response
                if (receivedBytes[2] == 0x43 && mode == 0x03) {
                    int frameLength = receivedBytes[1] + 4; // Increase frame length to capture all DTCs
                    int read = index;  // Start read position from current index

                    // Process the initial data bytes already read
                    Serial.print("Initial multi-frame data: ");
                    for (int j = 0; j < read; j++) {
                        Serial.print("0x");
                        Serial.print(receivedBytes[j], HEX);
                        Serial.print(" ");
                    }
                    Serial.println();

                    // Request additional frames until all expected DTCs are received
                    while (read < frameLength) {
                        delay(60);  // Delay between requests to allow for CAN bus processing

                        // Send Flow Control frame (0x30) to request the next frame
                        if (_useExtendedAddressing) {
                            CAN.beginExtendedPacket(0x18db33f1, 8);
                        } else {
                            CAN.beginPacket(0x7df, 8);
                        }
                        CAN.write(0x30); // Flow control to request next frame
                        CAN.endPacket();

                        // Wait for the next sequence frame
                        unsigned long timeoutStart = millis();

                        while (CAN.parsePacket() == 0) {
                            if (millis() - timeoutStart > 1000) { // 1-second timeout
                                Serial.println("Timeout waiting for additional frame.");
                                return numDTCs; // Exit if timeout occurs
                            }
                        }

                        // Read the additional frame
                        while (CAN.available() && read < frameLength) {
                            receivedBytes[read++] = CAN.read();
                        }

                        // Print the newly received bytes
                        Serial.print("Received additional multi-frame: ");
                        for (int j = index; j < read; j++) {
                            Serial.print("0x");
                            Serial.print(receivedBytes[j], HEX);
                            Serial.print(" ");
                        }
                        Serial.println();
                        
                        index = read;  // Update index to the latest read position
                    }

                    // After all frames are received, parse the DTCs
                    _lastPidResponseMillis = millis();
                    numDTCs += parseDTCs(receivedBytes, read);  // Parse multi-frame DTCs
                }
                // Handle Mode 07 multi-frame response
                else if (receivedBytes[2] == 0x47 && mode == 0x07) {
                    int frameLength = receivedBytes[1]; // Use receivedBytes[1] for mode 07
                    int read = index;  // Start read position from current index

                    // Process the initial data bytes already read
                    Serial.print("Initial multi-frame data: ");
                    for (int j = 0; j < read; j++) {
                        Serial.print("0x");
                        Serial.print(receivedBytes[j], HEX);
                        Serial.print(" ");
                    }
                    Serial.println();

                    // Request additional frames until all expected DTCs are received
                    while (read < frameLength) {
                        delay(60);  // Delay between requests to allow for CAN bus processing

                        // Send Flow Control frame (0x30) to request the next frame
                        if (_useExtendedAddressing) {
                            CAN.beginExtendedPacket(0x18db33f1, 8);
                        } else {
                            CAN.beginPacket(0x7df, 8);
                        }
                        CAN.write(0x30); // Flow control to request next frame
                        CAN.endPacket();

                        // Wait for the next sequence frame
                        unsigned long timeoutStart = millis();

                        while (CAN.parsePacket() == 0) {
                            if (millis() - timeoutStart > 1000) { // 1-second timeout
                                Serial.println("Timeout waiting for additional frame.");
                                return numDTCs; // Exit if timeout occurs
                            }
                        }

                        // Read the additional frame
                        while (CAN.available() && read < frameLength) {
                            receivedBytes[read++] = CAN.read();
                        }

                        // Print the newly received bytes
                        Serial.print("Received additional multi-frame: ");
                        for (int j = index; j < read; j++) {
                            Serial.print("0x");
                            Serial.print(receivedBytes[j], HEX);
                            Serial.print(" ");
                        }
                        Serial.println();
                        
                        index = read;  // Update index to the latest read position
                    }

                    // After all frames are received, parse the DTCs
                    _lastPidResponseMillis = millis();
                    numDTCs += parseDTCs(receivedBytes, read);  // Parse multi-frame DTCs
                }
            }
            // For single-frame response
            else if ((receivedBytes[1] == 0x43 && mode == 0x03) || (receivedBytes[1] == 0x47 && mode == 0x07)) {
                Serial.println("Single-frame valid response received.");
                numDTCs += parseDTCs(receivedBytes, index);  // Parse single-frame DTCs
            } else {
                Serial.println("Invalid response.");
            }
        }
    }

    Serial.print("Total number of DTCs: ");
    Serial.println(numDTCs);
    return numDTCs;
}



//11_11_2024 Working for all the versions (Single Frame and Multiframe Messages)
int OBD2Class::parseDTCs(uint8_t* receivedBytes, int length) {
    Serial.print("Received frames: ");
    for (int i = 0; i < length; i++) {
        Serial.print("0x");
        Serial.print(receivedBytes[i], HEX);
        Serial.print(" ");
    }
    Serial.println();

    int numDTCs = 0;
    int dtcCount = (receivedBytes[0] == 0x10) ? receivedBytes[3] : receivedBytes[2];
    int dtcStartIndex = (receivedBytes[0] == 0x10) ? 4 : 3;

    for (int i = 0; i < dtcCount; i++) {
        int dtcIndex = dtcStartIndex + i * 2;

        // Check for frame indicator and adjust index if needed
        while (receivedBytes[dtcIndex] >= 0x20 && receivedBytes[dtcIndex] <= 0x2F) {
            dtcIndex++;  // Move past the frame header
            dtcStartIndex++;  // Update the start index for consistent pairing
            
        }

        // Parse DTC only if there’s enough data
        if (dtcIndex + 1 < length) {
            // Check if 0x22 is detected in the multiframe message
            if (receivedBytes[dtcIndex+1] == 0x22){
                // If detected use next byte instead (i.e., 0x43 0x0 instead of 0x43 )
                uint16_t dtcRaw = (receivedBytes[dtcIndex] << 8) | receivedBytes[dtcIndex + 2];
                char dtc[6];
                decodeDTC(dtcRaw, dtc);  // Decode the DTC to text format
                Serial.print("DTC: ");
                Serial.println(dtc);
                numDTCs++;
            } 
            else{
                uint16_t dtcRaw = (receivedBytes[dtcIndex] << 8) | receivedBytes[dtcIndex + 1];
                char dtc[6];
                decodeDTC(dtcRaw, dtc);  // Decode the DTC to text format
                Serial.print("DTC: ");
                Serial.println(dtc);
                numDTCs++;
            }
        } else {
            Serial.println("Not enough data for additional DTCs.");
            break;
        }
    }
    return numDTCs;
}




//Latest-Working Version
// Function to decode a raw DTC into a string
void OBD2Class::decodeDTC(uint16_t dtcRaw, char* dtc) {
                                                                        // Decode the DTC category from the first two bits
    char dtcCategory = 'P';  // Default to powertrain
    switch ((dtcRaw & 0xC000) >> 14) {
        case 0x00: dtcCategory = 'P'; break;  // Powertrain
        case 0x01: dtcCategory = 'C'; break;  // Chassis
        case 0x02: dtcCategory = 'B'; break;  // Body
        case 0x03: dtcCategory = 'U'; break;  // Network
    }

    // Extract the DTC number (14 bits)
    uint16_t dtcNumber = dtcRaw & 0x3FFF;

    // Print the DTC in the format "PXXXX"
    sprintf(dtc, "%c%04X", dtcCategory, dtcNumber);
}


 int OBD2Class::getDTC(void* data,int length){
    //Serial.println("Enter the module name (ECM, TCM, ABS):");
        
        Serial.print("Preferred Mode:");  // Prints a newline

         while (true) {
        if (Serial.available() > 0) {
            break;  // Exit loop when input is available
        }
    }
          
    String modeInput = Serial.readStringUntil('\n'); // Read user's input until newline

   
    if (modeInput == "03") {
        int result = pidReadCustom(0x03,0x00,data,length);                                     //If the preferred mode is 03 then we send mode 0x03 to pidReadCustom
        Serial.println("Selected Mode 03 (Stored DTCs).");
        Serial.print("Result: ");
        Serial.println(result);  // Check how many bytes are being returned
        return result;
    } else if (modeInput == "07") {
        int result = pidReadCustom(0x07,0x00,data,length);                                     //If the preferred mode is 07 then we send mode 0x07 to pidReadCustom
        Serial.println("Selected Mode 07 (Pending DTCs).");
        Serial.print("Result: ");
        Serial.println(result);  // Check how many bytes are being returned
        return result;
    } 

}




//switch between several avaliable ECU modules which the Ozen Elektronik simulator provides 

void OBD2Class::setEcuModule(const char* moduleId) {
  Serial.print("Setting ECU module to: ");
  Serial.println(moduleId);

  if (strcmp(moduleId, "ECM") == 0) {
    Serial.println("ECM selected");
    _useExtendedAddressing = false;
    if (!CAN.filter(0x7e0)) {
      Serial.println("Error setting ECM filter");
    }
  } else if (strcmp(moduleId, "TCM") == 0) {
    Serial.println("TCM selected");
    _useExtendedAddressing = false;
    if (!CAN.filter(0x7e1)) {
      Serial.println("Error setting TCM filter");
    }
  } else if (strcmp(moduleId, "ABS") == 0) {
    Serial.println("ABS selected");
    _useExtendedAddressing = false;
    if (!CAN.filter(0x7e2)) {
      Serial.println("Error setting ABS filter");
    }
  } else if (strcmp(moduleId, "EXT_ECM") == 0) {
    Serial.println("EXT_ECM selected");
    _useExtendedAddressing = true;
    if (!CAN.filterExtended(0x18daf110)) {
      Serial.println("Error setting EXT_ECM filter");
    }
  } else if (strcmp(moduleId, "EXT_TCM") == 0) {
    Serial.println("EXT_TCM selected");
    _useExtendedAddressing = true;
    if (!CAN.filterExtended(0x18daf118)) {
      Serial.println("Error setting EXT_TCM filter");
    }
  } else if (strcmp(moduleId, "EXT_ABS") == 0) {
    Serial.println("EXT_ABS selected");
    _useExtendedAddressing = true;
    if (!CAN.filterExtended(0x18daf128)) {
      Serial.println("Error setting EXT_ABS filter");
    }
  } else {
    Serial.println("Invalid module identifier");
  }

  Serial.print("Extended addressing: ");
  Serial.println(_useExtendedAddressing);
}



//detection of ecu module
EcuModule OBD2Class::detectEcuModule() {
  if (CAN.parsePacket()) {  // Only proceed if a packet is available
    uint32_t receivedId = CAN.packetId();  // Capture the received CAN identifier
    Serial.print("Received CAN ID: 0x");
    Serial.println(receivedId, HEX);  // Print the received CAN ID

    if (receivedId == 0x7E0) {
      Serial.println("Module is ECM");
      _useExtendedAddressing = (receivedId == 0x10);  // Set addressing type
      return ECM;
    } else if (receivedId == 0x7E1) {
      Serial.println("Module is TCM");
      _useExtendedAddressing = (receivedId == 0x18);  // Set addressing type
      return TCM;
    } else if (receivedId == 0x7E2) {
      Serial.println("Module is ABS");
      _useExtendedAddressing = (receivedId == 0x28);  // Set addressing type
      return ABS;
    } else {
      Serial.println("Unknown module");
      return UNKNOWN;
    }
  }

  // No valid CAN packet received
  Serial.println("No CAN packet available.");
  return UNKNOWN;
}



OBD2Class OBD2;             //OBD2 Class is terminated here