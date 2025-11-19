#include "DigitalDelay2.h"

namespace DigitalDelay2 {

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
	Delay m_delay_1;
	int vectorsize;
	int __exception;
	Sah __m_sah_20;
	Sah __m_sah_21;
	Sah __m_sah_23;
	t_sample m_history_4;
	t_sample m_knob4_multitap_16;
	t_sample m_knob3_time_15;
	t_sample m_sw_14;
	t_sample m_knob2_fb_17;
	t_sample m_sw_19;
	t_sample m_knob1_level_18;
	t_sample samplerate;
	t_sample m_history_3;
	t_sample m_history_13;
	t_sample m_history_11;
	t_sample m_history_6;
	t_sample m_history_5;
	t_sample m_history_12;
	t_sample m_history_7;
	t_sample m_history_9;
	t_sample m_history_8;
	t_sample m_history_2;
	t_sample m_history_10;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_delay_1.reset("m_delay_1", ((int)192000));
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		m_history_13 = ((int)0);
		m_sw_14 = ((int)0);
		m_knob3_time_15 = ((int)0);
		m_knob4_multitap_16 = ((int)0);
		m_knob2_fb_17 = ((int)0);
		m_knob1_level_18 = ((int)0);
		m_sw_19 = ((int)0);
		__m_sah_20.reset(0);
		__m_sah_21.reset(0);
		__m_sah_23.reset(0);
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
		t_sample * __out6 = __outs[5];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample add_642 = (m_sw_19 + ((int)1));
		t_sample choice_25 = int(add_642);
		t_sample choice_26 = int(add_642);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out6 = ((int)0);
			t_sample sah_7 = __m_sah_20(m_history_13, m_sw_14, ((int)0));
			t_sample gen_645 = sah_7;
			t_sample rsub_5 = (((int)1) - sah_7);
			t_sample history_6_next_8 = fixdenorm(rsub_5);
			t_sample sah_730 = __m_sah_21(m_history_12, m_sw_14, ((int)0));
			t_sample gen_733 = sah_730;
			t_sample rsub_728 = (((int)1) - sah_730);
			t_sample history_729_next_731 = fixdenorm(rsub_728);
			t_sample out5 = (gen_733 + ((int)0));
			t_sample add_646 = (gen_645 + ((int)1));
			t_sample choice_22 = int(add_646);
			t_sample gate_643 = (((choice_22 >= 1) && (choice_22 < 2)) ? in1 : 0);
			t_sample gate_644 = ((choice_22 >= 2) ? in1 : 0);
			t_sample pass_658 = gate_644;
			t_sample sah_968 = __m_sah_23(m_history_11, m_sw_14, ((int)0));
			t_sample gen_732 = sah_968;
			t_sample rsub_967 = (((int)1) - sah_968);
			t_sample history_729_next_966 = fixdenorm(rsub_967);
			t_sample add_725 = (gen_732 + ((int)1));
			t_sample choice_24 = int(add_725);
			t_sample gate_726 = (((choice_24 >= 1) && (choice_24 < 2)) ? ((int)1) : 0);
			t_sample gate_727 = ((choice_24 >= 2) ? ((int)1) : 0);
			t_sample out4 = (gate_727 + ((int)0));
			t_sample out3 = (gate_726 + gen_645);
			t_sample mix_1141 = (m_history_10 + (((t_sample)0.0042742627044161) * (m_knob2_fb_17 - m_history_10)));
			t_sample mix_94 = mix_1141;
			t_sample mix_1142 = (m_history_9 + (((t_sample)0.0042742627044161) * (mix_94 - m_history_9)));
			t_sample mix_92 = mix_1142;
			t_sample mix_1143 = (m_history_8 + (((t_sample)0.0042742627044161) * (mix_92 - m_history_8)));
			t_sample mix_90 = mix_1143;
			t_sample gen_653 = mix_90;
			t_sample history_95_next_97 = fixdenorm(mix_94);
			t_sample history_93_next_98 = fixdenorm(mix_92);
			t_sample history_91_next_99 = fixdenorm(mix_90);
			t_sample mix_1144 = (m_history_7 + (((t_sample)0.0042742627044161) * (m_knob3_time_15 - m_history_7)));
			t_sample mix_972 = mix_1144;
			t_sample mix_1145 = (m_history_6 + (((t_sample)0.0042742627044161) * (mix_972 - m_history_6)));
			t_sample mix_974 = mix_1145;
			t_sample mix_1146 = (m_history_5 + (((t_sample)0.0042742627044161) * (mix_974 - m_history_5)));
			t_sample mix_979 = mix_1146;
			t_sample gen_647 = mix_979;
			t_sample history_95_next_980 = fixdenorm(mix_972);
			t_sample history_93_next_971 = fixdenorm(mix_974);
			t_sample history_91_next_973 = fixdenorm(mix_979);
			t_sample sub_1150 = (gen_647 - ((int)0));
			t_sample scale_1147 = ((safepow((sub_1150 * ((t_sample)1)), ((int)1)) * ((int)96000)) + ((int)0));
			t_sample mix_1151 = (m_history_4 + (((t_sample)0.0042742627044161) * (m_knob4_multitap_16 - m_history_4)));
			t_sample mix_985 = mix_1151;
			t_sample mix_1152 = (m_history_3 + (((t_sample)0.0042742627044161) * (mix_985 - m_history_3)));
			t_sample mix_987 = mix_1152;
			t_sample mix_1153 = (m_history_2 + (((t_sample)0.0042742627044161) * (mix_987 - m_history_2)));
			t_sample mix_992 = mix_1153;
			t_sample gen_636 = mix_992;
			t_sample history_95_next_993 = fixdenorm(mix_985);
			t_sample history_93_next_984 = fixdenorm(mix_987);
			t_sample history_91_next_986 = fixdenorm(mix_992);
			t_sample round_632 = round(gen_636);
			t_sample rdiv_637 = safediv(((int)1), round_632);
			t_sample mul_631 = (scale_1147 * rdiv_637);
			t_sample add_633 = (scale_1147 + mul_631);
			t_sample tap_656 = m_delay_1.read_cubic(scale_1147);
			t_sample tap_657 = m_delay_1.read_cubic(add_633);
			t_sample mul_652 = (tap_656 * m_knob1_level_18);
			t_sample gate_640 = (((choice_25 >= 1) && (choice_25 < 2)) ? mul_652 : 0);
			t_sample gate_641 = ((choice_25 >= 2) ? mul_652 : 0);
			t_sample mul_649 = (tap_657 * m_knob1_level_18);
			t_sample gate_638 = (((choice_26 >= 1) && (choice_26 < 2)) ? mul_649 : 0);
			t_sample gate_639 = ((choice_26 >= 2) ? mul_649 : 0);
			t_sample add_651 = (pass_658 + ((gate_638 + gate_640) + gate_641));
			t_sample add_630 = (gate_643 + add_651);
			t_sample out1 = add_630;
			t_sample add_648 = (pass_658 + ((gate_638 + gate_639) + gate_640));
			t_sample add_629 = (gate_643 + add_648);
			t_sample out2 = add_629;
			t_sample mul_650 = (tap_657 * gen_653);
			t_sample mul_654 = (tap_656 * gen_653);
			m_history_13 = history_6_next_8;
			m_history_12 = history_729_next_731;
			m_history_11 = history_729_next_966;
			m_history_10 = history_95_next_97;
			m_history_8 = history_91_next_99;
			m_history_9 = history_93_next_98;
			m_history_7 = history_95_next_980;
			m_history_5 = history_91_next_973;
			m_history_6 = history_93_next_971;
			m_history_4 = history_95_next_993;
			m_history_2 = history_91_next_986;
			m_history_3 = history_93_next_984;
			m_delay_1.write(((mul_654 + mul_650) + pass_658));
			m_delay_1.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			(*(__out6++)) = out6;
			
		};
		return __exception;
		
	};
	inline void set_sw1(t_param _value) {
		m_sw_14 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_time(t_param _value) {
		m_knob3_time_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4_multitap(t_param _value) {
		m_knob4_multitap_16 = (_value < 1 ? 1 : (_value > 6 ? 6 : _value));
	};
	inline void set_knob2_fb(t_param _value) {
		m_knob2_fb_17 = (_value < 0 ? 0 : (_value > 0.48 ? 0.48 : _value));
	};
	inline void set_knob1_level(t_param _value) {
		m_knob1_level_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw5(t_param _value) {
		m_sw_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 6;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 6; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2", "led1", "led2", "relay", "led4" };

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
		case 3: self->set_knob4_multitap(value); break;
		case 4: self->set_sw1(value); break;
		case 5: self->set_sw5(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob1_level_18; break;
		case 1: *value = self->m_knob2_fb_17; break;
		case 2: *value = self->m_knob3_time_15; break;
		case 3: *value = self->m_knob4_multitap_16; break;
		case 4: *value = self->m_sw_14; break;
		case 5: *value = self->m_sw_19; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(6 * sizeof(ParamInfo));
	self->__commonstate.numparams = 6;
	// initialize parameter 0 ("m_knob1_level_18")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1_level";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_level_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob2_fb_17")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2_fb";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob2_fb_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.48;
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
	// initialize parameter 3 ("m_knob4_multitap_16")
	pi = self->__commonstate.params + 3;
	pi->name = "knob4_multitap";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_multitap_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 6;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_sw_14")
	pi = self->__commonstate.params + 4;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_14;
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
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // DigitalDelay2::
