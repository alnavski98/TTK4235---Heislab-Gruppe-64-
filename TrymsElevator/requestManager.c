#include "requestManager.h"


Request initRequestDatabase(){

    Request requestDatabase;
    requestDatabase.numRequest = 0;

    for(int b = 0; b < N_BUTTONS; b++){
        for(int f = 0; f < N_FLOORS; f++){
            requestDatabase.Database[b][f] = 0;
        }
    }

    return requestDatabase;
}

void updateRequests(Request* requestDatabase){
    //printf("Updating requests");
    // Check for requests.
    for(int f = 0; f < N_FLOORS; f++){ // Loops through all the buttons if they are pressed?
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            // Add the pressed button/floor to the database
            if (btnPressed){
                elevio_buttonLamp(f, b, 1);
                requestDatabase->Database[b][f] = 1;
            }
        }
    }
}

void updateNrRequests(Request* database){
    int counter = 0;
    for(int f = 0; f < N_FLOORS; f++){ // Loops through all the buttons if they are pressed?
        for(int b = 0; b < N_BUTTONS; b++){
            if (database->Database[b][f] == 1){  
                counter += 1;
            }
        }
    }
    database->numRequest = counter;
}

int getRequest(int elevatorFloor, int dir, int database[N_BUTTONS][N_FLOORS]){
    if(dir == DIRN_STOP){
        // Request on floor: 
        for(int b = 0; b<N_BUTTONS; b++){
            if(database[b][elevatorFloor] == 1){
                return elevatorFloor;
            }
        }

        // Request above or below
        if(elevatorFloor < 2){
            for(int f = N_FLOORS-1; f >= 0; f--){ 
                for(int b = 0; b < N_BUTTONS; b++){
                    if (database[b][f] == 1){
                        return f;
                    }
                }
            }
        }else if(elevatorFloor >= 2){
            for(int f = 0; f < N_FLOORS; f++){ 
                for(int b = 0; b < N_BUTTONS; b++){
                    if (database[b][f] == 1){
                        return f;
                    }
                }
            }
        }
    }
}


int getRequestInDIrection(int elevatorFloor, MotorDirection dir, int currentRequest, int database[N_BUTTONS][N_FLOORS]){

    if(dir == DIRN_UP){
        if((currentRequest - elevatorFloor)>1){
            for(int b = 0; b < N_BUTTONS; b++){
                if (database[b][elevatorFloor+1] == 1){
                    return elevatorFloor+1;
                }
            }
        }
    }else if(dir == DIRN_DOWN){
        if((elevatorFloor-currentRequest) >1){
            for(int b = 0; b < N_BUTTONS; b++){
                if (database[b][elevatorFloor-1] == 1){
                    return elevatorFloor-1;
                }
            }
        }
    }
    return -1;
}


void deleteRequest(int floor, Request* database){
    for(int b = 0; b < N_BUTTONS; b++){
        if(database->Database[b][floor] == 1){
            elevio_buttonLamp(floor, b, 0);
            database->Database[b][floor] = 0;
            database->numRequest -=1;
        }
    }
}



void deleteAllRequests(Request* database){
    database->numRequest = 0;
    for(int b = 0; b < N_BUTTONS; b++){
        for(int f = 0; f < N_FLOORS; f++){
            database->Database[b][f] = 0;
            elevio_buttonLamp(f, b, 0);
        }
    }
}