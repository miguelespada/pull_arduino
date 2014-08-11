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
    
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
    
	ofArduino	ard;
	bool		bSetupArduino;
    
private:
    void setupArduino(const int & version);
    void digitalPinChanged(const int & pinNum);
    void analogPinChanged(const int & pinNum);
	void updateArduino();
    string getArduinoPort();
    void arduinoSetup();
    int analogValue, digitalValue = 1;
    bool arduinoConnected;
    
    myButton button;
    
};

