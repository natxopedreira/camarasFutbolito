#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    string ruta = "/Users/ignaciopedreiragonzalez/Documents/fotosFutbolitoParaSubir/";
    string arduFutbolin = "/dev/tty.usbmodem1441";
    
    
    camFutbolito.setup(0,3,600,ruta);
    futbolin.setup(arduFutbolin);
    ofAddListener(futbolin.tengoDatos, this, &testApp::marcaGol);
    
    
    /// jugadores del futbolin
    jugadores equipo1;
    equipo1.camaraFutbolin.deviceName = "234245345235235";
    equipo1.idVideoDevice = findIdinvector(camFutbolito.availableCams,"234245345235235");
    equipo1.idNombre = 1;
    
    jugadores equipo2;
    equipo2.camaraFutbolin.deviceName = "234245345235235";
    equipo2.idVideoDevice = findIdinvector(camFutbolito.availableCams,"234245345235235");
    equipo2.idNombre = 2;
    
    equipos.push_back(equipo1);
    equipos.push_back(equipo2);
    
    ///  audio
    sonidoAmbiente.loadSound("sonido-estadio345726.mp3");
    sonidoAmbiente.setLoop(true);
    sonidoAmbiente.play();
    
    sonidoGol.loadSound("Goal.mp3");
    sonidoFin.loadSound("End.mp3");
    
    timerSonidoFin.setup(2000);
    ofAddListener(timerSonidoFin.TIMER_COMPLETE , this, &testApp::timerSonidoFinCall);

}

//--------------------------------------------------------------
void testApp::update(){
    camFutbolito.update();
    futbolin.update();
}

//--------------------------------------------------------------
void testApp::draw(){
    camFutbolito.draw();
    //futbolin.drawScore();
}

//------------------------------------------------------------------------------
void testApp::timerSonidoFinCall( int &args ){
    sonidoFin.play();
}

//------------------------------------------------------------------------------
void testApp::marcaGol(int & equipo){
    cout << "goooool del equipo " << equipo << endl;
    
    /// sonido
    sonidoGol.play();
    
    if(futbolin.equipo1Goles>=6 || futbolin.equipo2Goles>=6){
        //es el ultimo gol para lanzar el sonido de fin
        timerSonidoFin.start(false);
    }
    
    // lanza las camaras
    disparaCamara(equipo);

    
}

//------------------------------------------------------------------------------
void testApp::disparaCamara(int & player){
    
    // find deviceid del equipo
    
    if(camFutbolito.debugMode){
        camFutbolito.cambiaCamaraDebug(findIdNombre(equipos,player));
    }else{
        camFutbolito.camaraGol(findIdNombre(equipos,player));
    }
}

//--------------------------------------------------------------
int testApp::findIdinvector(vector<ofVideoDevice> & devices, string valueWanted){
    for (int i = 0; i < devices.size(); i++) {
        if(devices.at(i).deviceName == valueWanted) return i;
    }
}

//--------------------------------------------------------------
int testApp::findIdNombre(vector<jugadores> & _equipos, int idWanted){
    for (int i = 0; i < _equipos.size(); i++) {
        if(_equipos.at(i).idNombre == idWanted) return _equipos.at(i).idVideoDevice;
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
            //
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
