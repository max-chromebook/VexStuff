#include "vex.h"

// ---------------------------------------------------------------->>> BEGIN BRAIN BUTTON CODE  <<<

/*--------------------------------------------------------------------------------------------------
       8756 Robo Bonobo Autonomous Selector                             
       Contributors:
       Liam Donovan, CJ Crocker - WalshBots 9791 unified competition template
       James Pearman - Brain Auton Button Selector
 -------------------------------------------------------------------------------------------------*/

// collect data for on screen button
typedef struct _button {
    int    xpos;
    int    ypos;
    int    width;
    int    height;
    bool   state;
    vex::color offColor;
    vex::color onColor;
    const char *offLabel;
    const char *onLabel;
} button;

// Button array definitions for each software button.
button buttons[] = {
//    xpos, ypos, w, h,   state, offColor, onColor,  offLabel,  onLabel
    {   20,  25, 80, 80,  false, 0xEE0000, 0x0000EE, "Red",     "Blue" }, 
    {  140,  25, 80, 80,  false, 0x00FF66, 0xFFBB00, "Front",    "Back" }, 
    {  260,  25, 80, 80,  false, 0x00FF66, 0xFFBB00, "Main",    "Alt" }, 
    {  380,  25, 80, 80,  false, 0x909090, 0x00FF66, "!Skills", "Skills" }, 
    {   20, 135, 80, 80,  false, 0x909090, 0x00FF66, "!5",      "5" }, 
    {  140, 135, 80, 80,  false, 0x909090, 0x00FF66, "!6",      "6" }, 
    {  260, 135, 80, 80,  false, 0x909090, 0x00FF66, "!7",      "7" }, 
    {  380, 135, 80, 80,  false, 0x909090, 0x00FF66, "!8",      "8" }  
};

// forward ref
void displayButtonControls( int index, bool pressed );

/*-----------------------------------------------------------------------------*/
/** @brief      Check if touch is inside button                                */
/*-----------------------------------------------------------------------------*/
int
findButton(  int16_t xpos, int16_t ypos ) {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      button *pButton = &buttons[ index ];
      if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
        continue;

      if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
        continue;

      return(index);
    }
    return (-1);
}



/*-----------------------------------------------------------------------------*/
/** @brief      Init button states                                             */
/*-----------------------------------------------------------------------------*/
void
initButtons() {
    int nButtons = sizeof(buttons) / sizeof(button);

    for( int index=0;index < nButtons;index++) {
      buttons[index].state = false;
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been touched                                        */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackPressed() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if( (index = findButton( xpos, ypos )) >= 0 ) {
      displayButtonControls( index, true );
    }

}

/*-----------------------------------------------------------------------------*/
/** @brief      Screen has been (un)touched                                    */
/*-----------------------------------------------------------------------------*/
void
userTouchCallbackReleased() {
    int index;
    int xpos = Brain.Screen.xPosition();
    int ypos = Brain.Screen.yPosition();

    if( (index = findButton( xpos, ypos )) >= 0 ) {

      // now set this one as true
      if( buttons[index].state == true) {
      buttons[index].state = false; }
      else    {
      buttons[index].state = true;}

      displayButtonControls( index, false );
    }
}

/*-----------------------------------------------------------------------------*/
/** @brief      Draw all buttons                                               */
/*-----------------------------------------------------------------------------*/
void
displayButtonControls( int index, bool pressed ) {
    vex::color c;
    Brain.Screen.setPenColor( vex::color(0x101010) ); // text and outline color
    Brain.Screen.setPenWidth(2); // outline thickness
    
    for(int i=0;i<sizeof(buttons)/sizeof(button);i++) {

      if( buttons[i].state )
        c = buttons[i].onColor;
      else
        c = buttons[i].offColor;

      Brain.Screen.setFillColor( c );

      // button fill
      if( i == index && pressed == true ) {
        c = c + 0xDDDDDD; // lightens the fill color while pressed
        Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height, c ); 
      }
      else
        Brain.Screen.drawRectangle( buttons[i].xpos, buttons[i].ypos, buttons[i].width, buttons[i].height );

      // draw label
      if( buttons[i].state ){ 
        Brain.Screen.printAt( buttons[i].xpos + 8, buttons[i].ypos + buttons[i].height - 8, buttons[i].onLabel );
      }
      else
        Brain.Screen.printAt( buttons[i].xpos + 8, buttons[i].ypos + buttons[i].height - 8, buttons[i].offLabel );
       
    }
}
// ---------------------------------------------------------------->>> END BRAIN BUTTON CODE  <<<

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/
int botSpeed = 60;
int botFSpeed = 100;
int turnSpeed = 38;
int turnDirection = 1; // turnDegrees() turns are multiplied by turn direction to make mirroring programs easy RED = 1, BLUE = -1 (set in button code)
int liftInches = 2; // Value of rotations that equals an inch

int converter (int distancecalc) {
    return distancecalc /(4*3.14) * 360;// do math 
}

void driveInches(int inches){
    BackRight.startRotateFor(converter(inches),rotationUnits::deg,botSpeed,velocityUnits::pct);
    BackLeft.startRotateFor(converter(inches),rotationUnits::deg,botSpeed,velocityUnits::pct);
    FrontRight.startRotateFor(converter(inches),rotationUnits::deg,botSpeed,velocityUnits::pct);
    FrontLeft.rotateFor(converter(inches),rotationUnits::deg,botSpeed,velocityUnits::pct);
}

void driveFSInches(int inches){
    BackRight.startRotateFor(converter(inches),rotationUnits::deg,botFSpeed,velocityUnits::pct);
    BackLeft.startRotateFor(converter(inches),rotationUnits::deg,botFSpeed,velocityUnits::pct);
    FrontRight.startRotateFor(converter(inches),rotationUnits::deg,botFSpeed,velocityUnits::pct);
    FrontLeft.rotateFor(converter(inches),rotationUnits::deg,botFSpeed,velocityUnits::pct);
}

void turnDegrees(int degrees){
    degrees = degrees* turnDirection;
    FrontLeft.startRotateFor(degrees,rotationUnits::deg,turnSpeed,velocityUnits::pct);
    BackLeft.startRotateFor(degrees,rotationUnits::deg,turnSpeed,velocityUnits::pct);   
    FrontRight.startRotateFor(-degrees,rotationUnits::deg,turnSpeed,velocityUnits::pct);
    BackRight.rotateFor(-degrees,rotationUnits::deg,turnSpeed,velocityUnits::pct); 
 
}
void liftClaw(int distance){

}
void quickGrab(){

}
void driveTurn(int speed){
    DriveMotors.spin(directionType::fwd,speed,velocityUnits::pct);
}
void driveStop(){
    DriveMotors.stop(brakeType::brake);
}
void driveHold(){
    DriveMotors.stop(brakeType::hold);
}
void preAuton( void ) {
    LiftMotors.setPosition(0, rotationUnits::rev);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {
      /* initialize capabilities from buttons */
    bool Blue_Ally = buttons[0].state;   // default is Red Alliance
    bool Back = buttons[1].state;         // default is Front start
    bool Alt = buttons[2].state;         // default is Main program
    bool Skills = buttons[3].state;      // default of Skills and 5-8 is unselected
    bool Five = buttons[4].state;        // these are for tweaking a step in auton... park or don't park, etc.
    bool Six = buttons[5].state;
    bool Seven = buttons[6].state;
    bool Eight = buttons[7].state;
      
    if (Blue_Ally){
        turnDirection = -1; // reverses turns on blue side
        Brain.Screen.clearScreen(color::blue);
    }
    else
        Brain.Screen.clearScreen(color::red);
    
    Brain.Screen.setFont(fontType::mono30);
    Brain.Screen.setPenColor(color::white);    
    
    if(Skills){ Brain.Screen.printAt(90,135,"SKILLS");
//SKILLS AUTON        
     
    }
    else if(!Back){            
        if(!Alt){             Brain.Screen.printAt(90,135,"FRONT MAIN");
//FRONT MAIN

DriveBase.driveFor(directionType::fwd, 14, distanceUnits::in, 65, velocityUnits::pct);
vex::task::sleep(200);
if(LiftMotors.position(rotationUnits::rev) >= 0.002){
  LiftMotors.rotateTo(.002, rotationUnits::rev);
}
vex::task::sleep(200);
ClawMotor.rotateTo(.5, rotationUnits::rev);
vex::task::sleep(200);
LiftMotors.rotateTo(3, rotationUnits::rev);
vex::task::sleep(200);
ClawMotor.rotateTo(2, rotationUnits::rev);
vex::task::sleep(200);
LiftMotors.rotateTo(4, rotationUnits::rev);
vex::task::sleep(200);
ClawMotor.rotateTo(2, rotationUnits::rev);
vex::task::sleep(200);
LiftMotors.rotateTo(1, rotationUnits::rev);
vex::task::sleep(200);
        }
        else{Brain.Screen.printAt(90,135,"FRONT ALT");
//FRONT ALT 
    //Step 5
    Brain.Screen.printAt(90, 135, "Step 5");
    int x = 4*4;
    for (int i = 1;i<=x;i++){
    DriveBase.driveFor(directionType::fwd, 24, distanceUnits::in, 60, velocityUnits::pct);
    vex::task::sleep(100);
    DriveBase.turnFor(45, rotationUnits::deg);
    vex::task::sleep(100);
    }
    //Step 6
    Brain.Screen.printAt(90, 135, "Step 6");
    ClawMotor.rotateFor(directionType::fwd, 4, rotationUnits::rev);
 }
    }   
    else{
        if(!Alt){Brain.Screen.printAt(90,135,"BACK MAIN");
//BACK MAIN
                   
            
        }
        else{Brain.Screen.printAt(90,135,"BACK ALT");
//BACK ALT
                        
            
        }
    }
      
  
  }
    




/*
/_    _
| |  | |
| |  | |  ___    ___   _ __
| |  | | / __|  / _ \ | '__|
| |__| | \__ \ |  __/ | |
\\____/  |___/  \___| |_|
*/
void usercontrol( void ) {
  LiftMotors.setPosition(0, rotationUnits::rev);
  
    while (true){
        double liftPosition=LiftRight.position(rotationUnits::rev);
        double clawPosition=ClawMotor.position(rotationUnits::rev);
        Brain.Screen.printAt(5, 30, true, "claw motor position %f2",clawPosition);
        Brain.Screen.printAt(5, 15, true, "lift motor position %f2",liftPosition);
        if(LiftStop.pressing()){
          LiftMotors.setPosition(0, rotationUnits::rev);
        }
      //  if(LiftStop. pressed(void (*callback)()))
  //    brain.screen.printAt()
        channel2 = Controller1.Axis2.position(percentUnits::pct);
        channel3 = Controller1.Axis3.position(percentUnits::pct);
        mapped2 = (((channel2)*(channel2)*(channel2))/10000);
        mapped3 = (((channel3)*(channel3)*(channel3))/10000);
//Drive        
        BackLeft.spin(vex::directionType::fwd, mapped3, velocityUnits::pct);
        FrontLeft.spin(vex::directionType::fwd, mapped3, velocityUnits::pct);
        BackRight.spin(vex::directionType::fwd, mapped2, velocityUnits::pct);
        FrontRight.spin(vex::directionType::fwd, mapped2, velocityUnits::pct);
      
//Slow Drive
        if(Controller1.ButtonUp.pressing()){
          DriveBase.drive(directionType::fwd);
        }
        if(Controller1.ButtonDown.pressing()){
          DriveBase.drive(directionType::rev);
        }
        if(Controller1.ButtonLeft.pressing()){
          DriveBase.turn(left, 50, velocityUnits::pct);
        }

//Lift
        if(Controller1.ButtonR1.pressing() && liftPosition <= 14){
          LiftMotors.spin(vex::directionType::fwd,100, pct);
          LiftPlus.spin(vex::directionType::fwd,62, pct);
        }
        else if(Controller1.ButtonR2.pressing() && !LiftStop.pressing()){
          LiftMotors.spin(vex::directionType::fwd,-100, pct);
          LiftPlus.spin(vex::directionType::fwd, -62,velocityUnits::pct);
        }
        else{
          LiftMotors.stop(brakeType::hold);
          LiftPlus.stop(brakeType::hold);
        }
  //claw
        if(Controller1.ButtonL1.pressing()){
          ClawMotor.spin(vex::directionType::fwd,100,velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing()){
          ClawMotor.spin(vex::directionType::rev,100,velocityUnits::pct);
        }
        else{
          ClawMotor.stop(brakeType(hold));
        } 
        
    }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
//----------------------------------------------------------MORE BRAIN BUTTON CODE 
    // register events for button selection
    Brain.Screen.pressed( userTouchCallbackPressed );
    Brain.Screen.released( userTouchCallbackReleased );

    // initial display
    Brain.Screen.clearScreen( color::black );// draw screen black
    displayButtonControls( 0, false );
//--------------------------------------------------------------------------------
    
    //Run the pre-autonomous function. 
    preAuton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100); //Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}