#include "requestManager.h"

void initRequestManager(){
    printf("Database initiating \n");
    requestManager.numRequest = 0;
    for(int b = 0; b < N_BUTTONS; b++){
        for(int f = 0; f < N_FLOORS; f++){
            requestManager.Database[b][f] = 0;
        }
    }
}

void printRequestManager(){
    printf("\n");
    printf("Request database:\n");
    printf("+-------------------------------+\n");
    printf("|                               |\n");
    printf("| Floor     |   0   1   2   3   |\n");
    printf("+-------------------------------+\n");
    printf("| Hall up   |   %d   %d   %d   %d   |\n", requestManager.Database[0][0], requestManager.Database[0][1], requestManager.Database[0][2], requestManager.Database[0][3]);
    printf("| Hall down |   %d   %d   %d   %d   |\n", requestManager.Database[1][0], requestManager.Database[1][1], requestManager.Database[1][2], requestManager.Database[1][3]);
    printf("| Cab       |   %d   %d   %d   %d   |\n", requestManager.Database[2][0], requestManager.Database[2][1], requestManager.Database[2][2], requestManager.Database[2][3]);
    printf("+-------------------------------+\n");
    printf("\n");
}


void pollElevatorButtons(){
    // Check for requests.
    for(int f = 0; f < N_FLOORS; f++){ 
        for(int b = 0; b < N_BUTTONS; b++){
            int btnPressed = elevio_callButton(f, b);
            if (btnPressed){
                elevio_buttonLamp(f, b, 1);
                requestManager.Database[b][f] = 1;
            }
        }
    }
}

void updateNrRequests(){
    int counter = 0;
    for(int f = 0; f < N_FLOORS; f++){ // Loops through all the buttons if they are pressed?
        for(int b = 0; b < N_BUTTONS; b++){
            if (requestManager.Database[b][f] == 1){  
                counter += 1;
            }
        }
    }
    requestManager.numRequest = counter;
}


void getRequest(){
    if(requestManager.numRequest >= 1 && elev.currentFloorRequest == -1){
        printf("Getting new request \n");
        if(elev.Dir[1] == DIRN_STOP){
            // Request on floor: 
            for(int b = 0; b<N_BUTTONS; b++){
                if(requestManager.Database[b][elev.Floor] == 1){
                    elev.currentFloorRequest = elev.Floor;
                    return;
                }
            }

            // Request above or below
            if(elev.Floor < 2){
                for(int f = N_FLOORS-1; f >= 0; f--){ 
                    for(int b = 0; b < N_BUTTONS; b++){
                        if (requestManager.Database[b][f] == 1){
                            elev.currentFloorRequest = f;
                            return;
                        }
                    }
                }
            }else if(elev.Floor >= 2){
                for(int f = 0; f < N_FLOORS; f++){ 
                    for(int b = 0; b < N_BUTTONS; b++){
                        if (requestManager.Database[b][f] == 1){
                            elev.currentFloorRequest = f;
                            return;
                        }
                    }
                }
            }
        }
        printf("Requested floor = %d \n", elev.currentFloorRequest);
    }
}


void getRequestInDIrection(){
    if(requestManager.numRequest >= 1 && elev.requestInDIr == -1){
        if(elev.Dir[1] == DIRN_UP){
            if((elev.currentFloorRequest - elev.Floor)>1){
                for(int b = 0; b < N_BUTTONS; b++){
                    if (requestManager.Database[b][elev.Floor+1] == 1){
                        elev.requestInDIr = elev.Floor + 1;
                        return;
                    }
                }
            }
        }else if(elev.Dir[1] == DIRN_DOWN){
            if((elev.Floor-elev.currentFloorRequest) >1){
                for(int b = 0; b < N_BUTTONS; b++){
                    if (requestManager.Database[b][elev.Floor-1] == 1){
                        elev.requestInDIr = elev.Floor - 1;
                        return;
                    }
                }
            }
        }
    }
}


void deleteRequest(){
    for(int b = 0; b < N_BUTTONS; b++){
        if(requestManager.Database[b][elev.Floor] == 1){
            elevio_buttonLamp(elev.Floor, b, 0);
            requestManager.Database[b][elev.Floor] = 0;
            requestManager.numRequest -= 1;
        }
    }
}



void deleteAllRequests(){
    requestManager.numRequest = 0;
    for(int b = 0; b < N_BUTTONS; b++){
        for(int f = 0; f < N_FLOORS; f++){
            requestManager.Database[b][f] = 0;
            elevio_buttonLamp(f, b, 0);
        }
    }
    elev.currentFloorRequest = -1;
    elev.requestInDIr = -1;
}