# pragma once
#include "elevio.h"
#include <stdio.h>

typedef struct {
    int numRequest;
    int Database[N_BUTTONS][N_FLOORS];
} Request;

Request initRequestDatabase();
void updateRequests(Request* database);
void updateNrRequests(Request* database);
//int isRequest();
int getRequest(int elevatorFloor,int dir, int database[N_BUTTONS][N_FLOORS]);
int getRequestInDIrection(int elevatorFloor, MotorDirection dir, int currentRequest, int database[N_BUTTONS][N_FLOORS]);
//void addRequest();
void deleteRequest(int floor, Request* database);
void deleteAllRequests(Request* database);