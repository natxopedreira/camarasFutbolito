//
//  camaras.h
//  example-ofxUVC
//
//  Created by Ignacio Pedreira gonzalez on 15/05/14.
//
//

#ifndef _camaras
#define _camaras

#include "ofMain.h"
#include "ofxUVC.h"
#include "ofxYAML.h"
#include "ofxGui.h"
#include "ofxSimpleTimer.h"
#include "ofxImageSequenceRecorder.h"

class camaras{
public:
    void setup(int _indexCam, int _maxPhotos, int _photoSpeed);
    void update();
    void draw();
    
    
    void averageColorOfArea(int cx, int cy, int avgW,int avgH);
    void timerCambioCamaraComplete( int &args );
    void timerFotoComplete( int &args );
    void dispara();
    
    ofQTKitGrabber	vidGrabber;
    
    ofTexture tex;
    
    ofxUVC uvcControl;
    ofxYAML yaml;
    string cameraName;
    vector<string> availableCams;
    
    int camWidth, camHeight;
    
    float focus;
    
    vector<ofxUVCControl> controls;
    
    ofxPanel gui;
    ofxFloatSlider whiteValues, exposureValue, gainValue, satValue, focusValue, brightValue, contrastValue;
    ofxToggle setsettings;
    
    ofxSimpleTimer timerFoto;
    ofxSimpleTimer timerCambioCamara;
    
    int maxPhotosPerCamera;
    int madePhotos;
    int indexCamera;
    

    
    ofxImageSequenceRecorder recorder;
    
};
#endif
