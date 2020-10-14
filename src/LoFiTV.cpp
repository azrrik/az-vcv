#include "plugin.hpp"
#include "widget/Widget.hpp"
#include "Slime.hpp"
#include "Util.hpp"

struct LoFiTV : Module {
	enum ParamIds {
		TOTAL_AGENTS,
		SENSOR_ANGLE,
		SENSOR_OFFSET,
		RED_WEIGHT,
		BLUE_WEIGHT,
		GREEN_WEIGHT,
		DIFFUSION_FACTOR,
		RETAINMENT_FACTOR,
		FORCE,
		RESET_TAP,
		NUM_PARAMS
	};
	enum InputIds {
		CLOCK,
		RESET,
		JITTER,
		FORCE_CV,
		RED_CV,
		BLUE_CV,
		GREEN_CV,
		TOTAL_AGENTS_CV,
		DIFFUSION_FACTOR_CV,
		RETAINMENT_FACTOR_CV,
		SENSOR_ANGLE_CV,
		SENSOR_OFFSET_CV,
		NUM_INPUTS
	};
	enum OutputIds {
		MOD3,
		MOD5,
		MOD7,
		NUM_OUTPUTS
	};
	enum LightIds {
		RESET_LIGHT,
		NUM_LIGHTS
	};

	Slime slime;
	dsp::SchmittTrigger clock;
	dsp::SchmittTrigger reset;
	dsp::SchmittTrigger jitter;
	dsp::BooleanTrigger resetTap;
	FramebufferWidget* fb;

	LoFiTV() : slime(100, 0.f, 0.7f, 0.9f) {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(TOTAL_AGENTS, 0.f, 5000.f, 1000.f, "Total Agents");
		configParam(SENSOR_ANGLE, 0.f, 1.f, 0.2477f, "Sensor Angle");
		configParam(SENSOR_OFFSET, 0.f, 1.f, 0.1337f, "Sensor Offset");
		configParam(RED_WEIGHT, 0.f, 1.f, 0.1f, "Red Weight");
		configParam(BLUE_WEIGHT, 0.f, 1.f, 0.67f, "Blue Weight");
		configParam(GREEN_WEIGHT, 0.f, 1.f, 0.9f, "Green Weight");
		configParam(DIFFUSION_FACTOR, 0.f, 1.f, 0.413f, "Diffusion Factor");
		configParam(RETAINMENT_FACTOR, 0.f, 1.f, 0.523f, "Retainment Factor");
		configParam(FORCE, 0.f, 25.0f, 13.7f, "Jitter Force");
	}

	void process(const ProcessArgs& args) override {
		bool someoneIsDirty = false;
		if (clock.process(inputs[CLOCK].getVoltage())) {
			float sensorAngle = 0.5f * M_PI * params[SENSOR_ANGLE].getValue();
			float sensorOffset = 20 * params[SENSOR_OFFSET].getValue();
			float diffusionFactor = params[DIFFUSION_FACTOR].getValue();
			float retainmentFactor = params[RETAINMENT_FACTOR].getValue();

			if (inputs[SENSOR_ANGLE_CV].isConnected()) {
				sensorAngle = 0.5f * M_PI * (inputs[SENSOR_ANGLE_CV].getVoltage() + 10.f)/ 20.f;
			}
			if (inputs[SENSOR_OFFSET_CV].isConnected()) {
				sensorOffset = inputs[SENSOR_OFFSET_CV].getVoltage() + 10.f;
			}
			if (inputs[DIFFUSION_FACTOR_CV].isConnected()) {
				diffusionFactor = (inputs[DIFFUSION_FACTOR_CV].getVoltage() + 10.f) / 20.f;
			}
			if (inputs[RETAINMENT_FACTOR_CV].isConnected()){
				retainmentFactor = (inputs[RETAINMENT_FACTOR_CV].getVoltage() + 10.f) / 20.f;
			}
			slime.step(sensorAngle, sensorOffset, diffusionFactor, retainmentFactor);
			someoneIsDirty = true;
		}

		bool tap = params[RESET_TAP].getValue() > 0.f;
		lights[RESET_LIGHT].setBrightness(tap);

		if (reset.process(inputs[RESET].getVoltage()) || resetTap.process(tap)) {
			float totalAgents = params[TOTAL_AGENTS].getValue();
			float redWeight = params[RED_WEIGHT].getValue();
			float blueWeight = params[BLUE_WEIGHT].getValue();
			float greenWeight = params[GREEN_WEIGHT].getValue();

			if (inputs[TOTAL_AGENTS_CV].isConnected()) {
				totalAgents = (inputs[TOTAL_AGENTS_CV].getVoltage() + 10.f) * 250;
			}
			if (inputs[RED_CV].isConnected()) {
				redWeight = (inputs[RED_CV].getVoltage() + 10.f) / 20.f;
			}
			if (inputs[BLUE_CV].isConnected()) {
				blueWeight = (inputs[BLUE_CV].getVoltage() + 10.f) / 20.f;
			}
			if (inputs[GREEN_CV].isConnected()) {
				greenWeight = (inputs[GREEN_CV].getVoltage() + 10.f) / 20.f;
			}
			slime.reset(totalAgents, redWeight, blueWeight, greenWeight);
			someoneIsDirty = true;
		}

		if (jitter.process(inputs[JITTER].getVoltage())) {
			float force = params[FORCE].getValue();
			if (inputs[FORCE_CV].isConnected()) {
				force = (inputs[FORCE_CV].getVoltage() + 10.f) / 20.f * 25.f;
			}
			slime.jitter(force);
			someoneIsDirty = true;
		}

		if (someoneIsDirty) { 
			fb->dirty = true;
			Modulation average = slime.getModulation(); 
			outputs[MOD3].setVoltage(average.mod3);
			outputs[MOD5].setVoltage(average.mod5);
			outputs[MOD7].setVoltage(average.mod7);
		}
	}
};


struct CanvasWidget : Widget {
	LoFiTV* module;

	void draw(const DrawArgs& args) override {
		if (module) {
			module->slime.renderTrailMap(args, this->box);
		}
	}
};

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

struct LoFiTVWidget : ModuleWidget {
	LoFiTVWidget(LoFiTV* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/LoFiTV.svg")));
		// ↯ ⧗
		addInput(createInputCentered<PJ301MPort>(Vec(410, 21), module, LoFiTV::JITTER));
		addInput(createInputCentered<PJ301MPort>(Vec(450, 21), module, LoFiTV::CLOCK));
		// !
		addParam(createParamCentered<RoundSmallWhiteKnob>(Vec(421, 73), module, LoFiTV::FORCE));
		addInput(createInputCentered<PJ301MPort>(Vec(451, 73), module, LoFiTV::FORCE_CV));
		// ↻
		addParam(createParamCentered<LEDBezel>(Vec(430, 110), module, LoFiTV::RESET_TAP));
		addChild(createLightCentered<LEDBezelLight<GreenLight>>(Vec(430, 110), module, LoFiTV::RESET_LIGHT));
		addInput(createInputCentered<PJ301MPort>(Vec(457, 110), module, LoFiTV::RESET));
		// #
		addParam(createParamCentered<RoundSmallWhiteKnob>(Vec(430, 141), module, LoFiTV::TOTAL_AGENTS));
		addInput(createInputCentered<PJ301MPort>(Vec(457, 141), module, LoFiTV::TOTAL_AGENTS_CV));
		
		addParam(createParamCentered<RoundSmallRedKnob>(Vec(403, 209), module, LoFiTV::RED_WEIGHT));
		addParam(createParamCentered<RoundSmallBlueKnob>(Vec(430, 209), module, LoFiTV::BLUE_WEIGHT));
		addParam(createParamCentered<RoundSmallGreenKnob>(Vec(457, 209), module, LoFiTV::GREEN_WEIGHT));
		addInput(createInputCentered<PJ301MPort>(Vec(403, 181), module, LoFiTV::RED_CV));
		addInput(createInputCentered<PJ301MPort>(Vec(430, 181), module, LoFiTV::BLUE_CV));
		addInput(createInputCentered<PJ301MPort>(Vec(457, 181), module, LoFiTV::GREEN_CV));
		// ✢ ▒ ∠ ↥
		addParam(createParamCentered<RoundSmallWhiteKnob>(Vec(430, 244), module, LoFiTV::DIFFUSION_FACTOR));
		addParam(createParamCentered<RoundSmallWhiteKnob>(Vec(430, 273.5), module, LoFiTV::RETAINMENT_FACTOR));
		addParam(createParamCentered<RoundSmallWhiteKnob>(Vec(430, 303), module, LoFiTV::SENSOR_ANGLE));
		addParam(createParamCentered<RoundSmallWhiteKnob>(Vec(430, 332.5), module, LoFiTV::SENSOR_OFFSET));
		addInput(createInputCentered<PJ301MPort>(Vec(457, 244), module, LoFiTV::DIFFUSION_FACTOR_CV));
		addInput(createInputCentered<PJ301MPort>(Vec(457, 273.5), module, LoFiTV::RETAINMENT_FACTOR_CV));
		addInput(createInputCentered<PJ301MPort>(Vec(457, 303), module, LoFiTV::SENSOR_ANGLE_CV));
		addInput(createInputCentered<PJ301MPort>(Vec(457, 332.5), module, LoFiTV::SENSOR_OFFSET_CV));

		CanvasWidget* canvas = new CanvasWidget();
		canvas->box = Rect(Vec(0, 0), Vec(380, 380));
		canvas->module = module;

		FramebufferWidget* fb = new FramebufferWidget();
		fb->box = Rect(Vec(0, 0), Vec(380, 380));
		fb->addChild(canvas);
		addChild(fb);
		if (module) {
			module->fb = fb;
		}

		addOutput(createOutputCentered<PJ301MDarkPort>(Vec(403, 365), module, LoFiTV::MOD3));
		addOutput(createOutputCentered<PJ301MDarkPort>(Vec(430, 365), module, LoFiTV::MOD5));
		addOutput(createOutputCentered<PJ301MDarkPort>(Vec(457, 365), module, LoFiTV::MOD7));
	}
};


Model* modelLoFiTV = createModel<LoFiTV, LoFiTVWidget>("LoFiTV");