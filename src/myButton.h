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
#include "OscAdapter.h"
#define ON 0
#define OFF 1

class myButton{
    
public:
    myButton(){};
    myButton(int _id);
    void update(int newValue);
    OscAdapter *osc;
    void draw();
private:
    int id;
    int value = OFF;
};



#endif
