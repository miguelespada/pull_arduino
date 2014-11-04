#pragma once

#include "ofMain.h"
#include "ofEvents.h"
#include "myButton.h"



class testApp : public ofSimpleApp{
    
public:
    
	void setup();
	void update();
	void draw();
    
	void keyPressed(int key);
	void keyReleased(int key);
    
	ofArduino	ard;
	bool		bSetupArduino;
    
private:
    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    
	void updateArduino();
    string getArduinoPort();
    void arduinoSetup();
    bool arduinoConnected;
    
    myButton buttons[4];
    float timer = 0;

    OscAdapter *osc;
    float lastTime;
};

