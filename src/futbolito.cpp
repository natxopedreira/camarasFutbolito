//
//  futbolito.cpp
//  futbolitoArdu
//
//  Created by Ignacio Pedreira gonzalez on 07/06/14.
//
//

#include "futbolito.h"


void futbolito::setup(string address){
    status = device.setup(address);
    
    /// no se pq tengo que mandarle algo para que me haga caso
    device.writeByte(401);
    
    timeLastGoal = ofGetElapsedTimeMillis();
    
    intervalValidGoal = 8000;
    
    equipo1Goles = 0;
    equipo2Goles = 0;

	fuente.loadFont("frabk.ttf", 80, true, true);

}

//------------------------------------------------------------------------------
void futbolito::update(){
    while(device.available() > 0)
    {
        
        uint8_t array[1];
        std::size_t n = device.readBytes(array, 1);
        
        int valor = (int)array[0];
        int equipo = 0;
        
        switch (valor) {
            case 100:
                
                // apagas el mac y cierras el app
                ofExit();
                break;
                
            case 101:
                // gol del equipo 1
                equipo = 1;
                
                if(ofGetElapsedTimeMillis()> timeLastGoal+intervalValidGoal){
                    ofNotifyEvent(tengoDatos,equipo,this);
                    timeLastGoal = ofGetElapsedTimeMillis();
                }
                break;
                
            case 102:
                // gol del equipo 2
                equipo = 2;
                
                if(ofGetElapsedTimeMillis()> timeLastGoal+intervalValidGoal){
                    ofNotifyEvent(tengoDatos,equipo,this);
                    timeLastGoal = ofGetElapsedTimeMillis();
                }
                break;
                
            default:
                /// es el marcador
                equipo1Goles = valor / 100 % 10;
                equipo2Goles = valor % 10;
                break;
        }
        
    }
}

//------------------------------------------------------------------------------
void futbolito::drawScore(){
    cout << "equipo 1::" << equipo1Goles << " -- equipo 2::" << equipo2Goles << endl;
    
    int x_inicial = (ofGetWidth()-1280)/2;
    int y_inicial  = (ofGetHeight()-720)/2;
    
    int anchoMarcador = 400;
    int altoMarcador = 120;
    
    ofPushStyle();
    ofSetColor(255, 0, 0);
    ofRect(x_inicial + (1280-anchoMarcador)/2, y_inicial + 710-altoMarcador, anchoMarcador, altoMarcador);
    
    ofSetColor(255, 255, 255);
    fuente.drawString(ofToString(equipo1Goles) + " - " + ofToString(equipo2Goles), x_inicial + 20 + (1280-anchoMarcador)/2 , y_inicial + 80 + 710-altoMarcador);

    ofPopStyle();
    
    
    
}

//------------------------------------------------------------------------------
bool futbolito::getStatus(){
    return status;
}
