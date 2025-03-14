#ifndef DTC_CODES_H
#define DTC_CODES_H

#include <stdint.h>

// Define the structure for a DTC code
typedef struct {
    uint8_t highByte;
    uint8_t lowByte;
    const char* description;
} dtc_code_t;

// Define the array of DTC codes
extern const dtc_code_t dtc_codes[];

// Function to get the description of a DTC code
const char* get_dtc_description(uint16_t code);

#endif  // DTC_CODES_H