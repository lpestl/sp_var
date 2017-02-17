#pragma once

#include "ofMain.h"
#include "eye.h"

class mainScene
{
public:
	mainScene();
	~mainScene();

	void setup();
	void update();
	void draw();
	void exit();

	void setupOnClick();

	void keyPressed(int key);
	void keyReleased(int key);
	void windowResized(int w, int h);

#ifdef TARGET_ANDROID
	void touchDown(int x, int y, int id);
	void touchMoved(int x, int y, int id);
	void touchUp(int x, int y, int id);
	void touchDoubleTap(int x, int y, int id);
	void touchCancelled(int x, int y, int id);
	//void swipe(ofxAndroidSwipeDir swipeDir, int id);

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
	string m_name;
	int m_id_scene;

	ofImage eyes, setupButton;
	int m_winWidth, m_winHeight;

	ofRectangle rectSetup;

	eye leftEye, rightEye;
	int indexLeft, indexRight;

	ofVideoGrabber vidGrabber;
	vector<ofVideoDevice> devices;

	string touchInfo;
};

