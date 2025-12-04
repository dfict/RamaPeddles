#include "repeater2_pedal.h"

namespace repeater2_pedal {

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
	Change __m_change_41;
	DCBlock __m_dcblock_36;
	Data m_segment_data_22;
	Data m_offset_data_20;
	Data m_length_data_21;
	Data m_rms_data_19;
	Sah __m_sah_31;
	Sah __m_sah_30;
	int __exception;
	int vectorsize;
	t_sample m_play_index_7;
	t_sample m_knob_24;
	t_sample m_knob_25;
	t_sample m_history_23;
	t_sample m_total_length_1;
	t_sample m_knob_26;
	t_sample m_knob_27;
	t_sample m_sw_28;
	t_sample __m_slide_33;
	t_sample m_energy_sum_2;
	t_sample samplerate;
	t_sample m_history_29;
	t_sample m_play_len_6;
	t_sample m_prev_input_3;
	t_sample m_capture_18;
	t_sample m_write_index_10;
	t_sample m_write_segment_11;
	t_sample m_crossing_count_9;
	t_sample m_play_segment_8;
	t_sample m_play_rms_4;
	t_sample m_freq_12;
	t_sample m_playmode_14;
	t_sample m_max_length_17;
	t_sample m_pitchedmode_13;
	t_sample m_play_offset_5;
	t_sample m_hold_15;
	t_sample m_min_length_16;
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
		m_hold_15 = ((int)0);
		m_min_length_16 = ((int)100);
		m_max_length_17 = ((int)10000);
		m_capture_18 = ((int)1);
		m_rms_data_19.reset("rms_data", ((int)64), ((int)1));
		m_offset_data_20.reset("offset_data", ((int)64), ((int)1));
		m_length_data_21.reset("length_data", ((int)64), ((int)1));
		m_segment_data_22.reset("segment_data", ((int)10004), ((int)64));
		m_history_23 = ((int)0);
		m_knob_24 = ((int)0);
		m_knob_25 = ((int)0);
		m_knob_26 = ((int)0);
		m_knob_27 = ((int)0);
		m_sw_28 = ((int)0);
		m_history_29 = ((int)0);
		__m_sah_30.reset(0);
		__m_sah_31.reset(0);
		__m_slide_33 = 0;
		__m_dcblock_36.reset();
		__m_change_41.reset(0);
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
		t_sample * __out8 = __outs[7];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) || (__out7 == 0) || (__out8 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample sub_677 = (m_knob_27 - ((int)0));
		t_sample scale_674 = ((safepow((sub_677 * ((t_sample)1)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample scale_431 = scale_674;
		t_sample mstosamps_440 = (((int)60) * (samplerate * 0.001));
		t_sample mstosamps_439 = (((int)101) * (samplerate * 0.001));
		t_sample iup_34 = (1 / maximum(1, abs(mstosamps_440)));
		t_sample idown_35 = (1 / maximum(1, abs(mstosamps_439)));
		int segment_data_dim = m_segment_data_22.dim;
		int segment_data_channels = m_segment_data_22.channels;
		int num_segments = segment_data_channels;
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_464 = __m_sah_30(m_history_29, m_sw_28, ((int)0));
			t_sample gen_467 = sah_464;
			t_sample rsub_462 = (((int)1) - sah_464);
			t_sample history_463_next_465 = fixdenorm(rsub_462);
			t_sample out5 = gen_467;
			t_sample sah_646 = __m_sah_31(m_history_23, m_sw_28, ((int)0));
			t_sample gen_466 = sah_646;
			t_sample rsub_647 = (((int)1) - sah_646);
			t_sample history_463_next_644 = fixdenorm(rsub_647);
			t_sample add_459 = (gen_466 + ((int)1));
			t_sample choice_32 = int(add_459);
			t_sample gate_460 = (((choice_32 >= 1) && (choice_32 < 2)) ? ((int)1) : 0);
			t_sample gate_461 = ((choice_32 >= 2) ? ((int)1) : 0);
			t_sample out4 = gate_461;
			t_sample out3 = gate_460;
			t_sample abs_448 = fabs(in1);
			__m_slide_33 = fixdenorm((__m_slide_33 + (((abs_448 > __m_slide_33) ? iup_34 : idown_35) * (abs_448 - __m_slide_33))));
			t_sample slide_447 = __m_slide_33;
			t_sample mul_443 = (slide_447 * ((int)5));
			t_sample clamp_441 = ((mul_443 <= ((int)0)) ? ((int)0) : ((mul_443 >= ((int)1)) ? ((int)1) : mul_443));
			t_sample sqrt_442 = sqrt(clamp_441);
			t_sample mul_446 = (sqrt_442 * scale_431);
			t_sample add_445 = (mul_446 + ((int)0));
			t_sample clamp_444 = ((add_445 <= ((int)0)) ? ((int)0) : ((add_445 >= ((int)1)) ? ((int)1) : add_445));
			t_sample mul_426 = (clamp_444 * ((int)1));
			t_sample out6 = mul_426;
			t_sample mul_428 = (mul_426 * ((t_sample)0.9));
			t_sample add_430 = (m_knob_25 + mul_428);
			t_sample out7 = add_430;
			t_sample sub_685 = (add_430 - ((int)0));
			t_sample scale_682 = ((safepow((sub_685 * ((t_sample)1)), ((int)1)) * ((int)199)) + ((int)1));
			t_sample scale_475 = scale_682;
			t_sample add_433 = (scale_475 + ((int)0));
			t_sample mul_427 = (mul_426 * ((t_sample)0.25));
			t_sample add_429 = (m_knob_26 + mul_427);
			t_sample out8 = add_429;
			t_sample sub_689 = (add_429 - ((int)0));
			t_sample scale_686 = ((safepow((sub_689 * ((t_sample)1)), ((int)1)) * ((int)19)) + ((int)1));
			t_sample add_434 = (scale_686 + ((int)0));
			t_sample crossKnob = add_433;
			t_sample crossings = crossKnob;
			t_sample repeats = add_434;
			t_sample unbiased_input = __m_dcblock_36(in1);
			m_energy_sum_2 = (m_energy_sum_2 + (unbiased_input * unbiased_input));
			m_write_index_10 = (m_write_index_10 + ((int)1));
			int channel_trunc_37 = fixnan(floor(m_write_segment_11));
			bool chan_ignore_38 = ((channel_trunc_37 < 0) || (channel_trunc_37 >= segment_data_channels));
			int index_trunc_39 = fixnan(floor(m_write_index_10));
			bool index_ignore_40 = ((index_trunc_39 >= segment_data_dim) || (index_trunc_39 < 0));
			if ((!(chan_ignore_38 || index_ignore_40))) {
				m_segment_data_22.write(unbiased_input, index_trunc_39, channel_trunc_37);
				
			};
			int is_crossing = (__m_change_41((unbiased_input > ((int)0))) > ((int)0));
			if (is_crossing) {
				if ((m_write_index_10 > m_max_length_17)) {
					m_crossing_count_9 = ((int)0);
					m_write_index_10 = ((int)0);
					
				} else {
					m_crossing_count_9 = (m_crossing_count_9 + ((int)1));
					int is_complete = ((m_capture_18 && (m_crossing_count_9 >= crossings)) && (m_write_index_10 >= m_min_length_16));
					if (is_complete) {
						t_sample offset = safediv(m_prev_input_3, (m_prev_input_3 - unbiased_input));
						int offset_data_dim = m_offset_data_20.dim;
						int offset_data_channels = m_offset_data_20.channels;
						int index_trunc_42 = fixnan(floor(m_write_segment_11));
						bool index_ignore_43 = ((index_trunc_42 >= offset_data_dim) || (index_trunc_42 < 0));
						// samples offset_data channel 1;
						t_sample prev_offset = (index_ignore_43 ? 0 : m_offset_data_20.read(index_trunc_42, 0));
						t_sample len = (((m_write_index_10 + offset) - prev_offset) - ((int)1));
						int length_data_dim = m_length_data_21.dim;
						int length_data_channels = m_length_data_21.channels;
						int index_trunc_44 = fixnan(floor(m_write_segment_11));
						bool index_ignore_45 = ((index_trunc_44 >= length_data_dim) || (index_trunc_44 < 0));
						// samples length_data channel 1;
						t_sample prev_length = (index_ignore_45 ? 0 : m_length_data_21.read(index_trunc_44, 0));
						m_total_length_1 = ((m_total_length_1 - prev_length) + len);
						int index_trunc_46 = fixnan(floor(m_write_segment_11));
						bool index_ignore_47 = ((index_trunc_46 >= length_data_dim) || (index_trunc_46 < 0));
						if ((!index_ignore_47)) {
							m_length_data_21.write(len, index_trunc_46, 0);
							
						};
						t_sample rms = sqrt(safediv(m_energy_sum_2, floor(len)));
						int rms_data_dim = m_rms_data_19.dim;
						int rms_data_channels = m_rms_data_19.channels;
						int index_trunc_48 = fixnan(floor(m_write_segment_11));
						bool index_ignore_49 = ((index_trunc_48 >= rms_data_dim) || (index_trunc_48 < 0));
						if ((!index_ignore_49)) {
							m_rms_data_19.write(rms, index_trunc_48, 0);
							
						};
						m_crossing_count_9 = ((int)0);
						m_energy_sum_2 = ((int)0);
						m_write_segment_11 = wrap((m_write_segment_11 + ((int)1)), ((int)0), num_segments);
						if ((m_write_segment_11 == m_play_segment_8)) {
							m_write_segment_11 = wrap((m_write_segment_11 + ((int)1)), ((int)0), num_segments);
							
						};
						int index_trunc_50 = fixnan(floor(m_write_segment_11));
						bool index_ignore_51 = ((index_trunc_50 >= offset_data_dim) || (index_trunc_50 < 0));
						if ((!index_ignore_51)) {
							m_offset_data_20.write(offset, index_trunc_50, 0);
							
						};
						int channel_trunc_52 = fixnan(floor(m_write_segment_11));
						bool chan_ignore_53 = ((channel_trunc_52 < 0) || (channel_trunc_52 >= segment_data_channels));
						if ((!chan_ignore_53)) {
							m_segment_data_22.write(m_prev_input_3, 0, channel_trunc_52);
							
						};
						int channel_trunc_54 = fixnan(floor(m_write_segment_11));
						bool chan_ignore_55 = ((channel_trunc_54 < 0) || (channel_trunc_54 >= segment_data_channels));
						bool index_ignore_56 = (((int)1) >= segment_data_dim);
						if ((!(chan_ignore_55 || index_ignore_56))) {
							m_segment_data_22.write(unbiased_input, ((int)1), channel_trunc_54);
							
						};
						m_write_index_10 = ((int)1);
						
					};
					
				};
				
			};
			m_prev_input_3 = unbiased_input;
			t_sample r = ((int)1);
			if ((m_pitchedmode_13 < ((int)1))) {
				
			} else {
				if ((m_pitchedmode_13 < ((int)2))) {
					t_sample d = safediv(m_play_index_7, m_play_len_6);
					r = (((int)1) * ((((int)1) < d) ? d : ((int)1)));
					
				} else {
					if ((m_pitchedmode_13 < ((int)3))) {
						t_sample d = ceil(safediv(m_play_index_7, m_play_len_6));
						t_sample maxb_57 = (d * d);
						r = safediv(((int)1), ((((int)1) < maxb_57) ? maxb_57 : ((int)1)));
						
					} else {
						r = safediv((m_freq_12 * m_play_len_6), (samplerate * crossings));
						
					};
					
				};
				
			};
			m_play_index_7 = (m_play_index_7 + r);
			t_sample actual_play_index = wrap(m_play_index_7, ((int)0), m_play_len_6);
			int index_trunc_58 = fixnan(floor((m_play_offset_5 + actual_play_index)));
			double index_fract_59 = ((m_play_offset_5 + actual_play_index) - index_trunc_58);
			int index_trunc_60 = (index_trunc_58 + 1);
			bool index_ignore_61 = ((index_trunc_58 >= segment_data_dim) || (index_trunc_58 < 0));
			bool index_ignore_62 = ((index_trunc_60 >= segment_data_dim) || (index_trunc_60 < 0));
			// samples segment_data channel 1;
			int chan_63 = m_play_segment_8;
			bool chan_ignore_64 = ((chan_63 < 0) || (chan_63 >= segment_data_channels));
			double read_segment_data_65 = ((chan_ignore_64 || index_ignore_61) ? 0 : m_segment_data_22.read(index_trunc_58, chan_63));
			double read_segment_data_66 = ((chan_ignore_64 || index_ignore_62) ? 0 : m_segment_data_22.read(index_trunc_60, chan_63));
			double readinterp_67 = linear_interp(index_fract_59, read_segment_data_65, read_segment_data_66);
			t_sample expr_643 = readinterp_67;
			if ((m_play_index_7 >= (m_play_len_6 * floor(repeats)))) {
				m_play_index_7 = actual_play_index;
				if ((!m_hold_15)) {
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
								t_sample sign_68 = noise();
								t_sample direction = ((sign_68 > 0) ? 1 : ((sign_68 < 0) ? -1 : 0));
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
					int length_data_dim = m_length_data_21.dim;
					int length_data_channels = m_length_data_21.channels;
					int index_trunc_69 = fixnan(floor(m_play_segment_8));
					bool index_ignore_70 = ((index_trunc_69 >= length_data_dim) || (index_trunc_69 < 0));
					// samples length_data channel 1;
					m_play_len_6 = (index_ignore_70 ? 0 : m_length_data_21.read(index_trunc_69, 0));
					int offset_data_dim = m_offset_data_20.dim;
					int offset_data_channels = m_offset_data_20.channels;
					int index_trunc_71 = fixnan(floor(m_play_segment_8));
					bool index_ignore_72 = ((index_trunc_71 >= offset_data_dim) || (index_trunc_71 < 0));
					// samples offset_data channel 1;
					m_play_offset_5 = (index_ignore_72 ? 0 : m_offset_data_20.read(index_trunc_71, 0));
					int rms_data_dim = m_rms_data_19.dim;
					int rms_data_channels = m_rms_data_19.channels;
					int index_trunc_73 = fixnan(floor(m_play_segment_8));
					bool index_ignore_74 = ((index_trunc_73 >= rms_data_dim) || (index_trunc_73 < 0));
					// samples rms_data channel 1;
					m_play_rms_4 = (index_ignore_74 ? 0 : m_rms_data_19.read(index_trunc_73, 0));
					
				};
				
			};
			t_sample mix_690 = (in1 + (((t_sample)0.5) * (expr_643 - in1)));
			t_sample out1 = mix_690;
			m_history_29 = history_463_next_465;
			m_history_23 = history_463_next_644;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = 0;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			(*(__out6++)) = out6;
			(*(__out7++)) = out7;
			(*(__out8++)) = out8;
			
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
	inline void set_hold(t_param _value) {
		m_hold_15 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_min_length(t_param _value) {
		m_min_length_16 = (_value < 16 ? 16 : (_value > 10000 ? 10000 : _value));
	};
	inline void set_max_length(t_param _value) {
		m_max_length_17 = (_value < 16 ? 16 : (_value > 10000 ? 10000 : _value));
	};
	inline void set_capture(t_param _value) {
		m_capture_18 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_rms_data(void * _value) {
		m_rms_data_19.setbuffer(_value);
	};
	inline void set_offset_data(void * _value) {
		m_offset_data_20.setbuffer(_value);
	};
	inline void set_length_data(void * _value) {
		m_length_data_21.setbuffer(_value);
	};
	inline void set_segment_data(void * _value) {
		m_segment_data_22.setbuffer(_value);
	};
	inline void set_knob4(t_param _value) {
		m_knob_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob1(t_param _value) {
		m_knob_25 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2(t_param _value) {
		m_knob_26 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3(t_param _value) {
		m_knob_27 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_28 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 8;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 16; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "source to sample" };
const char *gen_kernel_outnames[] = { "out1", "out2", "led1", "led2", "relay", "out6", "out7", "out8" };

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
		case 2: self->set_hold(value); break;
		case 3: self->set_knob1(value); break;
		case 4: self->set_knob2(value); break;
		case 5: self->set_knob3(value); break;
		case 6: self->set_knob4(value); break;
		case 7: self->set_length_data(ref); break;
		case 8: self->set_max_length(value); break;
		case 9: self->set_min_length(value); break;
		case 10: self->set_offset_data(ref); break;
		case 11: self->set_pitchedmode(value); break;
		case 12: self->set_playmode(value); break;
		case 13: self->set_rms_data(ref); break;
		case 14: self->set_segment_data(ref); break;
		case 15: self->set_sw1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_capture_18; break;
		case 1: *value = self->m_freq_12; break;
		case 2: *value = self->m_hold_15; break;
		case 3: *value = self->m_knob_25; break;
		case 4: *value = self->m_knob_26; break;
		case 5: *value = self->m_knob_27; break;
		case 6: *value = self->m_knob_24; break;
		
		case 8: *value = self->m_max_length_17; break;
		case 9: *value = self->m_min_length_16; break;
		
		case 11: *value = self->m_pitchedmode_13; break;
		case 12: *value = self->m_playmode_14; break;
		
		
		case 15: *value = self->m_sw_28; break;
		
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
	// initialize parameter 0 ("m_capture_18")
	pi = self->__commonstate.params + 0;
	pi->name = "capture";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_capture_18;
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
	// initialize parameter 2 ("m_hold_15")
	pi = self->__commonstate.params + 2;
	pi->name = "hold";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_hold_15;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob_25")
	pi = self->__commonstate.params + 3;
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
	// initialize parameter 4 ("m_knob_26")
	pi = self->__commonstate.params + 4;
	pi->name = "knob2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_knob_27")
	pi = self->__commonstate.params + 5;
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
	// initialize parameter 6 ("m_knob_24")
	pi = self->__commonstate.params + 6;
	pi->name = "knob4";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_length_data_21")
	pi = self->__commonstate.params + 7;
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
	// initialize parameter 8 ("m_max_length_17")
	pi = self->__commonstate.params + 8;
	pi->name = "max_length";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_max_length_17;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 16;
	pi->outputmax = 10000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_min_length_16")
	pi = self->__commonstate.params + 9;
	pi->name = "min_length";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_min_length_16;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 16;
	pi->outputmax = 10000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_offset_data_20")
	pi = self->__commonstate.params + 10;
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
	// initialize parameter 11 ("m_pitchedmode_13")
	pi = self->__commonstate.params + 11;
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
	// initialize parameter 12 ("m_playmode_14")
	pi = self->__commonstate.params + 12;
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
	// initialize parameter 13 ("m_rms_data_19")
	pi = self->__commonstate.params + 13;
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
	// initialize parameter 14 ("m_segment_data_22")
	pi = self->__commonstate.params + 14;
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
	// initialize parameter 15 ("m_sw_28")
	pi = self->__commonstate.params + 15;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_28;
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


} // repeater2_pedal::
