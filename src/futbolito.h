//
//  futbolito.h
//  futbolitoArdu
//
//  Created by Ignacio Pedreira gonzalez on 07/06/14.
//
//

#ifndef __example_serial__futbolito__
#define __example_serial__futbolito__

#include "ofMain.h"
#include "ofxSerial.h"

using namespace ofx::IO;

class futbolito {
public:
    
    void setup(string address);
    void update();
    void drawScore();
    void exit();
    
    bool getStatus();
    
    ofEvent<int> tengoDatos;
    int equipo1Goles;
    int equipo2Goles;
    int timeLastGoal;
    int intervalValidGoal;
    
private:
    SerialDevice device;
    bool    status;
    

    ofTrueTypeFont	fuente;
};


#endif /* defined(__example_serial__futbolito__) */
