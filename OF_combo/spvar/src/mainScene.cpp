#include "mainScene.h"

mainScene::mainScene()
{
}

mainScene::~mainScene()
{
}

void mainScene::setup()
{
	m_winWidth = ofGetWindowWidth();
	m_winHeight = ofGetWindowHeight();

	ofxGuiSetDefaultWidth(m_winWidth / 4);
	ofxGuiSetDefaultHeight(m_winHeight / 20);

#ifdef TARGET_ANDROID
	eyes.load("pics/eyes.png");
	setupButton.load("pics/setupTex.png");
#else
	eyes.load("data\\pics\\eyes.png");
	setupButton.load("data\\pics\\setupTex.png");
#endif

	rectSetup.set(m_winWidth / 2 - setupButton.getWidth() / 2, m_winHeight - setupButton.getHeight(), setupButton.getWidth(), setupButton.getHeight());
	//ofAddListener(setup_click, this, &mainScene::setupOnClick);


	devices = vidGrabber.listDevices();
	for (int i = 0; i < devices.size(); i++) {
		if (devices[i].bAvailable) {
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName;
		}
		else {
			ofLogNotice() << devices[i].id << ": " << devices[i].deviceName << " - unavailable ";
		}
	}

	leftEye.setup(ofRectangle(0, 0, m_winWidth / 2, m_winHeight), devices, eye::eye_type::LEFT_EYE);
	rightEye.setup(ofRectangle(m_winWidth / 2, 0, m_winWidth / 2, m_winHeight), devices, eye::eye_type::RIGHT_EYE);

	//leftEye.setMargins(10);
	//rightEye.setMargins(10);
	
	//leftEye.setActive(true);
	//rightEye.setActive(true);

	//leftEye.changeCam(0);
	//rightEye.changeCam(1);
	
	//leftEye.rotateImage(270);

	indexLeft = indexRight = -1;

	touchInfo = "No touch/click";
}

void mainScene::update()
{
	leftEye.update();
	rightEye.update();
}

void mainScene::draw()
{
	ofBackground(0, 0, 0);

	ofSetColor(255, 255, 255);
	eyes.draw(85, 50, m_winWidth - 100, m_winHeight - 100);

	leftEye.draw();
	rightEye.draw();

	ofSetColor(0, 0, 255);
	ofLine(m_winWidth / 2, 50, m_winWidth / 2, m_winHeight - 150);
	setupButton.draw(rectSetup);

	ofSetColor(255, 255, 0);
	ofDrawBitmapString(touchInfo, 10, m_winHeight - 30);
}

void mainScene::exit()
{
	leftEye.exit();
	rightEye.exit();
}

void mainScene::setupOnClick()
{
	cout << "[INFO] Click on setup" << endl;
	leftEye.setShowGui(!leftEye.getShowGui());
	rightEye.setShowGui(!rightEye.getShowGui());
}

void mainScene::keyPressed(int key)
{
}

void mainScene::keyReleased(int key)
{
}

void mainScene::windowResized(int w, int h)
{
}

#ifdef TARGET_ANDROID
void mainScene::touchDown(int x, int y, int id)
{
	stringstream t;
	t << "Touch/Click on x: " << x << "; y: " << y << ";";
	touchInfo = t.str();
	//cout << x << " " << y << " : " << rectSetup.x << ";"<<rectSetup.y<<":"<<rectSetup.width<<endl;
	if (rectSetup.inside(x, y)) {
		setupOnClick();
		return;
	}


	/*if (leftEye.getRect().inside(x, y)) {
		indexLeft++;
		if (indexLeft == vidGrabber.listDevices().size()) indexLeft = -1;
		leftEye.changeCam(indexLeft);
	}

	if (rightEye.getRect().inside(x, y)) {
		indexRight++;
		if (indexRight == vidGrabber.listDevices().size()) indexRight = -1;
		rightEye.changeCam(indexRight);
	}*/

}

void mainScene::touchMoved(int x, int y, int id)
{
}

void mainScene::touchUp(int x, int y, int id)
{
}

void mainScene::touchDoubleTap(int x, int y, int id)
{
}

void mainScene::touchCancelled(int x, int y, int id)
{
}

void mainScene::pause()
{
}

void mainScene::stop()
{
}

void mainScene::resume()
{
}

void mainScene::reloadTextures()
{
}

bool mainScene::backPressed()
{
	return false;
}

void mainScene::okPressed()
{
}

void mainScene::cancelPressed()
{
}

#else

void mainScene::mouseMoved(int x, int y)
{
}

void mainScene::mouseDragged(int x, int y, int button)
{
}

void mainScene::mousePressed(int x, int y, int button)
{
	stringstream t;
	t << "Touch/Click on x: " << x << "; y: " << y << ";";
	touchInfo = t.str();

	if (rectSetup.inside(x, y)) {
		setupOnClick();
		return;
	}

	/*
	if (leftEye.getRect().inside(x, y)) {
	indexLeft++;
	if (indexLeft == vidGrabber.listDevices().size()) indexLeft = -1;
	leftEye.changeCam(indexLeft);
	}

	if (rightEye.getRect().inside(x, y)) {
	indexRight++;
	if (indexRight == vidGrabber.listDevices().size()) indexRight = -1;
	rightEye.changeCam(indexRight);
	}
	*/
}

void mainScene::mouseReleased(int x, int y, int button)
{
}

void mainScene::mouseEntered(int x, int y)
{
}

void mainScene::mouseExited(int x, int y)
{
}

void mainScene::dragEvent(ofDragInfo dragInfo)
{
}

void mainScene::gotMessage(ofMessage msg)
{
}
#endif


