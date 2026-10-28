#include "TestTrem.h"

namespace TestTrem {

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
	Phasor __m_phasor_24;
	Sah __m_sah_21;
	Sah __m_sah_23;
	Sah __m_sah_19;
	int __exception;
	int vectorsize;
	t_sample m_last_value_3;
	t_sample m_knob_16;
	t_sample m_knob_15;
	t_sample m_sw_17;
	t_sample m_knob_18;
	t_sample m_phase_1;
	t_sample m_sw_14;
	t_sample samplerate;
	t_sample m_target_value_2;
	t_sample m_knob_13;
	t_sample m_history_11;
	t_sample m_history_6;
	t_sample m_history_5;
	t_sample m_history_4;
	t_sample m_history_12;
	t_sample m_history_7;
	t_sample m_history_9;
	t_sample m_history_8;
	t_sample samples_to_seconds;
	t_sample m_history_10;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_phase_1 = ((int)0);
		m_target_value_2 = ((int)0);
		m_last_value_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		m_knob_13 = ((int)0);
		m_sw_14 = ((int)0);
		m_knob_15 = ((int)0);
		m_knob_16 = ((int)0);
		m_sw_17 = ((int)0);
		m_knob_18 = ((int)0);
		__m_sah_19.reset(0);
		__m_sah_21.reset(0);
		__m_sah_23.reset(0);
		samples_to_seconds = (1 / samplerate);
		__m_phasor_24.reset(0);
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
		t_sample * __out6 = __outs[5];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__in2 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample sub_11315 = (m_knob_15 - ((int)0));
		t_sample scale_11312 = ((safepow((sub_11315 * ((t_sample)1)), ((int)1)) * ((int)-1)) + ((int)1));
		t_sample scale_9857 = scale_11312;
		t_sample sub_11323 = (m_knob_13 - ((int)0));
		t_sample scale_11320 = ((safepow((sub_11323 * ((t_sample)1)), ((int)1)) * ((t_sample)9.5)) + ((t_sample)0.5));
		samples_to_seconds = (1 / samplerate);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample out6 = ((int)0);
			t_sample sah_9881 = __m_sah_19(m_history_12, m_sw_14, ((int)0));
			t_sample gen_10203 = sah_9881;
			t_sample rsub_9879 = (((int)1) - sah_9881);
			t_sample history_9880_next_9882 = fixdenorm(rsub_9879);
			t_sample add_10204 = (gen_10203 + ((int)1));
			t_sample choice_20 = int(add_10204);
			t_sample gate_10201 = (((choice_20 >= 1) && (choice_20 < 2)) ? in1 : 0);
			t_sample gate_10202 = ((choice_20 >= 2) ? in1 : 0);
			t_sample sah_11232 = __m_sah_21(m_history_11, m_sw_14, ((int)0));
			t_sample gen_9883 = sah_11232;
			t_sample rsub_11230 = (((int)1) - sah_11232);
			t_sample history_9880_next_11231 = fixdenorm(rsub_11230);
			t_sample add_9876 = (gen_9883 + ((int)1));
			t_sample choice_22 = int(add_9876);
			t_sample gate_9877 = (((choice_22 >= 1) && (choice_22 < 2)) ? ((int)1) : 0);
			t_sample gate_9878 = ((choice_22 >= 2) ? ((int)1) : 0);
			t_sample out4 = gate_9878;
			t_sample out3 = (gen_10203 + gate_9877);
			t_sample sah_11236 = __m_sah_23(m_history_10, m_sw_17, ((int)0));
			t_sample gen_11106 = sah_11236;
			t_sample rsub_11235 = (((int)1) - sah_11236);
			t_sample history_9880_next_11237 = fixdenorm(rsub_11235);
			t_sample mix_11316 = (m_history_9 + (((t_sample)0.001308996565174) * (scale_9857 - m_history_9)));
			t_sample mix_9865 = mix_11316;
			t_sample mix_11317 = (m_history_8 + (((t_sample)0.001308996565174) * (mix_9865 - m_history_8)));
			t_sample mix_9863 = mix_11317;
			t_sample gen_9873 = mix_9863;
			t_sample history_9866_next_9868 = fixdenorm(mix_9865);
			t_sample history_9864_next_9869 = fixdenorm(mix_9863);
			t_sample mul_9858 = (gen_9873 * ((t_sample)0.75));
			t_sample mix_11318 = (m_history_7 + (((t_sample)0.001308996565174) * (m_knob_16 - m_history_7)));
			t_sample mix_11246 = mix_11318;
			t_sample mix_11319 = (m_history_6 + (((t_sample)0.001308996565174) * (mix_11246 - m_history_6)));
			t_sample mix_11245 = mix_11319;
			t_sample gen_9870 = mix_11245;
			t_sample history_9866_next_11243 = fixdenorm(mix_11246);
			t_sample history_9864_next_11241 = fixdenorm(mix_11245);
			t_sample phasor_9872 = __m_phasor_24(scale_11320, samples_to_seconds);
			t_sample triangle_9871 = triangle(phasor_9872, gen_9870);
			t_sample mix_11324 = (m_history_5 + (((t_sample)0.001308996565174) * (m_knob_18 - m_history_5)));
			t_sample mix_11255 = mix_11324;
			t_sample mix_11325 = (m_history_4 + (((t_sample)0.001308996565174) * (mix_11255 - m_history_4)));
			t_sample mix_11251 = mix_11325;
			t_sample gen_10042 = mix_11251;
			t_sample history_9866_next_11253 = fixdenorm(mix_11255);
			t_sample history_9864_next_11250 = fixdenorm(mix_11251);
			t_sample sub_11329 = (gen_10042 - ((int)0));
			t_sample scale_11326 = ((safepow((sub_11329 * ((t_sample)1)), ((int)1)) * ((t_sample)99.999)) + ((t_sample)0.001));
			t_sample scale_9993 = scale_11326;
			t_sample freq = scale_9993;
			t_sample phasor_inc = safediv(freq, samplerate);
			m_phase_1 = (m_phase_1 + phasor_inc);
			if ((m_phase_1 >= ((int)1))) {
				m_phase_1 = (m_phase_1 - ((int)1));
				m_last_value_3 = m_target_value_2;
				m_target_value_2 = noise();
				
			};
			t_sample interp = (m_last_value_3 + ((m_target_value_2 - m_last_value_3) * m_phase_1));
			t_sample output = ((interp * ((int)1)) + ((int)0));
			t_sample switch_10931 = (gen_11106 ? triangle_9871 : output);
			t_sample add_9859 = (mul_9858 + switch_10931);
			t_sample clamp_9860 = ((add_9859 <= ((int)0)) ? ((int)0) : ((add_9859 >= ((int)1)) ? ((int)1) : add_9859));
			t_sample mul_9862 = (gate_10202 * clamp_9860);
			t_sample add_10458 = (gate_10201 + mul_9862);
			t_sample out1 = add_10458;
			t_sample add_10457 = (gate_10201 + mul_9862);
			t_sample out2 = add_10457;
			m_history_12 = history_9880_next_9882;
			m_history_11 = history_9880_next_11231;
			m_history_10 = history_9880_next_11237;
			m_history_9 = history_9866_next_9868;
			m_history_8 = history_9864_next_9869;
			m_history_7 = history_9866_next_11243;
			m_history_6 = history_9864_next_11241;
			m_history_5 = history_9866_next_11253;
			m_history_4 = history_9864_next_11250;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = 0;
			(*(__out6++)) = out6;
			
		};
		return __exception;
		
	};
	inline void set_knob1(t_param _value) {
		m_knob_13 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw7(t_param _value) {
		m_sw_14 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2(t_param _value) {
		m_knob_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3(t_param _value) {
		m_knob_16 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw8(t_param _value) {
		m_sw_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4(t_param _value) {
		m_knob_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 2;
int gen_kernel_numouts = 6;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 6; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1", "in2" };
const char *gen_kernel_outnames[] = { "out1", "out2", "led1", "led2", "out5", "out6" };

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
		case 0: self->set_knob1(value); break;
		case 1: self->set_knob2(value); break;
		case 2: self->set_knob3(value); break;
		case 3: self->set_knob4(value); break;
		case 4: self->set_sw7(value); break;
		case 5: self->set_sw8(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob_13; break;
		case 1: *value = self->m_knob_15; break;
		case 2: *value = self->m_knob_16; break;
		case 3: *value = self->m_knob_18; break;
		case 4: *value = self->m_sw_14; break;
		case 5: *value = self->m_sw_17; break;
		
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
	// initialize parameter 0 ("m_knob_13")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob_15")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_15;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob_16")
	pi = self->__commonstate.params + 2;
	pi->name = "knob3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob_18")
	pi = self->__commonstate.params + 3;
	pi->name = "knob4";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_18;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_sw_14")
	pi = self->__commonstate.params + 4;
	pi->name = "sw7";
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
	// initialize parameter 5 ("m_sw_17")
	pi = self->__commonstate.params + 5;
	pi->name = "sw8";
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
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // TestTrem::
