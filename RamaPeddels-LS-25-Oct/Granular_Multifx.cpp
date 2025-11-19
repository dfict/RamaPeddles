#include "Granular_Multifx.h"

namespace Granular_Multifx {

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
	Change __m_change_83;
	Change __m_change_76;
	Data m_capture_61;
	DCBlock __m_dcblock_308;
	int __exception;
	int vectorsize;
	Phasor __m_phasor_82;
	PlusEquals __m_pluseq_141;
	PlusEquals __m_pluseq_81;
	PlusEquals __m_pluseq_154;
	PlusEquals __m_pluseq_155;
	PlusEquals __m_pluseq_168;
	PlusEquals __m_pluseq_140;
	PlusEquals __m_pluseq_127;
	PlusEquals __m_pluseq_126;
	PlusEquals __m_pluseq_169;
	PlusEquals __m_pluseq_84;
	PlusEquals __m_pluseq_77;
	PlusEquals __m_pluseq_98;
	PlusEquals __m_pluseq_112;
	PlusEquals __m_pluseq_99;
	PlusEquals __m_pluseq_113;
	PlusEquals __m_pluseq_182;
	PlusEquals __m_pluseq_196;
	PlusEquals __m_pluseq_267;
	PlusEquals __m_pluseq_266;
	PlusEquals __m_pluseq_253;
	PlusEquals __m_pluseq_280;
	PlusEquals __m_pluseq_294;
	PlusEquals __m_pluseq_281;
	PlusEquals __m_pluseq_295;
	PlusEquals __m_pluseq_183;
	PlusEquals __m_pluseq_252;
	PlusEquals __m_pluseq_238;
	PlusEquals __m_pluseq_210;
	PlusEquals __m_pluseq_197;
	PlusEquals __m_pluseq_239;
	PlusEquals __m_pluseq_211;
	PlusEquals __m_pluseq_225;
	PlusEquals __m_pluseq_224;
	PlusEquals __m_pluseq_69;
	PlusEquals __m_pluseq_85;
	Sah __m_sah_170;
	Sah __m_sah_198;
	Sah __m_sah_200;
	Sah __m_sah_100;
	Sah __m_sah_103;
	Sah __m_sah_102;
	Sah __m_sah_114;
	Sah __m_sah_89;
	Sah __m_sah_86;
	Sah __m_sah_172;
	Sah __m_sah_88;
	Sah __m_sah_212;
	Sah __m_sah_201;
	Sah __m_sah_299;
	Sah __m_sah_215;
	Sah __m_sah_116;
	Sah __m_sah_187;
	Sah __m_sah_173;
	Sah __m_sah_145;
	Sah __m_sah_156;
	Sah __m_sah_159;
	Sah __m_sah_158;
	Sah __m_sah_117;
	Sah __m_sah_144;
	Sah __m_sah_184;
	Sah __m_sah_186;
	Sah __m_sah_142;
	Sah __m_sah_128;
	Sah __m_sah_131;
	Sah __m_sah_130;
	Sah __m_sah_74;
	Sah __m_sah_214;
	Sah __m_sah_256;
	Sah __m_sah_284;
	Sah __m_sah_285;
	Sah __m_sah_243;
	Sah __m_sah_270;
	Sah __m_sah_254;
	Sah __m_sah_72;
	Sah __m_sah_282;
	Sah __m_sah_268;
	Sah __m_sah_257;
	Sah __m_sah_240;
	Sah __m_sah_242;
	Sah __m_sah_271;
	Sah __m_sah_67;
	Sah __m_sah_68;
	Sah __m_sah_226;
	Sah __m_sah_296;
	Sah __m_sah_298;
	Sah __m_sah_228;
	Sah __m_sah_229;
	t_sample m_history_6;
	t_sample m_sampmin_5;
	t_sample m_grainlen_19;
	t_sample m_history_3;
	t_sample m_history_20;
	t_sample m_buflen_4;
	t_sample m_grainlen_13;
	t_sample m_history_8;
	t_sample m_history_16;
	t_sample m_history_12;
	t_sample m_grainlen_15;
	t_sample m_history_14;
	t_sample m_grainlen_7;
	t_sample m_grainlen_11;
	t_sample m_grainlen_9;
	t_sample m_history_10;
	t_sample m_history_18;
	t_sample m_grainlen_17;
	t_sample m_history_40;
	t_sample m_history_26;
	t_sample m_history_22;
	t_sample m_footswitch_55;
	t_sample m_expression_56;
	t_sample m_knob_54;
	t_sample m_history_53;
	t_sample m_history_52;
	t_sample m_footswitch_57;
	t_sample m_knob_59;
	t_sample m_knob_58;
	t_sample samplerate;
	t_sample m_sw_60;
	t_sample m_knob_62;
	t_sample m_history_51;
	t_sample m_history_49;
	t_sample m_history_43;
	t_sample m_history_42;
	t_sample m_history_41;
	t_sample m_history_50;
	t_sample m_history_44;
	t_sample m_history_46;
	t_sample m_history_45;
	t_sample m_history_48;
	t_sample m_history_47;
	t_sample m_grainlen_21;
	t_sample m_knob_63;
	t_sample m_knob_65;
	t_sample m_history_28;
	t_sample m_grainlen_29;
	t_sample m_history_30;
	t_sample m_grainlen_31;
	t_sample m_grainlen_27;
	t_sample m_grainlen_25;
	t_sample m_history_39;
	t_sample m_grainlen_23;
	t_sample m_history_24;
	t_sample m_sw_64;
	t_sample m_history_32;
	t_sample m_grainlen_33;
	t_sample m_grainlen_37;
	t_sample m_history_38;
	t_sample m_sw_66;
	t_sample m_ampvar_1;
	t_sample m_history_36;
	t_sample m_grainlen_35;
	t_sample __m_slide_78;
	t_sample m_history_34;
	t_sample samples_to_seconds;
	t_sample m_history_2;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_ampvar_1 = ((int)0);
		m_history_2 = ((int)0);
		m_history_3 = ((int)0);
		m_buflen_4 = ((int)0);
		m_sampmin_5 = ((int)0);
		m_history_6 = ((int)0);
		m_grainlen_7 = ((int)0);
		m_history_8 = ((int)0);
		m_grainlen_9 = ((int)0);
		m_history_10 = ((int)0);
		m_grainlen_11 = ((int)0);
		m_history_12 = ((int)0);
		m_grainlen_13 = ((int)0);
		m_history_14 = ((int)0);
		m_grainlen_15 = ((int)0);
		m_history_16 = ((int)0);
		m_grainlen_17 = ((int)0);
		m_history_18 = ((int)0);
		m_grainlen_19 = ((int)0);
		m_history_20 = ((int)0);
		m_grainlen_21 = ((int)0);
		m_history_22 = ((int)0);
		m_grainlen_23 = ((int)0);
		m_history_24 = ((int)0);
		m_grainlen_25 = ((int)0);
		m_history_26 = ((int)0);
		m_grainlen_27 = ((int)0);
		m_history_28 = ((int)0);
		m_grainlen_29 = ((int)0);
		m_history_30 = ((int)0);
		m_grainlen_31 = ((int)0);
		m_history_32 = ((int)0);
		m_grainlen_33 = ((int)0);
		m_history_34 = ((int)0);
		m_grainlen_35 = ((int)0);
		m_history_36 = ((int)0);
		m_grainlen_37 = ((int)0);
		m_history_38 = ((int)0);
		m_history_39 = ((int)0);
		m_history_40 = ((int)0);
		m_history_41 = ((int)0);
		m_history_42 = ((int)0);
		m_history_43 = ((int)0);
		m_history_44 = ((int)0);
		m_history_45 = ((int)0);
		m_history_46 = ((int)0);
		m_history_47 = ((int)0);
		m_history_48 = ((int)0);
		m_history_49 = ((int)0);
		m_history_50 = ((int)0);
		m_history_51 = ((int)0);
		m_history_52 = ((int)0);
		m_history_53 = ((int)0);
		m_knob_54 = ((int)0);
		m_footswitch_55 = ((int)0);
		m_expression_56 = ((int)0);
		m_footswitch_57 = ((int)0);
		m_knob_58 = ((int)0);
		m_knob_59 = ((int)0);
		m_sw_60 = ((int)0);
		m_capture_61.reset("capture", ((int)1920000), ((int)1));
		m_knob_62 = ((int)0);
		m_knob_63 = ((int)0);
		m_sw_64 = ((int)0);
		m_knob_65 = ((int)0);
		m_sw_66 = ((int)0);
		__m_sah_67.reset(0);
		__m_sah_68.reset(0);
		__m_pluseq_69.reset(0);
		__m_sah_72.reset(0);
		__m_sah_74.reset(0);
		__m_change_76.reset(0);
		__m_pluseq_77.reset(0);
		__m_slide_78 = 0;
		__m_pluseq_81.reset(0);
		samples_to_seconds = (1 / samplerate);
		__m_phasor_82.reset(0);
		__m_change_83.reset(0);
		__m_pluseq_84.reset(0);
		__m_pluseq_85.reset(0);
		__m_sah_86.reset(0);
		__m_sah_88.reset(0);
		__m_sah_89.reset(0);
		__m_pluseq_98.reset(0);
		__m_pluseq_99.reset(0);
		__m_sah_100.reset(0);
		__m_sah_102.reset(0);
		__m_sah_103.reset(0);
		__m_pluseq_112.reset(0);
		__m_pluseq_113.reset(0);
		__m_sah_114.reset(0);
		__m_sah_116.reset(0);
		__m_sah_117.reset(0);
		__m_pluseq_126.reset(0);
		__m_pluseq_127.reset(0);
		__m_sah_128.reset(0);
		__m_sah_130.reset(0);
		__m_sah_131.reset(0);
		__m_pluseq_140.reset(0);
		__m_pluseq_141.reset(0);
		__m_sah_142.reset(0);
		__m_sah_144.reset(0);
		__m_sah_145.reset(0);
		__m_pluseq_154.reset(0);
		__m_pluseq_155.reset(0);
		__m_sah_156.reset(0);
		__m_sah_158.reset(0);
		__m_sah_159.reset(0);
		__m_pluseq_168.reset(0);
		__m_pluseq_169.reset(0);
		__m_sah_170.reset(0);
		__m_sah_172.reset(0);
		__m_sah_173.reset(0);
		__m_pluseq_182.reset(0);
		__m_pluseq_183.reset(0);
		__m_sah_184.reset(0);
		__m_sah_186.reset(0);
		__m_sah_187.reset(0);
		__m_pluseq_196.reset(0);
		__m_pluseq_197.reset(0);
		__m_sah_198.reset(0);
		__m_sah_200.reset(0);
		__m_sah_201.reset(0);
		__m_pluseq_210.reset(0);
		__m_pluseq_211.reset(0);
		__m_sah_212.reset(0);
		__m_sah_214.reset(0);
		__m_sah_215.reset(0);
		__m_pluseq_224.reset(0);
		__m_pluseq_225.reset(0);
		__m_sah_226.reset(0);
		__m_sah_228.reset(0);
		__m_sah_229.reset(0);
		__m_pluseq_238.reset(0);
		__m_pluseq_239.reset(0);
		__m_sah_240.reset(0);
		__m_sah_242.reset(0);
		__m_sah_243.reset(0);
		__m_pluseq_252.reset(0);
		__m_pluseq_253.reset(0);
		__m_sah_254.reset(0);
		__m_sah_256.reset(0);
		__m_sah_257.reset(0);
		__m_pluseq_266.reset(0);
		__m_pluseq_267.reset(0);
		__m_sah_268.reset(0);
		__m_sah_270.reset(0);
		__m_sah_271.reset(0);
		__m_pluseq_280.reset(0);
		__m_pluseq_281.reset(0);
		__m_sah_282.reset(0);
		__m_sah_284.reset(0);
		__m_sah_285.reset(0);
		__m_pluseq_294.reset(0);
		__m_pluseq_295.reset(0);
		__m_sah_296.reset(0);
		__m_sah_298.reset(0);
		__m_sah_299.reset(0);
		__m_dcblock_308.reset();
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
		t_sample * __out10 = __outs[9];
		t_sample * __out11 = __outs[10];
		if (__exception) {
			return __exception;
			
		} else if (( (__in1 == 0) || (__out1 == 0) || (__out2 == 0) || (__out3 == 0) || (__out4 == 0) || (__out5 == 0) || (__out6 == 0) || (__out7 == 0) || (__out8 == 0) || (__out9 == 0) || (__out10 == 0) || (__out11 == 0) )) {
			__exception = GENLIB_ERR_NULL_BUFFER;
			return __exception;
			
		};
		t_sample mstosamps_3123 = (((int)5) * (samplerate * 0.001));
		int capture_dim = m_capture_61.dim;
		int capture_channels = m_capture_61.channels;
		t_sample mstosamps_3179 = (((int)10) * (samplerate * 0.001));
		t_sample mstosamps_3177 = (((int)100) * (samplerate * 0.001));
		t_sample iup_79 = (1 / maximum(1, abs(mstosamps_3179)));
		t_sample idown_80 = (1 / maximum(1, abs(mstosamps_3177)));
		samples_to_seconds = (1 / samplerate);
		t_sample sampmin_next_4883 = fixdenorm(mstosamps_3123);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out11 = ((int)0);
			t_sample out6 = ((int)0);
			t_sample out10 = ((int)0);
			t_sample sah_3041 = __m_sah_67(m_history_53, m_sw_64, ((int)0));
			t_sample gen_3044 = sah_3041;
			t_sample rsub_3039 = (((int)1) - sah_3041);
			t_sample history_3040_next_3042 = fixdenorm(rsub_3039);
			t_sample sah_4240 = __m_sah_68(m_history_52, m_sw_64, ((int)0));
			t_sample gen_4243 = sah_4240;
			t_sample rsub_4238 = (((int)1) - sah_4240);
			t_sample history_4239_next_4241 = fixdenorm(rsub_4238);
			t_sample out5 = (gen_4243 + gen_3044);
			t_sample mix_5164 = (m_history_51 + (((t_sample)0.0042742627044161) * (m_knob_63 - m_history_51)));
			t_sample mix_3214 = mix_5164;
			t_sample mix_5165 = (m_history_50 + (((t_sample)0.0042742627044161) * (mix_3214 - m_history_50)));
			t_sample mix_3212 = mix_5165;
			t_sample mix_5166 = (m_history_49 + (((t_sample)0.0042742627044161) * (mix_3212 - m_history_49)));
			t_sample mix_3210 = mix_5166;
			t_sample gen_3220 = mix_3210;
			t_sample history_3215_next_3217 = fixdenorm(mix_3214);
			t_sample history_3213_next_3218 = fixdenorm(mix_3212);
			t_sample history_3211_next_3219 = fixdenorm(mix_3210);
			t_sample p_3166 = gen_3220;
			t_sample expr_4245 = (((int)1) - sqrt((((int)1) - p_3166)));
			t_sample mul_3167 = (expr_4245 * ((int)1920000));
			t_sample noise_3115 = noise();
			t_sample mix_5167 = (noise_3115 + (((t_sample)0.999) * (m_history_3 - noise_3115)));
			t_sample mix_3110 = mix_5167;
			t_sample plusequals_3181 = __m_pluseq_69.post(((int)1), m_history_2, 0);
			t_sample switch_3164 = (m_footswitch_57 ? ((int)-1) : plusequals_3181);
			int index_trunc_70 = fixnan(floor(switch_3164));
			bool index_ignore_71 = ((index_trunc_70 >= capture_dim) || (index_trunc_70 < 0));
			if ((!index_ignore_71)) {
				m_capture_61.write(in1, index_trunc_70, 0);
				
			};
			int gte_3170 = (plusequals_3181 >= m_buflen_4);
			int eq_3169 = (gte_3170 == ((int)1));
			t_sample sah_4250 = __m_sah_72(m_history_48, m_sw_64, ((int)0));
			t_sample gen_3043 = sah_4250;
			t_sample rsub_4252 = (((int)1) - sah_4250);
			t_sample history_3040_next_4251 = fixdenorm(rsub_4252);
			t_sample add_3036 = (gen_3043 + ((int)1));
			t_sample choice_73 = int(add_3036);
			t_sample gate_3037 = (((choice_73 >= 1) && (choice_73 < 2)) ? ((int)1) : 0);
			t_sample gate_3038 = ((choice_73 >= 2) ? ((int)1) : 0);
			t_sample sah_4256 = __m_sah_74(m_history_47, m_sw_64, ((int)0));
			t_sample gen_4242 = sah_4256;
			t_sample rsub_4254 = (((int)1) - sah_4256);
			t_sample history_4239_next_4257 = fixdenorm(rsub_4254);
			t_sample add_4235 = (gen_4242 + ((int)1));
			t_sample choice_75 = int(add_4235);
			t_sample gate_4236 = (((choice_75 >= 1) && (choice_75 < 2)) ? ((int)1) : 0);
			t_sample gate_4237 = ((choice_75 >= 2) ? ((int)1) : 0);
			int change_3227 = __m_change_76(m_footswitch_55);
			int clamp_3226 = ((change_3227 <= ((int)0)) ? ((int)0) : ((change_3227 >= ((int)1)) ? ((int)1) : change_3227));
			int plusequals_3228 = __m_pluseq_77.post(clamp_3226, ((int)0), 0, 2);
			t_sample out9 = plusequals_3228;
			int rsub_3223 = (((int)1) - plusequals_3228);
			t_sample out8 = rsub_3223;
			t_sample abs_3182 = fabs(in1);
			t_sample mul_3134 = (abs_3182 * ((int)30));
			__m_slide_78 = fixdenorm((__m_slide_78 + (((mul_3134 > __m_slide_78) ? iup_79 : idown_80) * (mul_3134 - __m_slide_78))));
			t_sample slide_3180 = __m_slide_78;
			t_sample clamp_3175 = ((slide_3180 <= ((int)0)) ? ((int)0) : ((slide_3180 >= ((int)1)) ? ((int)1) : slide_3180));
			t_sample out7 = clamp_3175;
			int plusequals_3190 = __m_pluseq_81.post(((int)0), ((int)0), 0, 9);
			int add_3189 = (plusequals_3190 + ((int)1));
			int pgm_3188 = add_3189;
			t_sample r = ((int)0);
			t_sample g = ((int)0);
			t_sample b = ((int)0);
			if ((pgm_3188 == ((int)1))) {
				r = ((int)1);
				g = ((int)0);
				b = ((int)0);
				
			} else {
				if ((pgm_3188 == ((int)2))) {
					r = ((int)1);
					g = ((t_sample)0.5);
					b = ((int)0);
					
				} else {
					if ((pgm_3188 == ((int)3))) {
						r = ((t_sample)0.5);
						g = ((int)1);
						b = ((int)0);
						
					} else {
						if ((pgm_3188 == ((int)4))) {
							r = ((int)0);
							g = ((int)1);
							b = ((int)0);
							
						} else {
							if ((pgm_3188 == ((int)5))) {
								r = ((int)0);
								g = ((int)1);
								b = ((t_sample)0.5);
								
							} else {
								if ((pgm_3188 == ((int)6))) {
									r = ((int)1);
									g = ((t_sample)0.5);
									b = ((int)1);
									
								} else {
									if ((pgm_3188 == ((int)7))) {
										r = ((int)0);
										g = ((int)0);
										b = ((int)1);
										
									} else {
										if ((pgm_3188 == ((int)8))) {
											r = ((t_sample)0.5);
											g = ((int)0);
											b = ((int)1);
											
										} else {
											if ((pgm_3188 == ((int)9))) {
												r = ((int)1);
												g = ((int)0);
												b = ((int)1);
												
											};
											
										};
										
									};
									
								};
								
							};
							
						};
						
					};
					
				};
				
			};
			t_sample out3 = ((gate_4236 + gate_3037) + b);
			t_sample out4 = ((gate_4237 + gate_3038) + g);
			t_sample out2 = r;
			t_sample mix_5168 = (m_history_46 + (((t_sample)0.0042742627044161) * (m_knob_65 - m_history_46)));
			t_sample mix_4263 = mix_5168;
			t_sample mix_5169 = (m_history_45 + (((t_sample)0.0042742627044161) * (mix_4263 - m_history_45)));
			t_sample mix_4267 = mix_5169;
			t_sample mix_5170 = (m_history_44 + (((t_sample)0.0042742627044161) * (mix_4267 - m_history_44)));
			t_sample mix_4262 = mix_5170;
			t_sample gen_3225 = mix_4262;
			t_sample history_3215_next_4261 = fixdenorm(mix_4263);
			t_sample history_3213_next_4266 = fixdenorm(mix_4267);
			t_sample history_3211_next_4265 = fixdenorm(mix_4262);
			t_sample p_3154 = gen_3225;
			t_sample mul_3105 = (p_3154 * ((int)2));
			t_sample fold_3104 = fold(mul_3105, ((int)0), ((int)1));
			t_sample rsub_3109 = (((int)1) - fold_3104);
			t_sample expr_4244 = (((int)1) - sqrt((((int)1) - rsub_3109)));
			t_sample mix_5171 = (m_history_43 + (((t_sample)0.0042742627044161) * (m_knob_54 - m_history_43)));
			t_sample mix_4273 = mix_5171;
			t_sample mix_5172 = (m_history_42 + (((t_sample)0.0042742627044161) * (mix_4273 - m_history_42)));
			t_sample mix_4280 = mix_5172;
			t_sample mix_5173 = (m_history_41 + (((t_sample)0.0042742627044161) * (mix_4280 - m_history_41)));
			t_sample mix_4277 = mix_5173;
			t_sample gen_3222 = mix_4277;
			t_sample history_3215_next_4275 = fixdenorm(mix_4273);
			t_sample history_3213_next_4279 = fixdenorm(mix_4280);
			t_sample history_3211_next_4276 = fixdenorm(mix_4277);
			t_sample p_3130 = gen_3222;
			t_sample mul_3097 = (p_3130 * ((int)2));
			t_sample sub_5177 = (mul_3097 - ((int)0));
			t_sample scale_5174 = ((safepow((sub_5177 * ((t_sample)1)), ((int)1)) * ((int)-1)) + ((int)1));
			t_sample scale_3095 = scale_5174;
			t_sample clamp_3094 = ((scale_3095 <= ((int)0)) ? ((int)0) : ((scale_3095 >= ((int)1)) ? ((int)1) : scale_3095));
			t_sample fold_3096 = fold(mul_3097, ((int)0), ((int)1));
			t_sample sqrt_3127 = sqrt(fold_3096);
			t_sample rsub_3132 = (((int)1) - fold_3096);
			t_sample sqrt_3131 = sqrt(rsub_3132);
			t_sample mul_3129 = (sqrt_3131 * in1);
			t_sample noise_3107 = noise();
			t_sample abs_3100 = fabs(noise_3107);
			t_sample sub_5181 = (mul_3105 - ((int)0));
			t_sample scale_5178 = ((safepow((sub_5181 * ((t_sample)1)), ((int)1)) * ((int)-1)) + ((int)1));
			t_sample scale_3102 = scale_5178;
			t_sample clamp_3101 = ((scale_3102 <= ((int)0)) ? ((int)0) : ((scale_3102 >= ((int)1)) ? ((int)1) : scale_3102));
			t_sample mul_3103 = (expr_4244 * clamp_3101);
			t_sample mul_3108 = (abs_3100 * mul_3103);
			t_sample sub_3106 = (expr_4244 - mul_3108);
			t_sample mul_3125 = (mul_3167 * sub_3106);
			t_sample clamp_3153 = ((mul_3125 <= m_sampmin_5) ? m_sampmin_5 : ((mul_3125 >= ((int)1920000)) ? ((int)1920000) : mul_3125));
			t_sample mix_5182 = (m_history_40 + (((t_sample)0.0042742627044161) * (m_knob_59 - m_history_40)));
			t_sample mix_4288 = mix_5182;
			t_sample mix_5183 = (m_history_39 + (((t_sample)0.0042742627044161) * (mix_4288 - m_history_39)));
			t_sample mix_4292 = mix_5183;
			t_sample mix_5184 = (m_history_38 + (((t_sample)0.0042742627044161) * (mix_4292 - m_history_38)));
			t_sample mix_4290 = mix_5184;
			t_sample gen_3229 = mix_4290;
			t_sample history_3215_next_4286 = fixdenorm(mix_4288);
			t_sample history_3213_next_4291 = fixdenorm(mix_4292);
			t_sample history_3211_next_4293 = fixdenorm(mix_4290);
			t_sample p_3152 = gen_3229;
			t_sample mul_3113 = (p_3152 * ((int)2));
			t_sample fold_3112 = fold(mul_3113, ((int)0), ((int)1));
			t_sample sub_5188 = (fold_3112 - ((int)0));
			t_sample scale_5185 = ((safepow((sub_5188 * ((t_sample)1)), ((int)1)) * ((int)-14)) + ((int)15));
			t_sample scale_3133 = scale_5185;
			int lt_3111 = (mul_3113 < ((int)1));
			int mul_3045 = (lt_3111 * ((int)500));
			t_sample mul_3116 = (mix_3110 * mul_3045);
			t_sample add_3114 = (scale_3133 + mul_3116);
			t_sample phasor_3121 = __m_phasor_82(add_3114, samples_to_seconds);
			int gt_3120 = (phasor_3121 > ((t_sample)0.5));
			int change_3118 = __m_change_83(gt_3120);
			int eq_3119 = (change_3118 == ((int)1));
			t_sample plusequals_3050 = __m_pluseq_84.post(m_history_36, ((int)0), 0, 4);
			t_sample add_3049 = (plusequals_3050 + ((int)1));
			t_sample plusequals_3078 = __m_pluseq_85.post(add_3049, m_history_36, 0);
			t_sample sub_3066 = (m_grainlen_37 - m_sampmin_5);
			t_sample noise_3074 = noise();
			t_sample abs_3073 = fabs(noise_3074);
			t_sample mul_3072 = (abs_3073 * sub_3066);
			t_sample sah_3075 = __m_sah_86(mul_3072, m_history_36, ((t_sample)0.5));
			t_sample add_3063 = (sah_3075 + m_sampmin_5);
			t_sample div_3069 = safediv(plusequals_3078, add_3063);
			t_sample clamp_3058 = ((div_3069 <= ((int)0)) ? ((int)0) : ((div_3069 >= ((int)1)) ? ((int)1) : div_3069));
			t_sample expr_3084 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_3058))));
			int lt_3062 = (plusequals_3078 < add_3063);
			int add_3059 = (lt_3062 + ((int)1));
			int choice_87 = add_3059;
			int gate_3060 = (((choice_87 >= 1) && (choice_87 < 2)) ? eq_3119 : 0);
			int gate_3061 = ((choice_87 >= 2) ? eq_3119 : 0);
			int gen_3162 = gate_3061;
			t_sample noise_3057 = noise();
			t_sample abs_3056 = fabs(noise_3057);
			t_sample sah_3055 = __m_sah_88(abs_3056, m_history_36, ((t_sample)0.5));
			t_sample mul_3054 = (sah_3055 * m_ampvar_1);
			t_sample rsub_3053 = (((int)1) - mul_3054);
			t_sample sqrt_3051 = sqrt(rsub_3053);
			t_sample noise_3081 = noise();
			t_sample abs_3080 = fabs(noise_3081);
			t_sample mul_3079 = (abs_3080 * m_buflen_4);
			t_sample sah_3082 = __m_sah_89(mul_3079, m_history_36, ((t_sample)0.5));
			t_sample add_3077 = (sah_3082 + plusequals_3078);
			t_sample mod_3076 = safemod(add_3077, m_buflen_4);
			t_sample switch_3064 = (lt_3062 ? mod_3076 : ((int)-1));
			int index_trunc_90 = fixnan(floor(switch_3064));
			double index_fract_91 = (switch_3064 - index_trunc_90);
			int index_trunc_92 = (index_trunc_90 + 1);
			bool index_ignore_93 = ((index_trunc_90 >= capture_dim) || (index_trunc_90 < 0));
			bool index_ignore_94 = ((index_trunc_92 >= capture_dim) || (index_trunc_92 < 0));
			// samples capture channel 1;
			double read_capture_95 = (index_ignore_93 ? 0 : m_capture_61.read(index_trunc_90, 0));
			double read_capture_96 = (index_ignore_94 ? 0 : m_capture_61.read(index_trunc_92, 0));
			double readinterp_97 = linear_interp(index_fract_91, read_capture_95, read_capture_96);
			t_sample sample_capture_3070 = readinterp_97;
			t_sample index_capture_3071 = switch_3064;
			t_sample mul_3067 = (sample_capture_3070 * expr_3084);
			t_sample mul_3052 = (mul_3067 * sqrt_3051);
			t_sample history_3083_next_3085 = fixdenorm(gate_3060);
			t_sample plusequals_4329 = __m_pluseq_98.post(m_history_34, ((int)0), 0, 4);
			t_sample add_4306 = (plusequals_4329 + ((int)1));
			t_sample plusequals_4328 = __m_pluseq_99.post(add_4306, m_history_34, 0);
			t_sample sub_4327 = (m_grainlen_35 - m_sampmin_5);
			t_sample noise_4326 = noise();
			t_sample abs_4332 = fabs(noise_4326);
			t_sample mul_4325 = (abs_4332 * sub_4327);
			t_sample sah_4298 = __m_sah_100(mul_4325, m_history_34, ((t_sample)0.5));
			t_sample add_4324 = (sah_4298 + m_sampmin_5);
			t_sample div_4323 = safediv(plusequals_4328, add_4324);
			t_sample clamp_4300 = ((div_4323 <= ((int)0)) ? ((int)0) : ((div_4323 >= ((int)1)) ? ((int)1) : div_4323));
			t_sample expr_4322 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_4300))));
			int lt_4321 = (plusequals_4328 < add_4324);
			int add_4320 = (lt_4321 + ((int)1));
			int choice_101 = add_4320;
			int gate_4301 = (((choice_101 >= 1) && (choice_101 < 2)) ? gen_3162 : 0);
			int gate_4319 = ((choice_101 >= 2) ? gen_3162 : 0);
			int gen_3160 = gate_4319;
			t_sample noise_4307 = noise();
			t_sample abs_4318 = fabs(noise_4307);
			t_sample sah_4317 = __m_sah_102(abs_4318, m_history_34, ((t_sample)0.5));
			t_sample mul_4331 = (sah_4317 * m_ampvar_1);
			t_sample rsub_4316 = (((int)1) - mul_4331);
			t_sample sqrt_4315 = sqrt(rsub_4316);
			t_sample noise_4313 = noise();
			t_sample abs_4312 = fabs(noise_4313);
			t_sample mul_4330 = (abs_4312 * m_buflen_4);
			t_sample sah_4304 = __m_sah_103(mul_4330, m_history_34, ((t_sample)0.5));
			t_sample add_4303 = (sah_4304 + plusequals_4328);
			t_sample mod_4311 = safemod(add_4303, m_buflen_4);
			t_sample switch_4310 = (lt_4321 ? mod_4311 : ((int)-1));
			int index_trunc_104 = fixnan(floor(switch_4310));
			double index_fract_105 = (switch_4310 - index_trunc_104);
			int index_trunc_106 = (index_trunc_104 + 1);
			bool index_ignore_107 = ((index_trunc_104 >= capture_dim) || (index_trunc_104 < 0));
			bool index_ignore_108 = ((index_trunc_106 >= capture_dim) || (index_trunc_106 < 0));
			// samples capture channel 1;
			double read_capture_109 = (index_ignore_107 ? 0 : m_capture_61.read(index_trunc_104, 0));
			double read_capture_110 = (index_ignore_108 ? 0 : m_capture_61.read(index_trunc_106, 0));
			double readinterp_111 = linear_interp(index_fract_105, read_capture_109, read_capture_110);
			t_sample sample_capture_4305 = readinterp_111;
			t_sample index_capture_4333 = switch_4310;
			t_sample mul_4334 = (sample_capture_4305 * expr_4322);
			t_sample mul_4299 = (mul_4334 * sqrt_4315);
			t_sample history_3083_next_4309 = fixdenorm(gate_4301);
			t_sample plusequals_4368 = __m_pluseq_112.post(m_history_32, ((int)0), 0, 4);
			t_sample add_4346 = (plusequals_4368 + ((int)1));
			t_sample plusequals_4367 = __m_pluseq_113.post(add_4346, m_history_32, 0);
			t_sample sub_4366 = (m_grainlen_33 - m_sampmin_5);
			t_sample noise_4365 = noise();
			t_sample abs_4371 = fabs(noise_4365);
			t_sample mul_4364 = (abs_4371 * sub_4366);
			t_sample sah_4337 = __m_sah_114(mul_4364, m_history_32, ((t_sample)0.5));
			t_sample add_4363 = (sah_4337 + m_sampmin_5);
			t_sample div_4362 = safediv(plusequals_4367, add_4363);
			t_sample clamp_4339 = ((div_4362 <= ((int)0)) ? ((int)0) : ((div_4362 >= ((int)1)) ? ((int)1) : div_4362));
			t_sample expr_4361 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_4339))));
			int lt_4350 = (plusequals_4367 < add_4363);
			int add_4360 = (lt_4350 + ((int)1));
			int choice_115 = add_4360;
			int gate_4340 = (((choice_115 >= 1) && (choice_115 < 2)) ? gen_3160 : 0);
			int gate_4345 = ((choice_115 >= 2) ? gen_3160 : 0);
			int gen_3158 = gate_4345;
			t_sample noise_4348 = noise();
			t_sample abs_4359 = fabs(noise_4348);
			t_sample sah_4358 = __m_sah_116(abs_4359, m_history_32, ((t_sample)0.5));
			t_sample mul_4370 = (sah_4358 * m_ampvar_1);
			t_sample rsub_4356 = (((int)1) - mul_4370);
			t_sample sqrt_4355 = sqrt(rsub_4356);
			t_sample noise_4347 = noise();
			t_sample abs_4354 = fabs(noise_4347);
			t_sample mul_4369 = (abs_4354 * m_buflen_4);
			t_sample sah_4343 = __m_sah_117(mul_4369, m_history_32, ((t_sample)0.5));
			t_sample add_4342 = (sah_4343 + plusequals_4367);
			t_sample mod_4353 = safemod(add_4342, m_buflen_4);
			t_sample switch_4352 = (lt_4350 ? mod_4353 : ((int)-1));
			int index_trunc_118 = fixnan(floor(switch_4352));
			double index_fract_119 = (switch_4352 - index_trunc_118);
			int index_trunc_120 = (index_trunc_118 + 1);
			bool index_ignore_121 = ((index_trunc_118 >= capture_dim) || (index_trunc_118 < 0));
			bool index_ignore_122 = ((index_trunc_120 >= capture_dim) || (index_trunc_120 < 0));
			// samples capture channel 1;
			double read_capture_123 = (index_ignore_121 ? 0 : m_capture_61.read(index_trunc_118, 0));
			double read_capture_124 = (index_ignore_122 ? 0 : m_capture_61.read(index_trunc_120, 0));
			double readinterp_125 = linear_interp(index_fract_119, read_capture_123, read_capture_124);
			t_sample sample_capture_4344 = readinterp_125;
			t_sample index_capture_4372 = switch_4352;
			t_sample mul_4373 = (sample_capture_4344 * expr_4361);
			t_sample mul_4338 = (mul_4373 * sqrt_4355);
			t_sample history_3083_next_4351 = fixdenorm(gate_4340);
			t_sample plusequals_4383 = __m_pluseq_126.post(m_history_30, ((int)0), 0, 4);
			t_sample add_4381 = (plusequals_4383 + ((int)1));
			t_sample plusequals_4384 = __m_pluseq_127.post(add_4381, m_history_30, 0);
			t_sample sub_4411 = (m_grainlen_31 - m_sampmin_5);
			t_sample noise_4400 = noise();
			t_sample abs_4409 = fabs(noise_4400);
			t_sample mul_4386 = (abs_4409 * sub_4411);
			t_sample sah_4376 = __m_sah_128(mul_4386, m_history_30, ((t_sample)0.5));
			t_sample add_4398 = (sah_4376 + m_sampmin_5);
			t_sample div_4397 = safediv(plusequals_4384, add_4398);
			t_sample clamp_4377 = ((div_4397 <= ((int)0)) ? ((int)0) : ((div_4397 >= ((int)1)) ? ((int)1) : div_4397));
			t_sample expr_4385 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_4377))));
			int lt_4391 = (plusequals_4384 < add_4398);
			int add_4407 = (lt_4391 + ((int)1));
			int choice_129 = add_4407;
			int gate_4393 = (((choice_129 >= 1) && (choice_129 < 2)) ? gen_3158 : 0);
			int gate_4405 = ((choice_129 >= 2) ? gen_3158 : 0);
			int gen_3156 = gate_4405;
			t_sample noise_4399 = noise();
			t_sample abs_4408 = fabs(noise_4399);
			t_sample sah_4410 = __m_sah_130(abs_4408, m_history_30, ((t_sample)0.5));
			t_sample mul_4388 = (sah_4410 * m_ampvar_1);
			t_sample rsub_4396 = (((int)1) - mul_4388);
			t_sample sqrt_4403 = sqrt(rsub_4396);
			t_sample noise_4404 = noise();
			t_sample abs_4389 = fabs(noise_4404);
			t_sample mul_4387 = (abs_4389 * m_buflen_4);
			t_sample sah_4379 = __m_sah_131(mul_4387, m_history_30, ((t_sample)0.5));
			t_sample add_4378 = (sah_4379 + plusequals_4384);
			t_sample mod_4406 = safemod(add_4378, m_buflen_4);
			t_sample switch_4401 = (lt_4391 ? mod_4406 : ((int)-1));
			int index_trunc_132 = fixnan(floor(switch_4401));
			double index_fract_133 = (switch_4401 - index_trunc_132);
			int index_trunc_134 = (index_trunc_132 + 1);
			bool index_ignore_135 = ((index_trunc_132 >= capture_dim) || (index_trunc_132 < 0));
			bool index_ignore_136 = ((index_trunc_134 >= capture_dim) || (index_trunc_134 < 0));
			// samples capture channel 1;
			double read_capture_137 = (index_ignore_135 ? 0 : m_capture_61.read(index_trunc_132, 0));
			double read_capture_138 = (index_ignore_136 ? 0 : m_capture_61.read(index_trunc_134, 0));
			double readinterp_139 = linear_interp(index_fract_133, read_capture_137, read_capture_138);
			t_sample sample_capture_4380 = readinterp_139;
			t_sample index_capture_4412 = switch_4401;
			t_sample mul_4390 = (sample_capture_4380 * expr_4385);
			t_sample mul_4392 = (mul_4390 * sqrt_4403);
			t_sample history_3083_next_4394 = fixdenorm(gate_4393);
			t_sample plusequals_4423 = __m_pluseq_140.post(m_history_28, ((int)0), 0, 4);
			t_sample add_4421 = (plusequals_4423 + ((int)1));
			t_sample plusequals_4424 = __m_pluseq_141.post(add_4421, m_history_28, 0);
			t_sample sub_4450 = (m_grainlen_29 - m_sampmin_5);
			t_sample noise_4440 = noise();
			t_sample abs_4446 = fabs(noise_4440);
			t_sample mul_4426 = (abs_4446 * sub_4450);
			t_sample sah_4415 = __m_sah_142(mul_4426, m_history_28, ((t_sample)0.5));
			t_sample add_4438 = (sah_4415 + m_sampmin_5);
			t_sample div_4437 = safediv(plusequals_4424, add_4438);
			t_sample clamp_4416 = ((div_4437 <= ((int)0)) ? ((int)0) : ((div_4437 >= ((int)1)) ? ((int)1) : div_4437));
			t_sample expr_4425 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_4416))));
			int lt_4431 = (plusequals_4424 < add_4438);
			int add_4449 = (lt_4431 + ((int)1));
			int choice_143 = add_4449;
			int gate_4433 = (((choice_143 >= 1) && (choice_143 < 2)) ? gen_3156 : 0);
			int gate_4444 = ((choice_143 >= 2) ? gen_3156 : 0);
			int gen_3151 = gate_4444;
			t_sample noise_4439 = noise();
			t_sample abs_4448 = fabs(noise_4439);
			t_sample sah_4447 = __m_sah_144(abs_4448, m_history_28, ((t_sample)0.5));
			t_sample mul_4428 = (sah_4447 * m_ampvar_1);
			t_sample rsub_4436 = (((int)1) - mul_4428);
			t_sample sqrt_4443 = sqrt(rsub_4436);
			t_sample noise_4418 = noise();
			t_sample abs_4429 = fabs(noise_4418);
			t_sample mul_4427 = (abs_4429 * m_buflen_4);
			t_sample sah_4419 = __m_sah_145(mul_4427, m_history_28, ((t_sample)0.5));
			t_sample add_4417 = (sah_4419 + plusequals_4424);
			t_sample mod_4445 = safemod(add_4417, m_buflen_4);
			t_sample switch_4441 = (lt_4431 ? mod_4445 : ((int)-1));
			int index_trunc_146 = fixnan(floor(switch_4441));
			double index_fract_147 = (switch_4441 - index_trunc_146);
			int index_trunc_148 = (index_trunc_146 + 1);
			bool index_ignore_149 = ((index_trunc_146 >= capture_dim) || (index_trunc_146 < 0));
			bool index_ignore_150 = ((index_trunc_148 >= capture_dim) || (index_trunc_148 < 0));
			// samples capture channel 1;
			double read_capture_151 = (index_ignore_149 ? 0 : m_capture_61.read(index_trunc_146, 0));
			double read_capture_152 = (index_ignore_150 ? 0 : m_capture_61.read(index_trunc_148, 0));
			double readinterp_153 = linear_interp(index_fract_147, read_capture_151, read_capture_152);
			t_sample sample_capture_4420 = readinterp_153;
			t_sample index_capture_4451 = switch_4441;
			t_sample mul_4430 = (sample_capture_4420 * expr_4425);
			t_sample mul_4432 = (mul_4430 * sqrt_4443);
			t_sample history_3083_next_4434 = fixdenorm(gate_4433);
			t_sample plusequals_4462 = __m_pluseq_154.post(m_history_26, ((int)0), 0, 4);
			t_sample add_4460 = (plusequals_4462 + ((int)1));
			t_sample plusequals_4463 = __m_pluseq_155.post(add_4460, m_history_26, 0);
			t_sample sub_4489 = (m_grainlen_27 - m_sampmin_5);
			t_sample noise_4477 = noise();
			t_sample abs_4486 = fabs(noise_4477);
			t_sample mul_4488 = (abs_4486 * sub_4489);
			t_sample sah_4454 = __m_sah_156(mul_4488, m_history_26, ((t_sample)0.5));
			t_sample add_4484 = (sah_4454 + m_sampmin_5);
			t_sample div_4483 = safediv(plusequals_4463, add_4484);
			t_sample clamp_4455 = ((div_4483 <= ((int)0)) ? ((int)0) : ((div_4483 >= ((int)1)) ? ((int)1) : div_4483));
			t_sample expr_4464 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_4455))));
			int lt_4469 = (plusequals_4463 < add_4484);
			int add_4473 = (lt_4469 + ((int)1));
			int choice_157 = add_4473;
			int gate_4471 = (((choice_157 >= 1) && (choice_157 < 2)) ? gen_3151 : 0);
			int gate_4482 = ((choice_157 >= 2) ? gen_3151 : 0);
			int gen_3149 = gate_4482;
			t_sample noise_4476 = noise();
			t_sample abs_4485 = fabs(noise_4476);
			t_sample sah_4487 = __m_sah_158(abs_4485, m_history_26, ((t_sample)0.5));
			t_sample mul_4466 = (sah_4487 * m_ampvar_1);
			t_sample rsub_4475 = (((int)1) - mul_4466);
			t_sample sqrt_4481 = sqrt(rsub_4475);
			t_sample noise_4457 = noise();
			t_sample abs_4467 = fabs(noise_4457);
			t_sample mul_4465 = (abs_4467 * m_buflen_4);
			t_sample sah_4458 = __m_sah_159(mul_4465, m_history_26, ((t_sample)0.5));
			t_sample add_4456 = (sah_4458 + plusequals_4463);
			t_sample mod_4478 = safemod(add_4456, m_buflen_4);
			t_sample switch_4479 = (lt_4469 ? mod_4478 : ((int)-1));
			int index_trunc_160 = fixnan(floor(switch_4479));
			double index_fract_161 = (switch_4479 - index_trunc_160);
			int index_trunc_162 = (index_trunc_160 + 1);
			bool index_ignore_163 = ((index_trunc_160 >= capture_dim) || (index_trunc_160 < 0));
			bool index_ignore_164 = ((index_trunc_162 >= capture_dim) || (index_trunc_162 < 0));
			// samples capture channel 1;
			double read_capture_165 = (index_ignore_163 ? 0 : m_capture_61.read(index_trunc_160, 0));
			double read_capture_166 = (index_ignore_164 ? 0 : m_capture_61.read(index_trunc_162, 0));
			double readinterp_167 = linear_interp(index_fract_161, read_capture_165, read_capture_166);
			t_sample sample_capture_4459 = readinterp_167;
			t_sample index_capture_4490 = switch_4479;
			t_sample mul_4468 = (sample_capture_4459 * expr_4464);
			t_sample mul_4470 = (mul_4468 * sqrt_4481);
			t_sample history_3083_next_4472 = fixdenorm(gate_4471);
			t_sample plusequals_4501 = __m_pluseq_168.post(m_history_24, ((int)0), 0, 4);
			t_sample add_4499 = (plusequals_4501 + ((int)1));
			t_sample plusequals_4502 = __m_pluseq_169.post(add_4499, m_history_24, 0);
			t_sample sub_4528 = (m_grainlen_25 - m_sampmin_5);
			t_sample noise_4517 = noise();
			t_sample abs_4525 = fabs(noise_4517);
			t_sample mul_4523 = (abs_4525 * sub_4528);
			t_sample sah_4493 = __m_sah_170(mul_4523, m_history_24, ((t_sample)0.5));
			t_sample add_4521 = (sah_4493 + m_sampmin_5);
			t_sample div_4515 = safediv(plusequals_4502, add_4521);
			t_sample clamp_4494 = ((div_4515 <= ((int)0)) ? ((int)0) : ((div_4515 >= ((int)1)) ? ((int)1) : div_4515));
			t_sample expr_4503 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_4494))));
			int lt_4508 = (plusequals_4502 < add_4521);
			int add_4527 = (lt_4508 + ((int)1));
			int choice_171 = add_4527;
			int gate_4510 = (((choice_171 >= 1) && (choice_171 < 2)) ? gen_3149 : 0);
			int gate_4522 = ((choice_171 >= 2) ? gen_3149 : 0);
			int gen_3147 = gate_4522;
			t_sample noise_4516 = noise();
			t_sample abs_4512 = fabs(noise_4516);
			t_sample sah_4526 = __m_sah_172(abs_4512, m_history_24, ((t_sample)0.5));
			t_sample mul_4505 = (sah_4526 * m_ampvar_1);
			t_sample rsub_4514 = (((int)1) - mul_4505);
			t_sample sqrt_4520 = sqrt(rsub_4514);
			t_sample noise_4496 = noise();
			t_sample abs_4506 = fabs(noise_4496);
			t_sample mul_4504 = (abs_4506 * m_buflen_4);
			t_sample sah_4497 = __m_sah_173(mul_4504, m_history_24, ((t_sample)0.5));
			t_sample add_4495 = (sah_4497 + plusequals_4502);
			t_sample mod_4524 = safemod(add_4495, m_buflen_4);
			t_sample switch_4518 = (lt_4508 ? mod_4524 : ((int)-1));
			int index_trunc_174 = fixnan(floor(switch_4518));
			double index_fract_175 = (switch_4518 - index_trunc_174);
			int index_trunc_176 = (index_trunc_174 + 1);
			bool index_ignore_177 = ((index_trunc_174 >= capture_dim) || (index_trunc_174 < 0));
			bool index_ignore_178 = ((index_trunc_176 >= capture_dim) || (index_trunc_176 < 0));
			// samples capture channel 1;
			double read_capture_179 = (index_ignore_177 ? 0 : m_capture_61.read(index_trunc_174, 0));
			double read_capture_180 = (index_ignore_178 ? 0 : m_capture_61.read(index_trunc_176, 0));
			double readinterp_181 = linear_interp(index_fract_175, read_capture_179, read_capture_180);
			t_sample sample_capture_4498 = readinterp_181;
			t_sample index_capture_4529 = switch_4518;
			t_sample mul_4507 = (sample_capture_4498 * expr_4503);
			t_sample mul_4509 = (mul_4507 * sqrt_4520);
			t_sample history_3083_next_4511 = fixdenorm(gate_4510);
			t_sample plusequals_4540 = __m_pluseq_182.post(m_history_22, ((int)0), 0, 4);
			t_sample add_4538 = (plusequals_4540 + ((int)1));
			t_sample plusequals_4541 = __m_pluseq_183.post(add_4538, m_history_22, 0);
			t_sample sub_4568 = (m_grainlen_23 - m_sampmin_5);
			t_sample noise_4557 = noise();
			t_sample abs_4565 = fabs(noise_4557);
			t_sample mul_4567 = (abs_4565 * sub_4568);
			t_sample sah_4532 = __m_sah_184(mul_4567, m_history_22, ((t_sample)0.5));
			t_sample add_4555 = (sah_4532 + m_sampmin_5);
			t_sample div_4563 = safediv(plusequals_4541, add_4555);
			t_sample clamp_4533 = ((div_4563 <= ((int)0)) ? ((int)0) : ((div_4563 >= ((int)1)) ? ((int)1) : div_4563));
			t_sample expr_4542 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_4533))));
			int lt_4547 = (plusequals_4541 < add_4555);
			int add_4552 = (lt_4547 + ((int)1));
			int choice_185 = add_4552;
			int gate_4550 = (((choice_185 >= 1) && (choice_185 < 2)) ? gen_3147 : 0);
			int gate_4562 = ((choice_185 >= 2) ? gen_3147 : 0);
			int gen_3145 = gate_4562;
			t_sample noise_4556 = noise();
			t_sample abs_4566 = fabs(noise_4556);
			t_sample sah_4564 = __m_sah_186(abs_4566, m_history_22, ((t_sample)0.5));
			t_sample mul_4544 = (sah_4564 * m_ampvar_1);
			t_sample rsub_4554 = (((int)1) - mul_4544);
			t_sample sqrt_4561 = sqrt(rsub_4554);
			t_sample noise_4535 = noise();
			t_sample abs_4545 = fabs(noise_4535);
			t_sample mul_4543 = (abs_4545 * m_buflen_4);
			t_sample sah_4536 = __m_sah_187(mul_4543, m_history_22, ((t_sample)0.5));
			t_sample add_4534 = (sah_4536 + plusequals_4541);
			t_sample mod_4548 = safemod(add_4534, m_buflen_4);
			t_sample switch_4558 = (lt_4547 ? mod_4548 : ((int)-1));
			int index_trunc_188 = fixnan(floor(switch_4558));
			double index_fract_189 = (switch_4558 - index_trunc_188);
			int index_trunc_190 = (index_trunc_188 + 1);
			bool index_ignore_191 = ((index_trunc_188 >= capture_dim) || (index_trunc_188 < 0));
			bool index_ignore_192 = ((index_trunc_190 >= capture_dim) || (index_trunc_190 < 0));
			// samples capture channel 1;
			double read_capture_193 = (index_ignore_191 ? 0 : m_capture_61.read(index_trunc_188, 0));
			double read_capture_194 = (index_ignore_192 ? 0 : m_capture_61.read(index_trunc_190, 0));
			double readinterp_195 = linear_interp(index_fract_189, read_capture_193, read_capture_194);
			t_sample sample_capture_4537 = readinterp_195;
			t_sample index_capture_4559 = switch_4558;
			t_sample mul_4546 = (sample_capture_4537 * expr_4542);
			t_sample mul_4549 = (mul_4546 * sqrt_4561);
			t_sample history_3083_next_4551 = fixdenorm(gate_4550);
			t_sample plusequals_4604 = __m_pluseq_196.post(m_history_20, ((int)0), 0, 4);
			t_sample add_4577 = (plusequals_4604 + ((int)1));
			t_sample plusequals_4580 = __m_pluseq_197.post(add_4577, m_history_20, 0);
			t_sample sub_4583 = (m_grainlen_21 - m_sampmin_5);
			t_sample noise_4599 = noise();
			t_sample abs_4605 = fabs(noise_4599);
			t_sample mul_4592 = (abs_4605 * sub_4583);
			t_sample sah_4571 = __m_sah_198(mul_4592, m_history_20, ((t_sample)0.5));
			t_sample add_4597 = (sah_4571 + m_sampmin_5);
			t_sample div_4596 = safediv(plusequals_4580, add_4597);
			t_sample clamp_4572 = ((div_4596 <= ((int)0)) ? ((int)0) : ((div_4596 >= ((int)1)) ? ((int)1) : div_4596));
			t_sample expr_4581 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_4572))));
			int lt_4589 = (plusequals_4580 < add_4597);
			int add_4594 = (lt_4589 + ((int)1));
			int choice_199 = add_4594;
			int gate_4591 = (((choice_199 >= 1) && (choice_199 < 2)) ? gen_3145 : 0);
			int gate_4603 = ((choice_199 >= 2) ? gen_3145 : 0);
			int gen_3143 = gate_4603;
			t_sample noise_4598 = noise();
			t_sample abs_4607 = fabs(noise_4598);
			t_sample sah_4606 = __m_sah_200(abs_4607, m_history_20, ((t_sample)0.5));
			t_sample mul_4586 = (sah_4606 * m_ampvar_1);
			t_sample rsub_4595 = (((int)1) - mul_4586);
			t_sample sqrt_4602 = sqrt(rsub_4595);
			t_sample noise_4574 = noise();
			t_sample abs_4587 = fabs(noise_4574);
			t_sample mul_4584 = (abs_4587 * m_buflen_4);
			t_sample sah_4575 = __m_sah_201(mul_4584, m_history_20, ((t_sample)0.5));
			t_sample add_4573 = (sah_4575 + plusequals_4580);
			t_sample mod_4578 = safemod(add_4573, m_buflen_4);
			t_sample switch_4600 = (lt_4589 ? mod_4578 : ((int)-1));
			int index_trunc_202 = fixnan(floor(switch_4600));
			double index_fract_203 = (switch_4600 - index_trunc_202);
			int index_trunc_204 = (index_trunc_202 + 1);
			bool index_ignore_205 = ((index_trunc_202 >= capture_dim) || (index_trunc_202 < 0));
			bool index_ignore_206 = ((index_trunc_204 >= capture_dim) || (index_trunc_204 < 0));
			// samples capture channel 1;
			double read_capture_207 = (index_ignore_205 ? 0 : m_capture_61.read(index_trunc_202, 0));
			double read_capture_208 = (index_ignore_206 ? 0 : m_capture_61.read(index_trunc_204, 0));
			double readinterp_209 = linear_interp(index_fract_203, read_capture_207, read_capture_208);
			t_sample sample_capture_4576 = readinterp_209;
			t_sample index_capture_4582 = switch_4600;
			t_sample mul_4588 = (sample_capture_4576 * expr_4581);
			t_sample mul_4590 = (mul_4588 * sqrt_4602);
			t_sample history_3083_next_4593 = fixdenorm(gate_4591);
			t_sample plusequals_4637 = __m_pluseq_210.post(m_history_18, ((int)0), 0, 4);
			t_sample add_4616 = (plusequals_4637 + ((int)1));
			t_sample plusequals_4618 = __m_pluseq_211.post(add_4616, m_history_18, 0);
			t_sample sub_4646 = (m_grainlen_19 - m_sampmin_5);
			t_sample noise_4634 = noise();
			t_sample abs_4644 = fabs(noise_4634);
			t_sample mul_4620 = (abs_4644 * sub_4646);
			t_sample sah_4610 = __m_sah_212(mul_4620, m_history_18, ((t_sample)0.5));
			t_sample add_4642 = (sah_4610 + m_sampmin_5);
			t_sample div_4632 = safediv(plusequals_4618, add_4642);
			t_sample clamp_4611 = ((div_4632 <= ((int)0)) ? ((int)0) : ((div_4632 >= ((int)1)) ? ((int)1) : div_4632));
			t_sample expr_4619 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_4611))));
			int lt_4625 = (plusequals_4618 < add_4642);
			int add_4629 = (lt_4625 + ((int)1));
			int choice_213 = add_4629;
			int gate_4627 = (((choice_213 >= 1) && (choice_213 < 2)) ? gen_3143 : 0);
			int gate_4641 = ((choice_213 >= 2) ? gen_3143 : 0);
			int gen_3141 = gate_4641;
			t_sample noise_4633 = noise();
			t_sample abs_4645 = fabs(noise_4633);
			t_sample sah_4638 = __m_sah_214(abs_4645, m_history_18, ((t_sample)0.5));
			t_sample mul_4622 = (sah_4638 * m_ampvar_1);
			t_sample rsub_4631 = (((int)1) - mul_4622);
			t_sample sqrt_4640 = sqrt(rsub_4631);
			t_sample noise_4613 = noise();
			t_sample abs_4623 = fabs(noise_4613);
			t_sample mul_4621 = (abs_4623 * m_buflen_4);
			t_sample sah_4614 = __m_sah_215(mul_4621, m_history_18, ((t_sample)0.5));
			t_sample add_4612 = (sah_4614 + plusequals_4618);
			t_sample mod_4643 = safemod(add_4612, m_buflen_4);
			t_sample switch_4635 = (lt_4625 ? mod_4643 : ((int)-1));
			int index_trunc_216 = fixnan(floor(switch_4635));
			double index_fract_217 = (switch_4635 - index_trunc_216);
			int index_trunc_218 = (index_trunc_216 + 1);
			bool index_ignore_219 = ((index_trunc_216 >= capture_dim) || (index_trunc_216 < 0));
			bool index_ignore_220 = ((index_trunc_218 >= capture_dim) || (index_trunc_218 < 0));
			// samples capture channel 1;
			double read_capture_221 = (index_ignore_219 ? 0 : m_capture_61.read(index_trunc_216, 0));
			double read_capture_222 = (index_ignore_220 ? 0 : m_capture_61.read(index_trunc_218, 0));
			double readinterp_223 = linear_interp(index_fract_217, read_capture_221, read_capture_222);
			t_sample sample_capture_4615 = readinterp_223;
			t_sample index_capture_4636 = switch_4635;
			t_sample mul_4624 = (sample_capture_4615 * expr_4619);
			t_sample mul_4626 = (mul_4624 * sqrt_4640);
			t_sample history_3083_next_4628 = fixdenorm(gate_4627);
			t_sample plusequals_4669 = __m_pluseq_224.post(m_history_16, ((int)0), 0, 4);
			t_sample add_4654 = (plusequals_4669 + ((int)1));
			t_sample plusequals_4670 = __m_pluseq_225.post(add_4654, m_history_16, 0);
			t_sample sub_4660 = (m_grainlen_17 - m_sampmin_5);
			t_sample noise_4665 = noise();
			t_sample abs_4668 = fabs(noise_4665);
			t_sample mul_4657 = (abs_4668 * sub_4660);
			t_sample sah_4676 = __m_sah_226(mul_4657, m_history_16, ((t_sample)0.5));
			t_sample add_4678 = (sah_4676 + m_sampmin_5);
			t_sample div_4663 = safediv(plusequals_4670, add_4678);
			t_sample clamp_4649 = ((div_4663 <= ((int)0)) ? ((int)0) : ((div_4663 >= ((int)1)) ? ((int)1) : div_4663));
			t_sample expr_4656 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_4649))));
			int lt_4674 = (plusequals_4670 < add_4678);
			int add_4677 = (lt_4674 + ((int)1));
			int choice_227 = add_4677;
			int gate_4675 = (((choice_227 >= 1) && (choice_227 < 2)) ? gen_3141 : 0);
			int gate_4667 = ((choice_227 >= 2) ? gen_3141 : 0);
			int gen_3139 = gate_4667;
			t_sample noise_4664 = noise();
			t_sample abs_4679 = fabs(noise_4664);
			t_sample sah_4682 = __m_sah_228(abs_4679, m_history_16, ((t_sample)0.5));
			t_sample mul_4658 = (sah_4682 * m_ampvar_1);
			t_sample rsub_4662 = (((int)1) - mul_4658);
			t_sample sqrt_4681 = sqrt(rsub_4662);
			t_sample noise_4651 = noise();
			t_sample abs_4659 = fabs(noise_4651);
			t_sample mul_4671 = (abs_4659 * m_buflen_4);
			t_sample sah_4652 = __m_sah_229(mul_4671, m_history_16, ((t_sample)0.5));
			t_sample add_4650 = (sah_4652 + plusequals_4670);
			t_sample mod_4672 = safemod(add_4650, m_buflen_4);
			t_sample switch_4680 = (lt_4674 ? mod_4672 : ((int)-1));
			int index_trunc_230 = fixnan(floor(switch_4680));
			double index_fract_231 = (switch_4680 - index_trunc_230);
			int index_trunc_232 = (index_trunc_230 + 1);
			bool index_ignore_233 = ((index_trunc_230 >= capture_dim) || (index_trunc_230 < 0));
			bool index_ignore_234 = ((index_trunc_232 >= capture_dim) || (index_trunc_232 < 0));
			// samples capture channel 1;
			double read_capture_235 = (index_ignore_233 ? 0 : m_capture_61.read(index_trunc_230, 0));
			double read_capture_236 = (index_ignore_234 ? 0 : m_capture_61.read(index_trunc_232, 0));
			double readinterp_237 = linear_interp(index_fract_231, read_capture_235, read_capture_236);
			t_sample sample_capture_4653 = readinterp_237;
			t_sample index_capture_4685 = switch_4680;
			t_sample mul_4673 = (sample_capture_4653 * expr_4656);
			t_sample mul_4661 = (mul_4673 * sqrt_4681);
			t_sample history_3083_next_4683 = fixdenorm(gate_4675);
			t_sample plusequals_4708 = __m_pluseq_238.post(m_history_14, ((int)0), 0, 4);
			t_sample add_4693 = (plusequals_4708 + ((int)1));
			t_sample plusequals_4709 = __m_pluseq_239.post(add_4693, m_history_14, 0);
			t_sample sub_4699 = (m_grainlen_15 - m_sampmin_5);
			t_sample noise_4704 = noise();
			t_sample abs_4707 = fabs(noise_4704);
			t_sample mul_4719 = (abs_4707 * sub_4699);
			t_sample sah_4715 = __m_sah_240(mul_4719, m_history_14, ((t_sample)0.5));
			t_sample add_4716 = (sah_4715 + m_sampmin_5);
			t_sample div_4702 = safediv(plusequals_4709, add_4716);
			t_sample clamp_4688 = ((div_4702 <= ((int)0)) ? ((int)0) : ((div_4702 >= ((int)1)) ? ((int)1) : div_4702));
			t_sample expr_4695 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_4688))));
			int lt_4713 = (plusequals_4709 < add_4716);
			int add_4722 = (lt_4713 + ((int)1));
			int choice_241 = add_4722;
			int gate_4714 = (((choice_241 >= 1) && (choice_241 < 2)) ? gen_3139 : 0);
			int gate_4706 = ((choice_241 >= 2) ? gen_3139 : 0);
			int gen_3137 = gate_4706;
			t_sample noise_4703 = noise();
			t_sample abs_4717 = fabs(noise_4703);
			t_sample sah_4698 = __m_sah_242(abs_4717, m_history_14, ((t_sample)0.5));
			t_sample mul_4696 = (sah_4698 * m_ampvar_1);
			t_sample rsub_4701 = (((int)1) - mul_4696);
			t_sample sqrt_4720 = sqrt(rsub_4701);
			t_sample noise_4690 = noise();
			t_sample abs_4697 = fabs(noise_4690);
			t_sample mul_4710 = (abs_4697 * m_buflen_4);
			t_sample sah_4691 = __m_sah_243(mul_4710, m_history_14, ((t_sample)0.5));
			t_sample add_4689 = (sah_4691 + plusequals_4709);
			t_sample mod_4711 = safemod(add_4689, m_buflen_4);
			t_sample switch_4718 = (lt_4713 ? mod_4711 : ((int)-1));
			int index_trunc_244 = fixnan(floor(switch_4718));
			double index_fract_245 = (switch_4718 - index_trunc_244);
			int index_trunc_246 = (index_trunc_244 + 1);
			bool index_ignore_247 = ((index_trunc_244 >= capture_dim) || (index_trunc_244 < 0));
			bool index_ignore_248 = ((index_trunc_246 >= capture_dim) || (index_trunc_246 < 0));
			// samples capture channel 1;
			double read_capture_249 = (index_ignore_247 ? 0 : m_capture_61.read(index_trunc_244, 0));
			double read_capture_250 = (index_ignore_248 ? 0 : m_capture_61.read(index_trunc_246, 0));
			double readinterp_251 = linear_interp(index_fract_245, read_capture_249, read_capture_250);
			t_sample sample_capture_4692 = readinterp_251;
			t_sample index_capture_4724 = switch_4718;
			t_sample mul_4712 = (sample_capture_4692 * expr_4695);
			t_sample mul_4700 = (mul_4712 * sqrt_4720);
			t_sample history_3083_next_4721 = fixdenorm(gate_4714);
			t_sample mul_3135 = ((((((((((((mul_3052 + mul_4626) + mul_4700) + mul_4432) + mul_4470) + mul_4509) + mul_4549) + mul_4299) + mul_4338) + mul_4392) + mul_4590) + mul_4661) * ((int)1));
			t_sample plusequals_4748 = __m_pluseq_252.post(m_history_12, ((int)0), 0, 4);
			t_sample add_4732 = (plusequals_4748 + ((int)1));
			t_sample plusequals_4749 = __m_pluseq_253.post(add_4732, m_history_12, 0);
			t_sample sub_4739 = (m_grainlen_13 - m_sampmin_5);
			t_sample noise_4744 = noise();
			t_sample abs_4747 = fabs(noise_4744);
			t_sample mul_4735 = (abs_4747 * sub_4739);
			t_sample sah_4756 = __m_sah_254(mul_4735, m_history_12, ((t_sample)0.5));
			t_sample add_4757 = (sah_4756 + m_sampmin_5);
			t_sample div_4742 = safediv(plusequals_4749, add_4757);
			t_sample clamp_4727 = ((div_4742 <= ((int)0)) ? ((int)0) : ((div_4742 >= ((int)1)) ? ((int)1) : div_4742));
			t_sample expr_4734 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_4727))));
			int lt_4753 = (plusequals_4749 < add_4757);
			int add_4759 = (lt_4753 + ((int)1));
			int choice_255 = add_4759;
			int gate_4754 = (((choice_255 >= 1) && (choice_255 < 2)) ? gen_3137 : 0);
			int gate_4746 = ((choice_255 >= 2) ? gen_3137 : 0);
			int gen_3093 = gate_4746;
			t_sample noise_4743 = noise();
			t_sample abs_4758 = fabs(noise_4743);
			t_sample sah_4738 = __m_sah_256(abs_4758, m_history_12, ((t_sample)0.5));
			t_sample mul_4736 = (sah_4738 * m_ampvar_1);
			t_sample rsub_4741 = (((int)1) - mul_4736);
			t_sample sqrt_4761 = sqrt(rsub_4741);
			t_sample noise_4729 = noise();
			t_sample abs_4737 = fabs(noise_4729);
			t_sample mul_4750 = (abs_4737 * m_buflen_4);
			t_sample sah_4730 = __m_sah_257(mul_4750, m_history_12, ((t_sample)0.5));
			t_sample add_4728 = (sah_4730 + plusequals_4749);
			t_sample mod_4751 = safemod(add_4728, m_buflen_4);
			t_sample switch_4760 = (lt_4753 ? mod_4751 : ((int)-1));
			int index_trunc_258 = fixnan(floor(switch_4760));
			double index_fract_259 = (switch_4760 - index_trunc_258);
			int index_trunc_260 = (index_trunc_258 + 1);
			bool index_ignore_261 = ((index_trunc_258 >= capture_dim) || (index_trunc_258 < 0));
			bool index_ignore_262 = ((index_trunc_260 >= capture_dim) || (index_trunc_260 < 0));
			// samples capture channel 1;
			double read_capture_263 = (index_ignore_261 ? 0 : m_capture_61.read(index_trunc_258, 0));
			double read_capture_264 = (index_ignore_262 ? 0 : m_capture_61.read(index_trunc_260, 0));
			double readinterp_265 = linear_interp(index_fract_259, read_capture_263, read_capture_264);
			t_sample sample_capture_4731 = readinterp_265;
			t_sample index_capture_4763 = switch_4760;
			t_sample mul_4752 = (sample_capture_4731 * expr_4734);
			t_sample mul_4740 = (mul_4752 * sqrt_4761);
			t_sample history_3083_next_4762 = fixdenorm(gate_4754);
			t_sample plusequals_4786 = __m_pluseq_266.post(m_history_10, ((int)0), 0, 4);
			t_sample add_4771 = (plusequals_4786 + ((int)1));
			t_sample plusequals_4787 = __m_pluseq_267.post(add_4771, m_history_10, 0);
			t_sample sub_4777 = (m_grainlen_11 - m_sampmin_5);
			t_sample noise_4782 = noise();
			t_sample abs_4785 = fabs(noise_4782);
			t_sample mul_4799 = (abs_4785 * sub_4777);
			t_sample sah_4794 = __m_sah_268(mul_4799, m_history_10, ((t_sample)0.5));
			t_sample add_4795 = (sah_4794 + m_sampmin_5);
			t_sample div_4780 = safediv(plusequals_4787, add_4795);
			t_sample clamp_4766 = ((div_4780 <= ((int)0)) ? ((int)0) : ((div_4780 >= ((int)1)) ? ((int)1) : div_4780));
			t_sample expr_4773 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_4766))));
			int lt_4791 = (plusequals_4787 < add_4795);
			int add_4797 = (lt_4791 + ((int)1));
			int choice_269 = add_4797;
			int gate_4792 = (((choice_269 >= 1) && (choice_269 < 2)) ? gen_3093 : 0);
			int gate_4784 = ((choice_269 >= 2) ? gen_3093 : 0);
			int gen_3091 = gate_4784;
			t_sample noise_4781 = noise();
			t_sample abs_4796 = fabs(noise_4781);
			t_sample sah_4776 = __m_sah_270(abs_4796, m_history_10, ((t_sample)0.5));
			t_sample mul_4774 = (sah_4776 * m_ampvar_1);
			t_sample rsub_4779 = (((int)1) - mul_4774);
			t_sample sqrt_4800 = sqrt(rsub_4779);
			t_sample noise_4768 = noise();
			t_sample abs_4775 = fabs(noise_4768);
			t_sample mul_4788 = (abs_4775 * m_buflen_4);
			t_sample sah_4769 = __m_sah_271(mul_4788, m_history_10, ((t_sample)0.5));
			t_sample add_4767 = (sah_4769 + plusequals_4787);
			t_sample mod_4789 = safemod(add_4767, m_buflen_4);
			t_sample switch_4798 = (lt_4791 ? mod_4789 : ((int)-1));
			int index_trunc_272 = fixnan(floor(switch_4798));
			double index_fract_273 = (switch_4798 - index_trunc_272);
			int index_trunc_274 = (index_trunc_272 + 1);
			bool index_ignore_275 = ((index_trunc_272 >= capture_dim) || (index_trunc_272 < 0));
			bool index_ignore_276 = ((index_trunc_274 >= capture_dim) || (index_trunc_274 < 0));
			// samples capture channel 1;
			double read_capture_277 = (index_ignore_275 ? 0 : m_capture_61.read(index_trunc_272, 0));
			double read_capture_278 = (index_ignore_276 ? 0 : m_capture_61.read(index_trunc_274, 0));
			double readinterp_279 = linear_interp(index_fract_273, read_capture_277, read_capture_278);
			t_sample sample_capture_4770 = readinterp_279;
			t_sample index_capture_4802 = switch_4798;
			t_sample mul_4790 = (sample_capture_4770 * expr_4773);
			t_sample mul_4778 = (mul_4790 * sqrt_4800);
			t_sample history_3083_next_4801 = fixdenorm(gate_4792);
			t_sample plusequals_4825 = __m_pluseq_280.post(m_history_8, ((int)0), 0, 4);
			t_sample add_4810 = (plusequals_4825 + ((int)1));
			t_sample plusequals_4826 = __m_pluseq_281.post(add_4810, m_history_8, 0);
			t_sample sub_4816 = (m_grainlen_9 - m_sampmin_5);
			t_sample noise_4821 = noise();
			t_sample abs_4824 = fabs(noise_4821);
			t_sample mul_4813 = (abs_4824 * sub_4816);
			t_sample sah_4833 = __m_sah_282(mul_4813, m_history_8, ((t_sample)0.5));
			t_sample add_4834 = (sah_4833 + m_sampmin_5);
			t_sample div_4819 = safediv(plusequals_4826, add_4834);
			t_sample clamp_4805 = ((div_4819 <= ((int)0)) ? ((int)0) : ((div_4819 >= ((int)1)) ? ((int)1) : div_4819));
			t_sample expr_4812 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_4805))));
			int lt_4830 = (plusequals_4826 < add_4834);
			int add_4836 = (lt_4830 + ((int)1));
			int choice_283 = add_4836;
			int gate_4831 = (((choice_283 >= 1) && (choice_283 < 2)) ? gen_3091 : 0);
			int gate_4823 = ((choice_283 >= 2) ? gen_3091 : 0);
			int gen_3089 = gate_4823;
			t_sample noise_4820 = noise();
			t_sample abs_4837 = fabs(noise_4820);
			t_sample sah_4835 = __m_sah_284(abs_4837, m_history_8, ((t_sample)0.5));
			t_sample mul_4814 = (sah_4835 * m_ampvar_1);
			t_sample rsub_4818 = (((int)1) - mul_4814);
			t_sample sqrt_4839 = sqrt(rsub_4818);
			t_sample noise_4807 = noise();
			t_sample abs_4815 = fabs(noise_4807);
			t_sample mul_4827 = (abs_4815 * m_buflen_4);
			t_sample sah_4808 = __m_sah_285(mul_4827, m_history_8, ((t_sample)0.5));
			t_sample add_4806 = (sah_4808 + plusequals_4826);
			t_sample mod_4828 = safemod(add_4806, m_buflen_4);
			t_sample switch_4838 = (lt_4830 ? mod_4828 : ((int)-1));
			int index_trunc_286 = fixnan(floor(switch_4838));
			double index_fract_287 = (switch_4838 - index_trunc_286);
			int index_trunc_288 = (index_trunc_286 + 1);
			bool index_ignore_289 = ((index_trunc_286 >= capture_dim) || (index_trunc_286 < 0));
			bool index_ignore_290 = ((index_trunc_288 >= capture_dim) || (index_trunc_288 < 0));
			// samples capture channel 1;
			double read_capture_291 = (index_ignore_289 ? 0 : m_capture_61.read(index_trunc_286, 0));
			double read_capture_292 = (index_ignore_290 ? 0 : m_capture_61.read(index_trunc_288, 0));
			double readinterp_293 = linear_interp(index_fract_287, read_capture_291, read_capture_292);
			t_sample sample_capture_4809 = readinterp_293;
			t_sample index_capture_4841 = switch_4838;
			t_sample mul_4829 = (sample_capture_4809 * expr_4812);
			t_sample mul_4817 = (mul_4829 * sqrt_4839);
			t_sample history_3083_next_4832 = fixdenorm(gate_4831);
			t_sample plusequals_4865 = __m_pluseq_294.post(m_history_6, ((int)0), 0, 4);
			t_sample add_4849 = (plusequals_4865 + ((int)1));
			t_sample plusequals_4866 = __m_pluseq_295.post(add_4849, m_history_6, 0);
			t_sample sub_4856 = (m_grainlen_7 - m_sampmin_5);
			t_sample noise_4861 = noise();
			t_sample abs_4864 = fabs(noise_4861);
			t_sample mul_4852 = (abs_4864 * sub_4856);
			t_sample sah_4875 = __m_sah_296(mul_4852, m_history_6, ((t_sample)0.5));
			t_sample add_4876 = (sah_4875 + m_sampmin_5);
			t_sample div_4859 = safediv(plusequals_4866, add_4876);
			t_sample clamp_4844 = ((div_4859 <= ((int)0)) ? ((int)0) : ((div_4859 >= ((int)1)) ? ((int)1) : div_4859));
			t_sample expr_4851 = (((t_sample)0.54) - (((t_sample)0.48) * cos((((t_sample)6.2831853071796) * clamp_4844))));
			int lt_4870 = (plusequals_4866 < add_4876);
			int add_4874 = (lt_4870 + ((int)1));
			int choice_297 = add_4874;
			int gate_4871 = (((choice_297 >= 1) && (choice_297 < 2)) ? gen_3089 : 0);
			int gate_4863 = ((choice_297 >= 2) ? gen_3089 : 0);
			t_sample noise_4860 = noise();
			t_sample abs_4877 = fabs(noise_4860);
			t_sample sah_4855 = __m_sah_298(abs_4877, m_history_6, ((t_sample)0.5));
			t_sample mul_4853 = (sah_4855 * m_ampvar_1);
			t_sample rsub_4858 = (((int)1) - mul_4853);
			t_sample sqrt_4879 = sqrt(rsub_4858);
			t_sample noise_4846 = noise();
			t_sample abs_4854 = fabs(noise_4846);
			t_sample mul_4867 = (abs_4854 * m_buflen_4);
			t_sample sah_4847 = __m_sah_299(mul_4867, m_history_6, ((t_sample)0.5));
			t_sample add_4845 = (sah_4847 + plusequals_4866);
			t_sample mod_4868 = safemod(add_4845, m_buflen_4);
			t_sample switch_4878 = (lt_4870 ? mod_4868 : ((int)-1));
			int index_trunc_300 = fixnan(floor(switch_4878));
			double index_fract_301 = (switch_4878 - index_trunc_300);
			int index_trunc_302 = (index_trunc_300 + 1);
			bool index_ignore_303 = ((index_trunc_300 >= capture_dim) || (index_trunc_300 < 0));
			bool index_ignore_304 = ((index_trunc_302 >= capture_dim) || (index_trunc_302 < 0));
			// samples capture channel 1;
			double read_capture_305 = (index_ignore_303 ? 0 : m_capture_61.read(index_trunc_300, 0));
			double read_capture_306 = (index_ignore_304 ? 0 : m_capture_61.read(index_trunc_302, 0));
			double readinterp_307 = linear_interp(index_fract_301, read_capture_305, read_capture_306);
			t_sample sample_capture_4848 = readinterp_307;
			t_sample index_capture_4873 = switch_4878;
			t_sample mul_4869 = (sample_capture_4848 * expr_4851);
			t_sample mul_4857 = (mul_4869 * sqrt_4879);
			t_sample history_3083_next_4880 = fixdenorm(gate_4871);
			t_sample mul_3048 = ((((mul_4740 + mul_4778) + mul_4817) + mul_4857) * ((int)1));
			t_sample mul_3117 = ((mul_3135 + mul_3048) * ((int)1));
			t_sample dcblock_3126 = __m_dcblock_308(mul_3117);
			t_sample mul_3128 = (sqrt_3127 * dcblock_3126);
			t_sample add_3124 = (mul_3129 + mul_3128);
			t_sample out1 = add_3124;
			t_sample buflen_next_4884 = fixdenorm(mul_3167);
			t_sample history_3047_next_4885 = fixdenorm(mix_3110);
			t_sample history_3168_next_4886 = fixdenorm(eq_3169);
			t_sample ampvar_next_4887 = fixdenorm(clamp_3094);
			t_sample grainlen_next_4888 = fixdenorm(clamp_3153);
			m_history_53 = history_3040_next_3042;
			m_history_52 = history_4239_next_4241;
			m_history_51 = history_3215_next_3217;
			m_history_49 = history_3211_next_3219;
			m_history_50 = history_3213_next_3218;
			m_history_48 = history_3040_next_4251;
			m_history_47 = history_4239_next_4257;
			m_history_46 = history_3215_next_4261;
			m_history_44 = history_3211_next_4265;
			m_history_45 = history_3213_next_4266;
			m_history_43 = history_3215_next_4275;
			m_history_41 = history_3211_next_4276;
			m_history_42 = history_3213_next_4279;
			m_history_40 = history_3215_next_4286;
			m_history_38 = history_3211_next_4293;
			m_history_39 = history_3213_next_4291;
			m_history_36 = history_3083_next_3085;
			m_history_34 = history_3083_next_4309;
			m_history_32 = history_3083_next_4351;
			m_history_30 = history_3083_next_4394;
			m_history_28 = history_3083_next_4434;
			m_history_26 = history_3083_next_4472;
			m_history_24 = history_3083_next_4511;
			m_history_22 = history_3083_next_4551;
			m_history_20 = history_3083_next_4593;
			m_history_18 = history_3083_next_4628;
			m_history_16 = history_3083_next_4683;
			m_history_14 = history_3083_next_4721;
			m_history_12 = history_3083_next_4762;
			m_history_10 = history_3083_next_4801;
			m_history_8 = history_3083_next_4832;
			m_history_6 = history_3083_next_4880;
			m_sampmin_5 = sampmin_next_4883;
			m_buflen_4 = buflen_next_4884;
			m_history_3 = history_3047_next_4885;
			m_history_2 = history_3168_next_4886;
			m_ampvar_1 = ampvar_next_4887;
			m_grainlen_37 = grainlen_next_4888;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = out2;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			(*(__out6++)) = out6;
			(*(__out7++)) = out7;
			(*(__out8++)) = out8;
			(*(__out9++)) = out9;
			(*(__out10++)) = out10;
			(*(__out11++)) = out11;
			
		};
		return __exception;
		
	};
	inline void set_knob4(t_param _value) {
		m_knob_54 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_footswitch_1(t_param _value) {
		m_footswitch_55 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_expression(t_param _value) {
		m_expression_56 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_footswitch_2(t_param _value) {
		m_footswitch_57 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5(t_param _value) {
		m_knob_58 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob1(t_param _value) {
		m_knob_59 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw2(t_param _value) {
		m_sw_60 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_capture(void * _value) {
		m_capture_61.setbuffer(_value);
	};
	inline void set_knob3(t_param _value) {
		m_knob_62 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob6(t_param _value) {
		m_knob_63 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_64 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2(t_param _value) {
		m_knob_65 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw3(t_param _value) {
		m_sw_66 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	
} State;


///
///	Configuration for the genlib API
///

/// Number of signal inputs and outputs

int gen_kernel_numins = 1;
int gen_kernel_numouts = 11;

int num_inputs() { return gen_kernel_numins; }
int num_outputs() { return gen_kernel_numouts; }
int num_params() { return 13; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "led1_red", "led1_green", "led2", "led3_red", "led3_green", "led3_blue", "led2", "relay", "debug", "debug2" };

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
		case 0: self->set_capture(ref); break;
		case 1: self->set_expression(value); break;
		case 2: self->set_footswitch_1(value); break;
		case 3: self->set_footswitch_2(value); break;
		case 4: self->set_knob1(value); break;
		case 5: self->set_knob2(value); break;
		case 6: self->set_knob3(value); break;
		case 7: self->set_knob4(value); break;
		case 8: self->set_knob5(value); break;
		case 9: self->set_knob6(value); break;
		case 10: self->set_sw1(value); break;
		case 11: self->set_sw2(value); break;
		case 12: self->set_sw3(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		
		case 1: *value = self->m_expression_56; break;
		case 2: *value = self->m_footswitch_55; break;
		case 3: *value = self->m_footswitch_57; break;
		case 4: *value = self->m_knob_59; break;
		case 5: *value = self->m_knob_65; break;
		case 6: *value = self->m_knob_62; break;
		case 7: *value = self->m_knob_54; break;
		case 8: *value = self->m_knob_58; break;
		case 9: *value = self->m_knob_63; break;
		case 10: *value = self->m_sw_64; break;
		case 11: *value = self->m_sw_60; break;
		case 12: *value = self->m_sw_66; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(13 * sizeof(ParamInfo));
	self->__commonstate.numparams = 13;
	// initialize parameter 0 ("m_capture_61")
	pi = self->__commonstate.params + 0;
	pi->name = "capture";
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
	// initialize parameter 1 ("m_expression_56")
	pi = self->__commonstate.params + 1;
	pi->name = "expression";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_expression_56;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_footswitch_55")
	pi = self->__commonstate.params + 2;
	pi->name = "footswitch_1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_footswitch_55;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_footswitch_57")
	pi = self->__commonstate.params + 3;
	pi->name = "footswitch_2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_footswitch_57;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_knob_59")
	pi = self->__commonstate.params + 4;
	pi->name = "knob1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_59;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_knob_65")
	pi = self->__commonstate.params + 5;
	pi->name = "knob2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_65;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_knob_62")
	pi = self->__commonstate.params + 6;
	pi->name = "knob3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_62;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_knob_54")
	pi = self->__commonstate.params + 7;
	pi->name = "knob4";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_54;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_knob_58")
	pi = self->__commonstate.params + 8;
	pi->name = "knob5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_58;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_knob_63")
	pi = self->__commonstate.params + 9;
	pi->name = "knob6";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_63;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_sw_64")
	pi = self->__commonstate.params + 10;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_64;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_sw_60")
	pi = self->__commonstate.params + 11;
	pi->name = "sw2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_60;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 12 ("m_sw_66")
	pi = self->__commonstate.params + 12;
	pi->name = "sw3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_66;
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


} // Granular_Multifx::
