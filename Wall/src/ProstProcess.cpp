#include "PostProcess.h"
#include "ofApp.h"

PostProcess::PostProcess() {
	scale = 1.0;
	usePostFx = false;
	currentFx = -1;

	fx = new ofxSCSynth("fx");
	fx->create(0, 0);

	mix = new ofxSCSynth("mix");
	mix->create(0, 0);

	//Postprocessing
	post.init(ofGetWidth() / scale, ofGetHeight() / scale);

	kaleido = post.createPass<KaleidoscopePass>();
	noise = post.createPass<NoiseWarpPass>();
	toon = post.createPass<ToonPass>();
	pixel = post.createPass<PixelatePass>();
	sss = post.createPass<FakeSSSPass>();

	darken = post.createPass<LimbDarkeningPass>();
	/*
	contrast = post.createPass<ContrastPass>();
	edge = post.createPass<EdgePass>();
	god = post.createPass<GodRaysPass>();
	conv = post.createPass<ConvolutionPass>();
	edge = post.createPass<EdgePass>();
	dof = post.createPass<DofPass>();
	vtilt = post.createPass<VerticalTiltShifPass>();
	htilt = post.createPass<HorizontalTiltShifPass>();
	fxaa = post.createPass<FxaaPass>();
	rgb = post.createPass<RGBShiftPass>();
	god = post.createPass<GodRaysPass>();
	bleach = post.createPass<BleachBypassPass>();
	*/

	resetPostProcess();
}

void PostProcess::update() {

}

void PostProcess::draw() {

}

void PostProcess::resetPostProcess() {
	kaleido->setEnabled(false);
	noise->setEnabled(false);
	pixel->setEnabled(false);
	toon->setEnabled(false);
	sss->setEnabled(false);

	darken->setEnabled(true);

	/*
	contrast->setEnabled(false);
	edge->setEnabled(false);
	conv->setEnabled(false);
	dof->setEnabled(false);
	sss->setEnabled(false);
	fxaa->setEnabled(false);
	vtilt->setEnabled(false);
	htilt->setEnabled(false);
	god->setEnabled(false);
	bleach->setEnabled(false);
	fxaa->setEnabled(false);
	rgb->setEnabled(false);
	*/
	//lut->setEnabled(false);

}
void PostProcess::updateFx(int type, ofVec2f pos) {
	float length = pos.distance(ofVec2f(0.5, 0.5));
	switch (type) {
	case 0:
		kaleido->setSegments(length * 10.0);
		break;
	case 1:
		noise->setAmplitude(length * 0.5);
		break;
	case 2:
		//toon->setLevel(length * 10.0);
		break;
	case 3:
		pixel->resolution = ofVec2f((1.0 - pos.x) * 40.0, (1.0 - pos.y) * 40.0);
		break;
	case 4:
		break;
	}
}

void PostProcess::addFx(int type, int id) {
	ofApp *app = ((ofApp*)ofGetAppPtr());
	resetPostProcess();
	int n = type % 5;
	switch (n) {
	case 0:
		kaleido->setEnabled(true);
		break;
	case 1:
		noise->setEnabled(true);
		break;
	case 2:
		toon->setEnabled(true);
		toon->setLevel(4.0);
		break;
	case 3:
		pixel->setEnabled(true);
		break;
	case 4:
		sss->setEnabled(true);
		break;
	}

	//add sound fx
	if (id != currentFx) {
		if (usePostFx) {
			postFx->free();
			usePostFx = true;
		}

		switch (type) {
		case 0:
			postFx = new ofxSCSynth("comb");
			postFx->set("delaytime", ofRandom(0.02, 0.06));
			postFx->create(0, 0);
			break;
		case 1:
			postFx = new ofxSCSynth("am");
			postFx->set("ringFreq", ofRandom(6.0, 10.0));
			postFx->create(0, 0);
			break;
		case 2:
			postFx = new ofxSCSynth("distort");
			postFx->create(0, 0);
			break;
		case 3:
			postFx = new ofxSCSynth("bpf");
			postFx->set("freq", ofRandom(8000, 16000));
			postFx->set("rq", 0.1);
			postFx->create(0, 0);
			break;
		case 4:
			postFx = new ofxSCSynth("bpf");
			postFx->set("freq", ofRandom(200, 800));
			postFx->set("rq", 0.1);
			postFx->create(0, 0);
			break;
		}
		currentFx = id;
	}
}

void PostProcess::deleteFx() {
	currentFx = -1;
}

PostProcess::~PostProcess() {
}
