#include "pitchtracker.h"

namespace pitchtracker {

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
	Data m_audio_buffer_1;
	int __exception;
	int __loopcount;
	int vectorsize;
	t_sample m_block_peak_20;
	t_sample m_amp_env_21;
	t_sample m_confidence_19;
	t_sample m_prev2_corr_17;
	t_sample m_detected_pitch_18;
	t_sample m_prev_corr_16;
	t_sample m_target_22;
	t_sample m_target_24;
	t_sample m_tolerance_cents_28;
	t_sample m_target_23;
	t_sample m_conf_min_27;
	t_sample m_target_25;
	t_sample m_target_26;
	t_sample samplerate;
	t_sample m_energy_lag_15;
	t_sample m_end_lag_13;
	t_sample m_attack_ms_5;
	t_sample m_release_ms_6;
	t_sample m_threshold_4;
	t_sample m_min_freq_2;
	t_sample m_max_freq_3;
	t_sample m_min_level_29;
	t_sample m_write_idx_7;
	t_sample m_read_chan_9;
	t_sample m_start_lag_12;
	t_sample m_write_chan_8;
	t_sample m_current_lag_11;
	t_sample m_processing_10;
	t_sample m_energy_14;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_audio_buffer_1.reset("audio_buffer", ((int)2048), ((int)2));
		m_min_freq_2 = ((int)80);
		m_max_freq_3 = ((int)1000);
		m_threshold_4 = ((t_sample)0.6);
		m_attack_ms_5 = ((int)5);
		m_release_ms_6 = ((int)120);
		m_write_idx_7 = ((int)0);
		m_write_chan_8 = ((int)0);
		m_read_chan_9 = ((int)1);
		m_processing_10 = ((int)0);
		m_current_lag_11 = ((int)0);
		m_start_lag_12 = ((int)1);
		m_end_lag_13 = ((int)1);
		m_energy_14 = ((int)0);
		m_energy_lag_15 = ((int)0);
		m_prev_corr_16 = ((int)0);
		m_prev2_corr_17 = ((int)0);
		m_detected_pitch_18 = ((int)0);
		m_confidence_19 = ((int)0);
		m_block_peak_20 = ((int)0);
		m_amp_env_21 = ((int)0);
		m_target_22 = ((int)4);
		m_target_23 = ((int)6);
		m_target_24 = ((int)9);
		m_target_25 = ((int)11);
		m_target_26 = ((int)2);
		m_conf_min_27 = ((t_sample)0.9);
		m_tolerance_cents_28 = ((int)50);
		m_min_level_29 = ((int)0);
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
		t_sample * __out9 = __outs[8];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) || (__out7 == 0) || (__out8 == 0) || (__out9 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample att = exp(safediv(((int)-1), ((m_attack_ms_5 * ((t_sample)0.001)) * samplerate)));
		t_sample rel = exp(safediv(((int)-1), ((m_release_ms_6 * ((t_sample)0.001)) * samplerate)));
		int audio_buffer_dim = m_audio_buffer_1.dim;
		int audio_buffer_channels = m_audio_buffer_1.channels;
		__loopcount = (__n * GENLIB_LOOPCOUNT_BAIL);
		int cond_65 = (m_min_level_29 <= ((int)0));
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out9 = ((int)0);
			t_sample sig = in1;
			t_sample x = fabs(sig);
			int cond_30 = (x > m_amp_env_21);
			t_sample coef = (cond_30 ? att : rel);
			m_amp_env_21 = (x + (coef * (m_amp_env_21 - x)));
			int channel_trunc_31 = fixnan(floor(m_write_chan_8));
			bool chan_ignore_32 = ((channel_trunc_31 < 0) || (channel_trunc_31 >= audio_buffer_channels));
			int index_trunc_33 = fixnan(floor(m_write_idx_7));
			bool index_ignore_34 = ((index_trunc_33 >= audio_buffer_dim) || (index_trunc_33 < 0));
			if ((!(chan_ignore_32 || index_ignore_34))) {
				m_audio_buffer_1.write(sig, index_trunc_33, channel_trunc_31);
				
			};
			m_write_idx_7 = (m_write_idx_7 + ((int)1));
			if ((m_write_idx_7 >= ((int)2048))) {
				m_write_idx_7 = ((int)0);
				m_read_chan_9 = m_write_chan_8;
				m_write_chan_8 = (((int)1) - m_write_chan_8);
				t_sample maxa_35 = (floor(safediv(samplerate, m_max_freq_3)) - ((int)2));
				m_start_lag_12 = ((maxa_35 < ((int)1)) ? ((int)1) : maxa_35);
				t_sample mina_36 = ceil(safediv(samplerate, m_min_freq_2));
				m_end_lag_13 = ((((int)600) < mina_36) ? ((int)600) : mina_36);
				t_sample e0 = ((int)0);
				t_sample el = ((int)0);
				t_sample pk = ((int)0);
				int j = ((int)0);
				while ((j < ((int)1448))) {
					// abort processing if an infinite loop is suspected;
					if (((__loopcount--) <= 0)) {
						__exception = GENLIB_ERR_LOOP_OVERFLOW;
						break ;
						
					};
					bool index_ignore_37 = ((j >= audio_buffer_dim) || (j < 0));
					// samples audio_buffer channel 1;
					int chan_38 = m_read_chan_9;
					bool chan_ignore_39 = ((chan_38 < 0) || (chan_38 >= audio_buffer_channels));
					t_sample v = ((chan_ignore_39 || index_ignore_37) ? 0 : m_audio_buffer_1.read(j, chan_38));
					int index_trunc_40 = fixnan(floor((j + m_start_lag_12)));
					bool index_ignore_41 = ((index_trunc_40 >= audio_buffer_dim) || (index_trunc_40 < 0));
					// samples audio_buffer channel 1;
					int chan_42 = m_read_chan_9;
					bool chan_ignore_43 = ((chan_42 < 0) || (chan_42 >= audio_buffer_channels));
					t_sample w = ((chan_ignore_43 || index_ignore_41) ? 0 : m_audio_buffer_1.read(index_trunc_40, chan_42));
					e0 = (e0 + (v * v));
					el = (el + (w * w));
					t_sample maxb_44 = fabs(v);
					pk = ((pk < maxb_44) ? maxb_44 : pk);
					j = (j + ((int)1));
					
				};
				m_energy_14 = e0;
				m_energy_lag_15 = el;
				m_block_peak_20 = pk;
				m_current_lag_11 = m_start_lag_12;
				m_prev_corr_16 = ((int)0);
				m_prev2_corr_17 = ((int)0);
				if ((e0 > ((t_sample)0.0001))) {
					m_processing_10 = ((int)1);
					
				} else {
					m_processing_10 = ((int)0);
					
				};
				
			};
			// abort processing if an infinite loop is suspected;
			if (((__loopcount--) <= 0)) {
				__exception = GENLIB_ERR_LOOP_OVERFLOW;
				break ;
				
			};
			if ((m_processing_10 > ((int)0))) {
				t_sample lag = m_current_lag_11;
				int found = ((int)0);
				t_sample offset = ((int)0);
				t_sample c = ((int)0);
				int k = ((int)0);
				while ((k < ((int)1448))) {
					// abort processing if an infinite loop is suspected;
					if (((__loopcount--) <= 0)) {
						__exception = GENLIB_ERR_LOOP_OVERFLOW;
						break ;
						
					};
					bool index_ignore_45 = ((k >= audio_buffer_dim) || (k < 0));
					// samples audio_buffer channel 1;
					int chan_46 = m_read_chan_9;
					bool chan_ignore_47 = ((chan_46 < 0) || (chan_46 >= audio_buffer_channels));
					t_sample peek_1679 = ((chan_ignore_47 || index_ignore_45) ? 0 : m_audio_buffer_1.read(k, chan_46));
					t_sample peek_1680 = k;
					int index_trunc_48 = fixnan(floor((k + lag)));
					bool index_ignore_49 = ((index_trunc_48 >= audio_buffer_dim) || (index_trunc_48 < 0));
					// samples audio_buffer channel 1;
					int chan_50 = m_read_chan_9;
					bool chan_ignore_51 = ((chan_50 < 0) || (chan_50 >= audio_buffer_channels));
					t_sample peek_1681 = ((chan_ignore_51 || index_ignore_49) ? 0 : m_audio_buffer_1.read(index_trunc_48, chan_50));
					t_sample peek_1682 = (k + lag);
					c = (c + (peek_1679 * peek_1681));
					k = (k + ((int)1));
					
				};
				int cond_52 = (m_energy_14 > ((t_sample)0.001));
				t_sample iftrue_53 = safediv(c, m_energy_14);
				t_sample c_1683 = (cond_52 ? iftrue_53 : ((int)0));
				if ((lag >= (m_start_lag_12 + ((int)2)))) {
					if ((((m_prev_corr_16 > m_threshold_4) && (m_prev_corr_16 > m_prev2_corr_17)) && (m_prev_corr_16 >= c_1683))) {
						t_sample d = ((m_prev2_corr_17 - (((int)2) * m_prev_corr_16)) + c_1683);
						if ((fabs(d) > ((t_sample)1e-06))) {
							t_sample v_54 = safediv((((t_sample)0.5) * (m_prev2_corr_17 - c_1683)), d);
							offset = ((v_54 <= ((t_sample)-0.5)) ? ((t_sample)-0.5) : ((v_54 >= ((t_sample)0.5)) ? ((t_sample)0.5) : v_54));
							
						};
						m_detected_pitch_18 = safediv(samplerate, ((lag - ((int)1)) + offset));
						m_confidence_19 = m_prev_corr_16;
						found = ((int)1);
						
					};
					
				};
				if ((lag < m_end_lag_13)) {
					int index_trunc_55 = fixnan(floor(lag));
					bool index_ignore_56 = ((index_trunc_55 >= audio_buffer_dim) || (index_trunc_55 < 0));
					// samples audio_buffer channel 1;
					int chan_57 = m_read_chan_9;
					bool chan_ignore_58 = ((chan_57 < 0) || (chan_57 >= audio_buffer_channels));
					t_sample a0 = ((chan_ignore_58 || index_ignore_56) ? 0 : m_audio_buffer_1.read(index_trunc_55, chan_57));
					int index_trunc_59 = fixnan(floor((lag + ((int)1448))));
					bool index_ignore_60 = ((index_trunc_59 >= audio_buffer_dim) || (index_trunc_59 < 0));
					// samples audio_buffer channel 1;
					int chan_61 = m_read_chan_9;
					bool chan_ignore_62 = ((chan_61 < 0) || (chan_61 >= audio_buffer_channels));
					t_sample a1 = ((chan_ignore_62 || index_ignore_60) ? 0 : m_audio_buffer_1.read(index_trunc_59, chan_61));
					t_sample maxa_63 = ((m_energy_lag_15 - (a0 * a0)) + (a1 * a1));
					m_energy_lag_15 = ((maxa_63 < ((int)0)) ? ((int)0) : maxa_63);
					
				};
				m_prev2_corr_17 = m_prev_corr_16;
				m_prev_corr_16 = c_1683;
				m_current_lag_11 = (lag + ((int)1));
				if ((found > ((int)0))) {
					m_processing_10 = ((int)0);
					
				} else {
					if ((m_current_lag_11 > m_end_lag_13)) {
						m_processing_10 = ((int)0);
						
					};
					
				};
				
			};
			t_sample expr_1686 = m_detected_pitch_18;
			t_sample expr_1687 = m_confidence_19;
			t_sample expr_1688 = m_amp_env_21;
			t_sample out1 = sig;
			t_sample out2 = sig;
			t_sample out3 = expr_1686;
			int cond_64 = (expr_1686 > ((int)20));
			int valid_pitch = (cond_64 ? ((int)1) : ((int)0));
			t_sample midi = (((int)69) + (((int)12) * log2((((expr_1686 < ((int)20)) ? ((int)20) : expr_1686) * ((t_sample)0.0022727272727273)))));
			t_sample nearest = floor((midi + ((t_sample)0.5)));
			t_sample cents = ((midi - nearest) * ((int)100));
			t_sample pc = (nearest - (((int)12) * floor((nearest * ((t_sample)0.083333333333333)))));
			int cond_66 = (expr_1688 >= m_min_level_29);
			int iffalse_67 = (cond_66 ? ((int)1) : ((int)0));
			int loud_ok = (cond_65 ? ((int)1) : iffalse_67);
			int cond_68 = (expr_1687 >= m_conf_min_27);
			int conf_ok = (cond_68 ? ((int)1) : ((int)0));
			int cond_69 = (fabs(cents) <= m_tolerance_cents_28);
			int tune_ok = (cond_69 ? ((int)1) : ((int)0));
			int trusted = (((valid_pitch * conf_ok) * tune_ok) * loud_ok);
			int cond_70 = (fabs((pc - m_target_22)) < ((t_sample)0.5));
			int hit1 = (trusted * (cond_70 ? ((int)1) : ((int)0)));
			int cond_71 = (fabs((pc - m_target_23)) < ((t_sample)0.5));
			int hit2 = (trusted * (cond_71 ? ((int)1) : ((int)0)));
			int cond_72 = (fabs((pc - m_target_24)) < ((t_sample)0.5));
			int hit3 = (trusted * (cond_72 ? ((int)1) : ((int)0)));
			int cond_73 = (fabs((pc - m_target_25)) < ((t_sample)0.5));
			int hit4 = (trusted * (cond_73 ? ((int)1) : ((int)0)));
			int cond_74 = (fabs((pc - m_target_26)) < ((t_sample)0.5));
			int hit5 = (trusted * (cond_74 ? ((int)1) : ((int)0)));
			t_sample expr_1696 = (trusted ? pc : ((int)-1));
			t_sample out8 = expr_1696;
			t_sample out6 = ((((hit5 + hit4) + hit3) + hit2) + hit1);
			t_sample out4 = expr_1687;
			t_sample out5 = expr_1688;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			(*(__out6++)) = out6;
			(*(__out7++)) = 0;
			(*(__out8++)) = out8;
			(*(__out9++)) = out9;
			
		};
		return __exception;
		
	};
	inline void set_audio_buffer(void * _value) {
		m_audio_buffer_1.setbuffer(_value);
	};
	inline void set_min_freq(t_param _value) {
		m_min_freq_2 = (_value < 20 ? 20 : (_value > 500 ? 500 : _value));
	};
	inline void set_max_freq(t_param _value) {
		m_max_freq_3 = (_value < 200 ? 200 : (_value > 5000 ? 5000 : _value));
	};
	inline void set_threshold(t_param _value) {
		m_threshold_4 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_attack_ms(t_param _value) {
		m_attack_ms_5 = (_value < 0.1 ? 0.1 : (_value > 100 ? 100 : _value));
	};
	inline void set_release_ms(t_param _value) {
		m_release_ms_6 = (_value < 1 ? 1 : (_value > 2000 ? 2000 : _value));
	};
	inline void set_target1(t_param _value) {
		m_target_22 = (_value < -1 ? -1 : (_value > 11 ? 11 : _value));
	};
	inline void set_target2(t_param _value) {
		m_target_23 = (_value < -1 ? -1 : (_value > 11 ? 11 : _value));
	};
	inline void set_target3(t_param _value) {
		m_target_24 = (_value < -1 ? -1 : (_value > 11 ? 11 : _value));
	};
	inline void set_target4(t_param _value) {
		m_target_25 = (_value < -1 ? -1 : (_value > 11 ? 11 : _value));
	};
	inline void set_target5(t_param _value) {
		m_target_26 = (_value < -1 ? -1 : (_value > 11 ? 11 : _value));
	};
	inline void set_conf_min(t_param _value) {
		m_conf_min_27 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_tolerance_cents(t_param _value) {
		m_tolerance_cents_28 = (_value < 1 ? 1 : (_value > 50 ? 50 : _value));
	};
	inline void set_min_level(t_param _value) {
		m_min_level_29 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 9;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 14; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "out2", "out3", "out4", "out5", "out6", "out7", "out8", "out9" };

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
		case 0: self->set_attack_ms(value); break;
		case 1: self->set_audio_buffer(ref); break;
		case 2: self->set_conf_min(value); break;
		case 3: self->set_max_freq(value); break;
		case 4: self->set_min_freq(value); break;
		case 5: self->set_min_level(value); break;
		case 6: self->set_release_ms(value); break;
		case 7: self->set_target1(value); break;
		case 8: self->set_target2(value); break;
		case 9: self->set_target3(value); break;
		case 10: self->set_target4(value); break;
		case 11: self->set_target5(value); break;
		case 12: self->set_threshold(value); break;
		case 13: self->set_tolerance_cents(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_attack_ms_5; break;
		
		case 2: *value = self->m_conf_min_27; break;
		case 3: *value = self->m_max_freq_3; break;
		case 4: *value = self->m_min_freq_2; break;
		case 5: *value = self->m_min_level_29; break;
		case 6: *value = self->m_release_ms_6; break;
		case 7: *value = self->m_target_22; break;
		case 8: *value = self->m_target_23; break;
		case 9: *value = self->m_target_24; break;
		case 10: *value = self->m_target_25; break;
		case 11: *value = self->m_target_26; break;
		case 12: *value = self->m_threshold_4; break;
		case 13: *value = self->m_tolerance_cents_28; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(14 * sizeof(ParamInfo));
	self->__commonstate.numparams = 14;
	// initialize parameter 0 ("m_attack_ms_5")
	pi = self->__commonstate.params + 0;
	pi->name = "attack_ms";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_attack_ms_5;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0.1;
	pi->outputmax = 100;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_audio_buffer_1")
	pi = self->__commonstate.params + 1;
	pi->name = "audio_buffer";
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
	// initialize parameter 2 ("m_conf_min_27")
	pi = self->__commonstate.params + 2;
	pi->name = "conf_min";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_conf_min_27;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_max_freq_3")
	pi = self->__commonstate.params + 3;
	pi->name = "max_freq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_max_freq_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 200;
	pi->outputmax = 5000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_min_freq_2")
	pi = self->__commonstate.params + 4;
	pi->name = "min_freq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_min_freq_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_min_level_29")
	pi = self->__commonstate.params + 5;
	pi->name = "min_level";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_min_level_29;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_release_ms_6")
	pi = self->__commonstate.params + 6;
	pi->name = "release_ms";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_release_ms_6;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 2000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_target_22")
	pi = self->__commonstate.params + 7;
	pi->name = "target1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_target_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -1;
	pi->outputmax = 11;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_target_23")
	pi = self->__commonstate.params + 8;
	pi->name = "target2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_target_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -1;
	pi->outputmax = 11;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_target_24")
	pi = self->__commonstate.params + 9;
	pi->name = "target3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_target_24;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -1;
	pi->outputmax = 11;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_target_25")
	pi = self->__commonstate.params + 10;
	pi->name = "target4";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_target_25;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -1;
	pi->outputmax = 11;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_target_26")
	pi = self->__commonstate.params + 11;
	pi->name = "target5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_target_26;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -1;
	pi->outputmax = 11;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_threshold_4")
	pi = self->__commonstate.params + 12;
	pi->name = "threshold";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_threshold_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 13 ("m_tolerance_cents_28")
	pi = self->__commonstate.params + 13;
	pi->name = "tolerance_cents";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_tolerance_cents_28;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 1;
	pi->outputmax = 50;
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


} // pitchtracker::
