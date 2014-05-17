//
//  camaras.cpp
//  example-ofxUVC
//
//  Created by Ignacio Pedreira gonzalez on 15/05/14.
//
//

#include "camaras.h"


//--------------------------------------------------------------
void camaras::setup(int _indexCam, int _maxPhotos, int _photoSpeed){
    
    yaml.load("camera_settings.yml");
    
    int cameraToUse;
    yaml.doc["cameraToUse"] >> cameraToUse;
    
    int vendorId, productId, interfaceNum;
    yaml.doc["cameras"][cameraToUse]["vendorId"] >> vendorId;
    yaml.doc["cameras"][cameraToUse]["productId"] >> productId;
    yaml.doc["cameras"][cameraToUse]["interfaceNum"] >> interfaceNum;
    yaml.doc["cameras"][cameraToUse]["name"] >> cameraName;
    yaml.doc["cameras"][cameraToUse]["width"] >> camWidth;
    yaml.doc["cameras"][cameraToUse]["height"] >> camHeight;
    
    vidGrabber.initGrabber(camWidth, camHeight);
    
    int deviceId = 0;
    availableCams = vidGrabber.listVideoDevices();
    
    for(int i = 0; i < availableCams.size(); i++){
        if(availableCams.at(i) == cameraName){
            deviceId = i;
        }
    }
    
    vidGrabber.setDeviceID(deviceId);
    
    uvcControl.useCamera(vendorId, productId, interfaceNum);
    uvcControl.setAutoWhiteBalance(false);
    uvcControl.setAutoExposure(false);
    uvcControl.setAutoFocus(false);
    controls = uvcControl.getCameraControls();
    
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
    
    
    /// thread para guardar fotos
    recorder.setPrefix(ofToDataPath("fotos/"));
    recorder.setFormat("jpg");
    recorder.startThread(false, true);
    
    maxPhotosPerCamera = _maxPhotos;
    madePhotos = 0;
    
    indexCamera = _indexCam;
    
    //timers
    timerFoto.setup(_photoSpeed);
    timerCambioCamara.setup(1500);
    
    ofAddListener(timerFoto.TIMER_COMPLETE , this, &camaras::timerFotoComplete);
    ofAddListener(timerCambioCamara.TIMER_COMPLETE , this, &camaras::timerCambioCamaraComplete);
}

//--------------------------------------------------------------
void camaras::update(){
    timerFoto.update();
    
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
    
    ofSetColor(255);
    timerFoto.draw(camWidth - 250, 20);
    timerCambioCamara.draw(camWidth - 250, 45);
    
    gui.draw();
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
            cout << "FOTOOOOOO" << endl;
            recorder.addFrame(vidGrabber.getPixelsRef());
        }
        madePhotos++;
        
    }else{
        // no mas fotos

        timerFoto.stop();
        madePhotos = 0;
        
        //si hay mas camaras
        //cambia la camara
        // si no hay mas camaras se acabo
        indexCamera++;
        
        if(indexCamera<availableCams.size()){
            timerCambioCamara.start(false);
        }else{
            indexCamera = 0;
        }

    }
}

//--------------------------------------------------------------
void camaras::timerCambioCamaraComplete( int &args ){
    //camara cambiada
    cout << "CAMARA CAMBIADA" << endl;
    dispara();
}
//--------------------------------------------------------------
void camaras::dispara(){
    timerFoto.start(true);
}

