#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    
    arduinoConnected = false;
    
    
    osc = new OscAdapter();
    for(int i = 0; i < 4; i ++){
        buttons[i] = myButton(i);
        buttons[i].osc = osc;
    }
    
    lastTime = ofGetElapsedTimeMillis();
    
}
//--------------------------------------------------------------


string testApp::getArduinoPort(){
    ofSerial serial;
    vector <ofSerialDeviceInfo> deviceList =  serial.getDeviceList();
    for (int i=0; i<deviceList.size(); i++) {
        if(deviceList[i].getDeviceName().find("tty.usbmodem") != std::string::npos){
            return deviceList[i].getDeviceName();
        }
    }
    return "";
};

void testApp::arduinoSetup(){
    cout << "Trying to connect..." << endl;
    string deviceName = getArduinoPort();
    ard.disconnect();
	arduinoConnected = ard.connect(deviceName, 57600);
	ofAddListener(ard.EInitialized, this, &testApp::setupArduino);
	bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    if(arduinoConnected)
        updateArduino();
    
    if(ofGetFrameNum() % 60 == 0){
        if(getArduinoPort() == ""){
            cout << "Arduino not present..." << endl;
            arduinoConnected = false;
        }
        else {
            if(!arduinoConnected)
                arduinoSetup();
        }
    }
};

//--------------------------------------------------------------
void testApp::setupArduino(const int & version) {
	
	// remove listener because we don't need it anymore
	ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    cout << ard.getFirmwareName() << endl;
//    cout << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion() << endl;
    
    // set pins D2
    for(int i = 0; i < 4; i ++){
        ard.sendDigitalPinMode(i + 2, ARD_INPUT);
        ard.sendDigital(i  + 2 , ARD_HIGH);
    }
    ard.sendDigitalPinMode(6, ARD_INPUT);
  	
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &testApp::digitalPinChanged);
    
}

//--------------------------------------------------------------
void testApp::updateArduino(){
	ard.update();
}

//--------------------------------------------------------------
void testApp::digitalPinChanged(const int & pinNum) {
    if(pinNum == 6){
        if(ard.getDigital(pinNum) == ON){
            if(ofGetElapsedTimeMillis() - lastTime > 400){
                osc->sendAction("/key_down", 0);
                lastTime = ofGetElapsedTimeMillis();
                
            }
            
        }
    }
    else {
        buttons[pinNum - 2].update(ard.getDigital(pinNum));
    }
}


//--------------------------------------------------------------
void testApp::draw(){
    if(!arduinoConnected)
        ofBackground(127);
    else
        ofBackground(0);
    
    for(int i = 0; i < 4; i ++){
        buttons[i].draw();
    }
    
    ofSetColor(255, 0, 0);
    std::stringstream ss;
    ss << "Sending: " << osc->host << " " << osc->port;
    ofDrawBitmapString(ss.str(), 10, 14);

}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    if(key == ' ')
        buttons[0] = 0;
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    if(key == ' ')
        buttons[0] = 1;
    
}
