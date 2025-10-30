#include "Chorus2.h"

namespace Chorus2 {

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
	Sah __m_sah_23;
	Sah __m_sah_26;
	Sah __m_sah_24;
	SineCycle __m_cycle_28;
	SineCycle __m_cycle_29;
	SineCycle __m_cycle_30;
	SineCycle __m_cycle_32;
	SineCycle __m_cycle_31;
	SineCycle __m_cycle_33;
	SineCycle __m_cycle_34;
	SineCycle __m_cycle_35;
	SineData __sinedata;
	t_sample m_history_6;
	t_sample m_history_12;
	t_sample m_history_7;
	t_sample m_history_8;
	t_sample m_history_5;
	t_sample m_history_3;
	t_sample m_history_4;
	t_sample samplerate;
	t_sample m_history_2;
	t_sample m_history_11;
	t_sample m_history_9;
	t_sample m_knob2_rate_21;
	t_sample m_history_15;
	t_sample m_history_14;
	t_sample m_history_13;
	t_sample m_knob1_depth_22;
	t_sample m_history_10;
	t_sample m_sw_18;
	t_sample m_sw_17;
	t_sample m_knob3_breadth_20;
	t_sample m_knob4_taps_19;
	t_sample m_history_16;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_delay_1.reset("m_delay_1", ((int)20000));
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
		m_history_14 = ((int)0);
		m_history_15 = ((int)0);
		m_history_16 = ((int)0);
		m_sw_17 = ((int)0);
		m_sw_18 = ((int)0);
		m_knob4_taps_19 = ((int)0);
		m_knob3_breadth_20 = 256;
		m_knob2_rate_21 = ((int)0);
		m_knob1_depth_22 = ((int)0);
		__m_sah_23.reset(0);
		__m_sah_24.reset(0);
		__m_sah_26.reset(0);
		__m_cycle_28.reset(samplerate, 0);
		__m_cycle_29.reset(samplerate, 0);
		__m_cycle_30.reset(samplerate, 0);
		__m_cycle_31.reset(samplerate, 0);
		__m_cycle_32.reset(samplerate, 0);
		__m_cycle_33.reset(samplerate, 0);
		__m_cycle_34.reset(samplerate, 0);
		__m_cycle_35.reset(samplerate, 0);
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
		t_sample expr_5324 = (((int)1) - sqrt(sqrt((((int)1) - m_knob2_rate_21))));
		t_sample expr_5325 = (((int)1) - sqrt(sqrt((((int)1) - m_knob1_depth_22))));
		t_sample div_4662 = (m_sw_18 * ((t_sample)0.5));
		t_sample add_4661 = (div_4662 + ((t_sample)0.5));
		t_sample mul_4670 = (expr_5325 * ((int)1000));
		t_sample add_4669 = (mul_4670 + ((int)2));
		t_sample mul_4667 = (expr_5324 * ((int)5));
		t_sample add_4668 = (mul_4667 + ((t_sample)0.01));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_4763 = __m_sah_23(m_history_16, m_sw_17, ((int)0));
			t_sample gen_4843 = sah_4763;
			t_sample rsub_4761 = (((int)1) - sah_4763);
			t_sample history_4762_next_4764 = fixdenorm(rsub_4761);
			t_sample out5 = gen_4843;
			t_sample sah_5326 = __m_sah_24(m_history_15, m_sw_17, ((int)0));
			t_sample gen_4842 = sah_5326;
			t_sample rsub_5328 = (((int)1) - sah_5326);
			t_sample history_4762_next_5327 = fixdenorm(rsub_5328);
			t_sample add_4839 = (gen_4842 + ((int)1));
			t_sample choice_25 = int(add_4839);
			t_sample gate_4840 = (((choice_25 >= 1) && (choice_25 < 2)) ? ((int)1) : 0);
			t_sample gate_4841 = ((choice_25 >= 2) ? ((int)1) : 0);
			t_sample out4 = gate_4841;
			t_sample out3 = gate_4840;
			t_sample sah_5331 = __m_sah_26(m_history_14, m_sw_17, ((int)0));
			t_sample gen_4765 = sah_5331;
			t_sample rsub_5333 = (((int)1) - sah_5331);
			t_sample history_4762_next_5332 = fixdenorm(rsub_5333);
			t_sample add_4766 = (gen_4765 + ((int)1));
			t_sample choice_27 = int(add_4766);
			t_sample gate_4758 = (((choice_27 >= 1) && (choice_27 < 2)) ? in1 : 0);
			t_sample gate_4759 = ((choice_27 >= 2) ? in1 : 0);
			t_sample switch_4704 = (m_sw_18 ? ((int)0) : gate_4759);
			t_sample mix_5656 = (m_history_13 + (((t_sample)0.0042742627044161) * (m_knob4_taps_19 - m_history_13)));
			t_sample mix_4676 = mix_5656;
			t_sample mix_5657 = (m_history_12 + (((t_sample)0.0042742627044161) * (mix_4676 - m_history_12)));
			t_sample mix_4674 = mix_5657;
			t_sample mix_5658 = (m_history_11 + (((t_sample)0.0042742627044161) * (mix_4674 - m_history_11)));
			t_sample mix_4672 = mix_5658;
			t_sample gen_4702 = mix_4672;
			t_sample history_4677_next_4679 = fixdenorm(mix_4676);
			t_sample history_4675_next_4680 = fixdenorm(mix_4674);
			t_sample history_4673_next_4681 = fixdenorm(mix_4672);
			t_sample sub_5662 = (gen_4702 - ((int)0));
			t_sample scale_5659 = ((safepow((sub_5662 * ((t_sample)1)), ((int)1)) * ((t_sample)-0.5)) + ((int)1));
			t_sample sub_5666 = (gen_4702 - ((int)0));
			t_sample scale_5663 = ((safepow((sub_5666 * ((t_sample)1)), ((int)1)) * ((int)4)) + (-2));
			t_sample clamp_4688 = ((scale_5663 <= ((int)0)) ? ((int)0) : ((scale_5663 >= ((int)1)) ? ((int)1) : scale_5663));
			t_sample sub_5670 = (gen_4702 - ((int)0));
			t_sample scale_5667 = ((safepow((sub_5670 * ((t_sample)1)), ((int)1)) * ((int)4)) + (-3));
			t_sample clamp_4686 = ((scale_5667 <= ((int)0)) ? ((int)0) : ((scale_5667 >= ((int)1)) ? ((int)1) : scale_5667));
			t_sample sub_5674 = (gen_4702 - ((int)0));
			t_sample scale_5671 = ((safepow((sub_5674 * ((t_sample)1)), ((int)1)) * ((int)4)) + (-1));
			t_sample clamp_4690 = ((scale_5671 <= ((int)0)) ? ((int)0) : ((scale_5671 >= ((int)1)) ? ((int)1) : scale_5671));
			t_sample mix_5675 = (m_history_10 + (((t_sample)0.0042742627044161) * (m_knob3_breadth_20 - m_history_10)));
			t_sample mix_5343 = mix_5675;
			t_sample mix_5676 = (m_history_9 + (((t_sample)0.0042742627044161) * (mix_5343 - m_history_9)));
			t_sample mix_5336 = mix_5676;
			t_sample mix_5677 = (m_history_8 + (((t_sample)0.0042742627044161) * (mix_5336 - m_history_8)));
			t_sample mix_5345 = mix_5677;
			t_sample gen_4682 = mix_5345;
			t_sample history_4677_next_5341 = fixdenorm(mix_5343);
			t_sample history_4675_next_5339 = fixdenorm(mix_5336);
			t_sample history_4673_next_5338 = fixdenorm(mix_5345);
			t_sample mul_4671 = (gen_4682 * ((int)1));
			t_sample mul_4685 = (gen_4682 * ((int)2));
			t_sample mul_4684 = (gen_4682 * ((int)3));
			t_sample mul_4683 = (gen_4682 * ((int)4));
			t_sample mix_5678 = (m_history_7 + (((t_sample)0.0042742627044161) * (add_4669 - m_history_7)));
			t_sample mix_5358 = mix_5678;
			t_sample mix_5679 = (m_history_6 + (((t_sample)0.0042742627044161) * (mix_5358 - m_history_6)));
			t_sample mix_5349 = mix_5679;
			t_sample mix_5680 = (m_history_5 + (((t_sample)0.0042742627044161) * (mix_5349 - m_history_5)));
			t_sample mix_5353 = mix_5680;
			t_sample gen_4768 = mix_5353;
			t_sample history_4677_next_5356 = fixdenorm(mix_5358);
			t_sample history_4675_next_5357 = fixdenorm(mix_5349);
			t_sample history_4673_next_5351 = fixdenorm(mix_5353);
			t_sample mix_5681 = (m_history_4 + (((t_sample)0.0042742627044161) * (add_4668 - m_history_4)));
			t_sample mix_5371 = mix_5681;
			t_sample mix_5682 = (m_history_3 + (((t_sample)0.0042742627044161) * (mix_5371 - m_history_3)));
			t_sample mix_5362 = mix_5682;
			t_sample mix_5683 = (m_history_2 + (((t_sample)0.0042742627044161) * (mix_5362 - m_history_2)));
			t_sample mix_5367 = mix_5683;
			t_sample gen_4705 = mix_5367;
			t_sample history_4677_next_5369 = fixdenorm(mix_5371);
			t_sample history_4675_next_5370 = fixdenorm(mix_5362);
			t_sample history_4673_next_5364 = fixdenorm(mix_5367);
			t_sample mul_4709 = (gen_4705 * ((int)1));
			__m_cycle_28.freq(mul_4709);
			t_sample cycle_4747 = __m_cycle_28(__sinedata);
			t_sample cycleindex_4748 = __m_cycle_28.phase();
			t_sample mul_4745 = (cycle_4747 * gen_4768);
			t_sample add_4746 = (mul_4745 + mul_4671);
			t_sample mul_4740 = (gen_4705 * ((t_sample)1.51));
			__m_cycle_29.freq(mul_4740);
			t_sample cycle_4743 = __m_cycle_29(__sinedata);
			t_sample cycleindex_4744 = __m_cycle_29.phase();
			t_sample mul_4741 = (cycle_4743 * gen_4768);
			t_sample add_4742 = (mul_4741 + mul_4671);
			t_sample mul_4708 = (gen_4705 * ((t_sample)0.48));
			__m_cycle_30.freq(mul_4708);
			t_sample cycle_4737 = __m_cycle_30(__sinedata);
			t_sample cycleindex_4738 = __m_cycle_30.phase();
			t_sample mul_4735 = (cycle_4737 * gen_4768);
			t_sample add_4736 = (mul_4735 + mul_4685);
			t_sample mul_4730 = (gen_4705 * ((t_sample)0.73));
			__m_cycle_31.freq(mul_4730);
			t_sample cycle_4733 = __m_cycle_31(__sinedata);
			t_sample cycleindex_4734 = __m_cycle_31.phase();
			t_sample mul_4731 = (cycle_4733 * gen_4768);
			t_sample add_4732 = (mul_4731 + mul_4685);
			t_sample mul_4707 = (gen_4705 * ((t_sample)1.245));
			__m_cycle_32.freq(mul_4707);
			t_sample cycle_4726 = __m_cycle_32(__sinedata);
			t_sample cycleindex_4727 = __m_cycle_32.phase();
			t_sample mul_4724 = (cycle_4726 * gen_4768);
			t_sample add_4725 = (mul_4724 + mul_4684);
			t_sample mul_4719 = (gen_4705 * ((t_sample)0.81));
			__m_cycle_33.freq(mul_4719);
			t_sample cycle_4722 = __m_cycle_33(__sinedata);
			t_sample cycleindex_4723 = __m_cycle_33.phase();
			t_sample mul_4720 = (cycle_4722 * gen_4768);
			t_sample add_4721 = (mul_4720 + mul_4684);
			t_sample mul_4706 = (gen_4705 * ((t_sample)1.93));
			__m_cycle_34.freq(mul_4706);
			t_sample cycle_4717 = __m_cycle_34(__sinedata);
			t_sample cycleindex_4718 = __m_cycle_34.phase();
			t_sample mul_4715 = (cycle_4717 * gen_4768);
			t_sample add_4716 = (mul_4715 + mul_4683);
			t_sample mul_4710 = (gen_4705 * ((t_sample)2.11));
			__m_cycle_35.freq(mul_4710);
			t_sample cycle_4713 = __m_cycle_35(__sinedata);
			t_sample cycleindex_4714 = __m_cycle_35.phase();
			t_sample mul_4711 = (cycle_4713 * gen_4768);
			t_sample add_4712 = (mul_4711 + mul_4683);
			t_sample tap_4750 = m_delay_1.read_linear(add_4746);
			t_sample tap_4751 = m_delay_1.read_linear(add_4742);
			t_sample tap_4752 = m_delay_1.read_linear(add_4736);
			t_sample tap_4753 = m_delay_1.read_linear(add_4732);
			t_sample tap_4754 = m_delay_1.read_linear(add_4725);
			t_sample tap_4755 = m_delay_1.read_linear(add_4721);
			t_sample tap_4756 = m_delay_1.read_linear(add_4716);
			t_sample tap_4757 = m_delay_1.read_linear(add_4712);
			t_sample mul_4700 = (tap_4755 * clamp_4688);
			t_sample mul_4699 = (tap_4756 * clamp_4686);
			t_sample mul_4695 = (tap_4752 * clamp_4690);
			t_sample mul_4696 = (tap_4751 * ((int)1));
			t_sample mul_4728 = ((((mul_4696 + mul_4695) + mul_4699) + mul_4700) * scale_5659);
			t_sample add_4739 = (switch_4704 + mul_4728);
			t_sample mul_4663 = (add_4661 * add_4739);
			t_sample add_4659 = (gate_4758 + mul_4663);
			t_sample out2 = add_4659;
			t_sample mul_4701 = (tap_4754 * clamp_4688);
			t_sample mul_4698 = (tap_4757 * clamp_4686);
			t_sample mul_4694 = (tap_4753 * clamp_4690);
			t_sample mul_4697 = (tap_4750 * ((int)1));
			t_sample mul_4729 = ((((mul_4697 + mul_4694) + mul_4698) + mul_4701) * scale_5659);
			t_sample add_4767 = (switch_4704 + mul_4729);
			t_sample mul_4664 = (add_4661 * add_4767);
			t_sample add_4660 = (gate_4758 + mul_4664);
			t_sample out1 = add_4660;
			m_history_16 = history_4762_next_4764;
			m_history_15 = history_4762_next_5327;
			m_history_14 = history_4762_next_5332;
			m_history_13 = history_4677_next_4679;
			m_history_11 = history_4673_next_4681;
			m_history_12 = history_4675_next_4680;
			m_history_10 = history_4677_next_5341;
			m_history_8 = history_4673_next_5338;
			m_history_9 = history_4675_next_5339;
			m_history_7 = history_4677_next_5356;
			m_history_5 = history_4673_next_5351;
			m_history_6 = history_4675_next_5357;
			m_history_4 = history_4677_next_5369;
			m_history_2 = history_4673_next_5364;
			m_history_3 = history_4675_next_5370;
			m_delay_1.write(gate_4759);
			m_delay_1.step();
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
		m_sw_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw5(t_param _value) {
		m_sw_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4_taps(t_param _value) {
		m_knob4_taps_19 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3_breadth(t_param _value) {
		m_knob3_breadth_20 = (_value < 240 ? 240 : (_value > 2400 ? 2400 : _value));
	};
	inline void set_knob2_rate(t_param _value) {
		m_knob2_rate_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob1_depth(t_param _value) {
		m_knob1_depth_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
		case 0: self->set_knob1_depth(value); break;
		case 1: self->set_knob2_rate(value); break;
		case 2: self->set_knob3_breadth(value); break;
		case 3: self->set_knob4_taps(value); break;
		case 4: self->set_sw1(value); break;
		case 5: self->set_sw5(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob1_depth_22; break;
		case 1: *value = self->m_knob2_rate_21; break;
		case 2: *value = self->m_knob3_breadth_20; break;
		case 3: *value = self->m_knob4_taps_19; break;
		case 4: *value = self->m_sw_17; break;
		case 5: *value = self->m_sw_18; break;
		
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
	// initialize parameter 0 ("m_knob1_depth_22")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1_depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_depth_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob2_rate_21")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob2_rate_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob3_breadth_20")
	pi = self->__commonstate.params + 2;
	pi->name = "knob3_breadth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_breadth_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 240;
	pi->outputmax = 2400;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob4_taps_19")
	pi = self->__commonstate.params + 3;
	pi->name = "knob4_taps";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_taps_19;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_sw_17")
	pi = self->__commonstate.params + 4;
	pi->name = "sw1";
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
	// initialize parameter 5 ("m_sw_18")
	pi = self->__commonstate.params + 5;
	pi->name = "sw5";
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
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // Chorus2::
