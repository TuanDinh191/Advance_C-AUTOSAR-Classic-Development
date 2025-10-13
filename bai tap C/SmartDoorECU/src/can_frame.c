#include "../include/can_frame.h"
#include "stdint.h"

#define num_doors  4

void packDoorStatus(Door* doors, CANFrame_t* frame)
{
    printf("Pack Frame of Door Status:\n");
    for (int i = 0; i< num_doors; ++i)
    {
        frame->bytes[i] = doors[i].statusUnion.byte;
        printf("Door %d:  %02X\n", i+1, frame->bytes[i]);
    }
}

void unpackDoorStatus(CANFrame_t* frame, Door* doors)
{
    printf("Unpacked frame of Door Status:\n");
    for (int i =0; i<num_doors; ++i)
    {
        doors[i].statusUnion.byte = frame->bytes[i];
        printf("Door %d:  %02X\n", i+1, doors[i].statusUnion.byte);
    }
}