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
void camaras::averageColorOfArea(int cx, int cy, int avgW,int avgH){
	//average a certain area around a point in a pixel area
	//return the resulting averaged color in hex/int
	int rr = 0;
	int gg = 0;
	int bb = 0;
	float cnt=0;
	for (int xx = cx-avgW; xx <= cx+avgW; xx++){
		for (int yy = cy-avgH; yy <= cy+avgH; yy++){
			int cxx = xx;
			int cyy = yy;
			if(xx < 0) cxx = 0;
			if(xx >= camWidth) cxx = camWidth-1;
			if(yy < 0) cyy = 0;
			if(yy >= camHeight) cyy = camHeight-1;
            
			//rr = rr + pixels[(cyy * camWidth*3) + cxx * 3 + 0];
			//gg = gg + pixels[(cyy * camWidth*3) + cxx * 3 + 1];
			//bb = bb + pixels[(cyy * camWidth*3) + cxx * 3 + 2];
			cnt++;
		}
	}
	rr = int(rr/cnt);
	gg = int(gg/cnt);
	bb = int(bb/cnt);
	int lookUpIdx = (rr << 16) + (gg << 8) + bb;
	return lookUpIdx;
}

//--------------------------------------------------------------
void camaras::timerFotoComplete( int &args ){
    //saca foto
    if (madePhotos<maxPhotosPerCamera) {
        cout << "FOTOOOOOO" << endl;
        recorder.addFrame(vidGrabber.getPixelsRef());
        
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

