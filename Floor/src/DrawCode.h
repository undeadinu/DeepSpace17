#pragma once
#include "ofMain.h"

class DrawCode {
public:
	DrawCode();
	void draw();
	~DrawCode();

	vector<string> code;
	vector<string> synth;
	ofTrueTypeFont font;
};

