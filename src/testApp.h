#pragma once

#include "ofMain.h"
#include "camaras.h"


class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
    
        void exit();
    
    camaras camFutbolito;
    
    
};
   