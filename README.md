camarasFutbolito
================

futbolito uruguay

control de camaras para c920 con ofxUVC


addons
- ofxImageSequenceRecorder
- ofxSimpleTimer
- ofxYAML
- ofxGui
- ofxUVC


probado con 3 camaras c920 en un macmini 2.5 i5


modificar ofQtKitGrabber para obtener el location id instead el nombre de la cam

vector<string>& ofQTKitGrabber::listVideoDevices(){
    
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
	NSArray* videoDevices = [QTKitVideoGrabber listVideoDevices];
	videoDeviceVec.clear();
	for (id object in videoDevices){
		//string str = [[object description] UTF8String];
        UInt32 locationID = 0;
        sscanf( [[object uniqueID] UTF8String], "0x%8x", &locationID );
        videoDeviceVec.push_back(ofToString(locationID));
	}
	[pool release];
    
	return videoDeviceVec;
}
