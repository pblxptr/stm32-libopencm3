#pragma once 

#define DEFAULT_MSG 0

#define GET_GPS_BUFFER_REQ 1
#define GET_GPS_BUFFER_CFM 2 

#define SET_MAINTENANCE_MODE_REQ 3 
#define SET_MAINTENANCE_MODE_CFM 4

#define TOTAL_MESSAGES 4

typedef struct _msg_header_ {
    uint8_t msg_number;
} msg_header;

