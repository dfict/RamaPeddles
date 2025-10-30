#include "Gate.h"

namespace Gate {

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
	int __exception;
	int vectorsize;
	Sah __m_sah_11;
	Sah __m_sah_14;
	Sah __m_sah_12;
	t_sample m_sw_7;
	t_sample m_knob5_release_8;
	t_sample m_history_9;
	t_sample m_history_10;
	t_sample m_sw_6;
	t_sample m_knob3_threshold_4;
	t_sample samplerate;
	t_sample m_knob2_output_5;
	t_sample m_history_1;
	t_sample m_knob4_attack_3;
	t_sample m_knob1_input_2;
	t_sample __m_slide_16;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_knob1_input_2 = ((int)0);
		m_knob4_attack_3 = ((int)0);
		m_knob3_threshold_4 = ((int)0);
		m_knob2_output_5 = ((int)0);
		m_sw_6 = ((int)0);
		m_sw_7 = ((int)0);
		m_knob5_release_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		__m_sah_11.reset(0);
		__m_sah_12.reset(0);
		__m_sah_14.reset(0);
		__m_slide_16 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		const t_sample * __in2 = __ins[1];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		t_sample * __out4 = __outs[3];
		t_sample * __out5 = __outs[4];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample dbtoa_3568 = dbtoa(m_knob2_output_5);
		t_sample dbtoa_3583 = dbtoa(m_knob1_input_2);
		t_sample mstosamps_3555 = (m_knob4_attack_3 * (samplerate * 0.001));
		t_sample mstosamps_3554 = (m_knob5_release_8 * (samplerate * 0.001));
		t_sample iup_17 = (1 / maximum(1, abs(mstosamps_3555)));
		t_sample idown_18 = (1 / maximum(1, abs(mstosamps_3554)));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample sah_3565 = __m_sah_11(m_history_1, m_sw_6, ((int)0));
			t_sample gen_3592 = sah_3565;
			t_sample rsub_3563 = (((int)1) - sah_3565);
			t_sample history_3564_next_3566 = fixdenorm(rsub_3563);
			t_sample out5 = gen_3592;
			t_sample sah_3624 = __m_sah_12(m_history_9, m_sw_6, ((int)0));
			t_sample gen_3591 = sah_3624;
			t_sample rsub_3625 = (((int)1) - sah_3624);
			t_sample history_3564_next_3623 = fixdenorm(rsub_3625);
			t_sample add_3588 = (gen_3591 + ((int)1));
			t_sample choice_13 = int(add_3588);
			t_sample gate_3589 = (((choice_13 >= 1) && (choice_13 < 2)) ? ((int)1) : 0);
			t_sample gate_3590 = ((choice_13 >= 2) ? ((int)1) : 0);
			t_sample out3 = gate_3589;
			t_sample out4 = gate_3590;
			t_sample sah_3629 = __m_sah_14(m_history_10, m_sw_6, ((int)0));
			t_sample gen_3567 = sah_3629;
			t_sample rsub_3630 = (((int)1) - sah_3629);
			t_sample history_3564_next_3628 = fixdenorm(rsub_3630);
			t_sample add_3558 = (gen_3567 + ((int)1));
			t_sample choice_15 = int(add_3558);
			t_sample gate_3559 = (((choice_15 >= 1) && (choice_15 < 2)) ? in1 : 0);
			t_sample gate_3560 = ((choice_15 >= 2) ? in1 : 0);
			t_sample mul_3586 = (gate_3560 * dbtoa_3583);
			t_sample switch_3556 = (m_sw_7 ? in2 : mul_3586);
			t_sample abs_3582 = fabs(switch_3556);
			__m_slide_16 = fixdenorm((__m_slide_16 + (((abs_3582 > __m_slide_16) ? iup_17 : idown_18) * (abs_3582 - __m_slide_16))));
			t_sample slide_3570 = __m_slide_16;
			t_sample atodb_3581 = atodb(slide_3570);
			int lt_3579 = (atodb_3581 < m_knob3_threshold_4);
			t_sample sub_3580 = (atodb_3581 - m_knob3_threshold_4);
			t_sample mul_3576 = (sub_3580 * ((t_sample)0.9999));
			t_sample dbtoa_3575 = dbtoa(mul_3576);
			t_sample rsub_3574 = (((int)1) - dbtoa_3575);
			t_sample mul_3573 = (rsub_3574 * (-1));
			t_sample mul_3572 = (lt_3579 * mul_3573);
			t_sample add_3571 = (mul_3572 + ((int)1));
			t_sample clamp_3561 = ((add_3571 <= ((int)0)) ? ((int)0) : ((add_3571 >= ((int)1)) ? ((int)1) : add_3571));
			t_sample mul_3585 = (mul_3586 * clamp_3561);
			t_sample mul_3569 = (mul_3585 * dbtoa_3568);
			t_sample add_3584 = (gate_3559 + mul_3569);
			t_sample out2 = add_3584;
			t_sample out1 = add_3584;
			m_history_1 = history_3564_next_3566;
			m_history_10 = history_3564_next_3628;
			m_history_9 = history_3564_next_3623;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			
		};
		return __exception;
		
	};
	inline void set_knob1_input(t_param _value) {
		m_knob1_input_2 = (_value < -70 ? -70 : (_value > 15 ? 15 : _value));
	};
	inline void set_knob4_attack(t_param _value) {
		m_knob4_attack_3 = (_value < 0.5 ? 0.5 : (_value > 200 ? 200 : _value));
	};
	inline void set_knob3_threshold(t_param _value) {
		m_knob3_threshold_4 = (_value < -70 ? -70 : (_value > 18 ? 18 : _value));
	};
	inline void set_knob2_output(t_param _value) {
		m_knob2_output_5 = (_value < -70 ? -70 : (_value > 15 ? 15 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_6 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw5(t_param _value) {
		m_sw_7 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5_release(t_param _value) {
		m_knob5_release_8 = (_value < 5 ? 5 : (_value > 1000 ? 1000 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 5;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 7; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
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
		case 0: self->set_knob1_input(value); break;
		case 1: self->set_knob2_output(value); break;
		case 2: self->set_knob3_threshold(value); break;
		case 3: self->set_knob4_attack(value); break;
		case 4: self->set_knob5_release(value); break;
		case 5: self->set_sw1(value); break;
		case 6: self->set_sw5(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob1_input_2; break;
		case 1: *value = self->m_knob2_output_5; break;
		case 2: *value = self->m_knob3_threshold_4; break;
		case 3: *value = self->m_knob4_attack_3; break;
		case 4: *value = self->m_knob5_release_8; break;
		case 5: *value = self->m_sw_6; break;
		case 6: *value = self->m_sw_7; break;
		
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
	// initialize parameter 0 ("m_knob1_input_2")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1_input";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_input_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 15;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob2_output_5")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2_output";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob2_output_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 15;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob3_threshold_4")
	pi = self->__commonstate.params + 2;
	pi->name = "knob3_threshold";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_threshold_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 18;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob4_attack_3")
	pi = self->__commonstate.params + 3;
	pi->name = "knob4_attack";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_attack_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 200;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_knob5_release_8")
	pi = self->__commonstate.params + 4;
	pi->name = "knob5_release";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob5_release_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 5;
	pi->outputmax = 1000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_sw_6")
	pi = self->__commonstate.params + 5;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_sw_7")
	pi = self->__commonstate.params + 6;
	pi->name = "sw5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_7;
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


} // Gate::
