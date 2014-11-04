//
//  OscAdapter.cpp
//  pull_arduino
//
//  Created by miguel on 30/10/14.
//
//

#include "OscAdapter.h"

OscAdapter::OscAdapter(){
    host = "localhost";
    port = 8080;
    sender.setup(host, port);
    cout << "Sending to "<< host << " " << port << endl;
}

OscAdapter::~OscAdapter(){
    
}

void OscAdapter::sendAction(string msg, int param){
    
    ofxOscMessage m;
    m.setAddress(msg);
    m.addIntArg(param);
    cout << m.getAddress() << " "  << m.getArgAsInt32(0) << endl;
    sender.sendMessage(m);
}
