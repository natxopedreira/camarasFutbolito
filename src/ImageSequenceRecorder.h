/*
 
 Based on code by Memo from this thread:
 http://forum.openframeworks.cc/index.php?topic=1687.0
 
 */

#include "ofMain.h"

typedef struct {
    string fileName;
    ofPixels pixels;
} QueuedImage;

class ImageSequenceRecorder : public ofThread {
public:
    
    queue<QueuedImage> q;
    
    void threadedFunction() {
        while(isThreadRunning()) {
            if(!q.empty()){
                QueuedImage i = q.front();
                ofSaveImage(i.pixels, i.fileName);
                q.pop();
            } else {
                stopThread();
            }
        }
    }
    
    void addFrame(ofPixels &_pixels, string _fileName) {
        QueuedImage qImage;
        qImage.fileName = _fileName;
        qImage.pixels = _pixels;
        q.push(qImage);
        if(!isThreadRunning()){
            startThread(false, true);
        }
    }
};