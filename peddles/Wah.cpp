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
	t_sample m_knob2_range_8;
	t_sample m_knob4_res_9;
	t_sample m_history_10;
	t_sample m_history_11;
	t_sample m_knob3_slew_7;
	t_sample m_knob1_base_6;
	t_sample m_history_5;
	t_sample m_history_4;
	t_sample samplerate;
	t_sample m_history_12;
	t_sample m_y_1;
	t_sample m_history_3;
	t_sample m_y_2;
	t_sample __m_slide_13;
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
		m_knob1_base_6 = 0;
		m_knob3_slew_7 = 1;
		m_knob2_range_8 = 1;
		m_knob4_res_9 = 0.5;
		m_history_10 = ((int)0);
		m_history_11 = ((int)0);
		m_history_12 = ((int)0);
		__m_slide_13 = 0;
		genlib_reset_complete(this);
		
	};
	// the signal processing routine;
	inline int perform(t_sample ** __ins, t_sample ** __outs, int __n) {
		vectorsize = __n;
		const t_sample * __in1 = __ins[0];
		t_sample * __out1 = __outs[0];
		t_sample * __out2 = __outs[1];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample mul_1250 = (m_knob3_slew_7 * ((int)1));
		t_sample mstosamps_1252 = (mul_1250 * (samplerate * 0.001));
		t_sample mul_1249 = (m_knob3_slew_7 * ((int)10));
		t_sample mstosamps_1251 = (mul_1249 * (samplerate * 0.001));
		t_sample iup_14 = (1 / maximum(1, abs(mstosamps_1252)));
		t_sample idown_15 = (1 / maximum(1, abs(mstosamps_1251)));
		t_sample clamp_1244 = ((m_knob4_res_9 <= ((int)0)) ? ((int)0) : ((m_knob4_res_9 >= ((t_sample)0.999999)) ? ((t_sample)0.999999) : m_knob4_res_9));
		t_sample mul_1242 = (clamp_1244 * ((t_sample)0.125));
		t_sample exp_1243 = exp(mul_1242);
		t_sample mul_1241 = (exp_1243 * ((t_sample)0.882497));
		t_sample mul_1237 = (mul_1241 * mul_1241);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample mix_1310 = (m_history_12 + (((t_sample)0.0042742627044161) * (m_knob1_base_6 - m_history_12)));
			t_sample mix_1219 = mix_1310;
			t_sample mix_1311 = (m_history_11 + (((t_sample)0.0042742627044161) * (mix_1219 - m_history_11)));
			t_sample mix_1217 = mix_1311;
			t_sample mix_1312 = (m_history_10 + (((t_sample)0.0042742627044161) * (mix_1217 - m_history_10)));
			t_sample mix_1215 = mix_1312;
			t_sample gen_1227 = mix_1215;
			t_sample history_1220_next_1222 = fixdenorm(mix_1219);
			t_sample history_1218_next_1223 = fixdenorm(mix_1217);
			t_sample history_1216_next_1224 = fixdenorm(mix_1215);
			t_sample mix_1313 = (m_history_5 + (((t_sample)0.0042742627044161) * (m_knob2_range_8 - m_history_5)));
			t_sample mix_1266 = mix_1313;
			t_sample mix_1314 = (m_history_4 + (((t_sample)0.0042742627044161) * (mix_1266 - m_history_4)));
			t_sample mix_1257 = mix_1314;
			t_sample mix_1315 = (m_history_3 + (((t_sample)0.0042742627044161) * (mix_1257 - m_history_3)));
			t_sample mix_1265 = mix_1315;
			t_sample gen_1225 = mix_1265;
			t_sample history_1220_next_1261 = fixdenorm(mix_1266);
			t_sample history_1218_next_1258 = fixdenorm(mix_1257);
			t_sample history_1216_next_1259 = fixdenorm(mix_1265);
			t_sample abs_1254 = fabs(in1);
			__m_slide_13 = fixdenorm((__m_slide_13 + (((abs_1254 > __m_slide_13) ? iup_14 : idown_15) * (abs_1254 - __m_slide_13))));
			t_sample slide_1253 = __m_slide_13;
			t_sample mul_1214 = (slide_1253 * ((int)30));
			t_sample clamp_1212 = ((mul_1214 <= ((int)0)) ? ((int)0) : ((mul_1214 >= ((int)1)) ? ((int)1) : mul_1214));
			t_sample sqrt_1213 = sqrt(clamp_1212);
			t_sample mul_1248 = (sqrt_1213 * gen_1225);
			t_sample add_1229 = (mul_1248 + gen_1227);
			t_sample clamp_1228 = ((add_1229 <= ((int)0)) ? ((int)0) : ((add_1229 >= ((int)1)) ? ((int)1) : add_1229));
			t_sample sub_1319 = (clamp_1228 - ((int)0));
			t_sample scale_1316 = ((safepow((sub_1319 * ((t_sample)1)), ((int)1)) * ((int)120)) + ((int)15));
			t_sample scale_1230 = scale_1316;
			t_sample mtof_1226 = mtof(scale_1230, ((int)440));
			t_sample mul_1231 = (mtof_1226 * safediv(6.2831853071796, samplerate));
			t_sample cos_1240 = cos(mul_1231);
			t_sample mul_1233 = (mul_1237 * m_y_2);
			t_sample mul_1239 = (cos_1240 * mul_1241);
			t_sample mul_1238 = (mul_1239 * (-2));
			t_sample mul_1234 = (mul_1238 * m_y_1);
			t_sample add_1236 = ((mul_1237 + mul_1238) + ((int)1));
			t_sample mul_1235 = (in1 * add_1236);
			t_sample sub_1232 = (mul_1235 - (mul_1233 + mul_1234));
			t_sample gen_1247 = sub_1232;
			t_sample y2_next_1245 = fixdenorm(m_y_1);
			t_sample y1_next_1246 = fixdenorm(sub_1232);
			t_sample add_1256 = (gen_1247 + ((int)0));
			t_sample out1 = add_1256;
			t_sample add_1255 = (gen_1247 + ((int)0));
			t_sample out2 = add_1255;
			m_history_12 = history_1220_next_1222;
			m_history_10 = history_1216_next_1224;
			m_history_11 = history_1218_next_1223;
			m_history_5 = history_1220_next_1261;
			m_history_3 = history_1216_next_1259;
			m_history_4 = history_1218_next_1258;
			m_y_2 = y2_next_1245;
			m_y_1 = y1_next_1246;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			
		};
		return __exception;
		
	};
	inline void set_knob1_base(t_param _value) {
		m_knob1_base_6 = (_value < 0 ? 0 : (_value > 0.8 ? 0.8 : _value));
	};
	inline void set_knob3_slew(t_param _value) {
		m_knob3_slew_7 = (_value < 1 ? 1 : (_value > 30 ? 30 : _value));
	};
	inline void set_knob2_range(t_param _value) {
		m_knob2_range_8 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4_res(t_param _value) {
		m_knob4_res_9 = (_value < 0.5 ? 0.5 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 2;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 4; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2" };

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
		case 0: self->set_knob1_base(value); break;
		case 1: self->set_knob2_range(value); break;
		case 2: self->set_knob3_slew(value); break;
		case 3: self->set_knob4_res(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob1_base_6; break;
		case 1: *value = self->m_knob2_range_8; break;
		case 2: *value = self->m_knob3_slew_7; break;
		case 3: *value = self->m_knob4_res_9; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(4 * sizeof(ParamInfo));
	self->__commonstate.numparams = 4;
	// initialize parameter 0 ("m_knob1_base_6")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1_base";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_base_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.8;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob2_range_8")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2_range";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob2_range_8;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob3_slew_7")
	pi = self->__commonstate.params + 2;
	pi->name = "knob3_slew";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_slew_7;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob4_res_9")
	pi = self->__commonstate.params + 3;
	pi->name = "knob4_res";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_res_9;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.5;
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
