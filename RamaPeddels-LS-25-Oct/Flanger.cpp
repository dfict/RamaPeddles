#include "Flanger.h"

namespace Flanger {

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
	Delay m_delay_6;
	Delay m_delay_2;
	Delay m_delay_1;
	int __exception;
	int vectorsize;
	Sah __m_sah_25;
	Sah __m_sah_23;
	Sah __m_sah_22;
	SineCycle __m_cycle_27;
	SineData __sinedata;
	t_sample m_history_7;
	t_sample m_knob4_res_20;
	t_sample m_knob3_rate_19;
	t_sample m_sw_18;
	t_sample m_history_21;
	t_sample m_history_3;
	t_sample m_history_4;
	t_sample samplerate;
	t_sample m_knob1_manual_17;
	t_sample m_sw_16;
	t_sample m_knob2_depth_15;
	t_sample m_history_9;
	t_sample m_history_8;
	t_sample m_history_5;
	t_sample m_history_10;
	t_sample m_history_13;
	t_sample m_history_11;
	t_sample m_history_14;
	t_sample m_history_12;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_delay_1.reset("m_delay_1", ((int)3840));
		m_delay_2.reset("m_delay_2", ((int)3940));
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_delay_6.reset("m_delay_6", ((int)3840));
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_history_9 = ((int)0);
		m_history_10 = ((int)0);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		m_history_13 = ((int)0);
		m_history_14 = ((int)0);
		m_knob2_depth_15 = ((int)0);
		m_sw_16 = ((int)0);
		m_knob1_manual_17 = ((int)0);
		m_sw_18 = ((int)0);
		m_knob3_rate_19 = ((int)0);
		m_knob4_res_20 = ((int)0);
		m_history_21 = ((int)0);
		__m_sah_22.reset(0);
		__m_sah_23.reset(0);
		__m_sah_25.reset(0);
		__m_cycle_27.reset(samplerate, 0);
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
		t_sample sqrt_5708 = sqrt(m_knob4_res_20);
		t_sample sqrt_5717 = sqrt(sqrt_5708);
		t_sample mul_5729 = (sqrt_5717 * ((t_sample)0.99));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_5711 = __m_sah_22(m_history_21, m_sw_18, ((int)0));
			t_sample gen_5778 = sah_5711;
			t_sample rsub_5709 = (((int)1) - sah_5711);
			t_sample history_5710_next_5712 = fixdenorm(rsub_5709);
			t_sample out5 = gen_5778;
			t_sample mix_6220 = (m_history_14 + (((t_sample)0.0042742627044161) * (m_knob3_rate_19 - m_history_14)));
			t_sample mix_5690 = mix_6220;
			t_sample mix_6221 = (m_history_13 + (((t_sample)0.0042742627044161) * (mix_5690 - m_history_13)));
			t_sample mix_5688 = mix_6221;
			t_sample mix_6222 = (m_history_12 + (((t_sample)0.0042742627044161) * (mix_5688 - m_history_12)));
			t_sample mix_5686 = mix_6222;
			t_sample gen_5697 = mix_5686;
			t_sample history_5691_next_5693 = fixdenorm(mix_5690);
			t_sample history_5689_next_5694 = fixdenorm(mix_5688);
			t_sample history_5687_next_5695 = fixdenorm(mix_5686);
			t_sample expr_6092 = (((int)1) - sqrt(sqrt((((int)1) - gen_5697))));
			t_sample mix_6223 = (m_history_11 + (((t_sample)0.0042742627044161) * (m_knob1_manual_17 - m_history_11)));
			t_sample mix_6096 = mix_6223;
			t_sample mix_6224 = (m_history_10 + (((t_sample)0.0042742627044161) * (mix_6096 - m_history_10)));
			t_sample mix_6102 = mix_6224;
			t_sample mix_6225 = (m_history_9 + (((t_sample)0.0042742627044161) * (mix_6102 - m_history_9)));
			t_sample mix_6100 = mix_6225;
			t_sample gen_5698 = mix_6100;
			t_sample history_5691_next_6098 = fixdenorm(mix_6096);
			t_sample history_5689_next_6101 = fixdenorm(mix_6102);
			t_sample history_5687_next_6094 = fixdenorm(mix_6100);
			t_sample expr_6091 = (((int)1) - sqrt((((int)1) - gen_5698)));
			t_sample sah_6109 = __m_sah_23(m_history_8, m_sw_18, ((int)0));
			t_sample gen_5777 = sah_6109;
			t_sample rsub_6107 = (((int)1) - sah_6109);
			t_sample history_5710_next_6106 = fixdenorm(rsub_6107);
			t_sample add_5774 = (gen_5777 + ((int)1));
			t_sample choice_24 = int(add_5774);
			t_sample gate_5775 = (((choice_24 >= 1) && (choice_24 < 2)) ? ((int)1) : 0);
			t_sample gate_5776 = ((choice_24 >= 2) ? ((int)1) : 0);
			t_sample out4 = gate_5776;
			t_sample out3 = gate_5775;
			t_sample sah_6113 = __m_sah_25(m_history_7, m_sw_18, ((int)0));
			t_sample gen_5713 = sah_6113;
			t_sample rsub_6112 = (((int)1) - sah_6113);
			t_sample history_5710_next_6111 = fixdenorm(rsub_6112);
			t_sample add_5716 = (gen_5713 + ((int)1));
			t_sample choice_26 = int(add_5716);
			t_sample gate_5714 = (((choice_26 >= 1) && (choice_26 < 2)) ? in1 : 0);
			t_sample gate_5715 = ((choice_26 >= 2) ? in1 : 0);
			t_sample mul_5731 = (expr_6091 * ((int)1920));
			t_sample tap_5707 = m_delay_6.read_linear(mul_5731);
			t_sample switch_5705 = (m_sw_16 ? tap_5707 : gate_5715);
			t_sample mul_5720 = (expr_6092 * ((int)10));
			__m_cycle_27.freq(mul_5720);
			t_sample cycle_5721 = __m_cycle_27(__sinedata);
			t_sample cycleindex_5722 = __m_cycle_27.phase();
			t_sample mix_6226 = (m_history_5 + (((t_sample)0.0042742627044161) * (m_knob2_depth_15 - m_history_5)));
			t_sample mix_6123 = mix_6226;
			t_sample mix_6227 = (m_history_4 + (((t_sample)0.0042742627044161) * (mix_6123 - m_history_4)));
			t_sample mix_6119 = mix_6227;
			t_sample mix_6228 = (m_history_3 + (((t_sample)0.0042742627044161) * (mix_6119 - m_history_3)));
			t_sample mix_6118 = mix_6228;
			t_sample gen_5696 = mix_6118;
			t_sample history_5691_next_6124 = fixdenorm(mix_6123);
			t_sample history_5689_next_6120 = fixdenorm(mix_6119);
			t_sample history_5687_next_6117 = fixdenorm(mix_6118);
			t_sample mul_5725 = (gen_5696 * mul_5731);
			t_sample mul_5719 = (cycle_5721 * mul_5725);
			t_sample add_5723 = (mul_5731 + mul_5719);
			t_sample clamp_5724 = ((add_5723 <= ((int)0)) ? ((int)0) : ((add_5723 >= ((int)3940)) ? ((int)3940) : add_5723));
			t_sample tap_5728 = m_delay_2.read_linear(clamp_5724);
			t_sample add_5703 = (switch_5705 + tap_5728);
			t_sample div_5701 = (add_5703 * ((t_sample)0.5));
			t_sample add_5684 = (gate_5714 + div_5701);
			t_sample out2 = add_5684;
			t_sample mul_5726 = (tap_5728 * mul_5729);
			t_sample tap_5733 = m_delay_1.read_linear(clamp_5724);
			t_sample add_5704 = (switch_5705 + tap_5733);
			t_sample div_5702 = (add_5704 * ((t_sample)0.5));
			t_sample add_5685 = (gate_5714 + div_5702);
			t_sample out1 = add_5685;
			t_sample mul_5730 = (tap_5733 * mul_5729);
			m_history_21 = history_5710_next_5712;
			m_history_14 = history_5691_next_5693;
			m_history_12 = history_5687_next_5695;
			m_history_13 = history_5689_next_5694;
			m_history_11 = history_5691_next_6098;
			m_history_9 = history_5687_next_6094;
			m_history_10 = history_5689_next_6101;
			m_history_8 = history_5710_next_6106;
			m_history_7 = history_5710_next_6111;
			m_delay_6.write(gate_5715);
			m_history_5 = history_5691_next_6124;
			m_history_3 = history_5687_next_6117;
			m_history_4 = history_5689_next_6120;
			m_delay_2.write(mul_5730);
			m_delay_1.write((mul_5726 + gate_5715));
			m_delay_1.step();
			m_delay_2.step();
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
	inline void set_knob2_depth(t_param _value) {
		m_knob2_depth_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw5(t_param _value) {
		m_sw_16 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob1_manual(t_param _value) {
		m_knob1_manual_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_rate(t_param _value) {
		m_knob3_rate_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4_res(t_param _value) {
		m_knob4_res_20 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
int num_params() { return 6; }

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
		case 0: self->set_knob1_manual(value); break;
		case 1: self->set_knob2_depth(value); break;
		case 2: self->set_knob3_rate(value); break;
		case 3: self->set_knob4_res(value); break;
		case 4: self->set_sw1(value); break;
		case 5: self->set_sw5(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob1_manual_17; break;
		case 1: *value = self->m_knob2_depth_15; break;
		case 2: *value = self->m_knob3_rate_19; break;
		case 3: *value = self->m_knob4_res_20; break;
		case 4: *value = self->m_sw_18; break;
		case 5: *value = self->m_sw_16; break;
		
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
	// initialize parameter 0 ("m_knob1_manual_17")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1_manual";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_manual_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob2_depth_15")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2_depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob2_depth_15;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob3_rate_19")
	pi = self->__commonstate.params + 2;
	pi->name = "knob3_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_rate_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob4_res_20")
	pi = self->__commonstate.params + 3;
	pi->name = "knob4_res";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_res_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_sw_18")
	pi = self->__commonstate.params + 4;
	pi->name = "sw1";
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
	// initialize parameter 5 ("m_sw_16")
	pi = self->__commonstate.params + 5;
	pi->name = "sw5";
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


} // Flanger::
