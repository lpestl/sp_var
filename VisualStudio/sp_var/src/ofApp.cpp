#include "ofApp.h"

ofApp::ofApp()
{
	main_sc = new mainScene();
}

ofApp::~ofApp()
{
	delete main_sc;
}

//--------------------------------------------------------------
void ofApp::setup(){
	main_sc->setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	main_sc->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	main_sc->draw();
}

void ofApp::exit()
{
	main_sc->exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
	main_sc->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	main_sc->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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
