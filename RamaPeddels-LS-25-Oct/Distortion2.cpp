#include "Distortion2.h"

namespace Distortion2 {

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
	Sah __m_sah_12;
	Sah __m_sah_14;
	t_sample m_history_3;
	t_sample m_knob3_tone_9;
	t_sample m_history_10;
	t_sample samplerate;
	t_sample m_d_2;
	t_sample m_sw_8;
	t_sample m_knob2_squish_6;
	t_sample m_knob1_drive_7;
	t_sample m_history_4;
	t_sample m_d_1;
	t_sample m_knob4_output_5;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_d_1 = ((int)0);
		m_d_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_knob4_output_5 = ((int)0);
		m_knob2_squish_6 = ((int)0);
		m_knob1_drive_7 = ((int)0);
		m_sw_8 = ((int)0);
		m_knob3_tone_9 = ((int)0);
		m_history_10 = ((int)0);
		__m_sah_11.reset(0);
		__m_sah_12.reset(0);
		__m_sah_14.reset(0);
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
		t_sample mtof_4376 = mtof(m_knob3_tone_9, ((int)440));
		t_sample dbtoa_4404 = dbtoa(m_knob4_output_5);
		t_sample freq = mtof_4376;
		t_sample f1 = sin(safediv((((t_sample)6.2831853071796) * freq), samplerate));
		t_sample sub_4654 = (m_knob1_drive_7 - ((int)0));
		t_sample scale_4651 = ((safepow((sub_4654 * ((t_sample)1)), ((int)1)) * ((int)6)) + ((int)1));
		t_sample sub_4658 = (m_knob1_drive_7 - ((int)0));
		t_sample scale_4655 = ((safepow((sub_4658 * ((t_sample)1)), ((int)1)) * ((int)-76)) + ((int)6));
		t_sample rdiv_4385 = safediv(((int)1), m_knob2_squish_6);
		t_sample rsub_4384 = (((int)1) - rdiv_4385);
		t_sample rdiv_4369 = safediv(((int)1), m_knob2_squish_6);
		t_sample rsub_4368 = (((int)1) - rdiv_4369);
		t_sample rdiv_4354 = safediv(((int)1), m_knob2_squish_6);
		t_sample rsub_4353 = (((int)1) - rdiv_4354);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_4398 = __m_sah_11(m_history_10, m_sw_8, ((int)0));
			t_sample gen_4424 = sah_4398;
			t_sample rsub_4396 = (((int)1) - sah_4398);
			t_sample history_4397_next_4399 = fixdenorm(rsub_4396);
			t_sample out5 = gen_4424;
			t_sample sah_4564 = __m_sah_12(m_history_4, m_sw_8, ((int)0));
			t_sample gen_4423 = sah_4564;
			t_sample rsub_4561 = (((int)1) - sah_4564);
			t_sample history_4397_next_4563 = fixdenorm(rsub_4561);
			t_sample add_4420 = (gen_4423 + ((int)1));
			t_sample choice_13 = int(add_4420);
			t_sample gate_4421 = (((choice_13 >= 1) && (choice_13 < 2)) ? ((int)1) : 0);
			t_sample gate_4422 = ((choice_13 >= 2) ? ((int)1) : 0);
			t_sample out3 = gate_4421;
			t_sample out4 = gate_4422;
			t_sample sah_4569 = __m_sah_14(m_history_3, m_sw_8, ((int)0));
			t_sample gen_4400 = sah_4569;
			t_sample rsub_4566 = (((int)1) - sah_4569);
			t_sample history_4397_next_4567 = fixdenorm(rsub_4566);
			t_sample add_4403 = (gen_4400 + ((int)1));
			t_sample choice_15 = int(add_4403);
			t_sample gate_4401 = (((choice_15 >= 1) && (choice_15 < 2)) ? in1 : 0);
			t_sample gate_4402 = ((choice_15 >= 2) ? in1 : 0);
			t_sample L = (m_d_1 + (f1 * m_d_2));
			t_sample H = ((gate_4402 - L) - (((t_sample)0.2) * m_d_2));
			t_sample B = ((f1 * H) + m_d_2);
			m_d_2 = B;
			m_d_1 = L;
			t_sample abs_4389 = fabs(L);
			t_sample atodb_4388 = atodb(abs_4389);
			int gt_4386 = (atodb_4388 > scale_4655);
			t_sample sub_4387 = (scale_4655 - atodb_4388);
			t_sample mul_4383 = (sub_4387 * rsub_4384);
			t_sample dbtoa_4382 = dbtoa(mul_4383);
			t_sample rsub_4381 = (((int)1) - dbtoa_4382);
			t_sample mul_4380 = (rsub_4381 * (-1));
			t_sample mul_4379 = (gt_4386 * mul_4380);
			t_sample add_4378 = (mul_4379 + ((int)1));
			t_sample clamp_4377 = ((add_4378 <= ((int)0)) ? ((int)0) : ((add_4378 >= ((int)1)) ? ((int)1) : add_4378));
			t_sample mul_4390 = (L * clamp_4377);
			t_sample abs_4373 = fabs(H);
			t_sample atodb_4372 = atodb(abs_4373);
			int gt_4370 = (atodb_4372 > scale_4655);
			t_sample sub_4371 = (scale_4655 - atodb_4372);
			t_sample mul_4367 = (sub_4371 * rsub_4368);
			t_sample dbtoa_4366 = dbtoa(mul_4367);
			t_sample rsub_4365 = (((int)1) - dbtoa_4366);
			t_sample mul_4364 = (rsub_4365 * (-1));
			t_sample mul_4363 = (gt_4370 * mul_4364);
			t_sample add_4362 = (mul_4363 + ((int)1));
			t_sample clamp_4361 = ((add_4362 <= ((int)0)) ? ((int)0) : ((add_4362 >= ((int)1)) ? ((int)1) : add_4362));
			t_sample mul_4374 = (H * clamp_4361);
			t_sample abs_4358 = fabs(B);
			t_sample atodb_4357 = atodb(abs_4358);
			int gt_4355 = (atodb_4357 > scale_4655);
			t_sample sub_4356 = (scale_4655 - atodb_4357);
			t_sample mul_4352 = (sub_4356 * rsub_4353);
			t_sample dbtoa_4351 = dbtoa(mul_4352);
			t_sample rsub_4350 = (((int)1) - dbtoa_4351);
			t_sample mul_4349 = (rsub_4350 * (-1));
			t_sample mul_4348 = (gt_4355 * mul_4349);
			t_sample add_4347 = (mul_4348 + ((int)1));
			t_sample clamp_4346 = ((add_4347 <= ((int)0)) ? ((int)0) : ((add_4347 >= ((int)1)) ? ((int)1) : add_4347));
			t_sample mul_4359 = (B * clamp_4346);
			t_sample mul_4344 = (((mul_4359 + mul_4374) + mul_4390) * scale_4651);
			t_sample mul_4405 = (mul_4344 * dbtoa_4404);
			t_sample add_4342 = (gate_4401 + mul_4405);
			t_sample out1 = add_4342;
			t_sample out2 = add_4342;
			m_history_10 = history_4397_next_4399;
			m_history_4 = history_4397_next_4563;
			m_history_3 = history_4397_next_4567;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			
		};
		return __exception;
		
	};
	inline void set_knob4_output(t_param _value) {
		m_knob4_output_5 = (_value < -70 ? -70 : (_value > 15 ? 15 : _value));
	};
	inline void set_knob2_squish(t_param _value) {
		m_knob2_squish_6 = (_value < 1 ? 1 : (_value > 5 ? 5 : _value));
	};
	inline void set_knob1_drive(t_param _value) {
		m_knob1_drive_7 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_8 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_tone(t_param _value) {
		m_knob3_tone_9 = (_value < 20 ? 20 : (_value > 80 ? 80 : _value));
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
		case 0: self->set_knob1_drive(value); break;
		case 1: self->set_knob2_squish(value); break;
		case 2: self->set_knob3_tone(value); break;
		case 3: self->set_knob4_output(value); break;
		case 4: self->set_sw1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob1_drive_7; break;
		case 1: *value = self->m_knob2_squish_6; break;
		case 2: *value = self->m_knob3_tone_9; break;
		case 3: *value = self->m_knob4_output_5; break;
		case 4: *value = self->m_sw_8; break;
		
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
	// initialize parameter 0 ("m_knob1_drive_7")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1_drive";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_drive_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob2_squish_6")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2_squish";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob2_squish_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 5;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob3_tone_9")
	pi = self->__commonstate.params + 2;
	pi->name = "knob3_tone";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_tone_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 80;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob4_output_5")
	pi = self->__commonstate.params + 3;
	pi->name = "knob4_output";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_output_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -70;
	pi->outputmax = 15;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_sw_8")
	pi = self->__commonstate.params + 4;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_8;
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


} // Distortion2::
