#include "repeater3_pedal.h"

namespace repeater3_pedal {

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
	Change __m_change_40;
	DCBlock __m_dcblock_35;
	Data m_segment_data_21;
	Data m_offset_data_19;
	Data m_length_data_20;
	Data m_rms_data_18;
	Sah __m_sah_30;
	Sah __m_sah_29;
	int __exception;
	int vectorsize;
	t_sample m_play_index_7;
	t_sample m_knob_24;
	t_sample m_knob_25;
	t_sample m_knob_23;
	t_sample m_history_22;
	t_sample m_total_length_1;
	t_sample m_sw_26;
	t_sample m_history_28;
	t_sample m_knob_27;
	t_sample __m_slide_32;
	t_sample samplerate;
	t_sample m_play_len_6;
	t_sample m_energy_sum_2;
	t_sample m_play_rms_4;
	t_sample m_write_index_10;
	t_sample m_write_segment_11;
	t_sample m_crossing_count_9;
	t_sample m_play_segment_8;
	t_sample m_prev_input_3;
	t_sample m_freq_12;
	t_sample m_playmode_14;
	t_sample m_capture_17;
	t_sample m_pitchedmode_13;
	t_sample m_min_length_16;
	t_sample m_play_offset_5;
	t_sample m_hold_15;
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
		m_capture_17 = ((int)1);
		m_rms_data_18.reset("rms_data", ((int)64), ((int)1));
		m_offset_data_19.reset("offset_data", ((int)64), ((int)1));
		m_length_data_20.reset("length_data", ((int)64), ((int)1));
		m_segment_data_21.reset("segment_data", ((int)10004), ((int)64));
		m_history_22 = ((int)0);
		m_knob_23 = ((int)0);
		m_knob_24 = ((int)0);
		m_knob_25 = ((int)0);
		m_sw_26 = ((int)0);
		m_knob_27 = ((int)0);
		m_history_28 = ((int)0);
		__m_sah_29.reset(0);
		__m_sah_30.reset(0);
		__m_slide_32 = 0;
		__m_dcblock_35.reset();
		__m_change_40.reset(0);
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
		t_sample add_171 = (m_knob_27 + ((int)0));
		t_sample sub_447 = (add_171 - ((int)0));
		t_sample scale_444 = ((safepow((sub_447 * ((t_sample)1)), ((int)1)) * ((int)4980)) + ((int)20));
		t_sample add_172 = (scale_444 + ((int)0));
		t_sample sub_459 = (m_knob_24 - ((int)0));
		t_sample scale_456 = ((safepow((sub_459 * ((t_sample)1)), ((int)1)) * ((int)1)) + ((int)0));
		t_sample scale_191 = scale_456;
		t_sample mstosamps_200 = (((int)60) * (samplerate * 0.001));
		t_sample mstosamps_199 = (((int)101) * (samplerate * 0.001));
		t_sample iup_33 = (1 / maximum(1, abs(mstosamps_200)));
		t_sample idown_34 = (1 / maximum(1, abs(mstosamps_199)));
		int segment_data_dim = m_segment_data_21.dim;
		int segment_data_channels = m_segment_data_21.channels;
		int num_segments = segment_data_channels;
		t_sample max_length = add_172;
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_215 = __m_sah_29(m_history_28, m_sw_26, ((int)0));
			t_sample gen_218 = sah_215;
			t_sample rsub_213 = (((int)1) - sah_215);
			t_sample history_214_next_216 = fixdenorm(rsub_213);
			t_sample out5 = gen_218;
			t_sample sah_391 = __m_sah_30(m_history_22, m_sw_26, ((int)0));
			t_sample gen_217 = sah_391;
			t_sample rsub_392 = (((int)1) - sah_391);
			t_sample history_214_next_390 = fixdenorm(rsub_392);
			t_sample add_210 = (gen_217 + ((int)1));
			t_sample choice_31 = int(add_210);
			t_sample gate_211 = (((choice_31 >= 1) && (choice_31 < 2)) ? ((int)1) : 0);
			t_sample gate_212 = ((choice_31 >= 2) ? ((int)1) : 0);
			t_sample out3 = gate_211;
			t_sample out4 = gate_212;
			t_sample abs_208 = fabs(in1);
			__m_slide_32 = fixdenorm((__m_slide_32 + (((abs_208 > __m_slide_32) ? iup_33 : idown_34) * (abs_208 - __m_slide_32))));
			t_sample slide_207 = __m_slide_32;
			t_sample mul_203 = (slide_207 * ((int)5));
			t_sample clamp_201 = ((mul_203 <= ((int)0)) ? ((int)0) : ((mul_203 >= ((int)1)) ? ((int)1) : mul_203));
			t_sample sqrt_202 = sqrt(clamp_201);
			t_sample mul_206 = (sqrt_202 * scale_191);
			t_sample add_205 = (mul_206 + ((int)0));
			t_sample clamp_204 = ((add_205 <= ((int)0)) ? ((int)0) : ((add_205 >= ((int)1)) ? ((int)1) : add_205));
			t_sample mul_186 = (clamp_204 * ((int)1));
			t_sample out6 = mul_186;
			t_sample mul_387 = (mul_186 * ((t_sample)0.525));
			t_sample add_189 = (m_knob_23 + mul_387);
			t_sample out8 = add_189;
			t_sample sub_463 = (add_189 - ((int)0));
			t_sample scale_460 = ((safepow((sub_463 * ((t_sample)1)), ((int)1)) * ((int)19)) + ((int)1));
			t_sample add_194 = (scale_460 + ((int)0));
			t_sample mul_355 = (mul_186 * ((t_sample)0.39));
			t_sample add_190 = (m_knob_25 + mul_355);
			t_sample out7 = add_190;
			t_sample sub_467 = (add_190 - ((int)0));
			t_sample scale_464 = ((safepow((sub_467 * ((t_sample)1)), ((int)1)) * ((int)199)) + ((int)1));
			t_sample scale_226 = scale_464;
			t_sample add_193 = (scale_226 + ((int)0));
			t_sample crossKnob = add_193;
			t_sample crossings = crossKnob;
			t_sample repeats = add_194;
			t_sample unbiased_input = __m_dcblock_35(in1);
			m_energy_sum_2 = (m_energy_sum_2 + (unbiased_input * unbiased_input));
			m_write_index_10 = (m_write_index_10 + ((int)1));
			int channel_trunc_36 = fixnan(floor(m_write_segment_11));
			bool chan_ignore_37 = ((channel_trunc_36 < 0) || (channel_trunc_36 >= segment_data_channels));
			int index_trunc_38 = fixnan(floor(m_write_index_10));
			bool index_ignore_39 = ((index_trunc_38 >= segment_data_dim) || (index_trunc_38 < 0));
			if ((!(chan_ignore_37 || index_ignore_39))) {
				m_segment_data_21.write(unbiased_input, index_trunc_38, channel_trunc_36);
				
			};
			int is_crossing = (__m_change_40((unbiased_input > ((int)0))) > ((int)0));
			if (is_crossing) {
				if ((m_write_index_10 > max_length)) {
					m_crossing_count_9 = ((int)0);
					m_write_index_10 = ((int)0);
					
				} else {
					m_crossing_count_9 = (m_crossing_count_9 + ((int)1));
					int is_complete = ((m_capture_17 && (m_crossing_count_9 >= crossings)) && (m_write_index_10 >= m_min_length_16));
					if (is_complete) {
						t_sample offset = safediv(m_prev_input_3, (m_prev_input_3 - unbiased_input));
						int offset_data_dim = m_offset_data_19.dim;
						int offset_data_channels = m_offset_data_19.channels;
						int index_trunc_41 = fixnan(floor(m_write_segment_11));
						bool index_ignore_42 = ((index_trunc_41 >= offset_data_dim) || (index_trunc_41 < 0));
						// samples offset_data channel 1;
						t_sample prev_offset = (index_ignore_42 ? 0 : m_offset_data_19.read(index_trunc_41, 0));
						t_sample len = (((m_write_index_10 + offset) - prev_offset) - ((int)1));
						int length_data_dim = m_length_data_20.dim;
						int length_data_channels = m_length_data_20.channels;
						int index_trunc_43 = fixnan(floor(m_write_segment_11));
						bool index_ignore_44 = ((index_trunc_43 >= length_data_dim) || (index_trunc_43 < 0));
						// samples length_data channel 1;
						t_sample prev_length = (index_ignore_44 ? 0 : m_length_data_20.read(index_trunc_43, 0));
						m_total_length_1 = ((m_total_length_1 - prev_length) + len);
						int index_trunc_45 = fixnan(floor(m_write_segment_11));
						bool index_ignore_46 = ((index_trunc_45 >= length_data_dim) || (index_trunc_45 < 0));
						if ((!index_ignore_46)) {
							m_length_data_20.write(len, index_trunc_45, 0);
							
						};
						t_sample rms = sqrt(safediv(m_energy_sum_2, floor(len)));
						int rms_data_dim = m_rms_data_18.dim;
						int rms_data_channels = m_rms_data_18.channels;
						int index_trunc_47 = fixnan(floor(m_write_segment_11));
						bool index_ignore_48 = ((index_trunc_47 >= rms_data_dim) || (index_trunc_47 < 0));
						if ((!index_ignore_48)) {
							m_rms_data_18.write(rms, index_trunc_47, 0);
							
						};
						m_crossing_count_9 = ((int)0);
						m_energy_sum_2 = ((int)0);
						m_write_segment_11 = wrap((m_write_segment_11 + ((int)1)), ((int)0), num_segments);
						if ((m_write_segment_11 == m_play_segment_8)) {
							m_write_segment_11 = wrap((m_write_segment_11 + ((int)1)), ((int)0), num_segments);
							
						};
						int index_trunc_49 = fixnan(floor(m_write_segment_11));
						bool index_ignore_50 = ((index_trunc_49 >= offset_data_dim) || (index_trunc_49 < 0));
						if ((!index_ignore_50)) {
							m_offset_data_19.write(offset, index_trunc_49, 0);
							
						};
						int channel_trunc_51 = fixnan(floor(m_write_segment_11));
						bool chan_ignore_52 = ((channel_trunc_51 < 0) || (channel_trunc_51 >= segment_data_channels));
						if ((!chan_ignore_52)) {
							m_segment_data_21.write(m_prev_input_3, 0, channel_trunc_51);
							
						};
						int channel_trunc_53 = fixnan(floor(m_write_segment_11));
						bool chan_ignore_54 = ((channel_trunc_53 < 0) || (channel_trunc_53 >= segment_data_channels));
						bool index_ignore_55 = (((int)1) >= segment_data_dim);
						if ((!(chan_ignore_54 || index_ignore_55))) {
							m_segment_data_21.write(unbiased_input, ((int)1), channel_trunc_53);
							
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
						t_sample maxb_56 = (d * d);
						r = safediv(((int)1), ((((int)1) < maxb_56) ? maxb_56 : ((int)1)));
						
					} else {
						r = safediv((m_freq_12 * m_play_len_6), (samplerate * crossings));
						
					};
					
				};
				
			};
			m_play_index_7 = (m_play_index_7 + r);
			t_sample actual_play_index = wrap(m_play_index_7, ((int)0), m_play_len_6);
			int index_trunc_57 = fixnan(floor((m_play_offset_5 + actual_play_index)));
			double index_fract_58 = ((m_play_offset_5 + actual_play_index) - index_trunc_57);
			int index_trunc_59 = (index_trunc_57 + 1);
			bool index_ignore_60 = ((index_trunc_57 >= segment_data_dim) || (index_trunc_57 < 0));
			bool index_ignore_61 = ((index_trunc_59 >= segment_data_dim) || (index_trunc_59 < 0));
			// samples segment_data channel 1;
			int chan_62 = m_play_segment_8;
			bool chan_ignore_63 = ((chan_62 < 0) || (chan_62 >= segment_data_channels));
			double read_segment_data_64 = ((chan_ignore_63 || index_ignore_60) ? 0 : m_segment_data_21.read(index_trunc_57, chan_62));
			double read_segment_data_65 = ((chan_ignore_63 || index_ignore_61) ? 0 : m_segment_data_21.read(index_trunc_59, chan_62));
			double readinterp_66 = linear_interp(index_fract_58, read_segment_data_64, read_segment_data_65);
			t_sample expr_388 = readinterp_66;
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
								t_sample sign_67 = noise();
								t_sample direction = ((sign_67 > 0) ? 1 : ((sign_67 < 0) ? -1 : 0));
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
					int length_data_dim = m_length_data_20.dim;
					int length_data_channels = m_length_data_20.channels;
					int index_trunc_68 = fixnan(floor(m_play_segment_8));
					bool index_ignore_69 = ((index_trunc_68 >= length_data_dim) || (index_trunc_68 < 0));
					// samples length_data channel 1;
					m_play_len_6 = (index_ignore_69 ? 0 : m_length_data_20.read(index_trunc_68, 0));
					int offset_data_dim = m_offset_data_19.dim;
					int offset_data_channels = m_offset_data_19.channels;
					int index_trunc_70 = fixnan(floor(m_play_segment_8));
					bool index_ignore_71 = ((index_trunc_70 >= offset_data_dim) || (index_trunc_70 < 0));
					// samples offset_data channel 1;
					m_play_offset_5 = (index_ignore_71 ? 0 : m_offset_data_19.read(index_trunc_70, 0));
					int rms_data_dim = m_rms_data_18.dim;
					int rms_data_channels = m_rms_data_18.channels;
					int index_trunc_72 = fixnan(floor(m_play_segment_8));
					bool index_ignore_73 = ((index_trunc_72 >= rms_data_dim) || (index_trunc_72 < 0));
					// samples rms_data channel 1;
					m_play_rms_4 = (index_ignore_73 ? 0 : m_rms_data_18.read(index_trunc_72, 0));
					
				};
				
			};
			t_sample mix_468 = (in1 + (((int)1) * (expr_388 - in1)));
			t_sample out1 = mix_468;
			m_history_28 = history_214_next_216;
			m_history_22 = history_214_next_390;
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
		m_freq_12 = (_value < 0 ? 0 : (_value > 16000 ? 16000 : _value));
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
	inline void set_capture(t_param _value) {
		m_capture_17 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_rms_data(void * _value) {
		m_rms_data_18.setbuffer(_value);
	};
	inline void set_offset_data(void * _value) {
		m_offset_data_19.setbuffer(_value);
	};
	inline void set_length_data(void * _value) {
		m_length_data_20.setbuffer(_value);
	};
	inline void set_segment_data(void * _value) {
		m_segment_data_21.setbuffer(_value);
	};
	inline void set_knob2(t_param _value) {
		m_knob_23 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3(t_param _value) {
		m_knob_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob1(t_param _value) {
		m_knob_25 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_26 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4(t_param _value) {
		m_knob_27 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
int num_params() { return 15; }

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
		case 8: self->set_min_length(value); break;
		case 9: self->set_offset_data(ref); break;
		case 10: self->set_pitchedmode(value); break;
		case 11: self->set_playmode(value); break;
		case 12: self->set_rms_data(ref); break;
		case 13: self->set_segment_data(ref); break;
		case 14: self->set_sw1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_capture_17; break;
		case 1: *value = self->m_freq_12; break;
		case 2: *value = self->m_hold_15; break;
		case 3: *value = self->m_knob_25; break;
		case 4: *value = self->m_knob_23; break;
		case 5: *value = self->m_knob_24; break;
		case 6: *value = self->m_knob_27; break;
		
		case 8: *value = self->m_min_length_16; break;
		
		case 10: *value = self->m_pitchedmode_13; break;
		case 11: *value = self->m_playmode_14; break;
		
		
		case 14: *value = self->m_sw_26; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(15 * sizeof(ParamInfo));
	self->__commonstate.numparams = 15;
	// initialize parameter 0 ("m_capture_17")
	pi = self->__commonstate.params + 0;
	pi->name = "capture";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_capture_17;
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
	pi->outputmax = 16000;
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
	// initialize parameter 4 ("m_knob_23")
	pi = self->__commonstate.params + 4;
	pi->name = "knob2";
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
	// initialize parameter 5 ("m_knob_24")
	pi = self->__commonstate.params + 5;
	pi->name = "knob3";
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
	// initialize parameter 6 ("m_knob_27")
	pi = self->__commonstate.params + 6;
	pi->name = "knob4";
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
	// initialize parameter 7 ("m_length_data_20")
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
	// initialize parameter 8 ("m_min_length_16")
	pi = self->__commonstate.params + 8;
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
	// initialize parameter 9 ("m_offset_data_19")
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
	// initialize parameter 12 ("m_rms_data_18")
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
	// initialize parameter 13 ("m_segment_data_21")
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
	// initialize parameter 14 ("m_sw_26")
	pi = self->__commonstate.params + 14;
	pi->name = "sw1";
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


} // repeater3_pedal::
