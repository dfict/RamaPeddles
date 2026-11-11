#include "DigitalDelay.h"

namespace DigitalDelay {

/****************************************************************************************
Copyright (c) 2023 Cycling '74

The code that Max generates automatically and that end users are capable of
exporting and using, and any associated documentation files (the “Software”)
is a work of authorship for which Cycling '74 is the author and owner for
copyright purposes.

This Software is dual-licensed either under the terms of the Cycling '74
License for Max-Generated Code for Export, or alternatively under the terms
of the General Public License (GPL) Version 3. You may use the Software
according to either of these licenses as it is most appropriate for your
project on a case-by-case basis (proprietary or not).

A) Cycling '74 License for Max-Generated Code for Export

A license is hereby granted, free of charge, to any person obtaining a copy
of the Software (“Licensee”) to use, copy, modify, merge, publish, and
distribute copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The Software is licensed to Licensee for all uses that do not include the sale,
sublicensing, or commercial distribution of software that incorporates this
source code. This means that the Licensee is free to use this software for
educational, research, and prototyping purposes, to create musical or other
creative works with software that incorporates this source code, or any other
use that does not constitute selling software that makes use of this source
code. Commercial distribution also includes the packaging of free software with
other paid software, hardware, or software-provided commercial services.

For entities with UNDER 200k USD in annual revenue or funding, a license is hereby
granted, free of charge, for the sale, sublicensing, or commercial distribution
of software that incorporates this source code, for as long as the entity's
annual revenue remains below 200k USD annual revenue or funding.

For entities with OVER 200k USD in annual revenue or funding interested in the
sale, sublicensing, or commercial distribution of software that incorporates
this source code, please send inquiries to licensing (at) cycling74.com.

The above copyright notice and this license shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

Please see
https://support.cycling74.com/hc/en-us/articles/360050779193-Gen-Code-Export-Licensing-FAQ
for additional information

B) General Public License Version 3 (GPLv3)
Details of the GPLv3 license can be found at: https://www.gnu.org/licenses/gpl-3.0.html
****************************************************************************************/

// global noise generator
Noise noise;
static const int GENLIB_LOOPCOUNT_BAIL = 100000;


// The State struct contains all the state and procedures for the gendsp kernel
typedef struct State {
	CommonState __commonstate;
	Delay m_delay_5;
	Delay m_delay_6;
	Sah __m_sah_28;
	Sah __m_sah_24;
	Sah __m_sah_26;
	Sah __m_sah_29;
	int __exception;
	int vectorsize;
	t_sample m_history_3;
	t_sample m_knob6_lowpass_19;
	t_sample m_sw_18;
	t_sample m_knob5_time_20;
	t_sample m_knob3_level_17;
	t_sample m_sw_21;
	t_sample m_history_23;
	t_sample m_knob4_fb_22;
	t_sample samplerate;
	t_sample m_history_4;
	t_sample m_sw_16;
	t_sample m_history_14;
	t_sample m_history_8;
	t_sample m_history_7;
	t_sample m_history_2;
	t_sample m_history_15;
	t_sample m_history_9;
	t_sample m_history_11;
	t_sample m_history_10;
	t_sample m_history_13;
	t_sample m_y_1;
	t_sample m_history_12;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_y_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_delay_5.reset("m_delay_5", ((int)96000));
		m_delay_6.reset("m_delay_6", ((int)96000));
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		m_history_13 = ((int)0);
		m_history_14 = ((int)0);
		m_history_15 = ((int)0);
		m_sw_16 = ((int)0);
		m_knob3_level_17 = ((int)0);
		m_sw_18 = ((int)0);
		m_knob6_lowpass_19 = ((int)0);
		m_knob5_time_20 = ((int)0);
		m_sw_21 = ((int)0);
		m_knob4_fb_22 = ((int)0);
		m_history_23 = ((int)0);
		__m_sah_24.reset(0);
		__m_sah_26.reset(0);
		__m_sah_28.reset(0);
		__m_sah_29.reset(0);
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		t_sample * __out4 = __outs[3];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_147 = __m_sah_24(m_history_23, m_sw_21, ((int)0));
			t_sample gen_290 = sah_147;
			t_sample rsub_145 = (((int)1) - sah_147);
			t_sample history_146_next_148 = fixdenorm(rsub_145);
			int not_255 = (!gen_290);
			t_sample out3 = not_255;
			t_sample mix_456 = (m_history_15 + (((t_sample)0.003926980723806) * (m_knob4_fb_22 - m_history_15)));
			t_sample mix_271 = mix_456;
			t_sample mix_457 = (m_history_14 + (((t_sample)0.003926980723806) * (mix_271 - m_history_14)));
			t_sample mix_269 = mix_457;
			t_sample mix_458 = (m_history_13 + (((t_sample)0.003926980723806) * (mix_269 - m_history_13)));
			t_sample mix_267 = mix_458;
			t_sample gen_300 = mix_267;
			t_sample history_272_next_274 = fixdenorm(mix_271);
			t_sample history_270_next_275 = fixdenorm(mix_269);
			t_sample history_268_next_276 = fixdenorm(mix_267);
			t_sample add_291 = (gen_290 + ((int)1));
			t_sample choice_25 = int(add_291);
			t_sample gate_288 = (((choice_25 >= 1) && (choice_25 < 2)) ? in1 : 0);
			t_sample gate_289 = ((choice_25 >= 2) ? in1 : 0);
			t_sample pass_304 = gate_289;
			t_sample sah_372 = __m_sah_26(m_history_12, m_sw_16, ((int)0));
			t_sample gen_260 = sah_372;
			t_sample rsub_370 = (((int)1) - sah_372);
			t_sample history_146_next_369 = fixdenorm(rsub_370);
			t_sample add_257 = (gen_260 + ((int)1));
			t_sample choice_27 = int(add_257);
			t_sample gate_258 = (((choice_27 >= 1) && (choice_27 < 2)) ? ((int)1) : 0);
			t_sample gate_259 = ((choice_27 >= 2) ? ((int)1) : 0);
			t_sample out4 = gate_258;
			t_sample sah_374 = __m_sah_28(m_history_11, m_sw_18, ((int)0));
			t_sample gen_261 = sah_374;
			t_sample rsub_376 = (((int)1) - sah_374);
			t_sample history_146_next_375 = fixdenorm(rsub_376);
			t_sample add_287 = (gen_261 + ((int)1));
			t_sample sah_379 = __m_sah_29(m_history_10, m_sw_16, ((int)0));
			t_sample gen_262 = sah_379;
			t_sample rsub_380 = (((int)1) - sah_379);
			t_sample history_146_next_382 = fixdenorm(rsub_380);
			t_sample mix_459 = (m_history_9 + (((t_sample)0.003926980723806) * (m_knob5_time_20 - m_history_9)));
			t_sample mix_387 = mix_459;
			t_sample mix_460 = (m_history_8 + (((t_sample)0.003926980723806) * (mix_387 - m_history_8)));
			t_sample mix_384 = mix_460;
			t_sample mix_461 = (m_history_7 + (((t_sample)0.003926980723806) * (mix_384 - m_history_7)));
			t_sample mix_389 = mix_461;
			t_sample gen_292 = mix_389;
			t_sample history_272_next_391 = fixdenorm(mix_387);
			t_sample history_270_next_393 = fixdenorm(mix_384);
			t_sample history_268_next_385 = fixdenorm(mix_389);
			t_sample sub_465 = (gen_292 - ((int)0));
			t_sample scale_462 = ((safepow((sub_465 * ((t_sample)1)), ((int)1)) * ((int)72000)) + ((int)24000));
			t_sample scale_264 = scale_462;
			t_sample sub_469 = (gen_292 - ((int)0));
			t_sample scale_466 = ((safepow((sub_469 * ((t_sample)1)), ((int)1)) * ((int)24000)) + ((int)0));
			t_sample scale_265 = scale_466;
			t_sample switch_266 = (gen_262 ? scale_264 : scale_265);
			t_sample tap_303 = m_delay_6.read_cubic(switch_266);
			t_sample mul_301 = (tap_303 * gen_300);
			t_sample mul_299 = (tap_303 * m_knob3_level_17);
			t_sample choice_30 = int(add_287);
			t_sample gate_285 = (((choice_30 >= 1) && (choice_30 < 2)) ? mul_299 : 0);
			t_sample gate_286 = ((choice_30 >= 2) ? mul_299 : 0);
			t_sample tap_297 = m_delay_5.read_cubic(switch_266);
			t_sample mul_295 = (tap_297 * gen_300);
			t_sample mul_294 = (tap_297 * m_knob3_level_17);
			t_sample choice_31 = int(add_287);
			t_sample gate_283 = (((choice_31 >= 1) && (choice_31 < 2)) ? mul_294 : 0);
			t_sample gate_284 = ((choice_31 >= 2) ? mul_294 : 0);
			t_sample add_293 = ((gate_288 + pass_304) + ((gate_283 + gate_284) + gate_285));
			t_sample out2 = add_293;
			t_sample add_298 = ((gate_288 + pass_304) + ((gate_283 + gate_285) + gate_286));
			t_sample out1 = add_298;
			t_sample mix_470 = (m_history_4 + (((t_sample)0.003926980723806) * (m_knob6_lowpass_19 - m_history_4)));
			t_sample mix_407 = mix_470;
			t_sample mix_471 = (m_history_3 + (((t_sample)0.003926980723806) * (mix_407 - m_history_3)));
			t_sample mix_400 = mix_471;
			t_sample mix_472 = (m_history_2 + (((t_sample)0.003926980723806) * (mix_400 - m_history_2)));
			t_sample mix_404 = mix_472;
			t_sample gen_277 = mix_404;
			t_sample history_272_next_406 = fixdenorm(mix_407);
			t_sample history_270_next_399 = fixdenorm(mix_400);
			t_sample history_268_next_401 = fixdenorm(mix_404);
			t_sample mtof_278 = mtof(gen_277, ((int)440));
			t_sample mul_280 = (mtof_278 * safediv((-6.2831853071796), samplerate));
			t_sample exp_281 = exp(mul_280);
			t_sample clamp_282 = ((exp_281 <= ((int)0)) ? ((int)0) : ((exp_281 >= ((int)1)) ? ((int)1) : exp_281));
			t_sample mix_473 = (m_y_1 + (clamp_282 * (mul_301 - m_y_1)));
			t_sample mix_263 = mix_473;
			t_sample add_475 = (mul_295 + pass_304);
			t_sample mix_474 = (m_y_1 + (clamp_282 * (add_475 - m_y_1)));
			t_sample mix_279 = mix_474;
			t_sample y0_next_412 = fixdenorm(mix_263);
			t_sample y0_next_413 = fixdenorm(mix_279);
			m_history_23 = history_146_next_148;
			m_history_15 = history_272_next_274;
			m_history_13 = history_268_next_276;
			m_history_14 = history_270_next_275;
			m_history_12 = history_146_next_369;
			m_history_11 = history_146_next_375;
			m_history_10 = history_146_next_382;
			m_history_9 = history_272_next_391;
			m_history_7 = history_268_next_385;
			m_history_8 = history_270_next_393;
			m_delay_6.write(mix_279);
			m_delay_5.write(mix_263);
			m_history_4 = history_272_next_406;
			m_history_2 = history_268_next_401;
			m_history_3 = history_270_next_399;
			m_y_1 = y0_next_412;
			m_y_1 = y0_next_413;
			m_delay_5.step();
			m_delay_6.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			
		};
		return __exception;
		
	};
	inline void set_sw8(t_param _value) {
		m_sw_16 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_level(t_param _value) {
		m_knob3_level_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw5(t_param _value) {
		m_sw_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob6_lowpass(t_param _value) {
		m_knob6_lowpass_19 = (_value < 54 ? 54 : (_value > 138 ? 138 : _value));
	};
	inline void set_knob5_time(t_param _value) {
		m_knob5_time_20 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw7(t_param _value) {
		m_sw_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4_fb(t_param _value) {
		m_knob4_fb_22 = (_value < 0 ? 0 : (_value > 0.99 ? 0.99 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 4;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 7; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2", "led1", "led2" };

/// Invoke the signal process of a State object

int perform(CommonState *cself, t_sample **ins, long numins, t_sample **outs, long numouts, long n) {
	State* self = (State *)cself;
	return self->perform(ins, outs, n);
}

/// Reset all parameters and stateful operators of a State object

void reset(CommonState *cself) {
	State* self = (State *)cself;
	self->reset(cself->sr, cself->vs);
}

/// Set a parameter of a State object

void setparameter(CommonState *cself, long index, t_param value, void *ref) {
	State *self = (State *)cself;
	switch (index) {
		case 0: self->set_knob3_level(value); break;
		case 1: self->set_knob4_fb(value); break;
		case 2: self->set_knob5_time(value); break;
		case 3: self->set_knob6_lowpass(value); break;
		case 4: self->set_sw5(value); break;
		case 5: self->set_sw7(value); break;
		case 6: self->set_sw8(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob3_level_17; break;
		case 1: *value = self->m_knob4_fb_22; break;
		case 2: *value = self->m_knob5_time_20; break;
		case 3: *value = self->m_knob6_lowpass_19; break;
		case 4: *value = self->m_sw_18; break;
		case 5: *value = self->m_sw_21; break;
		case 6: *value = self->m_sw_16; break;
		
		default: break;
	}
}

/// Get the name of a parameter of a State object

const char *getparametername(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].name;
	}
	return 0;
}

/// Get the minimum value of a parameter of a State object

t_param getparametermin(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmin;
	}
	return 0;
}

/// Get the maximum value of a parameter of a State object

t_param getparametermax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].outputmax;
	}
	return 0;
}

/// Get parameter of a State object has a minimum and maximum value

char getparameterhasminmax(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].hasminmax;
	}
	return 0;
}

/// Get the units of a parameter of a State object

const char *getparameterunits(CommonState *cself, long index) {
	if (index >= 0 && index < cself->numparams) {
		return cself->params[index].units;
	}
	return 0;
}

/// Get the size of the state of all parameters of a State object

size_t getstatesize(CommonState *cself) {
	return genlib_getstatesize(cself, &getparameter);
}

/// Get the state of all parameters of a State object

short getstate(CommonState *cself, char *state) {
	return genlib_getstate(cself, state, &getparameter);
}

/// set the state of all parameters of a State object

short setstate(CommonState *cself, const char *state) {
	return genlib_setstate(cself, state, &setparameter);
}

/// Allocate and configure a new State object and it's internal CommonState:

void *create(t_param sr, long vs) {
	State *self = new State;
	self->reset(sr, vs);
	ParamInfo *pi;
	self->__commonstate.inputnames = gen_kernel_innames;
	self->__commonstate.outputnames = gen_kernel_outnames;
	self->__commonstate.numins = gen_kernel_numins;
	self->__commonstate.numouts = gen_kernel_numouts;
	self->__commonstate.sr = sr;
	self->__commonstate.vs = vs;
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(7 * sizeof(ParamInfo));
	self->__commonstate.numparams = 7;
	// initialize parameter 0 ("m_knob3_level_17")
	pi = self->__commonstate.params + 0;
	pi->name = "knob3_level";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_level_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob4_fb_22")
	pi = self->__commonstate.params + 1;
	pi->name = "knob4_fb";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_fb_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.99;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob5_time_20")
	pi = self->__commonstate.params + 2;
	pi->name = "knob5_time";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_time_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob6_lowpass_19")
	pi = self->__commonstate.params + 3;
	pi->name = "knob6_lowpass";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob6_lowpass_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 54;
	pi->outputmax = 138;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_sw_18")
	pi = self->__commonstate.params + 4;
	pi->name = "sw5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_sw_21")
	pi = self->__commonstate.params + 5;
	pi->name = "sw7";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_sw_16")
	pi = self->__commonstate.params + 6;
	pi->name = "sw8";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // DigitalDelay::
