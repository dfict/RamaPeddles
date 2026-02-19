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
	int __exception;
	int vectorsize;
	Sah __m_sah_24;
	Sah __m_sah_23;
	Sah __m_sah_26;
	t_sample m_history_3;
	t_sample m_sw_19;
	t_sample m_sw_18;
	t_sample m_sw_17;
	t_sample m_knob1_level_16;
	t_sample m_knob2_fb_20;
	t_sample m_history_22;
	t_sample m_knob4_lowpass_21;
	t_sample samplerate;
	t_sample m_history_4;
	t_sample m_knob3_time_15;
	t_sample m_history_13;
	t_sample m_history_8;
	t_sample m_history_7;
	t_sample m_history_2;
	t_sample m_history_14;
	t_sample m_history_9;
	t_sample m_y_1;
	t_sample m_history_10;
	t_sample m_history_12;
	t_sample m_history_11;
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
		m_knob3_time_15 = ((int)0);
		m_knob1_level_16 = ((int)0);
		m_sw_17 = ((int)0);
		m_sw_18 = ((int)0);
		m_sw_19 = ((int)0);
		m_knob2_fb_20 = ((int)0);
		m_knob4_lowpass_21 = ((int)0);
		m_history_22 = ((int)0);
		__m_sah_23.reset(0);
		__m_sah_24.reset(0);
		__m_sah_26.reset(0);
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
		t_sample * __out5 = __outs[4];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample add_475 = (m_sw_18 + ((int)1));
		t_sample choice_28 = int(add_475);
		t_sample choice_29 = int(add_475);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_447 = __m_sah_23(m_history_22, m_sw_17, ((int)0));
			t_sample gen_450 = sah_447;
			t_sample rsub_445 = (((int)1) - sah_447);
			t_sample history_446_next_448 = fixdenorm(rsub_445);
			t_sample out5 = gen_450;
			t_sample sah_494 = __m_sah_24(m_history_14, m_sw_17, ((int)0));
			t_sample gen_478 = sah_494;
			t_sample rsub_495 = (((int)1) - sah_494);
			t_sample history_446_next_493 = fixdenorm(rsub_495);
			t_sample add_479 = (gen_478 + ((int)1));
			t_sample choice_25 = int(add_479);
			t_sample gate_476 = (((choice_25 >= 1) && (choice_25 < 2)) ? in1 : 0);
			t_sample gate_477 = ((choice_25 >= 2) ? in1 : 0);
			t_sample pass_492 = gate_477;
			t_sample mix_573 = (m_history_13 + (((t_sample)0.0042742627044161) * (m_knob2_fb_20 - m_history_13)));
			t_sample mix_459 = mix_573;
			t_sample mix_574 = (m_history_12 + (((t_sample)0.0042742627044161) * (mix_459 - m_history_12)));
			t_sample mix_457 = mix_574;
			t_sample mix_575 = (m_history_11 + (((t_sample)0.0042742627044161) * (mix_457 - m_history_11)));
			t_sample mix_455 = mix_575;
			t_sample gen_488 = mix_455;
			t_sample history_460_next_462 = fixdenorm(mix_459);
			t_sample history_458_next_463 = fixdenorm(mix_457);
			t_sample history_456_next_464 = fixdenorm(mix_455);
			t_sample sah_501 = __m_sah_26(m_history_10, m_sw_17, ((int)0));
			t_sample gen_449 = sah_501;
			t_sample rsub_500 = (((int)1) - sah_501);
			t_sample history_446_next_499 = fixdenorm(rsub_500);
			t_sample add_442 = (gen_449 + ((int)1));
			t_sample choice_27 = int(add_442);
			t_sample gate_443 = (((choice_27 >= 1) && (choice_27 < 2)) ? ((int)1) : 0);
			t_sample gate_444 = ((choice_27 >= 2) ? ((int)1) : 0);
			t_sample out3 = (gen_478 + gate_443);
			t_sample out4 = gate_444;
			t_sample mix_576 = (m_history_9 + (((t_sample)0.0042742627044161) * (m_knob3_time_15 - m_history_9)));
			t_sample mix_508 = mix_576;
			t_sample mix_577 = (m_history_8 + (((t_sample)0.0042742627044161) * (mix_508 - m_history_8)));
			t_sample mix_512 = mix_577;
			t_sample mix_578 = (m_history_7 + (((t_sample)0.0042742627044161) * (mix_512 - m_history_7)));
			t_sample mix_507 = mix_578;
			t_sample gen_480 = mix_507;
			t_sample history_460_next_510 = fixdenorm(mix_508);
			t_sample history_458_next_509 = fixdenorm(mix_512);
			t_sample history_456_next_506 = fixdenorm(mix_507);
			t_sample sub_582 = (gen_480 - ((int)0));
			t_sample scale_579 = ((safepow((sub_582 * ((t_sample)1)), ((int)1)) * ((int)72000)) + ((int)24000));
			t_sample scale_452 = scale_579;
			t_sample sub_586 = (gen_480 - ((int)0));
			t_sample scale_583 = ((safepow((sub_586 * ((t_sample)1)), ((int)1)) * ((int)24000)) + ((int)0));
			t_sample scale_453 = scale_583;
			t_sample switch_454 = (m_sw_19 ? scale_452 : scale_453);
			t_sample tap_491 = m_delay_6.read_cubic(switch_454);
			t_sample mul_489 = (tap_491 * gen_488);
			t_sample mul_487 = (tap_491 * m_knob1_level_16);
			t_sample gate_473 = (((choice_28 >= 1) && (choice_28 < 2)) ? mul_487 : 0);
			t_sample gate_474 = ((choice_28 >= 2) ? mul_487 : 0);
			t_sample tap_485 = m_delay_5.read_cubic(switch_454);
			t_sample mul_483 = (tap_485 * gen_488);
			t_sample mul_482 = (tap_485 * m_knob1_level_16);
			t_sample gate_471 = (((choice_29 >= 1) && (choice_29 < 2)) ? mul_482 : 0);
			t_sample gate_472 = ((choice_29 >= 2) ? mul_482 : 0);
			t_sample add_481 = ((gate_476 + pass_492) + ((gate_471 + gate_472) + gate_473));
			t_sample out2 = add_481;
			t_sample add_486 = ((gate_476 + pass_492) + ((gate_471 + gate_473) + gate_474));
			t_sample out1 = add_486;
			t_sample mix_587 = (m_history_4 + (((t_sample)0.0042742627044161) * (m_knob4_lowpass_21 - m_history_4)));
			t_sample mix_525 = mix_587;
			t_sample mix_588 = (m_history_3 + (((t_sample)0.0042742627044161) * (mix_525 - m_history_3)));
			t_sample mix_523 = mix_588;
			t_sample mix_589 = (m_history_2 + (((t_sample)0.0042742627044161) * (mix_523 - m_history_2)));
			t_sample mix_521 = mix_589;
			t_sample gen_465 = mix_521;
			t_sample history_460_next_524 = fixdenorm(mix_525);
			t_sample history_458_next_522 = fixdenorm(mix_523);
			t_sample history_456_next_516 = fixdenorm(mix_521);
			t_sample mtof_466 = mtof(gen_465, ((int)440));
			t_sample mul_468 = (mtof_466 * safediv((-6.2831853071796), samplerate));
			t_sample exp_469 = exp(mul_468);
			t_sample clamp_470 = ((exp_469 <= ((int)0)) ? ((int)0) : ((exp_469 >= ((int)1)) ? ((int)1) : exp_469));
			t_sample mix_590 = (m_y_1 + (clamp_470 * (mul_489 - m_y_1)));
			t_sample mix_451 = mix_590;
			t_sample add_592 = (mul_483 + pass_492);
			t_sample mix_591 = (m_y_1 + (clamp_470 * (add_592 - m_y_1)));
			t_sample mix_467 = mix_591;
			t_sample y0_next_529 = fixdenorm(mix_451);
			t_sample y0_next_530 = fixdenorm(mix_467);
			m_history_22 = history_446_next_448;
			m_history_14 = history_446_next_493;
			m_history_13 = history_460_next_462;
			m_history_11 = history_456_next_464;
			m_history_12 = history_458_next_463;
			m_history_10 = history_446_next_499;
			m_history_9 = history_460_next_510;
			m_history_7 = history_456_next_506;
			m_history_8 = history_458_next_509;
			m_delay_6.write(mix_467);
			m_delay_5.write(mix_451);
			m_history_4 = history_460_next_524;
			m_history_2 = history_456_next_516;
			m_history_3 = history_458_next_522;
			m_y_1 = y0_next_529;
			m_y_1 = y0_next_530;
			m_delay_5.step();
			m_delay_6.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			
		};
		return __exception;
		
	};
	inline void set_knob3_time(t_param _value) {
		m_knob3_time_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob1_level(t_param _value) {
		m_knob1_level_16 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw6(t_param _value) {
		m_sw_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw5(t_param _value) {
		m_sw_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2_fb(t_param _value) {
		m_knob2_fb_20 = (_value < 0 ? 0 : (_value > 0.99 ? 0.99 : _value));
	};
	inline void set_knob4_lowpass(t_param _value) {
		m_knob4_lowpass_21 = (_value < 54 ? 54 : (_value > 138 ? 138 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 5;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 7; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2", "led1", "led2", "relay" };

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
		case 0: self->set_knob1_level(value); break;
		case 1: self->set_knob2_fb(value); break;
		case 2: self->set_knob3_time(value); break;
		case 3: self->set_knob4_lowpass(value); break;
		case 4: self->set_sw1(value); break;
		case 5: self->set_sw5(value); break;
		case 6: self->set_sw6(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob1_level_16; break;
		case 1: *value = self->m_knob2_fb_20; break;
		case 2: *value = self->m_knob3_time_15; break;
		case 3: *value = self->m_knob4_lowpass_21; break;
		case 4: *value = self->m_sw_17; break;
		case 5: *value = self->m_sw_19; break;
		case 6: *value = self->m_sw_18; break;
		
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
	// initialize parameter 0 ("m_knob1_level_16")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1_level";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_level_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob2_fb_20")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2_fb";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob2_fb_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.99;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob3_time_15")
	pi = self->__commonstate.params + 2;
	pi->name = "knob3_time";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_time_15;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob4_lowpass_21")
	pi = self->__commonstate.params + 3;
	pi->name = "knob4_lowpass";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_lowpass_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 54;
	pi->outputmax = 138;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_sw_17")
	pi = self->__commonstate.params + 4;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_sw_19")
	pi = self->__commonstate.params + 5;
	pi->name = "sw5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_sw_18")
	pi = self->__commonstate.params + 6;
	pi->name = "sw6";
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
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // DigitalDelay::
