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
    
    /// gui
    gui.setup("controles de camaras");
    
    /// camara 0
    gui.add(whiteValues0.setup("CAM0 white", 0, 0, 1));
    gui.add(exposureValue0.setup("CAM0 exposure", 0, 0, 1));
    gui.add(gainValue0.setup("CAM0 ganancia", 0, 0, 1));
    gui.add(focusValue0.setup("CAM0 focus", 0, 0, 1));
    gui.add(brightValue0.setup("CAM0 brightness", 0, 0, 1));
    gui.add(satValue0.setup("CAM0 saturacion", 0, 0, 1));
    gui.add(contrastValue0.setup("CAM0 contraste", 0, 0, 1));
    
    /// camara 1
    gui.add(whiteValues1.setup("CAM1 white", 0, 0, 1));
    gui.add(exposureValue1.setup("CAM1 exposure", 0, 0, 1));
    gui.add(gainValue1.setup("CAM1 ganancia", 0, 0, 1));
    gui.add(focusValue1.setup("CAM1 focus", 0, 0, 1));
    gui.add(brightValue1.setup("CAM1 brightness", 0, 0, 1));
    gui.add(satValue1.setup("CAM1 saturacion", 0, 0, 1));
    gui.add(contrastValue1.setup("CAM1 contraste", 0, 0, 1));
    
    /// camara 2
    gui.add(whiteValues2.setup("CAM2 white", 0, 0, 1));
    gui.add(exposureValue2.setup("CAM2 exposure", 0, 0, 1));
    gui.add(gainValue2.setup("CAM2 ganancia", 0, 0, 1));
    gui.add(focusValue2.setup("CAM2 focus", 0, 0, 1));
    gui.add(brightValue2.setup("CAM2 brightness", 0, 0, 1));
    gui.add(satValue2.setup("CAM2 saturacion", 0, 0, 1));
    gui.add(contrastValue2.setup("CAM2 contraste", 0, 0, 1));
    
    
    vidGrabber.setDeviceID(1);
    vidGrabber.initGrabber(camWidth, camHeight);
    
    //uvcControl0
    uvcControl0.setCamera(437452800);
    uvcControl0.setAutoWhiteBalance(false);
    uvcControl0.setAutoExposure(false);
    uvcControl0.setAutoFocus(false);
    
    //uvcControl1
    uvcControl1.setCamera(487784448);
    uvcControl1.setAutoWhiteBalance(false);
    uvcControl1.setAutoExposure(false);
    uvcControl1.setAutoFocus(false);
    
    //uvcControl2
    uvcControl2.setCamera(437387264);
    uvcControl2.setAutoWhiteBalance(false);
    uvcControl2.setAutoExposure(false);
    uvcControl2.setAutoFocus(false);
    
    controls0 = uvcControl0.getCameraControls();
    controls1 = uvcControl1.getCameraControls();
    controls2 = uvcControl2.getCameraControls();
    
    
    gui.add(thresholdBrightnes.setup("threshold image valid", 0, 0, 255));
    gui.add(setsettings.setup("live settings", false));
    gui.loadFromFile("settings.xml");
    
    
    /// set gui values to uvc
    uvcControl0.setWhiteBalance(whiteValues0);
    uvcControl0.setExposure(exposureValue0);
    uvcControl0.setGain(gainValue0);
    uvcControl0.setSaturation(satValue0);
    uvcControl0.setAbsoluteFocus(focusValue0);
    uvcControl0.setBrightness(brightValue0);
    uvcControl0.setContrast(contrastValue0);

    /// set gui values to uvc
    uvcControl1.setWhiteBalance(whiteValues1);
    uvcControl1.setExposure(exposureValue1);
    uvcControl1.setGain(gainValue1);
    uvcControl1.setSaturation(satValue1);
    uvcControl1.setAbsoluteFocus(focusValue1);
    uvcControl1.setBrightness(brightValue1);
    uvcControl1.setContrast(contrastValue1);
    
    /// set gui values to uvc
    uvcControl2.setWhiteBalance(whiteValues2);
    uvcControl2.setExposure(exposureValue2);
    uvcControl2.setGain(gainValue2);
    uvcControl2.setSaturation(satValue2);
    uvcControl2.setAbsoluteFocus(focusValue2);
    uvcControl2.setBrightness(brightValue2);
    uvcControl2.setContrast(contrastValue2);
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
void camaras::update(){
    timerFoto.update();
    timerCambioCamara.update();
    
    vidGrabber.update();
    if(vidGrabber.isFrameNew())
    {
        tex.loadData(vidGrabber.getPixelsRef());
    }
    
    
    
    // OFXUVC
    //
    controls0 = uvcControl0.getCameraControls();
    controls1 = uvcControl1.getCameraControls();
    controls2 = uvcControl2.getCameraControls();
    
    if(setsettings){
        // uvcControl0
        uvcControl0.setWhiteBalance(whiteValues0);
        uvcControl0.setExposure(exposureValue0);
        uvcControl0.setGain(gainValue0);
        uvcControl0.setSaturation(satValue0);
        uvcControl0.setAbsoluteFocus(focusValue0);
        uvcControl0.setBrightness(brightValue0);
        uvcControl0.setContrast(contrastValue0);
        
        // uvcControl1
        uvcControl1.setWhiteBalance(whiteValues1);
        uvcControl1.setExposure(exposureValue1);
        uvcControl1.setGain(gainValue1);
        uvcControl1.setSaturation(satValue1);
        uvcControl1.setAbsoluteFocus(focusValue1);
        uvcControl1.setBrightness(brightValue1);
        uvcControl1.setContrast(contrastValue1);
        
        // uvcControl2
        uvcControl2.setWhiteBalance(whiteValues2);
        uvcControl2.setExposure(exposureValue2);
        uvcControl2.setGain(gainValue2);
        uvcControl2.setSaturation(satValue2);
        uvcControl2.setAbsoluteFocus(focusValue2);
        uvcControl2.setBrightness(brightValue2);
        uvcControl2.setContrast(contrastValue2);
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

