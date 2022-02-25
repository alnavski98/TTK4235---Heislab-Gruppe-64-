# include "stateMachine.h"


// To do
// Printe på gode tidspunkt
// Lage actions -> det å gå mellom statsene som egne funksjoner
// Lage køsystem

void stateMachine(){
    // Initializes an instance of the elevatorState to "default" start values of:
    // - elevator.State = UNDEFINED;
    // - elevator.Floor = -1;
    // - elevator.Dir = 0; //Assumes it dosen't move when we start up. 
    // - elevator.currentFloorRequest = -1;
    printf("Elevator initiating \n");
    elevatorState elevator = elevatorInit();

    printf("Elevator Initiated \n");
    printElevatorState(elevator);

    // Initializes an instance of Request to "default" start values of:
    // - requestDatabase.numRequest = 0;
    // - requestDatabase.Database[b][f] = 0; // Integer value
    // Where "b" and "f" represents a given button and floor respectively
    printf("Database initiating \n");
    Request requestDatabase = initRequestDatabase();
    printf("Database initiated \n");

    int requestInDIr = -1; // 

    clock_t start;
    clock_t end;

    while(1){
        // Update floor
        int Floor = elevio_floorSensor();
        if(Floor != elevator.Floor && Floor != -1){
            elevator.Floor = Floor;
            elevio_floorIndicator(Floor);
        }

        // Requests
        updateRequests(&requestDatabase);
        updateNrRequests(&requestDatabase);
        
        if(requestDatabase.numRequest >= 1 && elevator.currentFloorRequest == -1){
            printf("Getting new request \n");
            elevator.currentFloorRequest = getRequest(elevator.Floor, elevator.Dir, requestDatabase.Database);
        }

        if(requestDatabase.numRequest >= 1 && requestInDIr == -1){
            //printf("Getting new request in direction \n");
            requestInDIr = getRequestInDIrection(elevator.Floor, elevator.Dir, elevator.currentFloorRequest, requestDatabase.Database);
        }

        switch(elevator.State){
            case UNDEFINED:
                //Find floor, direction and go to IDLE. 
                printf("In UNDEFINED\n");
                
                while(1){
                    // waiting for a defined floor reached.
                    int Floor = elevio_floorSensor();
                    if (Floor == -1){
                        elevator.Dir = DIRN_DOWN;
                        move(DIRN_DOWN);
                    }else{
                        stopElevator();
                        elevator.Dir = DIRN_STOP;
                        break;
                    }
                }
                int Floor = elevio_floorSensor();
                elevio_floorIndicator(Floor);
                elevator.Floor = Floor;
                elevator.State = IDLE;

                printf("State defined! \n");
                printElevatorState(elevator);
                break;

            case IDLE:
                
                // CHeck stop button
                if(elevio_stopButton()){
                    printf("Stop Button pressed\n");
                    elevator.State = STOPBUTTON;
                    elevio_stopLamp(1);
                }

                // Check requests
                if(elevator.currentFloorRequest != -1){
                    printf("Requested floor = %d \n", elevator.currentFloorRequest);
                    if( compareFloor(elevator.Floor, elevator.currentFloorRequest)){
                        stopElevator();
                        elevator.State = DOOROPEN;
                        openDoor();
                        start = startTimer();
                        deleteRequest(elevator.currentFloorRequest, &requestDatabase);
                        elevator.currentFloorRequest = -1;
                        //elevio_buttonLamp(elevator.currentFloorRequest, buttonPress[0], 0);
                        //elevator.currentFloorRequest = -1;
                        //buttonPress[0];
                    }else if(requestIsAbove(elevator.Floor, elevator.currentFloorRequest)){
                        elevator.State = MOVING;
                        elevator.Dir = DIRN_UP;
                        move(DIRN_UP);
                    }else{
                        elevator.State = MOVING;
                        elevator.Dir = DIRN_DOWN;
                        move(DIRN_DOWN);
                    }
                    printElevatorState(elevator);
                }
                break;

            case INBETWEEN:
                printf("In between floors");
                elevator.PrevFloor = elevator.Floor; // Store previous floor here
                elevator.Floor = -1;  // Not in defined/specific floor
                // If elevator moves in the upwards direction and the new floor requested
                // is greater than the floor it was on (PrevFloor) update the request list
                // and move towards that floor
                if(elevator.Dir == DIRN_UP && elevator.PrevFloor < elevator.currentFloorRequest){
                    elevator.State = MOVING;
                }
                // If elevator moves in the downwards direction and the new floor requested
                // is smaller/less than the floor it was on (PrevFloor) update the request list
                // and move towards that floor
                else if(elevator.Dir = DIRN_DOWN && elevator.PrevFloor > elevator.currentFloorRequest){
                    elevator.State = MOVING;
                }
                break;

            case MOVING:
                //Check stop button
                if(elevio_stopButton()){
                    printf("Stop Button pressed\n");
                    stopElevator();
                    elevator.State = STOPBUTTON;
                    elevio_stopLamp(1);
                }
                if(compareFloor(elevator.Floor, requestInDIr)){
                    stopElevator();
                    requestInDIr = -1;
                    deleteRequest(elevator.Floor, &requestDatabase);
                    openDoor();
                    elevator.State = DOOROPEN;
                    start = startTimer();
                }
                // Check if floor reached
                //printf("floor: %d",elevator.Floor);
                //printf("request: %d",elevator.currentFloorRequest);
                if(compareFloor(elevator.Floor, elevator.currentFloorRequest)){
                    stopElevator();
                    elevator.currentFloorRequest = -1;
                    deleteRequest(elevator.Floor, &requestDatabase);
                    //elevio_buttonLamp(order[0], buttonPress[0], 0);
                    openDoor();
                    elevator.State = DOOROPEN;
                    elevator.Dir = DIRN_STOP;
                    //order[0] = -1;
                    start = startTimer();

                    printElevatorState(elevator);
                }

                break;

            case DOOROPEN:
                end = endTimer();

                // Check for obstruction
                if(elevio_obstruction()){
                    printf("Obstruction in Door!\n");
                    elevator.State = OBSTRUCTION;
                }
                
                // Check for stop button
                if(elevio_stopButton()){
                    printf("Stop Button pressed\n");
                    elevio_stopLamp(1);
                    elevator.State = STOPBUTTON;
                }

                // Close door after 3 seconds
                if(timeSpent(end, start) >= 3){
                    printf("Door closed!\n");
                    closeDoor();
                    elevator.State = IDLE;

                    printElevatorState(elevator);
                }

                break;

            case OBSTRUCTION:

                // Check stop button
                if(elevio_stopButton()){
                    printf("Stop Button pressed\n");
                    elevator.State = STOPBUTTON;
                    elevio_stopLamp(1);
                }

                // Check if obstruction removed
                if(!elevio_obstruction()){
                    printf("Obstruction removed\n");
                    elevator.State = DOOROPEN;
                    start = startTimer();
                }

                break;

            case STOPBUTTON:
                deleteAllRequests(&requestDatabase);
                elevator.currentFloorRequest = -1;
                requestInDIr = -1;
                //order[0] = -1; // Delete all orders
                // If we are on floor -> open door
                if(elevio_floorSensor() != -1 && (elevator.Dir == DIRN_DOWN || elevator.Dir == DIRN_UP)){ 
                    openDoor();
                }

                start = startTimer();
                end = endTimer();
                while(timeSpent(end, start) < 0.5){
                    if(elevio_stopButton()){
                        start = startTimer();
                    }
                    end = endTimer();
                } // This while is not working correctly. 
                // It seems like the while loop is not gonna be working. 
                // It does not enter the while loop since it is not a switch like the obstruction.
                // It is a signal that i not constantly high. 
                // Mabye use while(1) and have some condition inside. 
                // If stopbutton() start time. outside the 
                
                // If inbetween floors go to undefined state. 
                // Think mabye going to undefined is not correct way to handle it. 
                // Because we know our state; it is not undefined. So we should just have a method to handle it. 
                // If on floor go to door open.
                if(elevio_floorSensor() == -1 && (elevator.Dir == DIRN_UP || elevator.Dir == DIRN_DOWN)){
                    // elevator.State = IDLE;
                    elevator.State = INBETWEEN;
                }
                else{
                    elevator.State = DOOROPEN;
                    start = startTimer();
                }
                elevio_stopLamp(0);

                break;

            default: 
                printf("Not Working\n");
                break;
            
        }
    }
}