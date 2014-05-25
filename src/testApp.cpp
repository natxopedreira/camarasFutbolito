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
    
    switch (key) {
        case 'd':
             camFutbolito.debugMode = !camFutbolito.debugMode;
            break;

        case 48:
            if(camFutbolito.debugMode){
                camFutbolito.cambiaCamaraDebug(0);
            }else{
                camFutbolito.camaraGol(0);
            }
            break;
            
        case 49:
            if(camFutbolito.debugMode){
                camFutbolito.cambiaCamaraDebug(1);
            }else{
                camFutbolito.camaraGol(1);
            }
            break;
            
        case 50:
            if(camFutbolito.debugMode){
                camFutbolito.cambiaCamaraDebug(2);
            }else{
                camFutbolito.camaraGol(2);
            }
            break;
            
        default:
            break;
    }
}
