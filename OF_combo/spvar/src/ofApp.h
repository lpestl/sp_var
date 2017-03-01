#pragma once

/*
For different platform using:

#ifdef TARGET_ANDROID

#else

#endif

*/

#include "ofMain.h"
#ifdef TARGET_ANDROID
#include "ofxAndroid.h"
#include "ofxAccelerometer.h"
#endif
#include "mainScene.h"

#ifdef TARGET_ANDROID
class ofApp : public ofxAndroidApp {
#else
class ofApp : public ofBaseApp {
#endif
	public:
		ofApp();
		~ofApp();

		void setup();
		void update();
		void draw();
		void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void windowResized(int w, int h);

#ifdef TARGET_ANDROID
		void touchDown(int x, int y, int id);
		void touchMoved(int x, int y, int id);
		void touchUp(int x, int y, int id);
		void touchDoubleTap(int x, int y, int id);
		void touchCancelled(int x, int y, int id);
		void swipe(ofxAndroidSwipeDir swipeDir, int id);

		void pause();
		void stop();
		void resume();
		void reloadTextures();

		bool backPressed();
		void okPressed();
		void cancelPressed();
#else
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
#endif
		
		
	private:
		mainScene *main_sc;
};
