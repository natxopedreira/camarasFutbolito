#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    //int _indexCam, int _maxPhotos, int _photoSpeed
    
    camFutbolito.setup(0,3,600);
}

//--------------------------------------------------------------
void testApp::update(){
    camFutbolito.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    camFutbolito.draw();
}

void testApp::exit(){
    
    camFutbolito.recorder.waitForThread();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    camFutbolito.dispara();
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

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