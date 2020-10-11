#include "plugin.hpp"
#include "widget/Widget.hpp"

struct Tanh : Module {
	enum ParamIds {
		GAIN,
		NUM_PARAMS
	};
	enum InputIds {
		IN,
		NUM_INPUTS
	};
	enum OutputIds {
		OUT,
		NUM_OUTPUTS
	};
	enum LightIds {
		L1,
		NUM_LIGHTS
	};

	Tanh() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(GAIN, -10.f, 10.f, 0.f, "GAIN");
	}

	bool add = true;
	float intensity = 0.f;
	float delta = 0.000001f;
	void process(const ProcessArgs& args) override {
		if (add)
			intensity += delta;
		else
			intensity -= delta;

		lights[0].setBrightness(intensity);
		if (intensity >= 1.f && add) add = false;
		if (intensity <= 0.f && !add) add = true;


		float gain = params[GAIN].getValue();

		float out = std::tanh(inputs[IN].getVoltage() / gain) * gain;

		outputs[OUT].setVoltage(out);
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

struct TanhWidget : ModuleWidget {
	TanhWidget(Tanh* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Tanh.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	
		addChild(createLightCentered<HiLight<BlueLight>>(mm2px(Vec(14.5, 12.5)), module, Tanh::L1));

		addParam(createParamCentered<Davies1900hWhiteKnob>(mm2px(Vec(10.0, 40)), module, Tanh::GAIN));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(7.0, 90.5)), module, Tanh::IN));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(14.0, 105.0)), module, Tanh::OUT));
	}
};


Model* modelTanh = createModel<Tanh, TanhWidget>("Tanh");