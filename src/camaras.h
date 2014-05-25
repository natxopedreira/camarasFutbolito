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
    
    void dispara();
    void cambiaCamara(int _indexCamera);
    
    void camaraGol(int _camara);
    
    ofQTKitGrabber	vidGrabber;
    ofSoundPlayer  shutter;
    ofTexture tex;
    

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
    
    // OFXUVC
    vector<ofxUVCControl> controls0;
    vector<ofxUVCControl> controls1;
    vector<ofxUVCControl> controls2;
    ofxUVC uvcControl0, uvcControl1, uvcControl2;
    
    // ImageSequenceRecorder
    ImageSequenceRecorder recorder;
    
    /// GUI
    ofxPanel gui;
    ofxFloatSlider whiteValues0, exposureValue0, gainValue0, satValue0, focusValue0, brightValue0, contrastValue0;
    ofxFloatSlider whiteValues1, exposureValue1, gainValue1, satValue1, focusValue1, brightValue1, contrastValue1;
    ofxFloatSlider whiteValues2, exposureValue2, gainValue2, satValue2, focusValue2, brightValue2, contrastValue2;
    ofxIntSlider thresholdBrightnes;
    ofxToggle setsettings;
    
    /// TIMER
    ofxSimpleTimer timerFoto;
    ofxSimpleTimer timerCambioCamara;
};
#endif
