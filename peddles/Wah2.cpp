#include "Wah2.h"

namespace Wah2 {

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
	Phasor __m_phasor_32;
	Sah __m_sah_27;
	Sah __m_sah_26;
	SineCycle __m_cycle_33;
	SineData __sinedata;
	int __exception;
	int vectorsize;
	t_sample m_knob4_res_22;
	t_sample m_s_4;
	t_sample m_knob2_depth_23;
	t_sample m_knob1_manual_21;
	t_sample m_knob3_rate_20;
	t_sample m_sw_24;
	t_sample m_history_25;
	t_sample m_s_1;
	t_sample samples_to_seconds;
	t_sample m_history_19;
	t_sample __m_slide_29;
	t_sample samplerate;
	t_sample m_s_3;
	t_sample m_history_18;
	t_sample m_history_16;
	t_sample m_slim_8;
	t_sample m_s_9;
	t_sample m_s_7;
	t_sample m_s_5;
	t_sample m_s_6;
	t_sample m_history_17;
	t_sample m_previn_10;
	t_sample m_fc_12;
	t_sample m_s_2;
	t_sample m_rc_11;
	t_sample m_history_14;
	t_sample m_history_13;
	t_sample m_history_15;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_s_1 = ((int)0);
		m_s_2 = ((int)0);
		m_s_3 = ((int)0);
		m_s_4 = ((int)0);
		m_s_5 = ((int)0);
		m_s_6 = ((int)0);
		m_s_7 = ((int)0);
		m_slim_8 = ((int)0);
		m_s_9 = ((int)0);
		m_previn_10 = ((int)0);
		m_rc_11 = ((int)0);
		m_fc_12 = ((int)1);
		m_history_13 = ((int)0);
		m_history_14 = ((int)0);
		m_history_15 = ((int)0);
		m_history_16 = ((int)0);
		m_history_17 = ((int)0);
		m_history_18 = ((int)0);
		m_history_19 = ((int)0);
		m_knob3_rate_20 = 0.1;
		m_knob1_manual_21 = 0;
		m_knob4_res_22 = 0.5;
		m_knob2_depth_23 = 1;
		m_sw_24 = ((int)0);
		m_history_25 = ((int)0);
		__m_sah_26.reset(0);
		__m_sah_27.reset(0);
		__m_slide_29 = 0;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_32.reset(0);
		__m_cycle_33.reset(samplerate, 0);
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
		t_sample sub_659 = (m_knob3_rate_20 - ((int)0));
		t_sample scale_656 = ((safepow((sub_659 * ((t_sample)1)), ((int)1)) * ((int)9)) + ((int)1));
		t_sample scale_308 = scale_656;
		t_sample mstosamps_447 = (scale_308 * (samplerate * 0.001));
		t_sample sub_663 = (m_knob3_rate_20 - ((int)0));
		t_sample scale_660 = ((safepow((sub_663 * ((t_sample)1)), ((int)1)) * ((int)40)) + ((int)60));
		t_sample scale_307 = scale_660;
		t_sample mstosamps_446 = (scale_307 * (samplerate * 0.001));
		t_sample iup_30 = (1 / maximum(1, abs(mstosamps_447)));
		t_sample idown_31 = (1 / maximum(1, abs(mstosamps_446)));
		samples_to_seconds = (1 / samplerate);
		int choice_34 = ((int)2);
		t_sample minb_35 = ((((t_sample)1e-05) < m_knob4_res_22) ? m_knob4_res_22 : ((t_sample)1e-05));
		t_sample maxb_36 = safediv(((t_sample)12.5), samplerate);
		t_sample minb_37 = ((((t_sample)0.0001) < maxb_36) ? maxb_36 : ((t_sample)0.0001));
		t_sample expr_354 = sqrt(((minb_37 < ((int)1)) ? minb_37 : ((int)1)));
		t_sample expr_353 = (((int)-1) * log(expr_354));
		int min_40 = (-1);
		int min_43 = (-1);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_315 = __m_sah_26(m_history_25, m_sw_24, ((int)0));
			t_sample gen_318 = sah_315;
			t_sample rsub_313 = (((int)1) - sah_315);
			t_sample history_314_next_316 = fixdenorm(rsub_313);
			t_sample out5 = gen_318;
			t_sample sah_461 = __m_sah_27(m_history_19, m_sw_24, ((int)0));
			t_sample gen_317 = sah_461;
			t_sample rsub_460 = (((int)1) - sah_461);
			t_sample history_314_next_462 = fixdenorm(rsub_460);
			t_sample add_310 = (gen_317 + ((int)1));
			t_sample choice_28 = int(add_310);
			t_sample gate_311 = (((choice_28 >= 1) && (choice_28 < 2)) ? ((int)1) : 0);
			t_sample gate_312 = ((choice_28 >= 2) ? ((int)1) : 0);
			t_sample out4 = gate_312;
			t_sample out3 = gate_311;
			t_sample mix_653 = (m_history_18 + (((t_sample)0.0042742627044161) * (m_knob1_manual_21 - m_history_18)));
			t_sample mix_326 = mix_653;
			t_sample mix_654 = (m_history_17 + (((t_sample)0.0042742627044161) * (mix_326 - m_history_17)));
			t_sample mix_324 = mix_654;
			t_sample mix_655 = (m_history_16 + (((t_sample)0.0042742627044161) * (mix_324 - m_history_16)));
			t_sample mix_322 = mix_655;
			t_sample gen_332 = mix_322;
			t_sample history_327_next_329 = fixdenorm(mix_326);
			t_sample history_325_next_330 = fixdenorm(mix_324);
			t_sample history_323_next_331 = fixdenorm(mix_322);
			t_sample abs_451 = fabs(in1);
			__m_slide_29 = fixdenorm((__m_slide_29 + (((abs_451 > __m_slide_29) ? iup_30 : idown_31) * (abs_451 - __m_slide_29))));
			t_sample slide_450 = __m_slide_29;
			t_sample mul_448 = (slide_450 * ((int)30));
			t_sample sqrt_320 = sqrt(mul_448);
			t_sample mix_664 = (m_history_15 + (((t_sample)0.0042742627044161) * (m_knob3_rate_20 - m_history_15)));
			t_sample mix_465 = mix_664;
			t_sample mix_665 = (m_history_14 + (((t_sample)0.0042742627044161) * (mix_465 - m_history_14)));
			t_sample mix_467 = mix_665;
			t_sample mix_666 = (m_history_13 + (((t_sample)0.0042742627044161) * (mix_467 - m_history_13)));
			t_sample mix_464 = mix_666;
			t_sample gen_445 = mix_464;
			t_sample history_327_next_470 = fixdenorm(mix_465);
			t_sample history_325_next_469 = fixdenorm(mix_467);
			t_sample history_323_next_471 = fixdenorm(mix_464);
			t_sample rsub_454 = (((int)1) - gen_445);
			t_sample sqrt_453 = sqrt(rsub_454);
			t_sample rsub_452 = (((int)1) - sqrt_453);
			t_sample mul_458 = (rsub_452 * ((int)10));
			t_sample phasor_457 = __m_phasor_32(mul_458, samples_to_seconds);
			__m_cycle_33.phase(phasor_457);
			t_sample cycle_443 = __m_cycle_33(__sinedata);
			t_sample cycleindex_444 = __m_cycle_33.phase();
			t_sample sub_670 = (cycle_443 - (-1));
			t_sample scale_667 = ((safepow((sub_670 * ((t_sample)0.5)), ((int)1)) * ((int)1)) + ((int)0));
			t_sample scale_321 = scale_667;
			t_sample selector_449 = ((choice_34 >= 2) ? sqrt_320 : ((choice_34 >= 1) ? scale_321 : 0));
			t_sample mul_442 = (selector_449 * m_knob2_depth_23);
			t_sample add_334 = (mul_442 + gen_332);
			t_sample clamp_333 = ((add_334 <= ((int)0)) ? ((int)0) : ((add_334 >= ((int)1)) ? ((int)1) : add_334));
			t_sample sub_674 = (clamp_333 - ((int)0));
			t_sample scale_671 = ((safepow((sub_674 * ((t_sample)1)), ((int)1)) * ((int)120)) + ((int)15));
			t_sample scale_335 = scale_671;
			t_sample expr_429 = (((((t_sample)1.05) * ((minb_35 < ((int)1)) ? minb_35 : ((int)1))) - m_rc_11) * ((t_sample)0.25));
			t_sample add_398 = (m_rc_11 + expr_429);
			t_sample noise_358 = noise();
			t_sample expr_414 = (in1 + (((t_sample)1e-11) * noise_358));
			t_sample fixdenorm_359 = fixdenorm(m_previn_10);
			t_sample gen_357 = m_fc_12;
			t_sample mul_341 = (scale_335 * ((t_sample)0.90193));
			t_sample add_338 = (mul_341 + ((t_sample)7.29));
			t_sample div_337 = (add_338 * ((t_sample)0.0078740157480315));
			t_sample clamp_343 = ((div_337 <= ((int)0)) ? ((int)0) : ((div_337 >= ((t_sample)0.99)) ? ((t_sample)0.99) : div_337));
			t_sample mul_342 = (clamp_343 * expr_353);
			t_sample expr_355 = (((t_sample)0.99999636) + ((((t_sample)0.031261316) + ((((t_sample)0.00048274797) + (((t_sample)5.949053e-06) * mul_342)) * mul_342)) * mul_342));
			t_sample mul_350 = (expr_355 * expr_355);
			t_sample mul_349 = (mul_350 * mul_350);
			t_sample mul_348 = (mul_349 * mul_349);
			t_sample mul_347 = (mul_348 * mul_348);
			t_sample mul_346 = (mul_347 * mul_347);
			t_sample mul_340 = (mul_346 * expr_354);
			t_sample sub_339 = (mul_340 - m_fc_12);
			t_sample div_336 = (sub_339 * ((t_sample)0.5));
			t_sample add_352 = (m_fc_12 + div_336);
			t_sample fc_next_356 = fixdenorm(add_352);
			t_sample expr_428 = (gen_357 * gen_357);
			t_sample expr_427 = (expr_428 * (((int)1) - m_rc_11));
			t_sample expr_426 = (expr_428 + (expr_427 * expr_427));
			t_sample expr_425 = ((((t_sample)1.25) + ((((t_sample)-0.74375) + (((t_sample)0.3) * expr_426)) * expr_426)) * expr_426);
			t_sample expr_424 = (m_rc_11 * (((t_sample)1.4) + ((((t_sample)0.108) + ((((t_sample)-0.164) - (((t_sample)0.069) * expr_425)) * expr_425)) * expr_425)));
			t_sample expr_423 = (((t_sample)0.18) + (((t_sample)0.25) * (expr_424 * expr_424)));
			t_sample expr_422 = ((fixdenorm_359 * expr_423) - (expr_424 * m_s_3));
			t_sample maxb_38 = (((((t_sample)0.062) * expr_422) * expr_422) + (((t_sample)0.993) * m_slim_8));
			t_sample minb_39 = ((((int)-1) < maxb_38) ? maxb_38 : ((int)-1));
			t_sample expr_421 = ((minb_39 < ((int)1)) ? minb_39 : ((int)1));
			t_sample expr_420 = (expr_422 * ((((int)1) - expr_421) + ((((t_sample)0.5) * expr_421) * expr_421)));
			t_sample rsub_399 = (((int)1) - expr_425);
			t_sample expr_419 = ((expr_420 * expr_425) + (rsub_399 * m_s_7));
			t_sample mul_381 = (m_s_4 * ((t_sample)0.3));
			t_sample mul_384 = (m_s_5 * ((t_sample)0.3));
			t_sample mul_374 = (expr_419 * ((t_sample)0.3));
			t_sample mul_392 = (m_s_7 * ((t_sample)0.3));
			t_sample add_390 = (expr_419 + mul_392);
			t_sample expr_418 = ((add_390 * expr_425) + (rsub_399 * m_s_6));
			t_sample mul_371 = (expr_418 * ((t_sample)0.3));
			t_sample mul_389 = (m_s_6 * ((t_sample)0.3));
			t_sample add_387 = (expr_418 + mul_389);
			t_sample clamp_386 = ((add_387 <= min_40) ? min_40 : ((add_387 >= ((int)1)) ? ((int)1) : add_387));
			t_sample expr_417 = (clamp_386 * (((int)1) - ((((t_sample)0.3333333) * clamp_386) * clamp_386)));
			t_sample expr_416 = ((expr_417 * expr_425) + (rsub_399 * m_s_5));
			t_sample add_382 = (expr_416 + mul_384);
			t_sample expr_415 = ((add_382 * expr_425) + (rsub_399 * m_s_4));
			t_sample add_379 = (expr_415 + mul_381);
			t_sample expr_413 = ((expr_414 * expr_423) - (expr_424 * add_379));
			t_sample maxb_41 = (((((t_sample)0.062) * expr_413) * expr_413) + (((t_sample)0.993) * expr_421));
			t_sample minb_42 = ((((int)-1) < maxb_41) ? maxb_41 : ((int)-1));
			t_sample expr_412 = ((minb_42 < ((int)1)) ? minb_42 : ((int)1));
			t_sample expr_411 = (expr_413 * ((((int)1) - expr_412) + ((((t_sample)0.5) * expr_412) * expr_412)));
			t_sample expr_410 = ((expr_411 * expr_425) + (rsub_399 * expr_419));
			t_sample add_372 = (expr_410 + mul_374);
			t_sample expr_409 = ((add_372 * expr_425) + (rsub_399 * expr_418));
			t_sample add_369 = (expr_409 + mul_371);
			t_sample clamp_368 = ((add_369 <= min_43) ? min_43 : ((add_369 >= ((int)1)) ? ((int)1) : add_369));
			t_sample expr_408 = (clamp_368 * (((int)1) - ((((t_sample)0.3333333) * clamp_368) * clamp_368)));
			t_sample expr_407 = ((expr_408 * expr_425) + (rsub_399 * expr_416));
			t_sample mul_363 = (expr_415 * ((t_sample)0.3));
			t_sample mul_366 = (expr_416 * ((t_sample)0.3));
			t_sample add_364 = (expr_407 + mul_366);
			t_sample expr_406 = ((add_364 * expr_425) + (rsub_399 * expr_415));
			t_sample add_361 = (expr_406 + mul_363);
			t_sample expr_405 = (((((t_sample)0.19) * (add_361 + m_s_9)) + (((t_sample)0.57) * (add_379 + m_s_2))) - (((t_sample)0.52) * m_s_1));
			t_sample gen_441 = expr_405;
			t_sample rc_next_430 = fixdenorm(add_398);
			t_sample previn_next_431 = fixdenorm(expr_414);
			t_sample s8_next_432 = fixdenorm(add_379);
			t_sample slim_next_433 = fixdenorm(expr_412);
			t_sample s1_next_434 = fixdenorm(expr_410);
			t_sample s2_next_435 = fixdenorm(expr_409);
			t_sample s3_next_436 = fixdenorm(expr_407);
			t_sample s4_next_437 = fixdenorm(expr_406);
			t_sample s5_next_438 = fixdenorm(add_361);
			t_sample s7_next_439 = fixdenorm(add_361);
			t_sample s6_next_440 = fixdenorm(expr_405);
			t_sample add_456 = (gen_441 + ((int)0));
			t_sample out1 = add_456;
			t_sample add_455 = (gen_441 + ((int)0));
			t_sample out2 = add_455;
			m_history_25 = history_314_next_316;
			m_history_19 = history_314_next_462;
			m_history_18 = history_327_next_329;
			m_history_16 = history_323_next_331;
			m_history_17 = history_325_next_330;
			m_history_15 = history_327_next_470;
			m_history_13 = history_323_next_471;
			m_history_14 = history_325_next_469;
			m_fc_12 = fc_next_356;
			m_s_1 = s6_next_440;
			m_s_2 = s7_next_439;
			m_s_3 = s5_next_438;
			m_s_4 = s4_next_437;
			m_s_5 = s3_next_436;
			m_s_6 = s2_next_435;
			m_s_7 = s1_next_434;
			m_slim_8 = slim_next_433;
			m_s_9 = s8_next_432;
			m_previn_10 = previn_next_431;
			m_rc_11 = rc_next_430;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			
		};
		return __exception;
		
	};
	inline void set_knob3_rate(t_param _value) {
		m_knob3_rate_20 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob1_manual(t_param _value) {
		m_knob1_manual_21 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4_res(t_param _value) {
		m_knob4_res_22 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2_depth(t_param _value) {
		m_knob2_depth_23 = (_value < -1 ? -1 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_24 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
		case 0: self->set_knob1_manual(value); break;
		case 1: self->set_knob2_depth(value); break;
		case 2: self->set_knob3_rate(value); break;
		case 3: self->set_knob4_res(value); break;
		case 4: self->set_sw1(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_knob1_manual_21; break;
		case 1: *value = self->m_knob2_depth_23; break;
		case 2: *value = self->m_knob3_rate_20; break;
		case 3: *value = self->m_knob4_res_22; break;
		case 4: *value = self->m_sw_24; break;
		
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
	// initialize parameter 0 ("m_knob1_manual_21")
	pi = self->__commonstate.params + 0;
	pi->name = "knob1_manual";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob1_manual_21;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_knob2_depth_23")
	pi = self->__commonstate.params + 1;
	pi->name = "knob2_depth";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob2_depth_23;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = -1;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_knob3_rate_20")
	pi = self->__commonstate.params + 2;
	pi->name = "knob3_rate";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob3_rate_20;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob4_res_22")
	pi = self->__commonstate.params + 3;
	pi->name = "knob4_res";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob4_res_22;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_sw_24")
	pi = self->__commonstate.params + 4;
	pi->name = "sw1";
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
	
	return self;
}

/// Release all resources and memory used by a State object:

void destroy(CommonState *cself) {
	State *self = (State *)cself;
	genlib_sysmem_freeptr(cself->params);
		
	delete self;
}


} // Wah2::
