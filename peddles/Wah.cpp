#include "Wah.h"

namespace Wah {

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
	Sah __m_sah_16;
	Sah __m_sah_17;
	t_sample m_knob2_base_14;
	t_sample m_knob1_range_10;
	t_sample m_history_15;
	t_sample m_sw_11;
	t_sample m_history_9;
	t_sample m_knob3_slew_12;
	t_sample m_knob4_res_13;
	t_sample m_history_8;
	t_sample m_history_6;
	t_sample m_y_1;
	t_sample samplerate;
	t_sample m_history_7;
	t_sample m_y_2;
	t_sample m_history_4;
	t_sample m_history_3;
	t_sample m_history_5;
	t_sample __m_slide_19;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_y_1 = ((int)0);
		m_y_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_knob1_range_10 = 1;
		m_sw_11 = ((int)0);
		m_knob3_slew_12 = 1;
		m_knob4_res_13 = 0.5;
		m_knob2_base_14 = 0;
		m_history_15 = ((int)0);
		__m_sah_16.reset(0);
		__m_sah_17.reset(0);
		__m_slide_19 = 0;
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
		t_sample mul_628 = (m_knob3_slew_12 * ((int)1));
		t_sample mstosamps_630 = (mul_628 * (samplerate * 0.001));
		t_sample mul_627 = (m_knob3_slew_12 * ((int)10));
		t_sample mstosamps_629 = (mul_627 * (samplerate * 0.001));
		t_sample iup_20 = (1 / maximum(1, abs(mstosamps_630)));
		t_sample idown_21 = (1 / maximum(1, abs(mstosamps_629)));
		t_sample clamp_622 = ((m_knob4_res_13 <= ((int)0)) ? ((int)0) : ((m_knob4_res_13 >= ((t_sample)0.99999)) ? ((t_sample)0.99999) : m_knob4_res_13));
		t_sample mul_620 = (clamp_622 * ((t_sample)0.125));
		t_sample exp_621 = exp(mul_620);
		t_sample mul_619 = (exp_621 * ((t_sample)0.882497));
		t_sample mul_615 = (mul_619 * mul_619);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_447 = __m_sah_16(m_history_15, m_sw_11, ((int)0));
			t_sample gen_599 = sah_447;
			t_sample rsub_445 = (((int)1) - sah_447);
			t_sample history_446_next_448 = fixdenorm(rsub_445);
			t_sample out5 = gen_599;
			t_sample sah_636 = __m_sah_17(m_history_9, m_sw_11, ((int)0));
			t_sample gen_598 = sah_636;
			t_sample rsub_637 = (((int)1) - sah_636);
			t_sample history_446_next_635 = fixdenorm(rsub_637);
			t_sample add_595 = (gen_598 + ((int)1));
			t_sample choice_18 = int(add_595);
			t_sample gate_596 = (((choice_18 >= 1) && (choice_18 < 2)) ? ((int)1) : 0);
			t_sample gate_597 = ((choice_18 >= 2) ? ((int)1) : 0);
			t_sample out3 = gate_596;
			t_sample mix_673 = (m_history_8 + (((t_sample)0.0042742627044161) * (m_knob2_base_14 - m_history_8)));
			t_sample mix_459 = mix_673;
			t_sample mix_674 = (m_history_7 + (((t_sample)0.0042742627044161) * (mix_459 - m_history_7)));
			t_sample mix_457 = mix_674;
			t_sample mix_675 = (m_history_6 + (((t_sample)0.0042742627044161) * (mix_457 - m_history_6)));
			t_sample mix_455 = mix_675;
			t_sample gen_605 = mix_455;
			t_sample history_460_next_462 = fixdenorm(mix_459);
			t_sample history_458_next_463 = fixdenorm(mix_457);
			t_sample history_456_next_464 = fixdenorm(mix_455);
			t_sample mix_676 = (m_history_5 + (((t_sample)0.0042742627044161) * (m_knob1_range_10 - m_history_5)));
			t_sample mix_647 = mix_676;
			t_sample mix_677 = (m_history_4 + (((t_sample)0.0042742627044161) * (mix_647 - m_history_4)));
			t_sample mix_646 = mix_677;
			t_sample mix_678 = (m_history_3 + (((t_sample)0.0042742627044161) * (mix_646 - m_history_3)));
			t_sample mix_644 = mix_678;
			t_sample gen_603 = mix_644;
			t_sample history_460_next_645 = fixdenorm(mix_647);
			t_sample history_458_next_640 = fixdenorm(mix_646);
			t_sample history_456_next_643 = fixdenorm(mix_644);
			t_sample abs_632 = fabs(in1);
			__m_slide_19 = fixdenorm((__m_slide_19 + (((abs_632 > __m_slide_19) ? iup_20 : idown_21) * (abs_632 - __m_slide_19))));
			t_sample slide_631 = __m_slide_19;
			t_sample mul_602 = (slide_631 * ((int)30));
			t_sample clamp_600 = ((mul_602 <= ((int)0)) ? ((int)0) : ((mul_602 >= ((int)1)) ? ((int)1) : mul_602));
			t_sample sqrt_601 = sqrt(clamp_600);
			t_sample mul_626 = (sqrt_601 * gen_603);
			t_sample add_607 = (mul_626 + gen_605);
			t_sample clamp_606 = ((add_607 <= ((int)0)) ? ((int)0) : ((add_607 >= ((int)1)) ? ((int)1) : add_607));
			t_sample out4 = (clamp_606 + gate_597);
			t_sample sub_682 = (clamp_606 - ((int)0));
			t_sample scale_679 = ((safepow((sub_682 * ((t_sample)1)), ((int)1)) * ((int)120)) + ((int)15));
			t_sample scale_608 = scale_679;
			t_sample mtof_604 = mtof(scale_608, ((int)440));
			t_sample mul_609 = (mtof_604 * safediv(6.2831853071796, samplerate));
			t_sample cos_618 = cos(mul_609);
			t_sample mul_611 = (mul_615 * m_y_2);
			t_sample mul_617 = (cos_618 * mul_619);
			t_sample mul_616 = (mul_617 * (-2));
			t_sample mul_612 = (mul_616 * m_y_1);
			t_sample add_614 = ((mul_615 + mul_616) + ((int)1));
			t_sample mul_613 = (in1 * add_614);
			t_sample sub_610 = (mul_613 - (mul_611 + mul_612));
			t_sample gen_625 = sub_610;
			t_sample y2_next_623 = fixdenorm(m_y_1);
			t_sample y1_next_624 = fixdenorm(sub_610);
			t_sample add_634 = (gen_625 + ((int)0));
			t_sample out1 = add_634;
			t_sample add_633 = (gen_625 + ((int)0));
			t_sample out2 = add_633;
			m_history_15 = history_446_next_448;
			m_history_9 = history_446_next_635;
			m_history_8 = history_460_next_462;
			m_history_6 = history_456_next_464;
			m_history_7 = history_458_next_463;
			m_history_5 = history_460_next_645;
			m_history_3 = history_456_next_643;
			m_history_4 = history_458_next_640;
			m_y_2 = y2_next_623;
			m_y_1 = y1_next_624;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			
		};
		return __exception;
		
	};
	inline void set_knob1_range(t_param _value) {
		m_knob1_range_10 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_11 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_slew(t_param _value) {
		m_knob3_slew_12 = (_value < 1 ? 1 : (_value > 30 ? 30 : _value));
	};
	inline void set_knob4_res(t_param _value) {
		m_knob4_res_13 = (_value < 0.5 ? 0.5 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2_base(t_param _value) {
		m_knob2_base_14 = (_value < 0 ? 0 : (_value > 0.8 ? 0.8 : _value));
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
int num_params() { return 5; }

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
		case 0: self->set_knob1_range(value); break;
		case 1: self->set_knob2_base(value); break;
		case 2: self->set_knob3_slew(value); break;
		case 3: self->set_knob4_res(value); break;
		case 4: self->set_sw1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob1_range_10; break;
		case 1: *value = self->m_knob2_base_14; break;
		case 2: *value = self->m_knob3_slew_12; break;
		case 3: *value = self->m_knob4_res_13; break;
		case 4: *value = self->m_sw_11; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(5 * sizeof(ParamInfo));
	self->__commonstate.numparams = 5;
	// initialize parameter 0 ("m_knob1_range_10")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1_range";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_range_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob2_base_14")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2_base";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob2_base_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.8;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob3_slew_12")
	pi = self->__commonstate.params + 2;
	pi->name = "knob3_slew";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_slew_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob4_res_13")
	pi = self->__commonstate.params + 3;
	pi->name = "knob4_res";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_res_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_sw_11")
	pi = self->__commonstate.params + 4;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_11;
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


} // Wah::
