#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    string ruta = "/Users/ignaciopedreiragonzalez/Documents/fotosFutbolitoParaSubir/";
    string arduFutbolin = "/dev/tty.usbmodem1441";
    
    camFutbolito.setup(0,3,600,ruta);
    
    futbolin.setup(arduFutbolin);
    
    ofAddListener(futbolin.tengoDatos, this, &testApp::marcaGol);
}

//--------------------------------------------------------------
void testApp::update(){
    camFutbolito.update();
    futbolin.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    camFutbolito.draw();
    
    
}

//------------------------------------------------------------------------------
void testApp::marcaGol(int & equipo){
    cout << "goooool del equipo " << equipo << endl;
    
    if(camFutbolito.debugMode){
        camFutbolito.cambiaCamaraDebug(equipo);
    }else{
        camFutbolito.camaraGol(equipo);
    }
    
}

//------------------------------------------------------------------------------
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
        case 'f':
            ofToggleFullscreen();
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
