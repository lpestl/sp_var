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
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

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


};

