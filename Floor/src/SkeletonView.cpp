#include "SkeletonView.h"
#include "ofApp.h"

SkeletonView::SkeletonView(){
}

void SkeletonView::draw() {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	float circleSize = ofGetWidth() / 32.0;
	ofNoFill();
	ofSetLineWidth(4);
	/*
	//draw circle  
	for (auto it = app->oscSender->cursorList.begin(); it != app->oscSender->cursorList.end(); it++) {
		ofxTuioCursor *blob = (*it);
		ofDrawCircle(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight(), circleSize);
	}
	for (auto it = app->oscSender->objectList.begin(); it != app->oscSender->objectList.end(); it++) {
		ofxTuioObject *blob = (*it);
		ofDrawCircle(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight(), circleSize);
	}
	*/
	ofSetColor(100);
	ofSetCircleResolution(64);
	for (int i = 0; i < app->objectController->ugenObjects.size(); i++) {
		ofVec2f pos = app->objectController->ugenObjects[i]->pos;
		ofDrawCircle(pos.x * ofGetWidth(), pos.y * ofGetHeight(), circleSize);
	}
	ofSetColor(0, 120, 120);
	ofSetCircleResolution(8);
	for (int i = 0; i < app->objectController->fxObjects.size(); i++) {
		ofVec2f pos = app->objectController->fxObjects[i]->pos;
		ofDrawCircle(pos.x * ofGetWidth(), pos.y * ofGetHeight(), circleSize);
	}

	//draw lines
	ofNoFill();
	ofSetLineWidth(3);
	for (auto i = app->oscSender->cursorList.begin(); i != app->oscSender->cursorList.end(); i++) {
		for (auto j = i; j != app->oscSender->cursorList.end(); j++) {
			ofxTuioCursor *blobi = (*i);
			ofxTuioCursor *blobj = (*j);
			ofVec2f begin = ofVec2f(blobi->getX()*ofGetWidth(), blobi->getY()*ofGetHeight());
			ofVec2f end = ofVec2f(blobj->getX()*ofGetWidth(), blobj->getY()*ofGetHeight());
			float dist = begin.distance(end);
			ofSetColor(255, ofMap(dist, 0, ofGetWidth() / 2, 191, 0));
			ofDrawLine(begin.x, begin.y, end.x, end.y);
		}
	}
	for (auto i = app->oscSender->objectList.begin(); i != app->oscSender->objectList.end(); i++) {
		for (auto j = i; j != app->oscSender->objectList.end(); j++) {
			ofxTuioObject *blobi = (*i);
			ofxTuioObject *blobj = (*j);
			ofVec2f begin = ofVec2f(blobi->getX()*ofGetWidth(), blobi->getY()*ofGetHeight());
			ofVec2f end = ofVec2f(blobj->getX()*ofGetWidth(), blobj->getY()*ofGetHeight());
			float dist = begin.distance(end);
			ofSetColor(255, ofMap(dist, 0, ofGetWidth() / 2, 191, 0));
			ofDrawLine(begin.x, begin.y, end.x, end.y);
		}
	}
	ofSetLineWidth(1);
	ofFill();
}

SkeletonView::~SkeletonView(){
}
