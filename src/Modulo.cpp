#include "plugin.hpp"
#include "Modulo.hpp"

struct Modulo : Module {
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
		configParam(DB0_PARAM, 0.f, 1.f, 0.f, "Db");
		configParam(EB0_PARAM, 0.f, 1.f, 0.f, "Eb");
		configParam(GB0_PARAM, 0.f, 1.f, 0.f, "Gb");
		configParam(AB0_PARAM, 0.f, 1.f, 0.f, "Ab");
		configParam(BB0_PARAM, 0.f, 1.f, 0.f, "Bb");
		configParam(C0_PARAM, 0.f, 1.f, 0.f, "C");
		configParam(D0_PARAM, 0.f, 1.f, 0.f, "D");
		configParam(E0_PARAM, 0.f, 1.f, 0.f, "E");
		configParam(F0_PARAM, 0.f, 1.f, 0.f, "F");
		configParam(G0_PARAM, 0.f, 1.f, 0.f, "G");
		configParam(A0_PARAM, 0.f, 1.f, 0.f, "A");
		configParam(B0_PARAM, 0.f, 1.f, 0.f, "B");
		configParam(DB1_PARAM, 0.f, 1.f, 0.f, "Db");
		configParam(EB1_PARAM, 0.f, 1.f, 0.f, "Eb");
		configParam(GB1_PARAM, 0.f, 1.f, 0.f, "Gb");
		configParam(AB1_PARAM, 0.f, 1.f, 0.f, "Ab");
		configParam(BB1_PARAM, 0.f, 1.f, 0.f, "Bb");
		configParam(C1_PARAM, 0.f, 1.f, 0.f, "C");
		configParam(D1_PARAM, 0.f, 1.f, 0.f, "D");
		configParam(E1_PARAM, 0.f, 1.f, 0.f, "E");
		configParam(F1_PARAM, 0.f, 1.f, 0.f, "F");
		configParam(G1_PARAM, 0.f, 1.f, 0.f, "G");
		configParam(A1_PARAM, 0.f, 1.f, 0.f, "A");
		configParam(B1_PARAM, 0.f, 1.f, 0.f, "B");
		configParam(DB2_PARAM, 0.f, 1.f, 0.f, "Db");
		configParam(EB2_PARAM, 0.f, 1.f, 0.f, "Eb");
		configParam(GB2_PARAM, 0.f, 1.f, 0.f, "Gb");
		configParam(AB2_PARAM, 0.f, 1.f, 0.f, "Ab");
		configParam(BB2_PARAM, 0.f, 1.f, 0.f, "Bb");
		configParam(C2_PARAM, 0.f, 1.f, 0.f, "C");
		configParam(D2_PARAM, 0.f, 1.f, 0.f, "D");
		configParam(E2_PARAM, 0.f, 1.f, 0.f, "E");
		configParam(F2_PARAM, 0.f, 1.f, 0.f, "F");
		configParam(G2_PARAM, 0.f, 1.f, 0.f, "G");
		configParam(A2_PARAM, 0.f, 1.f, 0.f, "A");
		configParam(B2_PARAM, 0.f, 1.f, 0.f, "B");
		configParam(LENGTH_ATV_PARAM, -10.f, 10.f, 0.f, "Length Attenuverter");
		configParam(LENGTH_PARAM, 0.f, 33.f, 4.f, "Length");
		configParam(STEP_ATV_PARAM, -10.f, 10.f, 0.f, "Step Attenuverter");
		configParam(STEP_PARAM, 0.f, 33.f, 5.f, "Step");
		configParam(PRIME_STEP_PARAM, 0.f, 1.f, 1.f, "Only Primes");
		configParam(PRIME_LENGTH_PARAM, 0.f, 1.f, 1.f, "Only Primes");
		configParam(SHIFT_PARAM, 0.f, 1.f, 0.f, "Shift");
	}

	static const int N = 36;
	int notes[N];

	dsp::SchmittTrigger resetTrigger;
	dsp::SchmittTrigger trigger;
	
	int length = 0;
	int step = 0;
	int current = 0;

	void process(const ProcessArgs& args) override {
		if (resetTrigger.process(inputs[RESET_INPUT].getVoltage())) {
			current = 0;
		}

		bool processTrigger = trigger.process(inputs[CLOCK_INPUT].getVoltage());

		length = (int) (
			(params[LENGTH_ATV_PARAM].getValue() * inputs[LENGTH_CV_INPUT].getVoltage()) + params[LENGTH_PARAM].getValue()
		);
		length = clamp(length, 0, PRIMES);
		length = ((bool) params[PRIME_LENGTH_PARAM].getValue()) ? primes[length] : length;

		step = (int) (
			(params[STEP_ATV_PARAM].getValue() * inputs[STEP_CV_INPUT].getVoltage()) + params[STEP_PARAM].getValue()
		);
		step = clamp(step, 0, PRIMES);
		step = ((bool) params[PRIME_STEP_PARAM].getValue()) ? primes[step] : step;


		if (processTrigger) {
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

			for (int k = 0; k < NUM_LIGHTS; k++) {
				lights[k].setBrightness(0.f);
			}

			lights[out].setBrightness(1.f);

			if (current >= length - 1) {
				current = 0;
			} else {
				current++;
			}

			outputs[OUT_OUTPUT].setVoltage((out / 12.f) - 1.f);
		}		
	}
};

struct LengthDisplay : ParamDisplay {
	Modulo* module;
	void step() override {
		int length = module ? module->length : 0;
		text = string::f("%d", length);
	}
};

struct StepDisplay : ParamDisplay {
	Modulo* module;
	void step() override {
		int step = module ? module->step : 0;
		text = string::f("%d", step);
	}
};

struct ModuloWidget : ModuleWidget {
	ModuloWidget(Modulo* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Modulo.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(14.5, 12.5)), module, Modulo::DB2_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(24.5, 12.5)), module, Modulo::EB2_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(44.5, 12.5)), module, Modulo::GB2_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(54.5, 12.5)), module, Modulo::AB2_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(64.5, 12.5)), module, Modulo::BB2_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(9.5, 23.0)), module, Modulo::C2_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(19.5, 23.0)), module, Modulo::D2_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(29.5, 23.0)), module, Modulo::E2_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(39.5, 23.0)), module, Modulo::F2_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(49.5, 23.0)), module, Modulo::G2_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(59.5, 23.0)), module, Modulo::A2_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(69.5, 23.0)), module, Modulo::B2_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(14.5, 36.5)), module, Modulo::DB1_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(24.5, 36.5)), module, Modulo::EB1_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(44.5, 36.5)), module, Modulo::GB1_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(54.5, 36.5)), module, Modulo::AB1_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(64.5, 36.5)), module, Modulo::BB1_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(9.5, 47.0)), module, Modulo::C1_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(19.5, 47.0)), module, Modulo::D1_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(29.5, 47.0)), module, Modulo::E1_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(39.5, 47.0)), module, Modulo::F1_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(49.5, 47.0)), module, Modulo::G1_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(59.5, 47.0)), module, Modulo::A1_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(69.5, 47.0)), module, Modulo::B1_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(14.5, 60.5)), module, Modulo::DB0_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(24.5, 60.5)), module, Modulo::EB0_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(44.5, 60.5)), module, Modulo::GB0_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(54.5, 60.5)), module, Modulo::AB0_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(64.5, 60.5)), module, Modulo::BB0_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(9.5, 71.0)), module, Modulo::C0_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(19.5, 71.0)), module, Modulo::D0_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(29.5, 71.0)), module, Modulo::E0_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(39.5, 71.0)), module, Modulo::F0_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(49.5, 71.0)), module, Modulo::G0_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(59.5, 71.0)), module, Modulo::A0_LIGHT));
		addChild(createLightCentered<HiLight<GreenLight>>(mm2px(Vec(69.5, 71.0)), module, Modulo::B0_LIGHT));

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

		addParam(createParamCentered<SmallBlackKnob>(mm2px(Vec(7.0, 82.5)), module, Modulo::LENGTH_ATV_PARAM));
		addParam(createParamCentered<LargeBlackKnob>(mm2px(Vec(22.0, 86.5)), module, Modulo::LENGTH_PARAM));
		addParam(createParamCentered<SmallBlackKnob>(mm2px(Vec(7.0, 102.5)), module, Modulo::STEP_ATV_PARAM));
		addParam(createParamCentered<LargeBlackKnob>(mm2px(Vec(22.0, 106.5)), module, Modulo::STEP_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.0, 90.5)), module, Modulo::LENGTH_CV_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.0, 110.5)), module, Modulo::STEP_CV_INPUT));

		addParam(createParamCentered<CKSSInverse>(mm2px(Vec(58.0, 85.0)), module, Modulo::PRIME_LENGTH_PARAM));
		addParam(createParamCentered<CKSSInverse>(mm2px(Vec(58.0, 105.0)), module, Modulo::PRIME_STEP_PARAM));
		
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(72.5, 85.0)), module, Modulo::RESET_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(85.0, 85.0)), module, Modulo::CLOCK_INPUT));

		addParam(createParamCentered<SmallBlackKnob>(mm2px(Vec(72.5, 105.0)), module, Modulo::SHIFT_PARAM));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(85.0, 105.0)), module, Modulo::OUT_OUTPUT));

		LengthDisplay* lengthDisplay = createWidget<LengthDisplay>(mm2px(Vec(41.75, 81.5)));
		lengthDisplay->module = module;
		addChild(lengthDisplay);

		StepDisplay* stepDisplay = createWidget<StepDisplay>(mm2px(Vec(41.75, 101.5)));
		stepDisplay->module = module;
		addChild(stepDisplay);
	}
};

Model* modelModulo = createModel<Modulo, ModuloWidget>("modulo");