#include "ofApp.h"

#include <ARToolKitPlus/TrackerSingleMarker.h>  
using ARToolKitPlus::TrackerSingleMarker;  
#include <ARToolKitPlus/TrackerMultiMarker.h>  
//--------------------------------------------------------------

static const 	int       		width = 640, height = 480, bpp = 1;  
static   		size_t        	numPixels = width*height*bpp;  
static    		unsigned char 	*cameraBuffer = new unsigned char[numPixels];  
static 			bool 			useBCH = false;  
static			bool 			bDraw = false;  
vector<int> markerId ;  
float mWidth = width;  
float mHeight = height; 
ARToolKitPlus::TrackerSingleMarker *tricker; 

void ofApp::setup(){
	ofBackground(0,0,0);
	    
	ofEnableAlphaBlending();

	/*
	mov.initGrabber(ofGetWidth(), ofGetHeight());
	img.allocate(ofGetWidth(), ofGetHeight());
	gray.allocate(ofGetWidth(), ofGetHeight());
	tracker.setup(ofGetWidth(), ofGetHeight());
	*/

	mov.initGrabber(width, height);
	img.allocate(width, height);
	gray.allocate(width, height);
	tracker.setup(width, height);
	


	tricker = new TrackerSingleMarker (width, height, 8, 16, 16, 16, 1);
	tricker->setPixelFormat(ARToolKitPlus::PIXEL_FORMAT_LUM);
	
	if (!tricker->init((const char *)ofToDataPath("Logitech_Notebook_Pro.cal").c_str(), 1.0f, 5000.0f)) // load MATLAB file  
    {  
        printf("ERROR: init() failed\n");  
        printf("ERROR: init() failed\n");  
        delete cameraBuffer;  
        delete tricker;  
        std::exit(-1);  
    }  

    tricker->setPatternWidth(80);  

    // the marker in the BCH test image has a thin border...  
    tricker->setBorderWidth(useBCH ? 0.125f : 0.250f);  

    // set a threshold. alternatively we could also activate automatic thresholding  
    tricker->setThreshold(150);  

    // let's use lookup-table undistortion for high-speed  
    // note: LUT only works with images up to 1024x1024  
    tricker->setUndistortionMode(ARToolKitPlus::UNDIST_LUT);

    tricker->setMarkerMode(useBCH ? ARToolKitPlus::MARKER_ID_BCH : ARToolKitPlus::MARKER_ID_SIMPLE);  
    tricker->setMarkerMode (ARToolKitPlus::MARKER_TEMPLATE);  
    tricker->setPatternWidth (80);  
    tricker->addPattern ((const char *)ofToDataPath("patt.hiro").c_str());
}

//--------------------------------------------------------------
void ofApp::update(){
	mWidth = ofGetWidth();  
	mHeight = ofGetHeight();

	mov.update();
	if (mov.isFrameNew()) {
	    img.setFromPixels(mov.getPixels(), width, height);
	    gray = img;

	    markerId = tricker->calc(gray.getPixels());  
        tricker->selectBestMarkerByCf();  
        float conf = tricker->getConfidence();  
        if ( conf > 0.0 ){  
            bDraw = true;  
        }else{
        	bDraw = false;	
        } 
	    // tracker.update(gray.getPixels());
	    //tracker.setFromPixels(gray.getPixels());
	    if(markerId.size()>0)  
        {  
        	ofSetColor(255, 0, 255);
        	ofCircle(200, 300, 60);
			printf("\n\nFound marker %d  (confidence %d%%)\n\nPose-Matrix:\n  ", markerId[0], (int(conf * 100.0f)));  
			for (int i = 0; i < 16; i++)  
			printf("%.2f  %s", tricker->getModelViewMatrix()[i], (i % 4 == 3) ? "\n  " : "");  
        }else{
        	ofSetColor(0, 255, 255);
        	ofCircle(200, 300, 60);
        }
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0xffffff);
    mov.draw(0, 0);
    
    // tracker.draw(width, ofGetHeight());
    
    // int myIndex = tracker.getMarkerIndex(0);
    // if(myIndex>=0){
    	/*
    	ARMarkerInfo &m = tracker.markers[i];
        tracker.loadMarkerModelViewMatrix(m);
    	ofSetColor(255, 255, 0, 100);
        ofCircle(0,0,25);
        ofSetColor(0);
        ofDrawBitmapString(ofToString(m.id),0,0);
        */
    //     printf("hai");
    // }
    /*
    for (int i=0; i<tracker.markers.size(); i++) {
        ARMarkerInfo &m = tracker.markers[i];
        tracker.loadMarkerModelViewMatrix(m);
        ofSetColor(255, 255, 0, 100);
        ofCircle(0,0,25);
        ofSetColor(0);
        ofDrawBitmapString(ofToString(m.id),0,0);
    }
    */
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') mov.videoSettings();
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
