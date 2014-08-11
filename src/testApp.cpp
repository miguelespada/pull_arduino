#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
	ofSetVerticalSync(true);
	ofSetFrameRate(60);
    
    arduinoConnected = false;
    
}

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
    
    button.update(digitalValue);
};

//--------------------------------------------------------------
void testApp::setupArduino(const int & version) {
	
	// remove listener because we don't need it anymore
	ofRemoveListener(ard.EInitialized, this, &testApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    cout << ard.getFirmwareName() << endl;
    cout << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion() << endl;
    
    // set pins D2
    ard.sendDigitalPinMode(2, ARD_INPUT);
    ard.sendDigital(2, ARD_HIGH);
    
    // set pin A0 to analog input
//    ard.sendAnalogPinReporting(0, ARD_ANALOG);
	
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &testApp::digitalPinChanged);
//      ofAddListener(ard.EAnalogPinChanged, this, &testApp::analogPinChanged);
}

//--------------------------------------------------------------
void testApp::updateArduino(){
	ard.update();
}

//--------------------------------------------------------------
void testApp::digitalPinChanged(const int & pinNum) {
    digitalValue = ard.getDigital(pinNum);
}

//--------------------------------------------------------------
void testApp::analogPinChanged(const int & pinNum) {
    analogValue = ard.getAnalog(pinNum);
}


//--------------------------------------------------------------
void testApp::draw(){
    if(digitalValue)
        ofBackground(255);
    else
        ofBackground(0);
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}