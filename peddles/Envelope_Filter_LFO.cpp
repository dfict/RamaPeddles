#include "Envelope_Filter_LFO.h"

namespace Envelope_Filter_LFO {

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
	Change __m_change_44;
	Change __m_change_72;
	DCBlock __m_dcblock_92;
	int __exception;
	int vectorsize;
	Phasor __m_phasor_51;
	PlusEquals __m_pluseq_45;
	Rate __m_rate_62;
	Sah __m_sah_61;
	Sah __m_sah_41;
	Sah __m_sah_87;
	Sah __m_sah_73;
	Sah __m_sah_42;
	Sah __m_sah_86;
	SineCycle __m_cycle_52;
	SineData __sinedata;
	t_sample m_f_54;
	t_sample m_f_55;
	t_sample m_f_56;
	t_sample m_f_57;
	t_sample m_output_53;
	t_sample m_f_76;
	t_sample m_f_82;
	t_sample __m_slide_83;
	t_sample m_f_58;
	t_sample __m_slide_46;
	t_sample samples_to_seconds;
	t_sample m_f_77;
	t_sample m_f_59;
	t_sample m_f_81;
	t_sample m_f_71;
	t_sample m_f_70;
	t_sample m_f_79;
	t_sample m_output_75;
	t_sample m_f_78;
	t_sample m_f_60;
	t_sample m_f_69;
	t_sample m_f_67;
	t_sample m_f_80;
	t_sample m_f_68;
	t_sample m_output_64;
	t_sample m_f_66;
	t_sample samplerate;
	t_sample m_f_65;
	t_sample m_y_2;
	t_sample m_footswitch_40;
	t_sample m_history_14;
	t_sample m_history_13;
	t_sample m_history_12;
	t_sample m_history_15;
	t_sample m_history_17;
	t_sample m_history_16;
	t_sample m_history_18;
	t_sample m_history_19;
	t_sample m_history_11;
	t_sample m_history_9;
	t_sample m_history_4;
	t_sample m_history_3;
	t_sample m_history_10;
	t_sample m_history_5;
	t_sample m_history_7;
	t_sample m_history_6;
	t_sample m_history_8;
	t_sample m_y_1;
	t_sample m_history_20;
	t_sample m_history_22;
	t_sample m_expression_34;
	t_sample m_sw_33;
	t_sample m_knob_32;
	t_sample m_knob_35;
	t_sample m_sw_37;
	t_sample m_sw_36;
	t_sample m_knob_38;
	t_sample m_history_21;
	t_sample m_knob_31;
	t_sample m_knob_29;
	t_sample m_history_24;
	t_sample m_history_23;
	t_sample m_footswitch_30;
	t_sample m_history_25;
	t_sample m_history_27;
	t_sample m_history_26;
	t_sample m_history_28;
	t_sample m_knob_39;
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
		m_history_18 = ((int)0);
		m_history_19 = ((int)0);
		m_history_20 = ((int)0);
		m_history_21 = ((int)0);
		m_history_22 = ((int)0);
		m_history_23 = ((int)0);
		m_history_24 = ((int)0);
		m_history_25 = ((int)0);
		m_history_26 = ((int)0);
		m_history_27 = ((int)0);
		m_history_28 = ((int)0);
		m_knob_29 = ((int)0);
		m_footswitch_30 = ((int)0);
		m_knob_31 = ((int)0);
		m_knob_32 = ((int)0);
		m_sw_33 = ((int)0);
		m_expression_34 = ((int)0);
		m_knob_35 = ((int)0);
		m_sw_36 = ((int)0);
		m_sw_37 = ((int)0);
		m_knob_38 = ((int)0);
		m_knob_39 = ((int)0);
		m_footswitch_40 = ((int)0);
		__m_sah_41.reset(0);
		__m_sah_42.reset(0);
		__m_change_44.reset(0);
		__m_pluseq_45.reset(0);
		__m_slide_46 = 0;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_51.reset(0);
		__m_cycle_52.reset(samplerate, 0);
		m_output_53 = ((int)0);
		m_f_54 = ((int)0);
		m_f_55 = ((int)0);
		m_f_56 = ((int)0);
		m_f_57 = ((int)0);
		m_f_58 = ((int)0);
		m_f_59 = ((int)0);
		m_f_60 = ((int)0);
		__m_sah_61.reset(0);
		__m_rate_62.reset();
		m_output_64 = ((int)0);
		m_f_65 = ((int)0);
		m_f_66 = ((int)0);
		m_f_67 = ((int)0);
		m_f_68 = ((int)0);
		m_f_69 = ((int)0);
		m_f_70 = ((int)0);
		m_f_71 = ((int)0);
		__m_change_72.reset(0);
		__m_sah_73.reset(0);
		m_output_75 = ((int)0);
		m_f_76 = ((int)0);
		m_f_77 = ((int)0);
		m_f_78 = ((int)0);
		m_f_79 = ((int)0);
		m_f_80 = ((int)0);
		m_f_81 = ((int)0);
		m_f_82 = ((int)0);
		__m_slide_83 = 0;
		__m_sah_86.reset(0);
		__m_sah_87.reset(0);
		__m_dcblock_92.reset();
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
		t_sample mstosamps_121 = (((int)10) * (samplerate * 0.001));
		t_sample mstosamps_120 = (((int)100) * (samplerate * 0.001));
		t_sample iup_47 = (1 / maximum(1, abs(mstosamps_121)));
		t_sample idown_48 = (1 / maximum(1, abs(mstosamps_120)));
		samples_to_seconds = (1 / samplerate);
		int min_91 = (-1);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample out6 = ((int)0);
			t_sample out7 = ((int)0);
			t_sample sah_7 = __m_sah_41(m_history_28, m_sw_36, ((int)0));
			t_sample gen_10 = sah_7;
			t_sample rsub_5 = (((int)1) - sah_7);
			t_sample history_6_next_8 = fixdenorm(rsub_5);
			t_sample out5 = gen_10;
			t_sample sah_126 = __m_sah_42(m_history_27, m_sw_36, ((int)0));
			t_sample gen_9 = sah_126;
			t_sample rsub_127 = (((int)1) - sah_126);
			t_sample history_6_next_128 = fixdenorm(rsub_127);
			t_sample add_2 = (gen_9 + ((int)1));
			t_sample choice_43 = int(add_2);
			t_sample gate_3 = (((choice_43 >= 1) && (choice_43 < 2)) ? ((int)1) : 0);
			t_sample gate_4 = ((choice_43 >= 2) ? ((int)1) : 0);
			t_sample mix_577 = (m_history_26 + (((t_sample)0.0042742627044161) * (m_knob_38 - m_history_26)));
			t_sample mix_94 = mix_577;
			t_sample mix_578 = (m_history_25 + (((t_sample)0.0042742627044161) * (mix_94 - m_history_25)));
			t_sample mix_92 = mix_578;
			t_sample mix_579 = (m_history_24 + (((t_sample)0.0042742627044161) * (mix_92 - m_history_24)));
			t_sample mix_90 = mix_579;
			t_sample gen_101 = mix_90;
			t_sample history_95_next_97 = fixdenorm(mix_94);
			t_sample history_93_next_98 = fixdenorm(mix_92);
			t_sample history_91_next_99 = fixdenorm(mix_90);
			t_sample mix_580 = (m_history_23 + (((t_sample)0.0042742627044161) * (m_knob_39 - m_history_23)));
			t_sample mix_137 = mix_580;
			t_sample mix_581 = (m_history_22 + (((t_sample)0.0042742627044161) * (mix_137 - m_history_22)));
			t_sample mix_131 = mix_581;
			t_sample mix_582 = (m_history_21 + (((t_sample)0.0042742627044161) * (mix_131 - m_history_21)));
			t_sample mix_136 = mix_582;
			t_sample gen_109 = mix_136;
			t_sample history_95_next_132 = fixdenorm(mix_137);
			t_sample history_93_next_133 = fixdenorm(mix_131);
			t_sample history_91_next_130 = fixdenorm(mix_136);
			t_sample mix_583 = (m_history_20 + (((t_sample)0.0042742627044161) * (m_knob_31 - m_history_20)));
			t_sample mix_144 = mix_583;
			t_sample mix_584 = (m_history_19 + (((t_sample)0.0042742627044161) * (mix_144 - m_history_19)));
			t_sample mix_146 = mix_584;
			t_sample mix_585 = (m_history_18 + (((t_sample)0.0042742627044161) * (mix_146 - m_history_18)));
			t_sample mix_147 = mix_585;
			t_sample gen_102 = mix_147;
			t_sample history_95_next_151 = fixdenorm(mix_144);
			t_sample history_93_next_143 = fixdenorm(mix_146);
			t_sample history_91_next_145 = fixdenorm(mix_147);
			int change_107 = __m_change_44(m_footswitch_40);
			int clamp_106 = ((change_107 <= ((int)0)) ? ((int)0) : ((change_107 >= ((int)1)) ? ((int)1) : change_107));
			int plusequals_108 = __m_pluseq_45.post(clamp_106, ((int)0), 0, 2);
			t_sample out9 = plusequals_108;
			int rsub_103 = (((int)1) - plusequals_108);
			t_sample out8 = rsub_103;
			t_sample mix_586 = (m_history_17 + (((t_sample)0.0042742627044161) * (m_knob_35 - m_history_17)));
			t_sample mix_157 = mix_586;
			t_sample mix_587 = (m_history_16 + (((t_sample)0.0042742627044161) * (mix_157 - m_history_16)));
			t_sample mix_159 = mix_587;
			t_sample mix_588 = (m_history_15 + (((t_sample)0.0042742627044161) * (mix_159 - m_history_15)));
			t_sample mix_162 = mix_588;
			t_sample gen_105 = mix_162;
			t_sample history_95_next_164 = fixdenorm(mix_157);
			t_sample history_93_next_156 = fixdenorm(mix_159);
			t_sample history_91_next_158 = fixdenorm(mix_162);
			t_sample mix_589 = (m_history_14 + (((t_sample)0.0042742627044161) * (m_knob_32 - m_history_14)));
			t_sample mix_170 = mix_589;
			t_sample mix_590 = (m_history_13 + (((t_sample)0.0042742627044161) * (mix_170 - m_history_13)));
			t_sample mix_174 = mix_590;
			t_sample mix_591 = (m_history_12 + (((t_sample)0.0042742627044161) * (mix_174 - m_history_12)));
			t_sample mix_172 = mix_591;
			t_sample gen_104 = mix_172;
			t_sample history_95_next_177 = fixdenorm(mix_170);
			t_sample history_93_next_169 = fixdenorm(mix_174);
			t_sample history_91_next_173 = fixdenorm(mix_172);
			t_sample mul_55 = (in1 * ((int)30));
			t_sample abs_117 = fabs(mul_55);
			__m_slide_46 = fixdenorm((__m_slide_46 + (((abs_117 > __m_slide_46) ? iup_47 : idown_48) * (abs_117 - __m_slide_46))));
			t_sample slide_123 = __m_slide_46;
			t_sample clamp_122 = ((slide_123 <= ((int)0)) ? ((int)0) : ((slide_123 >= ((int)1)) ? ((int)1) : slide_123));
			t_sample mul_19 = (gen_101 * clamp_122);
			t_sample mul_51 = (mul_19 * rsub_103);
			t_sample out3 = (mul_51 + gate_3);
			t_sample mul_20 = (gen_102 * clamp_122);
			t_sample mul_52 = (mul_20 * rsub_103);
			t_sample out2 = mul_52;
			t_sample add_116 = (gen_109 + mul_20);
			t_sample clamp_113 = ((add_116 <= ((int)0)) ? ((int)0) : ((add_116 >= ((int)1)) ? ((int)1) : add_116));
			t_sample expr_124 = (((int)1) - sqrt((((int)1) - clamp_113)));
			t_sample sub_595 = (expr_124 - ((int)0));
			t_sample scale_592 = ((safepow((sub_595 * ((t_sample)1)), ((int)1)) * ((int)12)) + ((int)0));
			t_sample scale_115 = scale_592;
			t_sample mix_596 = (m_history_11 + (((t_sample)0.0042742627044161) * (m_knob_29 - m_history_11)));
			t_sample mix_183 = mix_596;
			t_sample mix_597 = (m_history_10 + (((t_sample)0.0042742627044161) * (mix_183 - m_history_10)));
			t_sample mix_187 = mix_597;
			t_sample mix_598 = (m_history_9 + (((t_sample)0.0042742627044161) * (mix_187 - m_history_9)));
			t_sample mix_185 = mix_598;
			t_sample gen_100 = mix_185;
			t_sample history_95_next_190 = fixdenorm(mix_183);
			t_sample history_93_next_182 = fixdenorm(mix_187);
			t_sample history_91_next_186 = fixdenorm(mix_185);
			t_sample mix_599 = (m_history_8 + (((t_sample)0.0014247580910283) * (m_sw_37 - m_history_8)));
			t_sample mix_73 = mix_599;
			t_sample mix_600 = (m_history_7 + (((t_sample)0.0014247580910283) * (mix_73 - m_history_7)));
			t_sample mix_71 = mix_600;
			t_sample gen_83 = mix_71;
			t_sample history_74_next_76 = fixdenorm(mix_73);
			t_sample history_72_next_77 = fixdenorm(mix_71);
			t_sample mul_82 = (gen_83 * ((int)4));
			t_sample round_81 = round(mul_82);
			t_sample clamp_64 = ((round_81 <= ((int)1)) ? ((int)1) : ((round_81 >= ((int)3)) ? ((int)3) : round_81));
			t_sample sub_59 = (clamp_64 - ((int)1));
			t_sample mix_601 = (m_history_6 + (((t_sample)0.0014247580910283) * (m_sw_36 - m_history_6)));
			t_sample mix_195 = mix_601;
			t_sample mix_602 = (m_history_5 + (((t_sample)0.0014247580910283) * (mix_195 - m_history_5)));
			t_sample mix_199 = mix_602;
			t_sample gen_89 = mix_199;
			t_sample history_74_next_198 = fixdenorm(mix_195);
			t_sample history_72_next_197 = fixdenorm(mix_199);
			t_sample mul_88 = (gen_89 * ((int)4));
			t_sample round_87 = round(mul_88);
			t_sample clamp_62 = ((round_87 <= ((int)1)) ? ((int)1) : ((round_87 >= ((int)3)) ? ((int)3) : round_87));
			t_sample sw_63 = clamp_62;
			t_sample choice_49 = int(sw_63);
			t_sample selector_18 = ((choice_49 >= 3) ? ((int)50) : ((choice_49 >= 2) ? ((int)40) : ((choice_49 >= 1) ? ((int)65) : 0)));
			t_sample choice_50 = int(sw_63);
			t_sample selector_17 = ((choice_50 >= 3) ? ((int)110) : ((choice_50 >= 2) ? ((int)93) : ((choice_50 >= 1) ? ((int)97) : 0)));
			t_sample mix_603 = (m_history_4 + (((t_sample)0.0014247580910283) * (m_sw_33 - m_history_4)));
			t_sample mix_204 = mix_603;
			t_sample mix_604 = (m_history_3 + (((t_sample)0.0014247580910283) * (mix_204 - m_history_3)));
			t_sample mix_208 = mix_604;
			t_sample gen_86 = mix_208;
			t_sample history_74_next_205 = fixdenorm(mix_204);
			t_sample history_72_next_207 = fixdenorm(mix_208);
			t_sample mul_85 = (gen_86 * ((int)4));
			t_sample round_84 = round(mul_85);
			t_sample clamp_60 = ((round_84 <= ((int)1)) ? ((int)1) : ((round_84 >= ((int)3)) ? ((int)3) : round_84));
			t_sample sub_61 = (clamp_60 - ((int)1));
			t_sample mul_58 = (sub_61 * ((int)3));
			t_sample add_57 = (mul_58 + sub_59);
			t_sample phasor_43 = __m_phasor_51(scale_115, samples_to_seconds);
			t_sample add_42 = (phasor_43 + ((int)0));
			t_sample mod_41 = safemod(add_42, ((int)1));
			t_sample shape = gen_100;
			t_sample mode = add_57;
			t_sample val = mod_41;
			if ((mode == ((int)0))) {
				__m_cycle_52.phase(mod_41);
				val = __m_cycle_52(__sinedata);
				t_sample sub_608 = (shape - ((int)0));
				t_sample scale_605 = ((safepow((sub_608 * ((t_sample)1)), ((int)1)) * ((int)9)) + ((int)1));
				val = (val * scale_605);
				val = ((val <= ((int)-1)) ? ((int)-1) : ((val >= ((int)1)) ? ((int)1) : val));
				
			} else {
				if ((mode == ((int)1))) {
					val = ((((mod_41 * ((int)2)) - ((int)1)) * shape) + (cos(((mod_41 * ((t_sample)6.2831853071796)) + ((t_sample)1.5707963267949))) * (((int)1) - shape)));
					
				} else {
					if ((mode == ((int)2))) {
						shape = ((shape <= ((t_sample)0.01)) ? ((t_sample)0.01) : ((shape >= ((t_sample)0.99)) ? ((t_sample)0.99) : shape));
						val = (((mod_41 > shape) * ((int)2)) - ((int)1));
						
					} else {
						if ((mode == ((int)3))) {
							t_sample rand = pink_d(shape);
							val = __m_sah_61(rand, mod_41, ((t_sample)0.5));
							
						} else {
							if ((mode == ((int)4))) {
								t_sample p = __m_rate_62.perform_off(mod_41, ((t_sample)0.0625));
								t_sample rand = pink_d_63(shape);
								int click = __m_change_72((__m_sah_73(rand, p, ((t_sample)0.5)) > ((t_sample)0.5)));
								val = (((click == ((int)1)) * ((int)2)) - ((int)1));
								
							} else {
								if ((mode == ((int)5))) {
									t_sample rand = pink_d_74(shape);
									t_sample iup_84 = (1 / maximum(1, abs(((int)1000))));
									t_sample idown_85 = (1 / maximum(1, abs(((int)1000))));
									__m_slide_83 = fixdenorm((__m_slide_83 + (((__m_sah_86(rand, mod_41, ((t_sample)0.5)) > __m_slide_83) ? iup_84 : idown_85) * (__m_sah_87(rand, mod_41, ((t_sample)0.5)) - __m_slide_83))));
									val = __m_slide_83;
									
								} else {
									if ((mode == ((int)6))) {
										val = triangle(mod_41, ((t_sample)0.5));
										t_sample logval = sqrt(val);
										t_sample expval = (((int)1) - sqrt((((int)1) - val)));
										t_sample mul_610 = (shape * ((int)2));
										t_sample mix_609 = (expval + (mul_610 * (val - expval)));
										t_sample mul_612 = ((shape - ((t_sample)0.5)) * ((int)2));
										t_sample mix_611 = (val + (mul_612 * (logval - val)));
										int cond_88 = (shape < ((t_sample)0.5));
										val = (cond_88 ? mix_609 : mix_611);
										val = ((val * ((int)2)) - ((int)1));
										
									} else {
										if ((mode == ((int)7))) {
											val = triangle(mod_41, ((int)1));
											t_sample logval = sqrt(val);
											t_sample expval = (((int)1) - sqrt((((int)1) - val)));
											t_sample mul_614 = (shape * ((int)2));
											t_sample mix_613 = (expval + (mul_614 * (val - expval)));
											t_sample mul_616 = ((shape - ((t_sample)0.5)) * ((int)2));
											t_sample mix_615 = (val + (mul_616 * (logval - val)));
											int cond_89 = (shape < ((t_sample)0.5));
											val = (cond_89 ? mix_613 : mix_615);
											val = ((val * ((int)2)) - ((int)1));
											
										} else {
											if ((mode == ((int)8))) {
												val = triangle(mod_41, ((int)0));
												t_sample logval = sqrt(val);
												t_sample expval = (((int)1) - sqrt((((int)1) - val)));
												t_sample mul_618 = (shape * ((int)2));
												t_sample mix_617 = (expval + (mul_618 * (val - expval)));
												t_sample mul_620 = ((shape - ((t_sample)0.5)) * ((int)2));
												t_sample mix_619 = (val + (mul_620 * (logval - val)));
												int cond_90 = (shape < ((t_sample)0.5));
												val = (cond_90 ? mix_617 : mix_619);
												val = ((val * ((int)2)) - ((int)1));
												
											};
											
										};
										
									};
									
								};
								
							};
							
						};
						
					};
					
				};
				
			};
			t_sample expr_47 = val;
			t_sample gen_48 = expr_47;
			t_sample clamp_110 = ((gen_48 <= min_91) ? min_91 : ((gen_48 >= ((int)1)) ? ((int)1) : gen_48));
			t_sample sub_624 = (clamp_110 - (-1));
			t_sample scale_621 = ((safepow((sub_624 * ((t_sample)0.5)), ((int)1)) * ((int)1)) + ((int)0));
			t_sample scale_112 = scale_621;
			t_sample mul_111 = (scale_112 * gen_105);
			t_sample add_21 = (mul_111 + mul_19);
			t_sample mul_50 = (add_21 * rsub_103);
			t_sample out4 = (mul_50 + gate_4);
			t_sample orange_627 = (selector_17 - selector_18);
			t_sample sub_628 = (add_21 - ((int)0));
			t_sample scale_625 = ((safepow((sub_628 * ((t_sample)1)), ((int)1)) * orange_627) + selector_18);
			t_sample scale_23 = scale_625;
			t_sample mtof_22 = mtof(scale_23, ((int)440));
			t_sample mul_24 = (mtof_22 * safediv(6.2831853071796, samplerate));
			t_sample cos_33 = cos(mul_24);
			t_sample clamp_37 = ((gen_104 <= ((int)0)) ? ((int)0) : ((gen_104 >= ((t_sample)0.99999)) ? ((t_sample)0.99999) : gen_104));
			t_sample mul_35 = (clamp_37 * ((t_sample)0.125));
			t_sample exp_36 = exp(mul_35);
			t_sample mul_34 = (exp_36 * ((t_sample)0.882497));
			t_sample mul_30 = (mul_34 * mul_34);
			t_sample mul_26 = (mul_30 * m_y_2);
			t_sample mul_32 = (cos_33 * mul_34);
			t_sample mul_31 = (mul_32 * (-2));
			t_sample mul_27 = (mul_31 * m_y_1);
			t_sample add_29 = ((mul_30 + mul_31) + ((int)1));
			t_sample mul_28 = (mul_55 * add_29);
			t_sample sub_25 = (mul_28 - (mul_26 + mul_27));
			t_sample gen_40 = sub_25;
			t_sample y2_next_38 = fixdenorm(m_y_1);
			t_sample y1_next_39 = fixdenorm(sub_25);
			t_sample dcblock_66 = __m_dcblock_92(gen_40);
			t_sample fixdenorm_68 = fixdenorm(dcblock_66);
			t_sample fixnan_67 = fixnan(fixdenorm_68);
			t_sample div_54 = (fixnan_67 * ((t_sample)0.033333333333333));
			t_sample out1 = div_54;
			m_history_28 = history_6_next_8;
			m_history_27 = history_6_next_128;
			m_history_26 = history_95_next_97;
			m_history_24 = history_91_next_99;
			m_history_25 = history_93_next_98;
			m_history_23 = history_95_next_132;
			m_history_21 = history_91_next_130;
			m_history_22 = history_93_next_133;
			m_history_20 = history_95_next_151;
			m_history_18 = history_91_next_145;
			m_history_19 = history_93_next_143;
			m_history_17 = history_95_next_164;
			m_history_15 = history_91_next_158;
			m_history_16 = history_93_next_156;
			m_history_14 = history_95_next_177;
			m_history_12 = history_91_next_173;
			m_history_13 = history_93_next_169;
			m_history_11 = history_95_next_190;
			m_history_9 = history_91_next_186;
			m_history_10 = history_93_next_182;
			m_history_8 = history_74_next_76;
			m_history_7 = history_72_next_77;
			m_history_6 = history_74_next_198;
			m_history_5 = history_72_next_197;
			m_history_4 = history_74_next_205;
			m_history_3 = history_72_next_207;
			m_y_2 = y2_next_38;
			m_y_1 = y1_next_39;
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
			
		};
		return __exception;
		
	};
	inline void set_knob3(t_param _value) {
		m_knob_29 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_footswitch_2(t_param _value) {
		m_footswitch_30 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5(t_param _value) {
		m_knob_31 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob6(t_param _value) {
		m_knob_32 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw2(t_param _value) {
		m_sw_33 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_expression(t_param _value) {
		m_expression_34 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2(t_param _value) {
		m_knob_35 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw1(t_param _value) {
		m_sw_36 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw3(t_param _value) {
		m_sw_37 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4(t_param _value) {
		m_knob_38 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob1(t_param _value) {
		m_knob_39 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_footswitch_1(t_param _value) {
		m_footswitch_40 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline t_sample pink_d(t_sample s) {
		t_sample white = noise();
		m_f_60 = ((((t_sample)0.99886) * m_f_60) + (((t_sample)0.0555179) * white));
		m_f_59 = ((((t_sample)0.99332) * m_f_59) + (((t_sample)0.0750759) * white));
		m_f_58 = ((((t_sample)0.969) * m_f_58) + (((t_sample)0.153852) * white));
		m_f_57 = ((((t_sample)0.8665) * m_f_57) + (((t_sample)0.3104856) * white));
		m_f_56 = ((((t_sample)0.55) * m_f_56) + (((t_sample)0.5329522) * white));
		m_f_55 = (((-((t_sample)0.7616)) * m_f_55) - (((t_sample)0.016898) * white));
		t_sample p = (((((((m_f_60 + m_f_59) + m_f_58) + m_f_57) + m_f_56) + m_f_55) + m_f_54) + (white * ((t_sample)0.5362)));
		t_sample p_46 = (p * ((t_sample)0.144444));
		m_f_54 = (white * ((t_sample)0.115926));
		t_sample outp = ((p_46 * s) + (white * (((int)1) - s)));
		return outp;
		
	};
	inline t_sample pink_d_63(t_sample s) {
		t_sample white = noise();
		m_f_71 = ((((t_sample)0.99886) * m_f_71) + (((t_sample)0.0555179) * white));
		m_f_70 = ((((t_sample)0.99332) * m_f_70) + (((t_sample)0.0750759) * white));
		m_f_69 = ((((t_sample)0.969) * m_f_69) + (((t_sample)0.153852) * white));
		m_f_68 = ((((t_sample)0.8665) * m_f_68) + (((t_sample)0.3104856) * white));
		m_f_67 = ((((t_sample)0.55) * m_f_67) + (((t_sample)0.5329522) * white));
		m_f_66 = (((-((t_sample)0.7616)) * m_f_66) - (((t_sample)0.016898) * white));
		t_sample p = (((((((m_f_71 + m_f_70) + m_f_69) + m_f_68) + m_f_67) + m_f_66) + m_f_65) + (white * ((t_sample)0.5362)));
		t_sample p_46 = (p * ((t_sample)0.144444));
		m_f_65 = (white * ((t_sample)0.115926));
		t_sample outp = ((p_46 * s) + (white * (((int)1) - s)));
		return outp;
		
	};
	inline t_sample pink_d_74(t_sample s) {
		t_sample white = noise();
		m_f_82 = ((((t_sample)0.99886) * m_f_82) + (((t_sample)0.0555179) * white));
		m_f_81 = ((((t_sample)0.99332) * m_f_81) + (((t_sample)0.0750759) * white));
		m_f_80 = ((((t_sample)0.969) * m_f_80) + (((t_sample)0.153852) * white));
		m_f_79 = ((((t_sample)0.8665) * m_f_79) + (((t_sample)0.3104856) * white));
		m_f_78 = ((((t_sample)0.55) * m_f_78) + (((t_sample)0.5329522) * white));
		m_f_77 = (((-((t_sample)0.7616)) * m_f_77) - (((t_sample)0.016898) * white));
		t_sample p = (((((((m_f_82 + m_f_81) + m_f_80) + m_f_79) + m_f_78) + m_f_77) + m_f_76) + (white * ((t_sample)0.5362)));
		t_sample p_46 = (p * ((t_sample)0.144444));
		m_f_76 = (white * ((t_sample)0.115926));
		t_sample outp = ((p_46 * s) + (white * (((int)1) - s)));
		return outp;
		
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
int num_params() { return 12; }

/// Assistive lables for the signal inputs and outputs

const char *gen_kernel_innames[] = { "in1" };
const char *gen_kernel_outnames[] = { "out1", "led1_red", "led1", "led1_blue", "led3_red", "led3_blue", "led3_green", "led2", "relay" };

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
		case 0: self->set_expression(value); break;
		case 1: self->set_footswitch_1(value); break;
		case 2: self->set_footswitch_2(value); break;
		case 3: self->set_knob1(value); break;
		case 4: self->set_knob2(value); break;
		case 5: self->set_knob3(value); break;
		case 6: self->set_knob4(value); break;
		case 7: self->set_knob5(value); break;
		case 8: self->set_knob6(value); break;
		case 9: self->set_sw1(value); break;
		case 10: self->set_sw2(value); break;
		case 11: self->set_sw3(value); break;
		
		default: break;
	}
}

/// Get the value of a parameter of a State object

void getparameter(CommonState *cself, long index, t_param *value) {
	State *self = (State *)cself;
	switch (index) {
		case 0: *value = self->m_expression_34; break;
		case 1: *value = self->m_footswitch_40; break;
		case 2: *value = self->m_footswitch_30; break;
		case 3: *value = self->m_knob_39; break;
		case 4: *value = self->m_knob_35; break;
		case 5: *value = self->m_knob_29; break;
		case 6: *value = self->m_knob_38; break;
		case 7: *value = self->m_knob_31; break;
		case 8: *value = self->m_knob_32; break;
		case 9: *value = self->m_sw_36; break;
		case 10: *value = self->m_sw_33; break;
		case 11: *value = self->m_sw_37; break;
		
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
	self->__commonstate.params = (ParamInfo *)genlib_sysmem_newptr(12 * sizeof(ParamInfo));
	self->__commonstate.numparams = 12;
	// initialize parameter 0 ("m_expression_34")
	pi = self->__commonstate.params + 0;
	pi->name = "expression";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_expression_34;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_footswitch_40")
	pi = self->__commonstate.params + 1;
	pi->name = "footswitch_1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_footswitch_40;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_footswitch_30")
	pi = self->__commonstate.params + 2;
	pi->name = "footswitch_2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_footswitch_30;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob_39")
	pi = self->__commonstate.params + 3;
	pi->name = "knob1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_39;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_knob_35")
	pi = self->__commonstate.params + 4;
	pi->name = "knob2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_35;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 5 ("m_knob_29")
	pi = self->__commonstate.params + 5;
	pi->name = "knob3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_29;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_knob_38")
	pi = self->__commonstate.params + 6;
	pi->name = "knob4";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_38;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_knob_31")
	pi = self->__commonstate.params + 7;
	pi->name = "knob5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_31;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_knob_32")
	pi = self->__commonstate.params + 8;
	pi->name = "knob6";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_32;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 9 ("m_sw_36")
	pi = self->__commonstate.params + 9;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_36;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_sw_33")
	pi = self->__commonstate.params + 10;
	pi->name = "sw2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_33;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_sw_37")
	pi = self->__commonstate.params + 11;
	pi->name = "sw3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_37;
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


} // Envelope_Filter_LFO::
