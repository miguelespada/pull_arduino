//
//  myButton.cpp
//  arduino_pull
//
//  Created by miguel valero espada on 8/9/14.
//
//

#include "myButton.h"


myButton::myButton(int _id){
    id = _id;
};

void myButton::update(int newValue){
        if(newValue != value){
            if(newValue == ON){
                osc->sendAction("/player_on", id);
            }
            else{
                osc->sendAction("/player_off", id);
            }
            value = newValue;
        }
};

void myButton::draw(){
    if(value)
        ofSetColor(255, 0, 0);
    else
        ofSetColor(255, 255, 0);
    
    ofEllipse((50 * id) + 50, ofGetHeight()/2, 40, 40);
}




