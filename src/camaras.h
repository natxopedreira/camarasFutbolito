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
#include "ofxGui.h"
#include "ofxSimpleTimer.h"
#include "ImageSequenceRecorder.h"

class camaras{
public:
    void setup(int _indexCam, int _maxPhotos, int _photoSpeed, string _rutaCarpeta);
    void update();
    void draw();
    
    
    int getAverageColor(const ofPixels & pix);
    void timerCambioCamaraComplete( int &args );
    void timerFotoComplete( int &args );
    void initCameras();
    
    void dispara();
    void cambiaCamara(int _indexCamera);
    
    void camaraGol(int _camara);
    
    ofQTKitGrabber	vidGrabber;
    ofSoundPlayer  shutter;
    ofTexture tex;
    ImageSequenceRecorder recorder;

    string cameraName;
    vector<ofVideoDevice> availableCams;
    
    int maxPhotosPerCamera;
    int madePhotos;
    int camaraInicial;
    int indexCamera;
    int camWidth, camHeight;
    float focus;
    bool debugMode;
    string rutaCarpeta;
    
    vector<ofxUVCControl> controls;
    ofxUVC uvcControl;
    
    ofxPanel gui;
    ofxFloatSlider whiteValues, exposureValue, gainValue, satValue, focusValue, brightValue, contrastValue;
    ofxIntSlider thresholdBrightnes;
    ofxToggle setsettings;
    
    ofxSimpleTimer timerFoto;
    ofxSimpleTimer timerCambioCamara;
};
#endif
