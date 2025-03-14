#ifndef OBD2_H
#define OBD2_H

#define OBD_TIMEOUT_SHORT 1000




#include <Arduino.h>
enum {
  PIDS_SUPPORT_01_20                                = 0x00,
  MONITOR_STATUS_SINCE_DTCS_CLEARED                 = 0x01,
  FREEZE_DTC                                        = 0x02,
  FUEL_SYSTEM_STATUS                                = 0x03,
  CALCULATED_ENGINE_LOAD                            = 0x04,
  ENGINE_COOLANT_TEMPERATURE                        = 0x05,
  SHORT_TERM_FUEL_TRIM_BANK_1                       = 0x06,
  LONG_TERM_FUEL_TRIM_BANK_1                        = 0x07,
  SHORT_TERM_FUEL_TRIM_BANK_2                       = 0x08,
  LONG_TERM_FUEL_TRIM_BANK_2                        = 0x09,
  FUEL_PRESSURE                                     = 0x0a,
  INTAKE_MANIFOLD_ABSOLUTE_PRESSURE                 = 0x0b,
  ENGINE_RPM                                        = 0x0c,
  VEHICLE_SPEED                                     = 0x0d,
  TIMING_ADVANCE                                    = 0x0e,
  AIR_INTAKE_TEMPERATURE                            = 0x0f,
  MAF_AIR_FLOW_RATE                                 = 0x10,
  THROTTLE_POSITION                                 = 0x11,
  COMMANDED_SECONDARY_AIR_STATUS                    = 0x12,
  OXYGEN_SENSORS_PRESENT_IN_2_BANKS                 = 0x13,
  OXYGEN_SENSOR_1_SHORT_TERM_FUEL_TRIM              = 0x14,
  OXYGEN_SENSOR_2_SHORT_TERM_FUEL_TRIM              = 0x15,
  OXYGEN_SENSOR_3_SHORT_TERM_FUEL_TRIM              = 0x16,
  OXYGEN_SENSOR_4_SHORT_TERM_FUEL_TRIM              = 0x17,
  OXYGEN_SENSOR_5_SHORT_TERM_FUEL_TRIM              = 0x18,
  OXYGEN_SENSOR_6_SHORT_TERM_FUEL_TRIM              = 0x19,
  OXYGEN_SENSOR_7_SHORT_TERM_FUEL_TRIM              = 0x1a,
  OXYGEN_SENSOR_8_SHORT_TERM_FUEL_TRIM              = 0x1b,
  OBD_STANDARDS_THIS_VEHICLE_CONFORMS_TO            = 0x1c,
  OXYGEN_SENSORS_PRESENT_IN_4_BANKS                 = 0x1d,
  AUXILIARY_INPUT_STATUS                            = 0x1e,
  RUN_TIME_SINCE_ENGINE_START                       = 0x1f,

  PIDS_SUPPORT_21_40                                = 0x20,
  DISTANCE_TRAVELED_WITH_MIL_ON                     = 0x21,
  FUEL_RAIL_PRESSURE                                = 0x22,
  FUEL_RAIL_GAUGE_PRESSURE                          = 0x23,
  OXYGEN_SENSOR_1_FUEL_AIR_EQUIVALENCE_RATIO        = 0x24,
  OXYGEN_SENSOR_2_FUEL_AIR_EQUIVALENCE_RATIO        = 0x25,
  OXYGEN_SENSOR_3_FUEL_AIR_EQUIVALENCE_RATIO        = 0x26,
  OXYGEN_SENSOR_4_FUEL_AIR_EQUIVALENCE_RATIO        = 0x27,
  OXYGEN_SENSOR_5_FUEL_AIR_EQUIVALENCE_RATIO        = 0x28,
  OXYGEN_SENSOR_6_FUEL_AIR_EQUIVALENCE_RATIO        = 0x29,
  OXYGEN_SENSOR_7_FUEL_AIR_EQUIVALENCE_RATIO        = 0x2a,
  OXYGEN_SENSOR_8_FUEL_AIR_EQUIVALENCE_RATIO        = 0x2b,
  COMMANDED_EGR                                     = 0x2c,
  EGR_ERROR                                         = 0x2d,
  COMMANDED_EVAPORATIVE_PURGE                       = 0x2e,
  FUEL_TANK_LEVEL_INPUT                             = 0x2f,
  WARM_UPS_SINCE_CODES_CLEARED                      = 0x30,
  DISTANCE_TRAVELED_SINCE_CODES_CLEARED             = 0x31,
  EVAP_SYSTEM_VAPOR_PRESSURE                        = 0x32,
  ABSOLULTE_BAROMETRIC_PRESSURE                     = 0x33,
/*OXYGEN_SENSOR_1_FUEL_AIR_EQUIVALENCE_RATIO        = 0x34,
  OXYGEN_SENSOR_2_FUEL_AIR_EQUIVALENCE_RATIO        = 0x35,
  OXYGEN_SENSOR_3_FUEL_AIR_EQUIVALENCE_RATIO        = 0x36,
  OXYGEN_SENSOR_4_FUEL_AIR_EQUIVALENCE_RATIO        = 0x37,
  OXYGEN_SENSOR_5_FUEL_AIR_EQUIVALENCE_RATIO        = 0x38,
  OXYGEN_SENSOR_6_FUEL_AIR_EQUIVALENCE_RATIO        = 0x39,
  OXYGEN_SENSOR_7_FUEL_AIR_EQUIVALENCE_RATIO        = 0x3a,
  OXYGEN_SENSOR_8_FUEL_AIR_EQUIVALENCE_RATIO        = 0x3b,*/
  CATALYST_TEMPERATURE_BANK_1_SENSOR_1              = 0x3c,
  CATALYST_TEMPERATURE_BANK_2_SENSOR_1              = 0x3d,
  CATALYST_TEMPERATURE_BANK_1_SENSOR_2              = 0x3e,
  CATALYST_TEMPERATURE_BANK_2_SENSOR_2              = 0x3f,

  PIDS_SUPPORT_41_60                                = 0x40,
  MONITOR_STATUS_THIS_DRIVE_CYCLE                   = 0x41,
  CONTROL_MODULE_VOLTAGE                            = 0x42,
  ABSOLUTE_LOAD_VALUE                               = 0x43,
  FUEL_AIR_COMMANDED_EQUIVALENCE_RATE               = 0x44,
  RELATIVE_THROTTLE_POSITION                        = 0x45,
  AMBIENT_AIR_TEMPERATURE                           = 0x46,
  ABSOLUTE_THROTTLE_POSITION_B                      = 0x47,
  ABSOLUTE_THROTTLE_POSITION_C                      = 0x48,
  ABSOLUTE_THROTTLE_POSITION_D                      = 0x49,
  ABSOLUTE_THROTTLE_POSITION_E                      = 0x4a,
  ABSOLUTE_THROTTLE_POSITION_F                      = 0x4b,
  COMMANDED_THROTTLE_ACTUATOR                       = 0x4c,
  TIME_RUN_WITH_MIL_ON                              = 0x4d,
  TIME_SINCE_TROUBLE_CODES_CLEARED                  = 0x4e,
/*                                                  = 0x4f,
                                                    = 0x50,*/
  FUEL_TYPE                                         = 0x51,
  ETHANOL_FUEL_PERCENTAGE                           = 0x52,
  ABSOLUTE_EVAP_SYSTEM_VAPOR_PRESSURE               = 0x53,
/*EVAP_SYSTEM_VAPOR_PRESSURE                        = 0x54,*/
/*                                                  = 0x55,
                                                    = 0x56,
                                                    = 0x57,
                                                    = 0x58,*/
  FUEL_RAIL_ABSOLUTE_PRESSURE                       = 0x59,
  RELATIVE_ACCELERATOR_PEDAL_POSITTION              = 0x5a,
  HYBRID_BATTERY_PACK_REMAINING_LIFE                = 0x5b,
  ENGINE_OIL_TEMPERATURE                            = 0x5c,
  FUEL_INJECTION_TIMING                             = 0x5d,
  ENGINE_FUEL_RATE                                  = 0x5e,
  EMISSION_REQUIREMENT_TO_WHICH_VEHICLE_IS_DESIGNED = 0x5f,

  //PIDs added from: https://en.wikipedia.org/wiki/OBD-II_PIDs
};



enum EcuModule {
  ECM,
  TCM,
  ABS,
  EXT_ECM,
  EXT_TCM,
  EXT_ABS,
  UNKNOWN
};


// default timeout for a response in milliseconds
#define OBD2_DEFAULT_TIMEOUT 2000


class OBD2Class {
public:

  OBD2Class();
        

      
  virtual ~OBD2Class();   //The virtual keyword indicates it can be overridden by subclasses if needed

  int begin();    //it starts the communication with the OBD-II system and sets up the connection. Also, it returns an integer
  int _currentModule;

  void end();     // this method stops communication with the OBD-II system and cleans up resources
  
  int clearAllStoredDTC();    //attempts to clear all the stored Diagnostic Trouble Codes (DTCs) from the vehicle/simulator and returns an integer
  void performDTCCheck();              // Perform DTC check (blocking)
  void checkMILStatus(); 


  uint8_t getNumberOfDTCs();
 int isMILOn();


  // Read DTC codes
  int readDTC(uint16_t* dtcCodes, byte maxCodes);



  bool pidSupported(uint8_t pid);     //checks if a specific OBD-II parameter ID (PID) is supported by the vehicle. It takes a uint8_t (unsigned 8-bit integer) representing the PID and returns a bool (true if supported, false otherwise)
  bool pidValueRaw(uint8_t pid);      //checks if a raw value is available for a specific PID. It takes a uint8_t PID and returns a bool (true if raw value available, false otherwise) 
  String pidName(uint8_t pid);        //it retrieves a readable name for a specific PID. it takes a uint8_t PID and returns a bool 
  String pidUnits(uint8_t pid);       //it retrieves the units associated with a specific PID (for example., grams, volts)

  float pidRead(uint8_t pid);         //reads the actual value for a specific PID as a floating-point number
  uint32_t pidReadRaw(uint8_t pid);   //reads the raw value for a specific PID as a 32-bit unsigned integer. takes a uint8_t PID and returns a uint32_t with the raw value

  String vinRead();       //reads the Vehicle Identification Number (VIN) of the vehicle and returns it as a String
  String ecuNameRead();   //reads the name of the Engine Control Unit (ECU) and returns it as a String

  void setTimeout(unsigned long timeout);   //it sets a timeout value in milliseconds for communication with the OBD-II.takes an unsigned long (large unsigned integer) representing the timeout.

  int testDTC(String* &dtcCodes);
    int pidReadCustom(uint8_t mode, uint8_t pid, void* data, int length);
  int getDTC(void* data,int length);

  void setEcuModule(const char* moduleId); //trying to detect which ecm module the emulator uses
  EcuModule detectEcuModule(); 






    void setCurrentModuleName(int moduleId);
    int selectModule();

    int setPreferredModule();


    void sendPidRequest(uint8_t mode, uint8_t pid);
    int waitForResponse(uint8_t mode);
    int parseDTCs(uint8_t* receivedBytes, int length);


int waitForAdditionalPackets();
   void decodeDTC(uint16_t dtcRaw, char* dtc);
   void handleMultiFrameResponse();


private:          //not accessible methods, used in order to support the public methods 

  int supportedPidsRead();      //reads the supported PIDs from the vehicle

  int pidRead(uint8_t mode, uint8_t pid, void* data, int length);   //it is the core function for reading OBDII Data. takes additional parameters such as mode (which specifies the type of data to read), and also use a buffer to store the data

  const int DTC_BUTTON_PIN = 11; // Pin where the DTC button is connected
  
  uint8_t milStatus;                   // MIL status variable
  uint8_t numCodes;                    // Number of DTC codes
private:
  unsigned long _responseTimeout;       //stores the timeout value (in mseconds) waiting for a response from the OBD-II system after sending a command. This timeout prevent the  program from getting stuck waiting for a response that may never come  
  bool _useExtendedAddressing;          //a boolean flag which indicates whether the class should use extended addressing mode when communicating with the OBDII (standard or extended)
  unsigned long _lastPidResponseMillis;  //stores a timestamp (in mseconds) of the last time a valid response was received for a PID request
  uint32_t _supportedPids[32];            //is an array of 32 uint32_t elements. it stores the list of the PIDs supported by the current vehicle
    


   void sendFlowControlFrame();



 
    uint16_t hex2uint16(const char* str);
};

extern OBD2Class OBD2;      //declares an external instance of the OBD2Class named OBD2. allows other parts of the program to access this specific OBD-II interface

#endif    //marks the end of an ifdef