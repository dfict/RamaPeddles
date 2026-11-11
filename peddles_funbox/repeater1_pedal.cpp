#include "repeater1_pedal.h"

namespace repeater1_pedal {

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
	Change __m_change_38;
	DCBlock __m_dcblock_33;
	Data m_segment_data_19;
	Data m_offset_data_17;
	Data m_length_data_18;
	Data m_rms_data_16;
	Sah __m_sah_32;
	Sah __m_sah_30;
	int __exception;
	int vectorsize;
	t_sample m_sw_24;
	t_sample m_play_index_7;
	t_sample m_knob_25;
	t_sample m_knob_23;
	t_sample m_knob_22;
	t_sample m_knob_21;
	t_sample m_sw_26;
	t_sample m_knob_28;
	t_sample m_knob_27;
	t_sample samplerate;
	t_sample m_history_29;
	t_sample m_play_len_6;
	t_sample m_history_20;
	t_sample m_energy_sum_2;
	t_sample m_write_index_10;
	t_sample m_write_segment_11;
	t_sample m_crossing_count_9;
	t_sample m_play_segment_8;
	t_sample m_total_length_1;
	t_sample m_freq_12;
	t_sample m_playmode_14;
	t_sample m_prev_input_3;
	t_sample m_pitchedmode_13;
	t_sample m_play_rms_4;
	t_sample m_play_offset_5;
	t_sample m_capture_15;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_total_length_1 = ((int)0);
		m_energy_sum_2 = ((int)0);
		m_prev_input_3 = ((int)0);
		m_play_rms_4 = ((t_sample)0.1);
		m_play_offset_5 = ((int)0);
		m_play_len_6 = ((int)0);
		m_play_index_7 = ((int)0);
		m_play_segment_8 = ((int)0);
		m_crossing_count_9 = ((int)0);
		m_write_index_10 = ((int)0);
		m_write_segment_11 = ((int)1);
		m_freq_12 = ((int)220);
		m_pitchedmode_13 = ((int)0);
		m_playmode_14 = ((int)0);
		m_capture_15 = ((int)1);
		m_rms_data_16.reset("rms_data", ((int)64), ((int)1));
		m_offset_data_17.reset("offset_data", ((int)64), ((int)1));
		m_length_data_18.reset("length_data", ((int)64), ((int)1));
		m_segment_data_19.reset("segment_data", ((int)10004), ((int)64));
		m_history_20 = ((int)0);
		m_knob_21 = ((int)0);
		m_knob_22 = ((int)0);
		m_knob_23 = ((int)0);
		m_sw_24 = ((int)0);
		m_knob_25 = ((int)0);
		m_sw_26 = ((int)0);
		m_knob_27 = ((int)0);
		m_knob_28 = ((int)0);
		m_history_29 = ((int)0);
		__m_sah_30.reset(0);
		__m_sah_32.reset(0);
		__m_dcblock_33.reset();
		__m_change_38.reset(0);
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
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample sub_632 = (m_knob_25 - ((int)0));
		t_sample scale_629 = ((safepow((sub_632 * ((t_sample)1)), ((int)1)) * ((int)15)) + ((int)1));
		t_sample scale_443 = scale_629;
		t_sample sub_636 = (m_knob_22 - ((int)0));
		t_sample scale_633 = ((safepow((sub_636 * ((t_sample)1)), ((int)1)) * ((int)19)) + ((int)1));
		t_sample sub_640 = (m_knob_23 - ((int)0));
		t_sample scale_637 = ((safepow((sub_640 * ((t_sample)1)), ((int)3)) * ((int)9984)) + ((int)16));
		t_sample max_514 = ((m_knob_21 < m_knob_23) ? m_knob_23 : m_knob_21);
		t_sample sub_644 = (max_514 - ((int)0));
		t_sample scale_641 = ((safepow((sub_644 * ((t_sample)1)), ((int)3)) * ((int)9984)) + ((int)16));
		t_sample add_470 = (m_sw_26 + ((int)1));
		t_sample choice_31 = int(add_470);
		t_sample gate_471 = (((choice_31 >= 1) && (choice_31 < 2)) ? ((int)1) : 0);
		t_sample gate_472 = ((choice_31 >= 2) ? ((int)1) : 0);
		t_sample sub_648 = (m_knob_28 - ((int)0));
		t_sample scale_645 = ((safepow((sub_648 * ((t_sample)1)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample sub_652 = (m_knob_27 - ((int)0));
		t_sample scale_649 = ((safepow((sub_652 * ((t_sample)1)), ((int)1)) * ((int)2)) + (-1));
		t_sample scale_477 = scale_649;
		int sign_462 = ((scale_477 > 0) ? 1 : ((scale_477 < 0) ? -1 : 0));
		t_sample abs_466 = fabs(scale_477);
		t_sample sub_465 = (abs_466 - ((t_sample)0.2));
		t_sample max_464 = ((sub_465 < ((int)0)) ? ((int)0) : sub_465);
		t_sample div_463 = (max_464 * ((t_sample)1.25));
		t_sample mul_461 = (div_463 * sign_462);
		t_sample gen_467 = mul_461;
		t_sample pow_479 = safepow(((int)16), gen_467);
		t_sample mul_480 = (((int)1) * pow_479);
		int segment_data_dim = m_segment_data_19.dim;
		int segment_data_channels = m_segment_data_19.channels;
		int num_segments = segment_data_channels;
		t_sample crossKnob = scale_443;
		t_sample rateKnob = mul_480;
		t_sample hold = m_sw_26;
		t_sample max_length = scale_641;
		t_sample rate = rateKnob;
		t_sample crossings = crossKnob;
		t_sample repeats = scale_633;
		t_sample clamp_458 = ((scale_645 <= ((int)0)) ? ((int)0) : ((scale_645 >= ((int)1)) ? ((int)1) : scale_645));
		t_sample sqrt_456 = sqrt(clamp_458);
		t_sample rsub_457 = (((int)1) - clamp_458);
		t_sample sqrt_455 = sqrt(rsub_457);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_447 = __m_sah_30(m_history_29, m_sw_24, ((int)0));
			t_sample gen_474 = sah_447;
			t_sample rsub_445 = (((int)1) - sah_447);
			t_sample history_446_next_448 = fixdenorm(rsub_445);
			t_sample out3 = gen_474;
			t_sample out4 = gate_471;
			t_sample sah_579 = __m_sah_32(m_history_20, m_sw_24, ((int)0));
			t_sample gen_449 = sah_579;
			t_sample rsub_578 = (((int)1) - sah_579);
			t_sample history_446_next_577 = fixdenorm(rsub_578);
			int not_444 = (!gen_449);
			t_sample unbiased_input = __m_dcblock_33(in1);
			m_energy_sum_2 = (m_energy_sum_2 + (unbiased_input * unbiased_input));
			m_write_index_10 = (m_write_index_10 + ((int)1));
			int channel_trunc_34 = fixnan(floor(m_write_segment_11));
			bool chan_ignore_35 = ((channel_trunc_34 < 0) || (channel_trunc_34 >= segment_data_channels));
			int index_trunc_36 = fixnan(floor(m_write_index_10));
			bool index_ignore_37 = ((index_trunc_36 >= segment_data_dim) || (index_trunc_36 < 0));
			if ((!(chan_ignore_35 || index_ignore_37))) {
				m_segment_data_19.write(unbiased_input, index_trunc_36, channel_trunc_34);
				
			};
			int is_crossing = (__m_change_38((unbiased_input > ((int)0))) > ((int)0));
			if (is_crossing) {
				if ((m_write_index_10 > max_length)) {
					m_crossing_count_9 = ((int)0);
					m_write_index_10 = ((int)0);
					
				} else {
					m_crossing_count_9 = (m_crossing_count_9 + ((int)1));
					int is_complete = ((m_capture_15 && (m_crossing_count_9 >= crossings)) && (m_write_index_10 >= scale_637));
					if (is_complete) {
						t_sample offset = safediv(m_prev_input_3, (m_prev_input_3 - unbiased_input));
						int offset_data_dim = m_offset_data_17.dim;
						int offset_data_channels = m_offset_data_17.channels;
						int index_trunc_39 = fixnan(floor(m_write_segment_11));
						bool index_ignore_40 = ((index_trunc_39 >= offset_data_dim) || (index_trunc_39 < 0));
						// samples offset_data channel 1;
						t_sample prev_offset = (index_ignore_40 ? 0 : m_offset_data_17.read(index_trunc_39, 0));
						t_sample len = (((m_write_index_10 + offset) - prev_offset) - ((int)1));
						int length_data_dim = m_length_data_18.dim;
						int length_data_channels = m_length_data_18.channels;
						int index_trunc_41 = fixnan(floor(m_write_segment_11));
						bool index_ignore_42 = ((index_trunc_41 >= length_data_dim) || (index_trunc_41 < 0));
						// samples length_data channel 1;
						t_sample prev_length = (index_ignore_42 ? 0 : m_length_data_18.read(index_trunc_41, 0));
						m_total_length_1 = ((m_total_length_1 - prev_length) + len);
						int index_trunc_43 = fixnan(floor(m_write_segment_11));
						bool index_ignore_44 = ((index_trunc_43 >= length_data_dim) || (index_trunc_43 < 0));
						if ((!index_ignore_44)) {
							m_length_data_18.write(len, index_trunc_43, 0);
							
						};
						t_sample rms = sqrt(safediv(m_energy_sum_2, floor(len)));
						int rms_data_dim = m_rms_data_16.dim;
						int rms_data_channels = m_rms_data_16.channels;
						int index_trunc_45 = fixnan(floor(m_write_segment_11));
						bool index_ignore_46 = ((index_trunc_45 >= rms_data_dim) || (index_trunc_45 < 0));
						if ((!index_ignore_46)) {
							m_rms_data_16.write(rms, index_trunc_45, 0);
							
						};
						m_crossing_count_9 = ((int)0);
						m_energy_sum_2 = ((int)0);
						m_write_segment_11 = wrap((m_write_segment_11 + ((int)1)), ((int)0), num_segments);
						if ((m_write_segment_11 == m_play_segment_8)) {
							m_write_segment_11 = wrap((m_write_segment_11 + ((int)1)), ((int)0), num_segments);
							
						};
						int index_trunc_47 = fixnan(floor(m_write_segment_11));
						bool index_ignore_48 = ((index_trunc_47 >= offset_data_dim) || (index_trunc_47 < 0));
						if ((!index_ignore_48)) {
							m_offset_data_17.write(offset, index_trunc_47, 0);
							
						};
						int channel_trunc_49 = fixnan(floor(m_write_segment_11));
						bool chan_ignore_50 = ((channel_trunc_49 < 0) || (channel_trunc_49 >= segment_data_channels));
						if ((!chan_ignore_50)) {
							m_segment_data_19.write(m_prev_input_3, 0, channel_trunc_49);
							
						};
						int channel_trunc_51 = fixnan(floor(m_write_segment_11));
						bool chan_ignore_52 = ((channel_trunc_51 < 0) || (channel_trunc_51 >= segment_data_channels));
						bool index_ignore_53 = (((int)1) >= segment_data_dim);
						if ((!(chan_ignore_52 || index_ignore_53))) {
							m_segment_data_19.write(unbiased_input, ((int)1), channel_trunc_51);
							
						};
						m_write_index_10 = ((int)1);
						
					};
					
				};
				
			};
			m_prev_input_3 = unbiased_input;
			t_sample r = rate;
			if ((m_pitchedmode_13 < ((int)1))) {
				
			} else {
				if ((m_pitchedmode_13 < ((int)2))) {
					t_sample d = safediv(m_play_index_7, m_play_len_6);
					r = (rate * ((((int)1) < d) ? d : ((int)1)));
					
				} else {
					if ((m_pitchedmode_13 < ((int)3))) {
						t_sample d = ceil(safediv(m_play_index_7, m_play_len_6));
						t_sample maxb_54 = (d * d);
						r = safediv(rate, ((((int)1) < maxb_54) ? maxb_54 : ((int)1)));
						
					} else {
						r = safediv((m_freq_12 * m_play_len_6), (samplerate * crossings));
						
					};
					
				};
				
			};
			m_play_index_7 = (m_play_index_7 + r);
			t_sample actual_play_index = wrap(m_play_index_7, ((int)0), m_play_len_6);
			int index_trunc_55 = fixnan(floor((m_play_offset_5 + actual_play_index)));
			double index_fract_56 = ((m_play_offset_5 + actual_play_index) - index_trunc_55);
			int index_trunc_57 = (index_trunc_55 + 1);
			bool index_ignore_58 = ((index_trunc_55 >= segment_data_dim) || (index_trunc_55 < 0));
			bool index_ignore_59 = ((index_trunc_57 >= segment_data_dim) || (index_trunc_57 < 0));
			// samples segment_data channel 1;
			int chan_60 = m_play_segment_8;
			bool chan_ignore_61 = ((chan_60 < 0) || (chan_60 >= segment_data_channels));
			double read_segment_data_62 = ((chan_ignore_61 || index_ignore_58) ? 0 : m_segment_data_19.read(index_trunc_55, chan_60));
			double read_segment_data_63 = ((chan_ignore_61 || index_ignore_59) ? 0 : m_segment_data_19.read(index_trunc_57, chan_60));
			double readinterp_64 = linear_interp(index_fract_56, read_segment_data_62, read_segment_data_63);
			t_sample expr_575 = readinterp_64;
			if ((m_play_index_7 >= (m_play_len_6 * floor(repeats)))) {
				m_play_index_7 = actual_play_index;
				if ((!hold)) {
					if ((m_playmode_14 < ((int)1))) {
						m_play_segment_8 = wrap((m_play_segment_8 + ((int)1)), ((int)0), num_segments);
						if ((m_write_segment_11 == m_play_segment_8)) {
							m_play_segment_8 = wrap((m_write_segment_11 + ((int)1)), ((int)0), num_segments);
							
						};
						
					} else {
						if ((m_playmode_14 < ((int)2))) {
							m_play_segment_8 = wrap((m_play_segment_8 - ((int)1)), ((int)0), num_segments);
							if ((m_write_segment_11 == m_play_segment_8)) {
								m_play_segment_8 = wrap((m_write_segment_11 - ((int)1)), ((int)0), num_segments);
								
							};
							
						} else {
							if ((m_playmode_14 < ((int)3))) {
								t_sample sign_65 = noise();
								t_sample direction = ((sign_65 > 0) ? 1 : ((sign_65 < 0) ? -1 : 0));
								m_play_segment_8 = wrap((m_play_segment_8 + direction), ((int)0), num_segments);
								if ((m_write_segment_11 == m_play_segment_8)) {
									m_play_segment_8 = wrap((m_write_segment_11 + direction), ((int)0), num_segments);
									
								};
								
							} else {
								if ((m_playmode_14 < ((int)4))) {
									t_sample direction = (((int)1) + ceil(((num_segments * (noise() + ((int)1))) * ((t_sample)0.5))));
									m_play_segment_8 = wrap((m_play_segment_8 + direction), ((int)0), num_segments);
									if ((m_write_segment_11 == m_play_segment_8)) {
										m_play_segment_8 = wrap((m_write_segment_11 - ((int)1)), ((int)0), num_segments);
										
									};
									
								} else {
									m_play_segment_8 = wrap((m_write_segment_11 - ((int)1)), ((int)0), num_segments);
									
								};
								
							};
							
						};
						
					};
					int length_data_dim = m_length_data_18.dim;
					int length_data_channels = m_length_data_18.channels;
					int index_trunc_66 = fixnan(floor(m_play_segment_8));
					bool index_ignore_67 = ((index_trunc_66 >= length_data_dim) || (index_trunc_66 < 0));
					// samples length_data channel 1;
					m_play_len_6 = (index_ignore_67 ? 0 : m_length_data_18.read(index_trunc_66, 0));
					int offset_data_dim = m_offset_data_17.dim;
					int offset_data_channels = m_offset_data_17.channels;
					int index_trunc_68 = fixnan(floor(m_play_segment_8));
					bool index_ignore_69 = ((index_trunc_68 >= offset_data_dim) || (index_trunc_68 < 0));
					// samples offset_data channel 1;
					m_play_offset_5 = (index_ignore_69 ? 0 : m_offset_data_17.read(index_trunc_68, 0));
					int rms_data_dim = m_rms_data_16.dim;
					int rms_data_channels = m_rms_data_16.channels;
					int index_trunc_70 = fixnan(floor(m_play_segment_8));
					bool index_ignore_71 = ((index_trunc_70 >= rms_data_dim) || (index_trunc_70 < 0));
					// samples rms_data channel 1;
					m_play_rms_4 = (index_ignore_71 ? 0 : m_rms_data_16.read(index_trunc_70, 0));
					
				};
				
			};
			t_sample mul_453 = (sqrt_456 * expr_575);
			t_sample mul_454 = (sqrt_455 * in1);
			t_sample add_459 = (mul_454 + mul_453);
			t_sample switch_450 = (not_444 ? add_459 : in1);
			t_sample add_473 = (switch_450 + ((int)0));
			t_sample out2 = add_473;
			t_sample out1 = add_473;
			m_history_29 = history_446_next_448;
			m_history_20 = history_446_next_577;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			
		};
		return __exception;
		
	};
	inline void set_freq(t_param _value) {
		m_freq_12 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_pitchedmode(t_param _value) {
		m_pitchedmode_13 = (_value < 0 ? 0 : (_value > 4 ? 4 : _value));
	};
	inline void set_playmode(t_param _value) {
		m_playmode_14 = (_value < 0 ? 0 : (_value > 4 ? 4 : _value));
	};
	inline void set_capture(t_param _value) {
		m_capture_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_rms_data(void * _value) {
		m_rms_data_16.setbuffer(_value);
	};
	inline void set_offset_data(void * _value) {
		m_offset_data_17.setbuffer(_value);
	};
	inline void set_length_data(void * _value) {
		m_length_data_18.setbuffer(_value);
	};
	inline void set_segment_data(void * _value) {
		m_segment_data_19.setbuffer(_value);
	};
	inline void set_knob6(t_param _value) {
		m_knob_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2(t_param _value) {
		m_knob_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5(t_param _value) {
		m_knob_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw7(t_param _value) {
		m_sw_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob1(t_param _value) {
		m_knob_25 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw8(t_param _value) {
		m_sw_26 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3(t_param _value) {
		m_knob_27 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4(t_param _value) {
		m_knob_28 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 4;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 16; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2", "led1", "led2" };

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
		case 0: self->set_capture(value); break;
		case 1: self->set_freq(value); break;
		case 2: self->set_knob1(value); break;
		case 3: self->set_knob2(value); break;
		case 4: self->set_knob3(value); break;
		case 5: self->set_knob4(value); break;
		case 6: self->set_knob5(value); break;
		case 7: self->set_knob6(value); break;
		case 8: self->set_length_data(ref); break;
		case 9: self->set_offset_data(ref); break;
		case 10: self->set_pitchedmode(value); break;
		case 11: self->set_playmode(value); break;
		case 12: self->set_rms_data(ref); break;
		case 13: self->set_segment_data(ref); break;
		case 14: self->set_sw7(value); break;
		case 15: self->set_sw8(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_capture_15; break;
		case 1: *value = self->m_freq_12; break;
		case 2: *value = self->m_knob_25; break;
		case 3: *value = self->m_knob_22; break;
		case 4: *value = self->m_knob_27; break;
		case 5: *value = self->m_knob_28; break;
		case 6: *value = self->m_knob_23; break;
		case 7: *value = self->m_knob_21; break;
		
		
		case 10: *value = self->m_pitchedmode_13; break;
		case 11: *value = self->m_playmode_14; break;
		
		
		case 14: *value = self->m_sw_24; break;
		case 15: *value = self->m_sw_26; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(16 * sizeof(ParamInfo));
	self->__commonstate.numparams = 16;
	// initialize parameter 0 ("m_capture_15")
	pi = self->__commonstate.params + 0;
	pi->name = "capture";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_capture_15;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_freq_12")
	pi = self->__commonstate.params + 1;
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
	// initialize parameter 2 ("m_knob_25")
	pi = self->__commonstate.params + 2;
	pi->name = "knob1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob_22")
	pi = self->__commonstate.params + 3;
	pi->name = "knob2";
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
	// initialize parameter 4 ("m_knob_27")
	pi = self->__commonstate.params + 4;
	pi->name = "knob3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_27;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_knob_28")
	pi = self->__commonstate.params + 5;
	pi->name = "knob4";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_28;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_knob_23")
	pi = self->__commonstate.params + 6;
	pi->name = "knob5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_knob_21")
	pi = self->__commonstate.params + 7;
	pi->name = "knob6";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_length_data_18")
	pi = self->__commonstate.params + 8;
	pi->name = "length_data";
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
	// initialize parameter 9 ("m_offset_data_17")
	pi = self->__commonstate.params + 9;
	pi->name = "offset_data";
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
	// initialize parameter 10 ("m_pitchedmode_13")
	pi = self->__commonstate.params + 10;
	pi->name = "pitchedmode";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_pitchedmode_13;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 4;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_playmode_14")
	pi = self->__commonstate.params + 11;
	pi->name = "playmode";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_playmode_14;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 4;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_rms_data_16")
	pi = self->__commonstate.params + 12;
	pi->name = "rms_data";
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
	// initialize parameter 13 ("m_segment_data_19")
	pi = self->__commonstate.params + 13;
	pi->name = "segment_data";
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
	// initialize parameter 14 ("m_sw_24")
	pi = self->__commonstate.params + 14;
	pi->name = "sw7";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 15 ("m_sw_26")
	pi = self->__commonstate.params + 15;
	pi->name = "sw8";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_26;
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


} // repeater1_pedal::
