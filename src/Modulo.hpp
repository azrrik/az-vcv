#include "plugin.hpp"
#include <iomanip>

std::string padZero(int length, int i) {
	std::ostringstream str;
	str << std::setw(length) << std::setfill('0') << i;
	return str.str();
}

static const int PRIMES = 167;
int primes[PRIMES + 1] = {
	   2,    3,    5,    7,   11,   13,   17,   19,   23,   29,   31,   37,   41,   43, 
	  47,   53,   59,   61,   67,   71,   73,   79,   83,   89,   97,  101,  103,  107,  
	 109,  113,  127,  131,  137,  139,  149,  151,  157,  163,  167,  173,  179,  181,  
	 191,  193,  197,  199,  211,  223,  227,  229,  233,  239,  241,  251,  257,  263,  
	 269,  271,  277,  281,  283,  293,  307,  311,  313,  317,  331,  337,  347,  349,  
	 353,  359,  367,  373,  379,  383,  389,  397,  401,  409,  419,  421,  431,  433,  
	 439,  443,  449,  457,  461,  463,  467,  479,  487,  491,  499,  503,  509,  521,  
	 523,  541,  547,  557,  563,  569,  571,  577,  587,  593,  599,  601,  607,  613,  
	 617,  619,  631,  641,  643,  647,  653,  659,  661,  673,  677,  683,  691,  701, 
	 709,  719,  727,  733,  739,  743,  751,  757,  761,  769,  773,  787,  797,  809,  
	 811,  821,  823,  827,  829,  839,  853,  857,  859,  863,  877,  881,  883,  887, 
	 907,  911,  919,  929,  937,  941,  947,  953,  967,  971,  977,  983,  991,  997
};

struct WhiteKey : app::SvgSwitch {
	WhiteKey() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/WhiteKey.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/WhiteKeySelected.svg")));
	}
};

struct BlackKey : app::SvgSwitch {
	BlackKey() {
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/BlackKey.svg")));
		addFrame(APP->window->loadSvg(asset::plugin(pluginInstance, "res/BlackKeySelected.svg")));
	}
};


struct SmallBlackKnob : Davies1900hKnob {
	SmallBlackKnob() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SmallBlackKnob.svg")));
	}
};

struct LargeBlackKnob : Davies1900hKnob {
	LargeBlackKnob() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/LargeBlackKnob.svg")));
	}
};

struct BigLabel : Label {
	BigLabel() {
		fontSize = 30;
		color = nvgRGB(233, 233, 233);
	}
};

template <typename TBase>
struct HiLight : TBase {
	HiLight() {
		this->box.size = app::mm2px(math::Vec(10, 10));;
		this->bgColor = nvgRGBA(0, 0, 0, 100);
		this->borderColor = nvgRGBA(0, 0, 0, 100);
	}

	void drawLight(const widget::Widget::DrawArgs& args) override {
		nvgBeginPath(args.vg);
		nvgRoundedRect(args.vg, 0, 0, this->box.size.x, this->box.size.y, 5.f);

		// Background
		if (this->bgColor.a > 0.0) {
			nvgFillColor(args.vg, this->bgColor);
			nvgFill(args.vg);
		}

		// Foreground
		if (this->color.a > 0.0) {
			nvgFillColor(args.vg, this->color);
			nvgFill(args.vg);
		}

		// Border
		if (this->borderColor.a > 0.0) {
			nvgStrokeWidth(args.vg, 0.5);
			nvgStrokeColor(args.vg, this->borderColor);
			nvgStroke(args.vg);
		}
	}
};

struct CKSSInverse : app::SvgSwitch {
	CKSSInverse() {
		addFrame(APP->window->loadSvg(asset::system("res/ComponentLibrary/CKSS_1.svg")));
		addFrame(APP->window->loadSvg(asset::system("res/ComponentLibrary/CKSS_0.svg")));
	}
};
