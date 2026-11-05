#include "DigitalDelay.h"

namespace DigitalDelay {

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
	Delay m_delay_2;
	Delay m_delay_3;
	Sah __m_sah_25;
	Sah __m_sah_26;
	int __exception;
	int vectorsize;
	t_sample m_knob1_level_18;
	t_sample m_history_17;
	t_sample m_history_16;
	t_sample m_knob3_slew_19;
	t_sample m_knob3_time_21;
	t_sample m_history_15;
	t_sample m_mult_24;
	t_sample m_knob2_fb_20;
	t_sample m_sw_23;
	t_sample m_knob_22;
	t_sample m_history_14;
	t_sample m_history_12;
	t_sample m_history_11;
	t_sample m_history_4;
	t_sample m_history_5;
	t_sample m_y_1;
	t_sample samplerate;
	t_sample m_history_13;
	t_sample m_history_6;
	t_sample m_history_8;
	t_sample m_history_7;
	t_sample m_history_10;
	t_sample m_history_9;
	t_sample __m_slide_28;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_y_1 = ((int)0);
		m_delay_2.reset("m_delay_2", ((int)96000));
		m_delay_3.reset("m_delay_3", ((int)96000));
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
		m_history_14 = ((int)0);
		m_history_15 = ((int)0);
		m_history_16 = ((int)0);
		m_history_17 = ((int)0);
		m_knob1_level_18 = ((int)0);
		m_knob3_slew_19 = 1;
		m_knob2_fb_20 = ((int)0);
		m_knob3_time_21 = ((int)0);
		m_knob_22 = ((int)0);
		m_sw_23 = ((int)0);
		m_mult_24 = ((int)0);
		__m_sah_25.reset(0);
		__m_sah_26.reset(0);
		__m_slide_28 = 0;
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
		t_sample * __out7 = __outs[6];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) || (__out7 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample add_3606 = (m_knob2_fb_20 + ((int)0));
		t_sample mstosamps_3633 = (((int)10) * (samplerate * 0.001));
		t_sample mstosamps_3632 = (((int)100) * (samplerate * 0.001));
		t_sample iup_29 = (1 / maximum(1, abs(mstosamps_3633)));
		t_sample idown_30 = (1 / maximum(1, abs(mstosamps_3632)));
		int choice_31 = ((int)1);
		int choice_32 = ((int)1);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out7 = ((int)0);
			t_sample sah_3645 = __m_sah_25(m_history_17, m_sw_23, ((int)0));
			t_sample gen_3648 = sah_3645;
			t_sample rsub_3643 = (((int)1) - sah_3645);
			t_sample history_3644_next_3646 = fixdenorm(rsub_3643);
			t_sample out5 = gen_3648;
			t_sample sah_3819 = __m_sah_26(m_history_16, m_sw_23, ((int)0));
			t_sample gen_3647 = sah_3819;
			t_sample rsub_3821 = (((int)1) - sah_3819);
			t_sample history_3644_next_3820 = fixdenorm(rsub_3821);
			t_sample add_3640 = (gen_3647 + ((int)1));
			t_sample choice_27 = int(add_3640);
			t_sample gate_3641 = (((choice_27 >= 1) && (choice_27 < 2)) ? ((int)1) : 0);
			t_sample gate_3642 = ((choice_27 >= 2) ? ((int)1) : 0);
			t_sample out4 = gate_3642;
			t_sample out3 = gate_3641;
			t_sample pass_3676 = in1;
			t_sample mix_3915 = (m_history_15 + (((t_sample)0.003926980723806) * (add_3606 - m_history_15)));
			t_sample mix_3614 = mix_3915;
			t_sample mix_3916 = (m_history_14 + (((t_sample)0.003926980723806) * (mix_3614 - m_history_14)));
			t_sample mix_3612 = mix_3916;
			t_sample mix_3917 = (m_history_13 + (((t_sample)0.003926980723806) * (mix_3612 - m_history_13)));
			t_sample mix_3610 = mix_3917;
			t_sample gen_3672 = mix_3610;
			t_sample history_3615_next_3617 = fixdenorm(mix_3614);
			t_sample history_3613_next_3618 = fixdenorm(mix_3612);
			t_sample history_3611_next_3619 = fixdenorm(mix_3610);
			t_sample mix_3918 = (m_history_12 + (((t_sample)0.003926980723806) * (m_knob3_time_21 - m_history_12)));
			t_sample mix_3825 = mix_3918;
			t_sample mix_3919 = (m_history_11 + (((t_sample)0.003926980723806) * (mix_3825 - m_history_11)));
			t_sample mix_3829 = mix_3919;
			t_sample mix_3920 = (m_history_10 + (((t_sample)0.003926980723806) * (mix_3829 - m_history_10)));
			t_sample mix_3828 = mix_3920;
			t_sample gen_3664 = mix_3828;
			t_sample history_3615_next_3826 = fixdenorm(mix_3825);
			t_sample history_3613_next_3831 = fixdenorm(mix_3829);
			t_sample history_3611_next_3827 = fixdenorm(mix_3828);
			t_sample mix_3921 = (m_history_9 + (((t_sample)0.003926980723806) * (((int)0) - m_history_9)));
			t_sample mix_3838 = mix_3921;
			t_sample mix_3922 = (m_history_8 + (((t_sample)0.003926980723806) * (mix_3838 - m_history_8)));
			t_sample mix_3843 = mix_3922;
			t_sample mix_3923 = (m_history_7 + (((t_sample)0.003926980723806) * (mix_3843 - m_history_7)));
			t_sample mix_3841 = mix_3923;
			t_sample gen_3653 = mix_3841;
			t_sample history_3615_next_3839 = fixdenorm(mix_3838);
			t_sample history_3613_next_3844 = fixdenorm(mix_3843);
			t_sample history_3611_next_3840 = fixdenorm(mix_3841);
			t_sample mtof_3654 = mtof(gen_3653, ((int)440));
			t_sample mul_3656 = (mtof_3654 * safediv((-6.2831853071796), samplerate));
			t_sample exp_3657 = exp(mul_3656);
			t_sample clamp_3658 = ((exp_3657 <= ((int)0)) ? ((int)0) : ((exp_3657 >= ((int)1)) ? ((int)1) : exp_3657));
			t_sample abs_3635 = fabs(in1);
			__m_slide_28 = fixdenorm((__m_slide_28 + (((abs_3635 > __m_slide_28) ? iup_29 : idown_30) * (abs_3635 - __m_slide_28))));
			t_sample slide_3634 = __m_slide_28;
			t_sample mul_3627 = (slide_3634 * ((int)4));
			t_sample clamp_3625 = ((mul_3627 <= ((int)0)) ? ((int)0) : ((mul_3627 >= ((int)1)) ? ((int)1) : mul_3627));
			t_sample sqrt_3626 = sqrt(clamp_3625);
			t_sample mul_3629 = (sqrt_3626 * ((t_sample)0.75));
			t_sample add_3628 = (mul_3629 + m_knob_22);
			t_sample mul_3621 = (add_3628 * ((int)1));
			t_sample mix_3924 = (m_history_6 + (((t_sample)0.003926980723806) * (mul_3621 - m_history_6)));
			t_sample mix_3856 = mix_3924;
			t_sample mix_3925 = (m_history_5 + (((t_sample)0.003926980723806) * (mix_3856 - m_history_5)));
			t_sample mix_3858 = mix_3925;
			t_sample mix_3926 = (m_history_4 + (((t_sample)0.003926980723806) * (mix_3858 - m_history_4)));
			t_sample mix_3850 = mix_3926;
			t_sample gen_3620 = mix_3850;
			t_sample history_3615_next_3854 = fixdenorm(mix_3856);
			t_sample history_3613_next_3851 = fixdenorm(mix_3858);
			t_sample history_3611_next_3855 = fixdenorm(mix_3850);
			t_sample clamp_3609 = ((gen_3620 <= ((int)0)) ? ((int)0) : ((gen_3620 >= ((int)1)) ? ((int)1) : gen_3620));
			t_sample out6 = clamp_3609;
			t_sample add_3622 = (gen_3664 + clamp_3609);
			t_sample sub_3930 = (add_3622 - ((int)0));
			t_sample scale_3927 = ((safepow((sub_3930 * ((t_sample)1)), ((int)1)) * ((int)72000)) + ((int)24000));
			t_sample scale_3650 = scale_3927;
			t_sample sub_3934 = (add_3622 - ((int)0));
			t_sample scale_3931 = ((safepow((sub_3934 * ((t_sample)1)), ((int)1)) * ((int)24000)) + ((int)0));
			t_sample scale_3651 = scale_3931;
			t_sample switch_3652 = (((int)0) ? scale_3650 : scale_3651);
			t_sample tap_3675 = m_delay_3.read_cubic(switch_3652);
			t_sample mul_3673 = (tap_3675 * gen_3672);
			t_sample mix_3935 = (m_y_1 + (clamp_3658 * (mul_3673 - m_y_1)));
			t_sample mix_3649 = mix_3935;
			t_sample mul_3671 = (tap_3675 * m_knob1_level_18);
			t_sample gate_3661 = (((choice_31 >= 1) && (choice_31 < 2)) ? mul_3671 : 0);
			t_sample gate_3662 = ((choice_31 >= 2) ? mul_3671 : 0);
			t_sample tap_3669 = m_delay_2.read_cubic(switch_3652);
			t_sample mul_3667 = (tap_3669 * gen_3672);
			t_sample add_3937 = (mul_3667 + pass_3676);
			t_sample mix_3936 = (m_y_1 + (clamp_3658 * (add_3937 - m_y_1)));
			t_sample mix_3655 = mix_3936;
			t_sample mul_3666 = (tap_3669 * m_knob1_level_18);
			t_sample gate_3659 = (((choice_32 >= 1) && (choice_32 < 2)) ? mul_3666 : 0);
			t_sample gate_3660 = ((choice_32 >= 2) ? mul_3666 : 0);
			t_sample add_3670 = (pass_3676 + ((gate_3659 + gate_3661) + gate_3662));
			t_sample out1 = add_3670;
			t_sample add_3665 = (pass_3676 + ((gate_3659 + gate_3660) + gate_3661));
			t_sample out2 = add_3665;
			t_sample y0_next_3865 = fixdenorm(mix_3649);
			t_sample y0_next_3866 = fixdenorm(mix_3655);
			m_history_17 = history_3644_next_3646;
			m_history_16 = history_3644_next_3820;
			m_history_15 = history_3615_next_3617;
			m_history_13 = history_3611_next_3619;
			m_history_14 = history_3613_next_3618;
			m_history_12 = history_3615_next_3826;
			m_history_10 = history_3611_next_3827;
			m_history_11 = history_3613_next_3831;
			m_history_9 = history_3615_next_3839;
			m_history_7 = history_3611_next_3840;
			m_history_8 = history_3613_next_3844;
			m_history_6 = history_3615_next_3854;
			m_history_4 = history_3611_next_3855;
			m_history_5 = history_3613_next_3851;
			m_delay_3.write(mix_3655);
			m_delay_2.write(mix_3649);
			m_y_1 = y0_next_3865;
			m_y_1 = y0_next_3866;
			m_delay_2.step();
			m_delay_3.step();
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			(*(__out6++)) = out6;
			(*(__out7++)) = out7;
			
		};
		return __exception;
		
	};
	inline void set_knob1_level(t_param _value) {
		m_knob1_level_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_slew(t_param _value) {
		m_knob3_slew_19 = (_value < 1 ? 1 : (_value > 30 ? 30 : _value));
	};
	inline void set_knob2_fb(t_param _value) {
		m_knob2_fb_20 = (_value < 0 ? 0 : (_value > 0.99 ? 0.99 : _value));
	};
	inline void set_knob3_time(t_param _value) {
		m_knob3_time_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4(t_param _value) {
		m_knob_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_mult(t_param _value) {
		m_mult_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 7;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 7; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2", "led1", "led2", "relay", "out6", "out7" };

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
		case 2: self->set_knob3_slew(value); break;
		case 3: self->set_knob3_time(value); break;
		case 4: self->set_knob4(value); break;
		case 5: self->set_mult(value); break;
		case 6: self->set_sw1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob1_level_18; break;
		case 1: *value = self->m_knob2_fb_20; break;
		case 2: *value = self->m_knob3_slew_19; break;
		case 3: *value = self->m_knob3_time_21; break;
		case 4: *value = self->m_knob_22; break;
		case 5: *value = self->m_mult_24; break;
		case 6: *value = self->m_sw_23; break;
		
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
	// initialize parameter 1 ("m_knob2_fb_20")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2_fb";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob2_fb_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 0.99;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob3_slew_19")
	pi = self->__commonstate.params + 2;
	pi->name = "knob3_slew";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_slew_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 30;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob3_time_21")
	pi = self->__commonstate.params + 3;
	pi->name = "knob3_time";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_time_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_knob_22")
	pi = self->__commonstate.params + 4;
	pi->name = "knob4";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_mult_24")
	pi = self->__commonstate.params + 5;
	pi->name = "mult";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_mult_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_sw_23")
	pi = self->__commonstate.params + 6;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_23;
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


} // DigitalDelay::
