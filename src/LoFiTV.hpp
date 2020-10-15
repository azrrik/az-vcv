#include "plugin.hpp"


struct RoundSmallWhiteKnob : RoundKnob {
	RoundSmallWhiteKnob() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SmallWhiteKnob.svg")));
	}
};


struct RoundSmallRedKnob : RoundKnob {
	RoundSmallRedKnob() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SmallRedKnob.svg")));
	}
};


struct RoundSmallGreenKnob : RoundKnob {
	RoundSmallGreenKnob() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SmallGreenKnob.svg")));
	}
};


struct RoundSmallBlueKnob : RoundKnob {
	RoundSmallBlueKnob() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SmallBlueKnob.svg")));
	}
};


struct PJ301MDarkPort : app::SvgPort {
	PJ301MDarkPort() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/PJ301MDark.svg")));
	}
};