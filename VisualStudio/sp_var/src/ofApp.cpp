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
#ifdef TARGET_ANDROID
	// initialize the accelerometer
	ofxAccelerometer.setup();
#endif
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
void ofApp::windowResized(int w, int h) {

}

#ifdef TARGET_ANDROID
//--------------------------------------------------------------
void ofApp::touchDown(int x, int y, int id)
{
	main_sc->touchDown(x, y, id);
}

//--------------------------------------------------------------
void ofApp::touchMoved(int x, int y, int id)
{
}

//--------------------------------------------------------------
void ofApp::touchUp(int x, int y, int id)
{
}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(int x, int y, int id)
{
}

//--------------------------------------------------------------
void ofApp::touchCancelled(int x, int y, int id)
{
}

//--------------------------------------------------------------
void ofApp::swipe(ofxAndroidSwipeDir swipeDir, int id)
{
}

//--------------------------------------------------------------
void ofApp::pause()
{
}

//--------------------------------------------------------------
void ofApp::stop()
{
}

//--------------------------------------------------------------
void ofApp::resume()
{
}

//--------------------------------------------------------------
void ofApp::reloadTextures()
{
}

//--------------------------------------------------------------
bool ofApp::backPressed()
{
	return false;
}

//--------------------------------------------------------------
void ofApp::okPressed()
{
}

//--------------------------------------------------------------
void ofApp::cancelPressed()
{
}

#else
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	main_sc->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	main_sc->mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

#endif
