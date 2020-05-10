#include "plugin.hpp"
#include <iomanip>

std::string padZero(int length, int i) {
	std::ostringstream str;
	str << std::setw(length) << std::setfill('0') << i;
	return str.str();
}

struct Modulo : Module {
	int primes[100] = {
		  2,   3,   5,   7,  11,  13,  17,  19,  23,  29,  31,  37,  41,  43,
		 47,  53,  59,  61,  67,  71,  73,  79,  83,  89,  97, 101, 103, 107, 
		109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 
		191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 
		269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 
		353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 
		439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 
		523, 541
	};

	enum ParamIds {
		C0_PARAM,
		DB0_PARAM,
		D0_PARAM,
		EB0_PARAM,
		E0_PARAM,
		F0_PARAM,
		GB0_PARAM,
		G0_PARAM,
		AB0_PARAM,
		A0_PARAM,
		BB0_PARAM,
		B0_PARAM,
		C1_PARAM,
		DB1_PARAM,
		D1_PARAM,
		EB1_PARAM,
		E1_PARAM,
		F1_PARAM,
		GB1_PARAM,
		G1_PARAM,
		AB1_PARAM,
		A1_PARAM,
		BB1_PARAM,
		B1_PARAM,
		C2_PARAM,
		DB2_PARAM,
		D2_PARAM,
		EB2_PARAM,
		E2_PARAM,
		F2_PARAM,
		GB2_PARAM,
		G2_PARAM,
		AB2_PARAM,
		A2_PARAM,
		BB2_PARAM,
		B2_PARAM,	
		LENGTH_ATV_PARAM,
		LENGTH_PARAM,
		STEP_ATV_PARAM,
		STEP_PARAM,
		PRIME_STEP_PARAM,
		PRIME_LENGTH_PARAM,
		SHIFT_PARAM,
		NUM_PARAMS
	};
	enum InputIds {
		LENGTH_CV_INPUT,
		STEP_CV_INPUT,
		CLOCK_INPUT,
		RESET_INPUT,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT_OUTPUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		C0_LIGHT,
		DB0_LIGHT,
		D0_LIGHT,
		EB0_LIGHT,
		E0_LIGHT,
		F0_LIGHT,
		GB0_LIGHT,
		G0_LIGHT,
		AB0_LIGHT,
		A0_LIGHT,
		BB0_LIGHT,
		B0_LIGHT,
		C1_LIGHT,
		DB1_LIGHT,
		D1_LIGHT,
		EB1_LIGHT,
		E1_LIGHT,
		F1_LIGHT,
		GB1_LIGHT,
		G1_LIGHT,
		AB1_LIGHT,
		A1_LIGHT,
		BB1_LIGHT,
		B1_LIGHT,
		C2_LIGHT,
		DB2_LIGHT,
		D2_LIGHT,
		EB2_LIGHT,
		E2_LIGHT,
		F2_LIGHT,
		GB2_LIGHT,
		G2_LIGHT,
		AB2_LIGHT,
		A2_LIGHT,
		BB2_LIGHT,
		B2_LIGHT,
		NUM_LIGHTS
	};

	Modulo() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(DB0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(EB0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(GB0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(AB0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(BB0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(D0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(E0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(F0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(G0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(A0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(B0_PARAM, 0.f, 1.f, 0.f, "");
		configParam(DB1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(EB1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(GB1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(AB1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(BB1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(D1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(E1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(F1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(G1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(A1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(B1_PARAM, 0.f, 1.f, 0.f, "");
		configParam(DB2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(EB2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(GB2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(AB2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(BB2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(D2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(E2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(F2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(G2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(A2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(B2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(LENGTH_ATV_PARAM, -10.f, 10.f, 0.f, "Length Attenuverter");
		configParam(LENGTH_PARAM, 0.f, 33.f, 0.f, "Length");
		configParam(STEP_ATV_PARAM, -10.f, 10.f, 0.f, "Step Attenuverter");
		configParam(STEP_PARAM, 0.f, 33.f, 0.f, "Step");
		configParam(PRIME_STEP_PARAM, 0.f, 1.f, 1.f, "Only Primes");
		configParam(PRIME_LENGTH_PARAM, 0.f, 1.f, 1.f, "Only Primes");
		configParam(SHIFT_PARAM, 0.f, 1.f, 0.f, "Shift");
	}

	static const int N = 36;
	int notes[N];
	dsp::SchmittTrigger trigger;
	dsp::SchmittTrigger resetTrigger;
	int current = 0;
	Label *lengthLabel, *stepLabel;

	bool primeLength = true;
	bool primeStep = true;

	void process(const ProcessArgs& args) override {
		int length = (int) (
			(params[LENGTH_ATV_PARAM].getValue() * inputs[LENGTH_CV_INPUT].getVoltage()) + params[LENGTH_PARAM].getValue()
		);
		length = clamp(length, 0, 99);
		primeLength = (bool) params[PRIME_LENGTH_PARAM].getValue();
		length = primeLength ? primes[length] : length;
		lengthLabel->text = padZero(3, length);


		int step = (int) (
			(params[STEP_ATV_PARAM].getValue() * inputs[STEP_CV_INPUT].getVoltage()) + params[STEP_PARAM].getValue()
		);
		step = clamp(step, 0, 99);
		primeStep = (bool) params[PRIME_STEP_PARAM].getValue();
		step = primeStep ? primes[step] : step;
		stepLabel->text = padZero(3, step);

		if (resetTrigger.process(inputs[RESET_INPUT].getVoltage())) {
			current = 0;
		}

		if (trigger.process(inputs[CLOCK_INPUT].getVoltage())) {
 
			std::vector<int> activeNotes;			
			for (int j = 0; j < N; j++) {
				int note = params[j].getValue();

				if (note == 1) {
					activeNotes.push_back(j);
				}
			}

			int shift = (int) (params[SHIFT_PARAM].getValue() * length);

			int out = (activeNotes.size() != 0 && length != 0) ? 
				activeNotes[((step * (current + shift)) % length) % activeNotes.size()] : 0;


			// int out = 0;
			// if (activeNotes.size() != 0 && length != 0) {
			// 	out = activeNotes[((step * i) % length) % activeNotes.size()];
				
			// }
			for (int k = 0; k < NUM_LIGHTS; k++) {
				lights[k].setBrightness(0.f);
			}

			lights[out].setBrightness(1.f);


							



			// // DEBUG("WTF? %i %i %i", length, steps, i);

			// notes[0] = (int) params[C0_PARAM].getValue();
			// notes[1] = (int) params[DB0_PARAM].getValue();
			// notes[2] = (int) params[D0_PARAM].getValue();
			// notes[3] = (int) params[EB0_PARAM].getValue();
			// notes[4] = (int) params[E0_PARAM].getValue();
			// notes[5] = (int) params[F0_PARAM].getValue();
			// notes[6] = (int) params[GB0_PARAM].getValue();
			// notes[7] = (int) params[G0_PARAM].getValue();
			// notes[8] = (int) params[AB0_PARAM].getValue();
			// notes[9] = (int) params[A0_PARAM].getValue();
			// notes[10] = (int) params[BB0_PARAM].getValue();
			// notes[11] = (int) params[B0_PARAM].getValue();

			// int p = step * i;
			// // DEBUG("WTF2   %i = %i * %i", p, steps, i);


			// int current = (length != 0) ? p % length : 0;
			// // DEBUG("i=%i current=%i   %i %% %i", i, current, p, length);


			// std::string t = "";
			// std::vector<int> activeNotes;
			// for (int j = 0; j < N; j++) {
			// 	t += std::to_string(notes[j]);
			// 	if (j != (N - 1))
			// 		t += ", ";

			// 	if (notes[j] == 1) {
			// 		activeNotes.push_back(j);
			// 	}
			// }

			// int activeNotesN = activeNotes.size();
			
			// int out = 0;
			// if (activeNotesN != 0) {
			// 	int index = current % activeNotesN;
			// 	// int shift = current / activeNotesN;
			// 	out = activeNotes[index];
			// }

			DEBUG("out=%i shift=%i", out, shift);
			// DEBUG("activeNotesN=%i", activeNotesN);
			// DEBUG("index=%i", index);
			// DEBUG("shift=%i", shift);
			// DEBUG("out=%i activeNotesN=%i index=%i shift=%i", out, activeNotesN, index, shift); 


			// DEBUG("[%s] -> (%i, %i)", t.c_str(), length, steps);

			if (current >= length - 1) {
				current = 0;
			} else {
				current++;
			}

			outputs[OUT_OUTPUT].setVoltage(out / 12.f);
		}		
	}
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


struct SmallWhiteKnob : Davies1900hKnob {
	SmallWhiteKnob() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/SmallWhite.svg")));
	}
};

struct LargeWhiteKnob : Davies1900hKnob {
	LargeWhiteKnob() {
		setSvg(APP->window->loadSvg(asset::plugin(pluginInstance, "res/LargeWhite.svg")));
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


struct ModuloWidget : ModuleWidget {
	ModuloWidget(Modulo* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/modulo.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(14.5, 12.5)), module, Modulo::DB2_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(24.5, 12.5)), module, Modulo::EB2_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(44.5, 12.5)), module, Modulo::GB2_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(54.5, 12.5)), module, Modulo::AB2_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(64.5, 12.5)), module, Modulo::BB2_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(9.5, 23.0)), module, Modulo::C2_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(19.5, 23.0)), module, Modulo::D2_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(29.5, 23.0)), module, Modulo::E2_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(39.5, 23.0)), module, Modulo::F2_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(49.5, 23.0)), module, Modulo::G2_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(59.5, 23.0)), module, Modulo::A2_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(69.5, 23.0)), module, Modulo::B2_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(14.5, 36.5)), module, Modulo::DB1_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(24.5, 36.5)), module, Modulo::EB1_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(44.5, 36.5)), module, Modulo::GB1_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(54.5, 36.5)), module, Modulo::AB1_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(64.5, 36.5)), module, Modulo::BB1_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(9.5, 47.0)), module, Modulo::C1_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(19.5, 47.0)), module, Modulo::D1_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(29.5, 47.0)), module, Modulo::E1_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(39.5, 47.0)), module, Modulo::F1_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(49.5, 47.0)), module, Modulo::G1_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(59.5, 47.0)), module, Modulo::A1_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(69.5, 47.0)), module, Modulo::B1_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(14.5, 60.5)), module, Modulo::DB0_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(24.5, 60.5)), module, Modulo::EB0_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(44.5, 60.5)), module, Modulo::GB0_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(54.5, 60.5)), module, Modulo::AB0_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(64.5, 60.5)), module, Modulo::BB0_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(9.5, 71.0)), module, Modulo::C0_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(19.5, 71.0)), module, Modulo::D0_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(29.5, 71.0)), module, Modulo::E0_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(39.5, 71.0)), module, Modulo::F0_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(49.5, 71.0)), module, Modulo::G0_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(59.5, 71.0)), module, Modulo::A0_LIGHT));
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(69.5, 71.0)), module, Modulo::B0_LIGHT));

		addParam(createParamCentered<BlackKey>(mm2px(Vec(14.5, 12.5)), module, Modulo::DB2_PARAM));
		addParam(createParamCentered<BlackKey>(mm2px(Vec(24.5, 12.5)), module, Modulo::EB2_PARAM));
		addParam(createParamCentered<BlackKey>(mm2px(Vec(44.5, 12.5)), module, Modulo::GB2_PARAM));
		addParam(createParamCentered<BlackKey>(mm2px(Vec(54.5, 12.5)), module, Modulo::AB2_PARAM));
		addParam(createParamCentered<BlackKey>(mm2px(Vec(64.5, 12.5)), module, Modulo::BB2_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(9.5, 23.0)), module, Modulo::C2_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(19.5, 23.0)), module, Modulo::D2_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(29.5, 23.0)), module, Modulo::E2_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(39.5, 23.0)), module, Modulo::F2_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(49.5, 23.0)), module, Modulo::G2_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(59.5, 23.0)), module, Modulo::A2_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(69.5, 23.0)), module, Modulo::B2_PARAM));
		addParam(createParamCentered<BlackKey>(mm2px(Vec(14.5, 36.5)), module, Modulo::DB1_PARAM));
		addParam(createParamCentered<BlackKey>(mm2px(Vec(24.5, 36.5)), module, Modulo::EB1_PARAM));
		addParam(createParamCentered<BlackKey>(mm2px(Vec(44.5, 36.5)), module, Modulo::GB1_PARAM));
		addParam(createParamCentered<BlackKey>(mm2px(Vec(54.5, 36.5)), module, Modulo::AB1_PARAM));
		addParam(createParamCentered<BlackKey>(mm2px(Vec(64.5, 36.5)), module, Modulo::BB1_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(9.5, 47.0)), module, Modulo::C1_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(19.5, 47.0)), module, Modulo::D1_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(29.5, 47.0)), module, Modulo::E1_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(39.5, 47.0)), module, Modulo::F1_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(49.5, 47.0)), module, Modulo::G1_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(59.5, 47.0)), module, Modulo::A1_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(69.5, 47.0)), module, Modulo::B1_PARAM));
		addParam(createParamCentered<BlackKey>(mm2px(Vec(14.5, 60.5)), module, Modulo::DB0_PARAM));
		addParam(createParamCentered<BlackKey>(mm2px(Vec(24.5, 60.5)), module, Modulo::EB0_PARAM));
		addParam(createParamCentered<BlackKey>(mm2px(Vec(44.5, 60.5)), module, Modulo::GB0_PARAM));
		addParam(createParamCentered<BlackKey>(mm2px(Vec(54.5, 60.5)), module, Modulo::AB0_PARAM));
		addParam(createParamCentered<BlackKey>(mm2px(Vec(64.5, 60.5)), module, Modulo::BB0_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(9.5, 71.0)), module, Modulo::C0_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(19.5, 71.0)), module, Modulo::D0_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(29.5, 71.0)), module, Modulo::E0_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(39.5, 71.0)), module, Modulo::F0_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(49.5, 71.0)), module, Modulo::G0_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(59.5, 71.0)), module, Modulo::A0_PARAM));
		addParam(createParamCentered<WhiteKey>(mm2px(Vec(69.5, 71.0)), module, Modulo::B0_PARAM));

		addParam(createParamCentered<SmallWhiteKnob>(mm2px(Vec(7.0, 82.5)), module, Modulo::LENGTH_ATV_PARAM));
		addParam(createParamCentered<LargeWhiteKnob>(mm2px(Vec(22.0, 86.5)), module, Modulo::LENGTH_PARAM));
		addParam(createParamCentered<SmallWhiteKnob>(mm2px(Vec(7.0, 102.5)), module, Modulo::STEP_ATV_PARAM));
		addParam(createParamCentered<LargeWhiteKnob>(mm2px(Vec(22.0, 106.5)), module, Modulo::STEP_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.0, 90.5)), module, Modulo::LENGTH_CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.0, 110.5)), module, Modulo::STEP_CV_INPUT));

		addParam(createParamCentered<CKSSInverse>(mm2px(Vec(58.0, 85.0)), module, Modulo::PRIME_LENGTH_PARAM));
		addParam(createParamCentered<CKSSInverse>(mm2px(Vec(58.0, 105.0)), module, Modulo::PRIME_STEP_PARAM));
		
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(72.5, 85.0)), module, Modulo::RESET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(85.0, 85.0)), module, Modulo::CLOCK_INPUT));

		addParam(createParamCentered<SmallWhiteKnob>(mm2px(Vec(72.5, 105.0)), module, Modulo::SHIFT_PARAM));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(85.0, 105.0)), module, Modulo::OUT_OUTPUT));

		Label *lengthLabel = createWidget<BigLabel>(mm2px(Vec(30.0, 83.5)));
		addChild(lengthLabel);

		Label *stepLabel = createWidget<BigLabel>(mm2px(Vec(30.0, 103.5)));
		addChild(stepLabel);

		if (module) {
			 module->lengthLabel = lengthLabel;
			 module->stepLabel = stepLabel;
		}
	}
};


Model* modelModulo = createModel<Modulo, ModuloWidget>("modulo");