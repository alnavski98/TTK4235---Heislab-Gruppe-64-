# include "stateMachine.h"

// gjort
// We should define global variables instead of sending them into functions. This is how data is handled in c so we should do it like that. 
// Lage køsystem


// To do
// Printe på gode tidspunkt
// Lage actions -> det å gå mellom statsene som egne funksjoner
// Add one state
// Change to names that is more describing. Make functions for each state in stateMachine and run it in main. Makes is more clear? 
// Make more utilities functions. Polling button and floor sensor. 

void stateUNDEFINED(){
    //Find floor, direction and go to IDLE. 
    while(1){
        // waiting for a defined floor reached.
        if (elevio_floorSensor() == -1){
            move(DIRN_DOWN);
            elev.Dir = DIRN_DOWN;
        }else{
            stopElevator();
            elev.Dir = DIRN_STOP;
            break;
        }
    }
    int Floor = elevio_floorSensor();
    elev.Floor = Floor;
    elevio_floorIndicator(Floor);
    elev.State = IDLE;

    printf("State defined! \n");
    printElevatorState();
}

void stateIDLE(){
    // Check stop button
    pollStopButton();

    // Check requests
    if(elev.currentFloorRequest != -1){
        if( checkIfOnFloor(elev.currentFloorRequest)){
            stopElevator();
            elev.Dir = DIRN_STOP;

            openDoor();
            elev.State = DOOROPEN;

            deleteRequest();
            elev.currentFloorRequest = -1;

            start = startTimer();
        }else if(requestIsAbove()){
            move(DIRN_UP);
            elev.State = MOVING;
            elev.Dir = DIRN_UP;
        }else{
            move(DIRN_DOWN);
            elev.State = MOVING;
            elev.Dir = DIRN_DOWN;
        }
        printElevatorState();
        printRequestDatabase();
    }
}

void stateMOVING(){
    //Check stop button
    pollStopButton();

    // Check for request in dir.
    if(checkIfOnFloor(elev.requestInDIr)){
        stopElevator();
        elev.Dir = DIRN_STOP;

        openDoor();
        elev.State = DOOROPEN;

        elev.requestInDIr = -1;
        deleteRequest();
        
        start = startTimer();

        printElevatorState();
        printRequestDatabase();
    }

    // Check if floor reached
    if(checkIfOnFloor(elev.currentFloorRequest)){
        stopElevator();
        elev.Dir = DIRN_STOP;

        openDoor();
        elev.State = DOOROPEN;

        elev.currentFloorRequest = -1;
        deleteRequest();
    
        start = startTimer();

        printElevatorState();
        printRequestDatabase();
    }
}

void stateDOOROPEN(){
    end = endTimer();

    // Check for obstruction
    pollObstructionButton();
    
    // Check for stop button
    pollStopButton();

    // Close door after 3 seconds
    if(timeSpent(end, start) >= 3){
        closeDoor();
        elev.State = IDLE;

        printElevatorState();
        printRequestDatabase();
    }
}


void stateOBSTRUCTION(){
    // Check stop button
    pollStopButton();

    // Check if obstruction removed
    if(!elevio_obstruction()){
        printf("Obstruction removed\n");
        elev.State = DOOROPEN;
        start = startTimer();
    }
}

void stateSTOPBUTTON(){
    // Delete all requests. 
    deleteAllRequests();

    // If we are on floor -> open door
    if(elevio_floorSensor() != -1){ 
        openDoor();
    }

    // Wait till stopbutton is not pressed
    start = startTimer();
    end = endTimer();
    while(timeSpent(end, start) < 0.5){
        if(elevio_stopButton()){
            start = startTimer();
        }
        end = endTimer();
    }
    elevio_stopLamp(0);
    
    // If on floor go to door open
    // If inbetween floors go to IDLE
    if(elevio_floorSensor() == -1){
        elev.State = IDLE;
    }else{
        elev.State = DOOROPEN;
        start = startTimer();
    }
    
    // Print state
    printElevatorState();
    printRequestDatabase();
}



void stateMachine(){
    // Initiating elevator
    initElevator();
    printElevatorState();

    // Initiating requestManager
    initRequestManager();
    printRequestManager();

    while(1){
        // Update floor
        pollFloorSensor();
        
        // Poll buttons, update requestManager
        updateRequests();
        updateNrRequests();
        
        // Get requests and requests in direction of travel. 
        getRequest();
        getRequestInDIrection();

        switch(elev.State){
            case UNDEFINED:
                stateUNDEFINED();
                break;

            case IDLE:
                stateIDLE();
                break;

            case MOVING:
                stateMOVING();
                break;

            case DOOROPEN:
                stateDOOROPEN();
                break;

            case OBSTRUCTION:
                stateOBSTRUCTION();
                break;

            case STOPBUTTON:
                stateSTOPBUTTON();
                break;

            default: 
                printf("Not Working\n");
                break;
            
        }
    }
}