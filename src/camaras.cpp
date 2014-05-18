//
//  camaras.cpp
//  example-ofxUVC
//
//  Created by Ignacio Pedreira gonzalez on 15/05/14.
//
//

#include "camaras.h"


//--------------------------------------------------------------
void camaras::setup(int _indexCam, int _maxPhotos, int _photoSpeed, string _rutaCarpeta){
    
    camWidth = 1280;
    camHeight = 720;
    
    availableCams = vidGrabber.listDevices();
    
    rutaCarpeta = _rutaCarpeta;
    maxPhotosPerCamera = _maxPhotos;
    madePhotos = 0;
    
    indexCamera = _indexCam;
    initCameras();
    
    /// gui
    gui.setup("controles de camaras");
    gui.add(whiteValues.setup("white", 0, 0, 1));
    gui.add(exposureValue.setup("exposure", 0, 0, 1));
    gui.add(gainValue.setup("ganancia", 0, 0, 1));
    gui.add(focusValue.setup("focus", 0, 0, 1));
    gui.add(brightValue.setup("brightness", 0, 0, 1));
    gui.add(satValue.setup("saturacion", 0, 0, 1));
    gui.add(contrastValue.setup("contraste", 0, 0, 1));
    gui.add(thresholdBrightnes.setup("threshold image valid", 0, 0, 255));
    gui.add(setsettings.setup("live settings", false));
    
    gui.loadFromFile("settings.xml");
    
    
    /// set gui values to uvc
    uvcControl.setWhiteBalance(whiteValues);
    uvcControl.setExposure(exposureValue);
    uvcControl.setGain(gainValue);
    uvcControl.setSaturation(satValue);
    uvcControl.setAbsoluteFocus(focusValue);
    uvcControl.setBrightness(brightValue);
    uvcControl.setContrast(contrastValue);
    
    // debug mode
    debugMode = false;

    //sound
    shutter.loadSound("camera_shutter.mp3");
    shutter.setMultiPlay(false);
    
    //timers
    timerFoto.setup(_photoSpeed);
    timerCambioCamara.setup(1000);
    
    ofAddListener(timerFoto.TIMER_COMPLETE , this, &camaras::timerFotoComplete);
    ofAddListener(timerCambioCamara.TIMER_COMPLETE , this, &camaras::timerCambioCamaraComplete);
}
//--------------------------------------------------------------
void camaras::initCameras(){
    vidGrabber.setDeviceID(availableCams.at(indexCamera).id);
    vidGrabber.initGrabber(camWidth, camHeight);
    
    uvcControl.useCamera(0x046d, 0x82d, 0x03);
    uvcControl.setAutoWhiteBalance(false);
    uvcControl.setAutoExposure(false);
    uvcControl.setAutoFocus(false);
    controls = uvcControl.getCameraControls();

}
//--------------------------------------------------------------
void camaras::update(){
    timerFoto.update();
    timerCambioCamara.update();
    
    vidGrabber.update();
    if(vidGrabber.isFrameNew())
    {
        tex.loadData(vidGrabber.getPixelsRef());
    }
    controls = uvcControl.getCameraControls();
    
    if(setsettings){
        uvcControl.setWhiteBalance(whiteValues);
        uvcControl.setExposure(exposureValue);
        uvcControl.setGain(gainValue);
        uvcControl.setSaturation(satValue);
        uvcControl.setAbsoluteFocus(focusValue);
        uvcControl.setBrightness(brightValue);
        uvcControl.setContrast(contrastValue);
    }
}

//--------------------------------------------------------------
void camaras::draw(){
    ofBackground(0);
    tex.draw(0,0, camWidth, camHeight);
   
    if(debugMode){
        ofSetColor(255);
        timerFoto.draw(camWidth - 250, 20);
        timerCambioCamara.draw(camWidth - 250, 45);
    
        gui.draw();
    }
}

//--------------------------------------------------------------
int camaras::getAverageColor(const ofPixels & pix) {
    
    int pixelSize = pix.size();
    int r = 0, g = 0, b = 0;
    
    for (int i=0; i<pixelSize; i++) {
        
        ofColor c = pix[i];
        r += (c.r >> 16) & 0xFF;
        g += (c.g >> 8)  & 0xFF;
        b += c.b  & 0xFF;
    }
    r /= pixelSize;
    g /= pixelSize;
    b /= pixelSize;
    ofColor cAverage = ofColor(r, g, b);
    return cAverage.getBrightness();
}

//--------------------------------------------------------------
void camaras::timerFotoComplete( int &args ){
    //saca foto
    if (madePhotos<maxPhotosPerCamera) {
        /// check for valid image
        /// if brightness < thresholdBrightness
        /// the camera its on the box so dont use

        
        if(getAverageColor(vidGrabber.getPixelsRef())>thresholdBrightnes){
            //cout << "FOTOOOOOO" << endl;
            recorder.addFrame(vidGrabber.getPixelsRef(), rutaCarpeta +ofGetTimestampString()+".jpg");
            shutter.play();
        }else{
            cout << "OSCURO" << endl;
        }
        madePhotos++;
        
    }else{
        // no mas fotos

        timerFoto.stop();
        madePhotos = 0;
        
        //borras la camara del vector
        if(availableCams.size()>0) availableCams.erase(availableCams.begin()+indexCamera);
        
        cambiaCamara(0);
    }
}

//--------------------------------------------------------------
void camaras::cambiaCamara(int _indexCamera){
    //si hay mas camaras
    //cambia la camara
    // si no hay mas camaras se acabo
    //quita la camara del array

    if(_indexCamera<availableCams.size()){
        // esta dentro del array
        vidGrabber.setDeviceID(availableCams.at(_indexCamera).id);
        cout << "CAMARA setDeviceID" << _indexCamera << endl;
        timerCambioCamara.start(false);
        indexCamera = _indexCamera;
        
    }
}

//--------------------------------------------------------------
void camaras::camaraGol(int _camara){
    //cuando marcas un gol
    //la primera camara que se dispara es la del que
    //ha marcado
    availableCams.clear();
    availableCams = vidGrabber.listDevices();
    
    camaraInicial = _camara;
    cambiaCamara(_camara);
    
}

//--------------------------------------------------------------
void camaras::timerCambioCamaraComplete( int &args ){
    //camara cambiada
    dispara();
}

//--------------------------------------------------------------
void camaras::dispara(){
    timerFoto.start(true);
}

