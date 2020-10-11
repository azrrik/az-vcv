#include "plugin.hpp"
#include "widget/Widget.hpp"
#include "Slime.hpp"
#include "Util.hpp"

struct CanvasWidget;

struct Blank : Module {
	enum ParamIds {
		//GAIN,
		TOTAL_AGENTS,
		SENSOR_ANGLE,
		SENSOR_OFFSET,
		RED_WEIGHT,
		BLUE_WEIGHT,
		GREEN_WEIGHT,
		DIFFUSION_FACTOR,
		RETAINMENT_FACTOR,
		FORCE,
		NUM_PARAMS
	};
	enum InputIds {
		CLOCK,
		RESET,
		JITTER,
		NUM_INPUTS
	};
	enum OutputIds {
		NUM_OUTPUTS
	};
	enum LightIds {
		NUM_LIGHTS
	};

	Blank() : slime(100, 0.f, 0.7f, 0.9f) {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);
		configParam(TOTAL_AGENTS, 0.f, 10000.f, 100.f, "Total Agents");
		configParam(SENSOR_ANGLE, 0.f, 1.f, 0.25f, "Sensor Angle");
		configParam(SENSOR_OFFSET, 0.f, 1.f, 0.1f, "Sensor Offset");
		configParam(RED_WEIGHT, 0.f, 1.f, 0.f, "Red Weight");
		configParam(BLUE_WEIGHT, 0.f, 1.f, 0.7f, "Blue Weight");
		configParam(GREEN_WEIGHT, 0.f, 1.f, 0.9f, "Green Weight");
		configParam(DIFFUSION_FACTOR, 0.f, 1.f, 0.3f, "Diffusion Factor");
		configParam(RETAINMENT_FACTOR, 0.f, 1.f, 0.3f, "Retainment Factor");
		configParam(FORCE, 0.f, 10.0f, 0.0001f, "Jitter Force");
	}

	Slime slime;
	dsp::SchmittTrigger clock;
	dsp::SchmittTrigger reset;
	dsp::SchmittTrigger jitter;
	FramebufferWidget* fb;
	
	void process(const ProcessArgs& args) override {
		float totalAgents = params[TOTAL_AGENTS].getValue();
		float sensorAngle = 0.5f * M_PI * params[SENSOR_ANGLE].getValue();
		float sensorOffset = 20 * params[SENSOR_OFFSET].getValue();
		float redWeight = params[RED_WEIGHT].getValue();
		float blueWeight = params[BLUE_WEIGHT].getValue();
		float greenWeight = params[GREEN_WEIGHT].getValue();
		float diffusionFactor = params[DIFFUSION_FACTOR].getValue();
		float retainmentFactor = params[RETAINMENT_FACTOR].getValue();
		float force = params[FORCE].getValue();

		bool someoneIsDirty = false;
		if (clock.process(inputs[CLOCK].getVoltage())) {
			slime.step(sensorAngle, sensorOffset, diffusionFactor, retainmentFactor);
			someoneIsDirty = true;
		}

		if (reset.process(inputs[RESET].getVoltage())) {
			slime.reset(totalAgents, redWeight, blueWeight, greenWeight);
			someoneIsDirty = true;
		}

		if (jitter.process(inputs[JITTER].getVoltage())) {
			slime.jitter(force);
			someoneIsDirty = true;
		}
		if (someoneIsDirty) { fb->dirty = true; }
		// outputs[OUT].setVoltage(out);
	}
};


struct CanvasWidget : Widget {
	Blank* module ;
	CanvasWidget() {}

	void draw(const DrawArgs& args) override {
		module->slime.renderTrailMap(args, this->box);
		// module->slime.renderAgents(args);
	}
};


struct BlankWidget : ModuleWidget {
	BlankWidget(Blank* module) {
		setModule(module);
		setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/Blank.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<Davies1900hWhiteKnob>(Vec(20, 360), module, Blank::TOTAL_AGENTS));
		addParam(createParamCentered<Davies1900hWhiteKnob>(Vec(60, 360), module, Blank::SENSOR_ANGLE));
		addParam(createParamCentered<Davies1900hWhiteKnob>(Vec(100, 360), module, Blank::SENSOR_OFFSET));
		addParam(createParamCentered<Davies1900hRedKnob>(Vec(140, 360), module, Blank::RED_WEIGHT));
		addParam(createParamCentered<Davies1900hWhiteKnob>(Vec(180, 360), module, Blank::BLUE_WEIGHT));
		addParam(createParamCentered<Davies1900hWhiteKnob>(Vec(220, 360), module, Blank::GREEN_WEIGHT));
		addParam(createParamCentered<Davies1900hWhiteKnob>(Vec(260, 360), module, Blank::DIFFUSION_FACTOR));
		addParam(createParamCentered<Davies1900hWhiteKnob>(Vec(300, 360), module, Blank::RETAINMENT_FACTOR));
		addParam(createParamCentered<RoundSmallBlackKnob>(Vec(345, 155), module, Blank::FORCE));

		addInput(createInputCentered<PJ301MPort>(Vec(345, 40), module, Blank::CLOCK));
		addInput(createInputCentered<PJ301MPort>(Vec(345, 80), module, Blank::RESET));
		addInput(createInputCentered<PJ301MPort>(Vec(345, 120), module, Blank::JITTER));

		if (module) {
			CanvasWidget* canvas = new CanvasWidget();
			canvas->box = Rect(Vec(0, 5), Vec(box.size.x - 30, box.size.y - 50));
			canvas->module = module;
			
			FramebufferWidget* fb = new FramebufferWidget();
			fb->box = Rect(Vec(0, 5), Vec(box.size.x - 30, box.size.y - 50));
			fb->addChild(canvas);
			fb->dirty = true;

			module->fb = fb;
			addChild(fb);
		}
		// addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(14.0, 105.0)), module, Blank::OUT));
	}
};


Model* modelBlank = createModel<Blank, BlankWidget>("Blank");