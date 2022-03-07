# pragma once
#include <stdio.h>
#include "elevator.h"

typedef struct {
    int numRequest;
    int Database[N_BUTTONS][N_FLOORS];
} Request;

Request requestManager;

void initRequestManager();
void printRequestManager();
void pollElevatorButtons();
void getNewRequest();
void checkRequestInDirection();
void deleteRequestsOnFloor();
void deleteAllRequests();
