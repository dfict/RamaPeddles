#include "dario_27s_scrubber_wMouse_LFnoise_v2.h"

namespace dario_27s_scrubber_wMouse_LFnoise_v2 {

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
	Data m_mybuffer_4;
	int vectorsize;
	int __exception;
	t_sample m_freq_12;
	t_sample m_last_value_13;
	t_sample m_mul_11;
	t_sample m_target_value_14;
	t_sample m_phase_15;
	t_sample m_add_10;
	t_sample __m_carry_18;
	t_sample __m_count_16;
	t_sample m_current_value_9;
	t_sample m_phase_8;
	t_sample m_knob3_stutter_7;
	t_sample m_gate_1;
	t_sample samplerate;
	t_sample __m_slide_23;
	t_sample m_LFnoiseSwitch_2;
	t_sample m_knob2_stutter_5;
	t_sample m_knob4_mix_3;
	t_sample m_knob1_slide_6;
	t_sample __m_slide_26;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_gate_1 = ((int)0);
		m_LFnoiseSwitch_2 = ((int)0);
		m_knob4_mix_3 = ((int)0);
		m_mybuffer_4.reset("mybuffer", ((int)262144), ((int)1));
		m_knob2_stutter_5 = ((int)0);
		m_knob1_slide_6 = 1;
		m_knob3_stutter_7 = ((int)0);
		m_phase_8 = ((int)0);
		m_current_value_9 = ((int)0);
		m_add_10 = ((int)0);
		m_mul_11 = ((int)1);
		m_freq_12 = ((int)1);
		m_last_value_13 = ((int)0);
		m_target_value_14 = ((int)0);
		m_phase_15 = ((int)0);
		__m_count_16 = 0;
		__m_carry_18 = 0;
		__m_slide_23 = 0;
		__m_slide_26 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		t_sample * __out3 = __outs[2];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample phasor_inc = safediv(m_freq_12, samplerate);
		int mybuffer_dim = m_mybuffer_4.dim;
		int mybuffer_channels = m_mybuffer_4.channels;
		int mybuffer_dim_152 = mybuffer_dim;
		t_sample phasor_inc_252 = safediv(m_freq_12, samplerate);
		t_sample choice_20 = int(m_gate_1);
		t_sample add_128 = (m_knob2_stutter_5 + m_knob3_stutter_7);
		t_sample sub_285 = (add_128 - ((int)0));
		t_sample scale_282 = ((safepow((sub_285 * ((t_sample)0.5)), ((int)1)) * ((int)262144)) + ((int)0));
		t_sample iup_24 = (1 / maximum(1, abs(scale_282)));
		t_sample idown_25 = (1 / maximum(1, abs(scale_282)));
		t_sample iup_27 = (1 / maximum(1, abs(scale_282)));
		t_sample idown_28 = (1 / maximum(1, abs(scale_282)));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			m_phase_8 = (m_phase_8 + phasor_inc);
			if ((m_phase_8 >= ((int)1))) {
				m_phase_8 = (m_phase_8 - ((int)1));
				m_current_value_9 = noise();
				
			};
			t_sample output = ((m_current_value_9 * m_mul_11) + m_add_10);
			m_phase_15 = (m_phase_15 + phasor_inc_252);
			if ((m_phase_15 >= ((int)1))) {
				m_phase_15 = (m_phase_15 - ((int)1));
				m_last_value_13 = m_target_value_14;
				m_target_value_14 = noise();
				
			};
			t_sample interp = (m_last_value_13 + ((m_target_value_14 - m_last_value_13) * m_phase_15));
			t_sample output_253 = ((interp * m_mul_11) + m_add_10);
			t_sample out2 = ((int)3);
			t_sample out3 = in1;
			__m_count_16 = (((int)0) ? 0 : (fixdenorm(__m_count_16 + ((int)1))));
			int carry_17 = 0;
			if ((((int)0) != 0)) {
				__m_count_16 = 0;
				__m_carry_18 = 0;
				
			} else if (((mybuffer_dim_152 > 0) && (__m_count_16 >= mybuffer_dim_152))) {
				int wraps_19 = (__m_count_16 / mybuffer_dim_152);
				__m_carry_18 = (__m_carry_18 + wraps_19);
				__m_count_16 = (__m_count_16 - (wraps_19 * mybuffer_dim_152));
				carry_17 = 1;
				
			};
			int counter_149 = __m_count_16;
			int counter_150 = carry_17;
			int counter_151 = __m_carry_18;
			t_sample gate_141 = ((choice_20 >= 1) ? counter_149 : 0);
			int index_trunc_21 = fixnan(floor(gate_141));
			bool index_ignore_22 = ((index_trunc_21 >= mybuffer_dim) || (index_trunc_21 < 0));
			if ((!index_ignore_22)) {
				m_mybuffer_4.write(in1, index_trunc_21, 0);
				
			};
			t_sample switch_129 = (m_LFnoiseSwitch_2 ? output : output_253);
			__m_slide_23 = fixdenorm((__m_slide_23 + (((m_knob2_stutter_5 > __m_slide_23) ? iup_24 : idown_25) * (m_knob2_stutter_5 - __m_slide_23))));
			t_sample slide_140 = __m_slide_23;
			__m_slide_26 = fixdenorm((__m_slide_26 + (((m_knob3_stutter_7 > __m_slide_26) ? iup_27 : idown_28) * (m_knob3_stutter_7 - __m_slide_26))));
			t_sample slide_142 = __m_slide_26;
			t_sample sub_139 = (slide_140 - slide_142);
			t_sample abs_138 = fabs(sub_139);
			t_sample rdiv_137 = safediv(((int)1), abs_138);
			t_sample mul_143 = (switch_129 * rdiv_137);
			t_sample orange_288 = (slide_142 - slide_140);
			t_sample sub_289 = (mul_143 - ((int)0));
			t_sample scale_286 = ((safepow((sub_289 * ((t_sample)1)), ((int)1)) * orange_288) + slide_140);
			double sample_index_29 = (scale_286 * (mybuffer_dim - 1));
			int index_trunc_30 = fixnan(floor(sample_index_29));
			double index_fract_31 = (sample_index_29 - index_trunc_30);
			int index_trunc_32 = (index_trunc_30 + 1);
			bool index_ignore_33 = ((index_trunc_30 >= mybuffer_dim) || (index_trunc_30 < 0));
			bool index_ignore_34 = ((index_trunc_32 >= mybuffer_dim) || (index_trunc_32 < 0));
			// phase mybuffer channel 1;
			double read_mybuffer_35 = (index_ignore_33 ? 0 : m_mybuffer_4.read(index_trunc_30, 0));
			double read_mybuffer_36 = (index_ignore_34 ? 0 : m_mybuffer_4.read(index_trunc_32, 0));
			double readinterp_37 = linear_interp(index_fract_31, read_mybuffer_35, read_mybuffer_36);
			t_sample sample_mybuffer_146 = readinterp_37;
			t_sample index_mybuffer_147 = sample_index_29;
			t_sample mix_290 = (in1 + (m_knob4_mix_3 * (sample_mybuffer_146 - in1)));
			t_sample out1 = mix_290;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			
		};
		return __exception;
		
	};
	inline void set_gate1(t_param _value) {
		m_gate_1 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_LFnoiseSwitch(t_param _value) {
		m_LFnoiseSwitch_2 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4_mix(t_param _value) {
		m_knob4_mix_3 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_mybuffer(void * _value) {
		m_mybuffer_4.setbuffer(_value);
	};
	inline void set_knob2_stutter(t_param _value) {
		m_knob2_stutter_5 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob1_slide(t_param _value) {
		m_knob1_slide_6 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_stutter(t_param _value) {
		m_knob3_stutter_7 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_add(t_param _value) {
		m_add_10 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_mul(t_param _value) {
		m_mul_11 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_freq(t_param _value) {
		m_freq_12 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 3;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 10; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2", "out3" };

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
		case 0: self->set_LFnoiseSwitch(value); break;
		case 1: self->set_add(value); break;
		case 2: self->set_freq(value); break;
		case 3: self->set_gate1(value); break;
		case 4: self->set_knob1_slide(value); break;
		case 5: self->set_knob2_stutter(value); break;
		case 6: self->set_knob3_stutter(value); break;
		case 7: self->set_knob4_mix(value); break;
		case 8: self->set_mul(value); break;
		case 9: self->set_mybuffer(ref); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_LFnoiseSwitch_2; break;
		case 1: *value = self->m_add_10; break;
		case 2: *value = self->m_freq_12; break;
		case 3: *value = self->m_gate_1; break;
		case 4: *value = self->m_knob1_slide_6; break;
		case 5: *value = self->m_knob2_stutter_5; break;
		case 6: *value = self->m_knob3_stutter_7; break;
		case 7: *value = self->m_knob4_mix_3; break;
		case 8: *value = self->m_mul_11; break;
		
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(10 * sizeof(ParamInfo));
	self->__commonstate.numparams = 10;
	// initialize parameter 0 ("m_LFnoiseSwitch_2")
	pi = self->__commonstate.params + 0;
	pi->name = "LFnoiseSwitch";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_LFnoiseSwitch_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_add_10")
	pi = self->__commonstate.params + 1;
	pi->name = "add";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_add_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_freq_12")
	pi = self->__commonstate.params + 2;
	pi->name = "freq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_freq_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_gate_1")
	pi = self->__commonstate.params + 3;
	pi->name = "gate1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_gate_1;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_knob1_slide_6")
	pi = self->__commonstate.params + 4;
	pi->name = "knob1_slide";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_slide_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_knob2_stutter_5")
	pi = self->__commonstate.params + 5;
	pi->name = "knob2_stutter";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob2_stutter_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_knob3_stutter_7")
	pi = self->__commonstate.params + 6;
	pi->name = "knob3_stutter";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_stutter_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_knob4_mix_3")
	pi = self->__commonstate.params + 7;
	pi->name = "knob4_mix";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_mix_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_mul_11")
	pi = self->__commonstate.params + 8;
	pi->name = "mul";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mul_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_mybuffer_4")
	pi = self->__commonstate.params + 9;
	pi->name = "mybuffer";
	pi->paramtype = GENLIB_PARAMTYPE_SYM;
	pi->defaultvalue = 0.;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = false;
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


} // dario_27s_scrubber_wMouse_LFnoise_v2::
