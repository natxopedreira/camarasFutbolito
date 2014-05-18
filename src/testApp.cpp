#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    //int _indexCam, int _maxPhotos, int _photoSpeed
    string ruta = "/Users/ignaciopedreiragonzalez/Documents/OF_FUTBOLITO_081/apps/futbolito/camarasFutbolito/bin/data/fotos/";
    
    camFutbolito.setup(0,3,600,ruta);
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
    
    
    if (key == 'd' ||key == 'D'){
        camFutbolito.debugMode = !camFutbolito.debugMode;
    }else{
        camFutbolito.camaraGol(1);
    }
}
