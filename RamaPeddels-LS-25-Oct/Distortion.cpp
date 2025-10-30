#include "Distortion.h"

namespace Distortion {

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
	Sah __m_sah_8;
	Sah __m_sah_9;
	Sah __m_sah_11;
	t_sample m_history_3;
	t_sample m_history_7;
	t_sample samplerate;
	t_sample m_b_sbuf_2;
	t_sample m_knob1_drive_6;
	t_sample m_history_1;
	t_sample m_knob2_output_5;
	t_sample m_sw_4;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_b_sbuf_2 = ((int)0);
		m_history_3 = ((int)0);
		m_sw_4 = ((int)0);
		m_knob2_output_5 = ((int)0);
		m_knob1_drive_6 = ((int)0);
		m_history_7 = ((int)0);
		__m_sah_8.reset(0);
		__m_sah_9.reset(0);
		__m_sah_11.reset(0);
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
		t_sample sub_4341 = (m_knob1_drive_6 - ((int)0));
		t_sample scale_4338 = ((safepow((sub_4341 * ((t_sample)1)), ((int)1)) * ((t_sample)999.9999)) + ((t_sample)0.0001));
		t_sample scale_4157 = scale_4338;
		t_sample dbtoa_4176 = dbtoa(m_knob2_output_5);
		t_sample b_filterdrive = scale_4157;
		t_sample mul_4155 = (m_knob1_drive_6 * ((int)4));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_4170 = __m_sah_8(m_history_7, m_sw_4, ((int)0));
			t_sample gen_4197 = sah_4170;
			t_sample rsub_4168 = (((int)1) - sah_4170);
			t_sample history_4169_next_4171 = fixdenorm(rsub_4168);
			t_sample out5 = gen_4197;
			t_sample sah_4307 = __m_sah_9(m_history_3, m_sw_4, ((int)0));
			t_sample gen_4172 = sah_4307;
			t_sample rsub_4304 = (((int)1) - sah_4307);
			t_sample history_4169_next_4306 = fixdenorm(rsub_4304);
			t_sample add_4175 = (gen_4172 + ((int)1));
			t_sample choice_10 = int(add_4175);
			t_sample gate_4173 = (((choice_10 >= 1) && (choice_10 < 2)) ? in1 : 0);
			t_sample gate_4174 = ((choice_10 >= 2) ? in1 : 0);
			t_sample b_in = gate_4174;
			t_sample b_inr = fabs((b_in * b_filterdrive));
			t_sample b_inrns = b_inr;
			if ((b_inr > ((int)1))) {
				b_inr = ((int)1);
				
			};
			t_sample b_dax = (b_inr - ((b_inr * b_inr) * ((t_sample)0.5)));
			t_sample b_dax_4294 = (b_dax - b_inr);
			t_sample b_inr_4295 = (b_inr + b_dax_4294);
			t_sample b_inr_4296 = (b_inr_4295 * ((t_sample)0.24));
			if ((b_inr_4296 > ((int)1))) {
				b_inr_4296 = ((int)1);
				
			};
			t_sample b_dax_4297 = (b_inr_4296 - ((b_inr_4296 * ((t_sample)0.33333333)) * (b_inr_4296 * b_inr_4296)));
			t_sample b_dax_4298 = (b_dax_4297 - b_inr_4296);
			t_sample b_inr_4299 = (b_inr_4296 + b_dax_4298);
			t_sample b_inr_4300 = (b_inr_4299 * ((t_sample)4.1666666666667));
			t_sample b_mul = safediv(b_inrns, b_inr_4300);
			m_b_sbuf_2 = ((m_b_sbuf_2 - (m_b_sbuf_2 * ((t_sample)0.43))) + (b_mul * ((t_sample)0.43)));
			t_sample b_mul_4301 = (m_b_sbuf_2 + ((b_mul - m_b_sbuf_2) * ((t_sample)0.691)));
			t_sample b_in_4302 = safediv(b_in, b_mul_4301);
			t_sample sah_4310 = __m_sah_11(m_history_1, m_sw_4, ((int)0));
			t_sample gen_4196 = sah_4310;
			t_sample rsub_4311 = (((int)1) - sah_4310);
			t_sample history_4169_next_4309 = fixdenorm(rsub_4311);
			t_sample add_4193 = (gen_4196 + ((int)1));
			t_sample choice_12 = int(add_4193);
			t_sample gate_4194 = (((choice_12 >= 1) && (choice_12 < 2)) ? ((int)1) : 0);
			t_sample gate_4195 = ((choice_12 >= 2) ? ((int)1) : 0);
			t_sample out3 = gate_4194;
			t_sample out4 = gate_4195;
			t_sample mul_4154 = (b_in_4302 * mul_4155);
			t_sample mul_4177 = (mul_4154 * dbtoa_4176);
			t_sample add_4153 = (gate_4173 + mul_4177);
			t_sample out1 = add_4153;
			t_sample out2 = add_4153;
			m_history_7 = history_4169_next_4171;
			m_history_3 = history_4169_next_4306;
			m_history_1 = history_4169_next_4309;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			
		};
		return __exception;
		
	};
	inline void set_sw1(t_param _value) {
		m_sw_4 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2_output(t_param _value) {
		m_knob2_output_5 = (_value < -70 ? -70 : (_value > 20 ? 20 : _value));
	};
	inline void set_knob1_drive(t_param _value) {
		m_knob1_drive_6 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
int num_params() { return 3; }

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
		case 0: self->set_knob1_drive(value); break;
		case 1: self->set_knob2_output(value); break;
		case 2: self->set_sw1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob1_drive_6; break;
		case 1: *value = self->m_knob2_output_5; break;
		case 2: *value = self->m_sw_4; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(3 * sizeof(ParamInfo));
	self->__commonstate.numparams = 3;
	// initialize parameter 0 ("m_knob1_drive_6")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1_drive";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_drive_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
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
	pi->outputmax = 20;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_sw_4")
	pi = self->__commonstate.params + 2;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_4;
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


} // Distortion::
