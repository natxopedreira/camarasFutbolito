#pragma once

#include "ofMain.h"
#include "camaras.h"
#include "futbolito.h"

struct jugadores {
    ofVideoDevice camaraFutbolin;
    int idVideoDevice;
    int idNombre;
};

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);

        void exit();
    
    int findIdinvector(vector<ofVideoDevice> & devices, string valueWanted);
    int findIdNombre(vector<jugadores> & _equipos, int idWanted);
    
    void disparaCamara(int & player);
    void marcaGol(int & equipo);
    void timerSonidoFinCall( int &args );
    
    camaras camFutbolito;
    futbolito futbolin;
    
    vector<jugadores> equipos;
    
    //sounds
    ofSoundPlayer sonidoGol, sonidoFin, sonidoAmbiente;
    
    ofxSimpleTimer timerSonidoFin;
};
   