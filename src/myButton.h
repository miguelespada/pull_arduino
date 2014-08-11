//
//  myButton.h
//  arduino_pull
//
//  Created by miguel valero espada on 8/9/14.
//
//

#ifndef arduino_pull_myButton_h
#define arduino_pull_myButton_h

#include "ofMain.h"
#include "ofxOsc.h"

#define ON 0
#define OFF 1
#define HOLD_TIME 2000

class myButton{
    
public:
    myButton();
	void update(int newValue);

private:
    int value;
    unsigned long long last_change;
    ofxOscSender sender;

    
};



#endif
