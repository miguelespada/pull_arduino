//
//  myButton.cpp
//  arduino_pull
//
//  Created by miguel valero espada on 8/9/14.
//
//

#include "myButton.h"



myButton::myButton(){
    ofxJSONElement settings;
    last_change = 0;
    value = -1;
    
    host = "192.168.1.170";
    port = 8000;
    ofFile file;
    ofSetDataPathRoot("./data/");
    string path = ofToDataPath("settings.json");
    if(settings.open(path)){
        host = settings["host"].asString();
        port =  settings["port"].asInt();
    }
    sender.setup(host, port);
};

void myButton::update(int newValue){
    if(newValue != value){
        
        ofxOscMessage m;

        if(newValue == OFF){
           // if (ofGetElapsedTimeMillis() - last_change < HOLD_TIME){
              //  m.setAddress("/key_up");
            //   cout << "KEY UP!"  << endl;
            //}
        }
        else{
            m.setAddress("/key_down");
            cout << "KEY DOWN!"  << endl;
        }
        
        sender.sendMessage(m);
        value = newValue;
        last_change = ofGetElapsedTimeMillis();
    }
    else if (value == ON){
       // if (ofGetElapsedTimeMillis() - last_change > HOLD_TIME){
           // ofxOscMessage m;
           // cout << "CLICK AND HOLD" << endl;
          //  m.setAddress("/click_and_hold");
          //  sender.sendMessage(m);
       // }
    }
    
};




