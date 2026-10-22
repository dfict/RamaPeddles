#include "TestTone.h"

namespace TestTone {

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
	Sah __m_sah_20;
	Sah __m_sah_18;
	Sah __m_sah_17;
	SineCycle __m_cycle_23;
	SineCycle __m_cycle_21;
	SineCycle __m_cycle_22;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample m_history_6;
	t_sample m_history_3;
	t_sample m_history_16;
	t_sample m_knob_15;
	t_sample m_history_2;
	t_sample samplerate;
	t_sample m_history_1;
	t_sample m_history_5;
	t_sample m_sw_14;
	t_sample m_knob_12;
	t_sample m_history_8;
	t_sample m_history_7;
	t_sample m_knob_13;
	t_sample m_knob_9;
	t_sample m_knob_11;
	t_sample m_history_4;
	t_sample m_knob_10;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_history_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_history_4 = ((int)0);
		m_history_5 = ((int)0);
		m_history_6 = ((int)0);
		m_history_7 = ((int)0);
		m_history_8 = ((int)0);
		m_knob_9 = ((int)0);
		m_knob_10 = ((int)0);
		m_knob_11 = ((int)0);
		m_knob_12 = ((int)0);
		m_knob_13 = ((int)0);
		m_sw_14 = ((int)0);
		m_knob_15 = ((int)0);
		m_history_16 = ((int)0);
		__m_sah_17.reset(0);
		__m_sah_18.reset(0);
		__m_sah_20.reset(0);
		__m_cycle_21.reset(samplerate, 0);
		__m_cycle_22.reset(samplerate, 0);
		__m_cycle_23.reset(samplerate, 0);
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
		t_sample sub_5561 = (m_knob_11 - ((int)0));
		t_sample scale_5558 = ((safepow((sub_5561 * ((t_sample)1)), ((int)1)) * ((int)800)) + ((int)200));
		t_sample sub_5565 = (m_knob_9 - ((int)0));
		t_sample scale_5562 = ((safepow((sub_5565 * ((t_sample)1)), ((int)1)) * ((int)800)) + ((int)200));
		t_sample sub_5569 = (m_knob_15 - ((int)0));
		t_sample scale_5566 = ((safepow((sub_5569 * ((t_sample)1)), ((int)1)) * ((int)800)) + ((int)200));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			const t_sample in2 = (*(__in2++));
			t_sample sah_5368 = __m_sah_17(m_history_16, m_sw_14, ((int)0));
			t_sample gen_5379 = sah_5368;
			t_sample rsub_5366 = (((int)1) - sah_5368);
			t_sample history_5367_next_5369 = fixdenorm(rsub_5366);
			t_sample out5 = gen_5379;
			t_sample sah_5382 = __m_sah_18(m_history_8, m_sw_14, ((int)0));
			t_sample gen_5378 = sah_5382;
			t_sample rsub_5380 = (((int)1) - sah_5382);
			t_sample history_5367_next_5381 = fixdenorm(rsub_5380);
			t_sample add_5375 = (gen_5378 + ((int)1));
			t_sample choice_19 = int(add_5375);
			t_sample gate_5376 = (((choice_19 >= 1) && (choice_19 < 2)) ? ((int)1) : 0);
			t_sample gate_5377 = ((choice_19 >= 2) ? ((int)1) : 0);
			t_sample out4 = gate_5377;
			t_sample out3 = gate_5376;
			t_sample sah_5387 = __m_sah_20(m_history_7, m_sw_14, ((int)0));
			t_sample gen_5370 = sah_5387;
			t_sample rsub_5385 = (((int)1) - sah_5387);
			t_sample history_5367_next_5386 = fixdenorm(rsub_5385);
			t_sample add_5365 = (gen_5370 + ((int)1));
			t_sample mix_5552 = (m_history_6 + (((t_sample)0.001308996565174) * (m_knob_10 - m_history_6)));
			t_sample mix_5344 = mix_5552;
			t_sample mix_5553 = (m_history_5 + (((t_sample)0.001308996565174) * (mix_5344 - m_history_5)));
			t_sample mix_5342 = mix_5553;
			t_sample gen_5349 = mix_5342;
			t_sample history_5345_next_5347 = fixdenorm(mix_5344);
			t_sample history_5343_next_5348 = fixdenorm(mix_5342);
			t_sample mix_5554 = (m_history_4 + (((t_sample)0.001308996565174) * (m_knob_13 - m_history_4)));
			t_sample mix_5391 = mix_5554;
			t_sample mix_5555 = (m_history_3 + (((t_sample)0.001308996565174) * (mix_5391 - m_history_3)));
			t_sample mix_5390 = mix_5555;
			t_sample gen_5360 = mix_5390;
			t_sample history_5345_next_5396 = fixdenorm(mix_5391);
			t_sample history_5343_next_5394 = fixdenorm(mix_5390);
			t_sample mix_5556 = (m_history_2 + (((t_sample)0.001308996565174) * (m_knob_12 - m_history_2)));
			t_sample mix_5404 = mix_5556;
			t_sample mix_5557 = (m_history_1 + (((t_sample)0.001308996565174) * (mix_5404 - m_history_1)));
			t_sample mix_5403 = mix_5557;
			t_sample gen_5354 = mix_5403;
			t_sample history_5345_next_5402 = fixdenorm(mix_5404);
			t_sample history_5343_next_5400 = fixdenorm(mix_5403);
			__m_cycle_21.freq(scale_5558);
			t_sample cycle_5351 = __m_cycle_21(__sinedata);
			t_sample cycleindex_5352 = __m_cycle_21.phase();
			t_sample mul_5350 = (cycle_5351 * gen_5349);
			__m_cycle_22.freq(scale_5562);
			t_sample cycle_5362 = __m_cycle_22(__sinedata);
			t_sample cycleindex_5363 = __m_cycle_22.phase();
			t_sample mul_5361 = (cycle_5362 * gen_5360);
			__m_cycle_23.freq(scale_5566);
			t_sample cycle_5356 = __m_cycle_23(__sinedata);
			t_sample cycleindex_5357 = __m_cycle_23.phase();
			t_sample mul_5355 = (cycle_5356 * gen_5354);
			t_sample add_5359 = (mul_5361 + mul_5355);
			t_sample add_5341 = (add_5359 + mul_5350);
			t_sample choice_24 = int(add_5365);
			t_sample gate_5372 = (((choice_24 >= 1) && (choice_24 < 2)) ? add_5341 : 0);
			t_sample gate_5373 = ((choice_24 >= 2) ? add_5341 : 0);
			t_sample add_5371 = (((int)0) + gate_5372);
			t_sample out2 = add_5371;
			t_sample out1 = add_5371;
			m_history_16 = history_5367_next_5369;
			m_history_8 = history_5367_next_5381;
			m_history_7 = history_5367_next_5386;
			m_history_6 = history_5345_next_5347;
			m_history_5 = history_5343_next_5348;
			m_history_4 = history_5345_next_5396;
			m_history_3 = history_5343_next_5394;
			m_history_2 = history_5345_next_5402;
			m_history_1 = history_5343_next_5400;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			
		};
		return __exception;
		
	};
	inline void set_knob1(t_param _value) {
		m_knob_9 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob6(t_param _value) {
		m_knob_10 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3(t_param _value) {
		m_knob_11 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5(t_param _value) {
		m_knob_12 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4(t_param _value) {
		m_knob_13 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw7(t_param _value) {
		m_sw_14 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2(t_param _value) {
		m_knob_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
		case 0: self->set_knob1(value); break;
		case 1: self->set_knob2(value); break;
		case 2: self->set_knob3(value); break;
		case 3: self->set_knob4(value); break;
		case 4: self->set_knob5(value); break;
		case 5: self->set_knob6(value); break;
		case 6: self->set_sw7(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob_9; break;
		case 1: *value = self->m_knob_15; break;
		case 2: *value = self->m_knob_11; break;
		case 3: *value = self->m_knob_13; break;
		case 4: *value = self->m_knob_12; break;
		case 5: *value = self->m_knob_10; break;
		case 6: *value = self->m_sw_14; break;
		
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
	// initialize parameter 0 ("m_knob_9")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_9;
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
	// initialize parameter 2 ("m_knob_11")
	pi = self->__commonstate.params + 2;
	pi->name = "knob3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_11;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob_13")
	pi = self->__commonstate.params + 3;
	pi->name = "knob4";
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
	// initialize parameter 4 ("m_knob_12")
	pi = self->__commonstate.params + 4;
	pi->name = "knob5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_12;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_knob_10")
	pi = self->__commonstate.params + 5;
	pi->name = "knob6";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_10;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_sw_14")
	pi = self->__commonstate.params + 6;
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
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // TestTone::
