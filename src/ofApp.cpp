#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(0,0,0);
	    
	ofEnableAlphaBlending();

	mov.initGrabber(ofGetWidth(), ofGetHeight());
	img.allocate(ofGetWidth(), ofGetHeight());
	gray.allocate(ofGetWidth(), ofGetHeight());

	tracker.setup(ofGetWidth(), ofGetHeight());
	
}

//--------------------------------------------------------------
void ofApp::update(){

	mov.update();
	if (mov.isFrameNew()) {
	    img.setFromPixels(mov.getPixels(), ofGetWidth(), ofGetHeight());
	    gray = img;
	    // tracker.update(gray.getPixels());
	    //tracker.setFromPixels(gray.getPixels());
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0xffffff);
    mov.draw(0, 0);
    
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
