# pragma once
#include <stdio.h>
#include "elevator.h"
#include "elevio.h"

typedef struct {
    int numRequest;
    int Database[N_BUTTONS][N_FLOORS];
} Request;

Request requestManager;

void initRequestManager();
void printRequestManager();
void pollElevatorButtons();
void updateNrRequests();
void getRequest();
void getRequestInDIrection();
void deleteRequest();
void deleteAllRequests();