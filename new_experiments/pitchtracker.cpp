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
	t_sample m_best_lag_12;
	t_sample m_current_lag_11;
	t_sample m_processing_10;
	t_sample m_max_corr_13;
	t_sample m_curr_corr_15;
	t_sample m_prev_corr_14;
	t_sample m_total_energy_16;
	t_sample samplerate;
	t_sample m_peak_amplitude_9;
	t_sample m_detected_pitch_7;
	t_sample m_min_freq_3;
	t_sample m_sample_rate_2;
	t_sample m_found_peak_17;
	t_sample m_max_freq_4;
	t_sample m_write_idx_6;
	t_sample m_threshold_5;
	t_sample m_confidence_8;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_audio_buffer_1.reset("audio_buffer", ((int)2048), ((int)1));
		m_sample_rate_2 = ((int)48000);
		m_min_freq_3 = ((int)80);
		m_max_freq_4 = ((int)1000);
		m_threshold_5 = ((t_sample)0.6);
		m_write_idx_6 = ((int)0);
		m_detected_pitch_7 = ((int)0);
		m_confidence_8 = ((int)0);
		m_peak_amplitude_9 = ((int)0);
		m_processing_10 = ((int)0);
		m_current_lag_11 = ((int)0);
		m_best_lag_12 = ((int)0);
		m_max_corr_13 = ((int)0);
		m_prev_corr_14 = ((int)0);
		m_curr_corr_15 = ((int)0);
		m_total_energy_16 = ((int)0);
		m_found_peak_17 = ((int)0);
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
		int audio_buffer_dim = m_audio_buffer_1.dim;
		int audio_buffer_channels = m_audio_buffer_1.channels;
		__loopcount = (__n * GENLIB_LOOPCOUNT_BAIL);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			int index_trunc_18 = fixnan(floor(m_write_idx_6));
			bool index_ignore_19 = ((index_trunc_18 >= audio_buffer_dim) || (index_trunc_18 < 0));
			if ((!index_ignore_19)) {
				m_audio_buffer_1.write(in1, index_trunc_18, 0);
				
			};
			m_write_idx_6 = (m_write_idx_6 + ((int)1));
			if ((m_write_idx_6 >= ((int)2048))) {
				m_write_idx_6 = ((int)0);
				m_processing_10 = ((int)1);
				m_current_lag_11 = floor(safediv(m_sample_rate_2, m_max_freq_4));
				m_best_lag_12 = m_current_lag_11;
				m_max_corr_13 = ((int)-1);
				m_prev_corr_14 = ((int)0);
				m_curr_corr_15 = ((int)0);
				m_found_peak_17 = ((int)0);
				m_total_energy_16 = ((int)0);
				m_peak_amplitude_9 = ((int)0);
				int j = ((int)0);
				while ((j < ((int)1800))) {
					// abort processing if an infinite loop is suspected;
					if (((__loopcount--) <= 0)) {
						__exception = GENLIB_ERR_LOOP_OVERFLOW;
						break ;
						
					};
					bool index_ignore_20 = ((j >= audio_buffer_dim) || (j < 0));
					// samples audio_buffer channel 1;
					t_sample v = (index_ignore_20 ? 0 : m_audio_buffer_1.read(j, 0));
					t_sample abs_v = fabs(v);
					if ((abs_v > m_peak_amplitude_9)) {
						m_peak_amplitude_9 = abs_v;
						
					};
					m_total_energy_16 = (m_total_energy_16 + (v * v));
					j = (j + ((int)1));
					
				};
				
			};
			// abort processing if an infinite loop is suspected;
			if (((__loopcount--) <= 0)) {
				__exception = GENLIB_ERR_LOOP_OVERFLOW;
				break ;
				
			};
			if ((m_processing_10 > ((int)0))) {
				t_sample max_lag = floor(safediv(m_sample_rate_2, m_min_freq_3));
				if ((max_lag > ((int)600))) {
					max_lag = ((int)600);
					
				};
				if ((m_current_lag_11 < max_lag)) {
					if ((m_found_peak_17 == ((int)0))) {
						m_prev_corr_14 = m_curr_corr_15;
						t_sample corr = ((int)0);
						int k = ((int)0);
						while ((k < ((int)1800))) {
							// abort processing if an infinite loop is suspected;
							if (((__loopcount--) <= 0)) {
								__exception = GENLIB_ERR_LOOP_OVERFLOW;
								break ;
								
							};
							t_sample idx = (k + m_current_lag_11);
							if ((idx < ((int)2048))) {
								bool index_ignore_21 = ((k >= audio_buffer_dim) || (k < 0));
								// samples audio_buffer channel 1;
								t_sample v1 = (index_ignore_21 ? 0 : m_audio_buffer_1.read(k, 0));
								int index_trunc_22 = fixnan(floor(idx));
								bool index_ignore_23 = ((index_trunc_22 >= audio_buffer_dim) || (index_trunc_22 < 0));
								// samples audio_buffer channel 1;
								t_sample v2 = (index_ignore_23 ? 0 : m_audio_buffer_1.read(index_trunc_22, 0));
								corr = (corr + (v1 * v2));
								
							};
							k = (k + ((int)1));
							
						};
						if ((m_total_energy_16 > ((t_sample)0.001))) {
							corr = safediv(corr, m_total_energy_16);
							
						};
						m_curr_corr_15 = corr;
						if ((corr > m_threshold_5)) {
							t_sample next_corr = ((int)0);
							k = ((int)0);
							while ((k < ((int)1800))) {
								// abort processing if an infinite loop is suspected;
								if (((__loopcount--) <= 0)) {
									__exception = GENLIB_ERR_LOOP_OVERFLOW;
									break ;
									
								};
								t_sample idx = ((k + m_current_lag_11) + ((int)1));
								if ((idx < ((int)2048))) {
									bool index_ignore_24 = ((k >= audio_buffer_dim) || (k < 0));
									// samples audio_buffer channel 1;
									t_sample v1 = (index_ignore_24 ? 0 : m_audio_buffer_1.read(k, 0));
									int index_trunc_25 = fixnan(floor(idx));
									bool index_ignore_26 = ((index_trunc_25 >= audio_buffer_dim) || (index_trunc_25 < 0));
									// samples audio_buffer channel 1;
									t_sample v2 = (index_ignore_26 ? 0 : m_audio_buffer_1.read(index_trunc_25, 0));
									next_corr = (next_corr + (v1 * v2));
									
								};
								k = (k + ((int)1));
								
							};
							if ((m_total_energy_16 > ((t_sample)0.001))) {
								next_corr = safediv(next_corr, m_total_energy_16);
								
							};
							if ((corr > next_corr)) {
								if ((corr > m_prev_corr_14)) {
									if ((corr > m_max_corr_13)) {
										m_max_corr_13 = corr;
										m_best_lag_12 = m_current_lag_11;
										t_sample denom = ((m_prev_corr_14 - (((int)2) * corr)) + next_corr);
										if ((fabs(denom) > ((t_sample)0.0001))) {
											t_sample peak_offset = safediv((((t_sample)0.5) * (m_prev_corr_14 - next_corr)), denom);
											if ((peak_offset > (-((t_sample)0.5)))) {
												if ((peak_offset < ((t_sample)0.5))) {
													m_best_lag_12 = (m_current_lag_11 + peak_offset);
													
												};
												
											};
											
										};
										m_found_peak_17 = ((int)1);
										
									};
									
								};
								
							};
							
						};
						
					};
					m_current_lag_11 = (m_current_lag_11 + ((int)1));
					
				} else {
					if ((m_found_peak_17 > ((int)0))) {
						if ((m_max_corr_13 > m_threshold_5)) {
							m_detected_pitch_7 = safediv(m_sample_rate_2, m_best_lag_12);
							m_confidence_8 = m_max_corr_13;
							
						};
						
					};
					m_processing_10 = ((int)0);
					
				};
				
			};
			t_sample expr_1082 = m_detected_pitch_7;
			t_sample expr_1083 = m_confidence_8;
			t_sample expr_1084 = m_peak_amplitude_9;
			t_sample out1 = in1;
			t_sample out4 = expr_1083;
			t_sample out3 = expr_1082;
			t_sample out5 = expr_1084;
			t_sample out2 = in1;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			
		};
		return __exception;
		
	};
	inline void set_audio_buffer(void * _value) {
		m_audio_buffer_1.setbuffer(_value);
	};
	inline void set_sample_rate(t_param _value) {
		m_sample_rate_2 = (_value < 8000 ? 8000 : (_value > 96000 ? 96000 : _value));
	};
	inline void set_min_freq(t_param _value) {
		m_min_freq_3 = (_value < 20 ? 20 : (_value > 500 ? 500 : _value));
	};
	inline void set_max_freq(t_param _value) {
		m_max_freq_4 = (_value < 200 ? 200 : (_value > 5000 ? 5000 : _value));
	};
	inline void set_threshold(t_param _value) {
		m_threshold_5 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
const char *gen_kernel_outnames[] = { "out1", "out2", "out3", "out4", "out5" };

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
		case 0: self->set_audio_buffer(ref); break;
		case 1: self->set_max_freq(value); break;
		case 2: self->set_min_freq(value); break;
		case 3: self->set_sample_rate(value); break;
		case 4: self->set_threshold(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		
		case 1: *value = self->m_max_freq_4; break;
		case 2: *value = self->m_min_freq_3; break;
		case 3: *value = self->m_sample_rate_2; break;
		case 4: *value = self->m_threshold_5; break;
		
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
	// initialize parameter 0 ("m_audio_buffer_1")
	pi = self->__commonstate.params + 0;
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
	// initialize parameter 1 ("m_max_freq_4")
	pi = self->__commonstate.params + 1;
	pi->name = "max_freq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_max_freq_4;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 200;
	pi->outputmax = 5000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_min_freq_3")
	pi = self->__commonstate.params + 2;
	pi->name = "min_freq";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_min_freq_3;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 20;
	pi->outputmax = 500;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_sample_rate_2")
	pi = self->__commonstate.params + 3;
	pi->name = "sample_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sample_rate_2;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 8000;
	pi->outputmax = 96000;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_threshold_5")
	pi = self->__commonstate.params + 4;
	pi->name = "threshold";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_threshold_5;
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


} // pitchtracker::
