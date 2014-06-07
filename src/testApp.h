#pragma once

#include "ofMain.h"
#include "camaras.h"
#include "futbolito.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
        void marcaGol(int & equipo);
    
        void exit();
    
    camaras camFutbolito;
    futbolito futbolin;

    
};
   