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
	Change __m_change_55;
	DCBlock __m_dcblock_63;
	int __exception;
	int vectorsize;
	Phasor __m_phasor_57;
	Phasor __m_phasor_53;
	PlusEquals __m_pluseq_45;
	PlusEquals __m_pluseq_56;
	Sah __m_sah_43;
	Sah __m_sah_46;
	Sah __m_sah_59;
	SineCycle __m_cycle_54;
	SineData __sinedata;
	t_sample m_sw_34;
	t_sample m_d_2;
	t_sample m_footswitch_35;
	t_sample m_knob_33;
	t_sample m_footswitch_31;
	t_sample m_knob_36;
	t_sample m_knob_32;
	t_sample m_knob_37;
	t_sample m_history_42;
	t_sample m_knob_39;
	t_sample __m_slide_48;
	t_sample samples_to_seconds;
	t_sample m_expression_38;
	t_sample samplerate;
	t_sample m_sw_41;
	t_sample m_sw_30;
	t_sample m_knob_40;
	t_sample m_d_1;
	t_sample m_history_29;
	t_sample m_history_26;
	t_sample m_history_10;
	t_sample m_history_9;
	t_sample m_history_11;
	t_sample m_history_12;
	t_sample m_history_13;
	t_sample m_history_8;
	t_sample m_history_6;
	t_sample m_d_3;
	t_sample m_history_7;
	t_sample m_d_4;
	t_sample m_history_5;
	t_sample m_history_28;
	t_sample m_history_14;
	t_sample m_history_16;
	t_sample m_history_23;
	t_sample m_history_22;
	t_sample m_history_24;
	t_sample m_history_25;
	t_sample m_history_15;
	t_sample m_history_21;
	t_sample m_history_19;
	t_sample m_history_20;
	t_sample m_history_17;
	t_sample m_history_18;
	t_sample m_history_27;
	// re-initialize all member variables;
	inline void reset(t_param __sr, int __vs) {
		__exception = 0;
		vectorsize = __vs;
		samplerate = __sr;
		m_d_1 = ((int)0);
		m_d_2 = ((int)0);
		m_d_3 = ((int)0);
		m_d_4 = ((int)0);
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
		m_history_29 = ((int)0);
		m_sw_30 = ((int)0);
		m_footswitch_31 = ((int)0);
		m_knob_32 = ((int)0);
		m_knob_33 = ((int)0);
		m_sw_34 = ((int)0);
		m_footswitch_35 = ((int)0);
		m_knob_36 = ((int)0);
		m_knob_37 = ((int)0);
		m_expression_38 = ((int)0);
		m_knob_39 = ((int)0);
		m_knob_40 = ((int)0);
		m_sw_41 = ((int)0);
		m_history_42 = ((int)0);
		__m_sah_43.reset(0);
		__m_change_44.reset(0);
		__m_pluseq_45.reset(0);
		__m_sah_46.reset(0);
		__m_slide_48 = 0;
		samples_to_seconds = (1 / samplerate);
		__m_phasor_53.reset(0);
		__m_cycle_54.reset(samplerate, 0);
		__m_change_55.reset(0);
		__m_pluseq_56.reset(0);
		__m_phasor_57.reset(0);
		__m_sah_59.reset(0);
		__m_dcblock_63.reset();
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
		t_sample mstosamps_240 = (((int)10) * (samplerate * 0.001));
		t_sample mstosamps_239 = (((int)100) * (samplerate * 0.001));
		t_sample iup_49 = (1 / maximum(1, abs(mstosamps_240)));
		t_sample idown_50 = (1 / maximum(1, abs(mstosamps_239)));
		samples_to_seconds = (1 / samplerate);
		// the main sample loop;
		while ((__n--)) {
			const t_sample in1 = (*(__in1++));
			t_sample sah_115 = __m_sah_43(m_history_42, m_sw_30, ((int)0));
			t_sample gen_124 = sah_115;
			t_sample rsub_113 = (((int)1) - sah_115);
			t_sample history_114_next_116 = fixdenorm(rsub_113);
			t_sample out5 = gen_124;
			t_sample mix_1333 = (m_history_29 + (((t_sample)0.0042742627044161) * (m_knob_40 - m_history_29)));
			t_sample mix_143 = mix_1333;
			t_sample mix_1334 = (m_history_28 + (((t_sample)0.0042742627044161) * (mix_143 - m_history_28)));
			t_sample mix_141 = mix_1334;
			t_sample mix_1335 = (m_history_27 + (((t_sample)0.0042742627044161) * (mix_141 - m_history_27)));
			t_sample mix_139 = mix_1335;
			t_sample gen_149 = mix_139;
			t_sample history_144_next_146 = fixdenorm(mix_143);
			t_sample history_142_next_147 = fixdenorm(mix_141);
			t_sample history_140_next_148 = fixdenorm(mix_139);
			t_sample expr_915 = (((int)1) - sqrt((((int)1) - gen_149)));
			t_sample mul_194 = (in1 * ((int)30));
			t_sample mix_1336 = (m_history_26 + (((t_sample)0.0042742627044161) * (m_knob_39 - m_history_26)));
			t_sample mix_921 = mix_1336;
			t_sample mix_1337 = (m_history_25 + (((t_sample)0.0042742627044161) * (mix_921 - m_history_25)));
			t_sample mix_925 = mix_1337;
			t_sample mix_1338 = (m_history_24 + (((t_sample)0.0042742627044161) * (mix_925 - m_history_24)));
			t_sample mix_924 = mix_1338;
			t_sample gen_224 = mix_924;
			t_sample history_144_next_928 = fixdenorm(mix_921);
			t_sample history_142_next_923 = fixdenorm(mix_925);
			t_sample history_140_next_927 = fixdenorm(mix_924);
			t_sample sub_1342 = (gen_224 - ((int)0));
			t_sample scale_1339 = ((safepow((sub_1342 * ((t_sample)1)), ((int)1)) * ((int)49)) + ((int)1));
			t_sample scale_162 = scale_1339;
			t_sample mix_1343 = (m_history_23 + (((t_sample)0.0042742627044161) * (m_knob_33 - m_history_23)));
			t_sample mix_934 = mix_1343;
			t_sample mix_1344 = (m_history_22 + (((t_sample)0.0042742627044161) * (mix_934 - m_history_22)));
			t_sample mix_939 = mix_1344;
			t_sample mix_1345 = (m_history_21 + (((t_sample)0.0042742627044161) * (mix_939 - m_history_21)));
			t_sample mix_936 = mix_1345;
			t_sample gen_229 = mix_936;
			t_sample history_144_next_941 = fixdenorm(mix_934);
			t_sample history_142_next_935 = fixdenorm(mix_939);
			t_sample history_140_next_940 = fixdenorm(mix_936);
			int change_227 = __m_change_44(m_footswitch_31);
			int clamp_226 = ((change_227 <= ((int)0)) ? ((int)0) : ((change_227 >= ((int)1)) ? ((int)1) : change_227));
			int plusequals_228 = __m_pluseq_45.post(clamp_226, ((int)0), 0, 2);
			t_sample out9 = plusequals_228;
			int rsub_223 = (((int)1) - plusequals_228);
			t_sample out8 = rsub_223;
			t_sample sah_950 = __m_sah_46(m_history_20, m_sw_30, ((int)0));
			t_sample gen_123 = sah_950;
			t_sample rsub_949 = (((int)1) - sah_950);
			t_sample history_114_next_948 = fixdenorm(rsub_949);
			t_sample add_120 = (gen_123 + ((int)1));
			t_sample choice_47 = int(add_120);
			t_sample gate_121 = (((choice_47 >= 1) && (choice_47 < 2)) ? ((int)1) : 0);
			t_sample gate_122 = ((choice_47 >= 2) ? ((int)1) : 0);
			t_sample out3 = gate_121;
			t_sample out4 = gate_122;
			t_sample mix_1346 = (m_history_19 + (((t_sample)0.0042742627044161) * (m_knob_36 - m_history_19)));
			t_sample mix_961 = mix_1346;
			t_sample mix_1347 = (m_history_18 + (((t_sample)0.0042742627044161) * (mix_961 - m_history_18)));
			t_sample mix_956 = mix_1347;
			t_sample mix_1348 = (m_history_17 + (((t_sample)0.0042742627044161) * (mix_956 - m_history_17)));
			t_sample mix_959 = mix_1348;
			t_sample gen_222 = mix_959;
			t_sample history_144_next_958 = fixdenorm(mix_961);
			t_sample history_142_next_952 = fixdenorm(mix_956);
			t_sample history_140_next_955 = fixdenorm(mix_959);
			t_sample mix_1349 = (m_history_16 + (((t_sample)0.0042742627044161) * (m_knob_32 - m_history_16)));
			t_sample mix_974 = mix_1349;
			t_sample mix_1350 = (m_history_15 + (((t_sample)0.0042742627044161) * (mix_974 - m_history_15)));
			t_sample mix_969 = mix_1350;
			t_sample mix_1351 = (m_history_14 + (((t_sample)0.0042742627044161) * (mix_969 - m_history_14)));
			t_sample mix_972 = mix_1351;
			t_sample gen_225 = mix_972;
			t_sample history_144_next_971 = fixdenorm(mix_974);
			t_sample history_142_next_965 = fixdenorm(mix_969);
			t_sample history_140_next_968 = fixdenorm(mix_972);
			t_sample mix_1352 = (m_history_13 + (((t_sample)0.0042742627044161) * (m_knob_37 - m_history_13)));
			t_sample mix_987 = mix_1352;
			t_sample mix_1353 = (m_history_12 + (((t_sample)0.0042742627044161) * (mix_987 - m_history_12)));
			t_sample mix_981 = mix_1353;
			t_sample mix_1354 = (m_history_11 + (((t_sample)0.0042742627044161) * (mix_981 - m_history_11)));
			t_sample mix_984 = mix_1354;
			t_sample gen_221 = mix_984;
			t_sample history_144_next_983 = fixdenorm(mix_987);
			t_sample history_142_next_978 = fixdenorm(mix_981);
			t_sample history_140_next_980 = fixdenorm(mix_984);
			t_sample abs_236 = fabs(mul_194);
			t_sample mix_1355 = (m_history_10 + (((t_sample)0.0014247580910283) * (m_sw_41 - m_history_10)));
			t_sample mix_204 = mix_1355;
			t_sample mix_1356 = (m_history_9 + (((t_sample)0.0014247580910283) * (mix_204 - m_history_9)));
			t_sample mix_202 = mix_1356;
			t_sample gen_214 = mix_202;
			t_sample history_205_next_207 = fixdenorm(mix_204);
			t_sample history_203_next_208 = fixdenorm(mix_202);
			t_sample mul_213 = (gen_214 * ((int)4));
			t_sample round_212 = round(mul_213);
			t_sample clamp_132 = ((round_212 <= ((int)1)) ? ((int)1) : ((round_212 >= ((int)3)) ? ((int)3) : round_212));
			t_sample sw_168 = clamp_132;
			int gt_160 = (gen_229 > ((t_sample)0.01));
			__m_slide_48 = fixdenorm((__m_slide_48 + (((abs_236 > __m_slide_48) ? iup_49 : idown_50) * (abs_236 - __m_slide_48))));
			t_sample slide_242 = __m_slide_48;
			t_sample clamp_241 = ((slide_242 <= ((int)0)) ? ((int)0) : ((slide_242 >= ((int)1)) ? ((int)1) : slide_242));
			t_sample mul_182 = (gen_222 * clamp_241);
			t_sample add_235 = (gen_229 + mul_182);
			t_sample clamp_232 = ((add_235 <= ((int)0)) ? ((int)0) : ((add_235 >= ((int)1)) ? ((int)1) : add_235));
			t_sample expr_920 = (((int)1) - sqrt((((int)1) - clamp_232)));
			t_sample mul_181 = (gen_221 * clamp_241);
			t_sample mix_1357 = (m_history_8 + (((t_sample)0.0014247580910283) * (m_sw_30 - m_history_8)));
			t_sample mix_995 = mix_1357;
			t_sample mix_1358 = (m_history_7 + (((t_sample)0.0014247580910283) * (mix_995 - m_history_7)));
			t_sample mix_993 = mix_1358;
			t_sample gen_220 = mix_993;
			t_sample history_205_next_992 = fixdenorm(mix_995);
			t_sample history_203_next_997 = fixdenorm(mix_993);
			t_sample mul_219 = (gen_220 * ((int)4));
			t_sample round_218 = round(mul_219);
			t_sample clamp_195 = ((round_218 <= ((int)1)) ? ((int)1) : ((round_218 >= ((int)3)) ? ((int)3) : round_218));
			t_sample sw_196 = clamp_195;
			t_sample choice_51 = int(sw_196);
			t_sample selector_180 = ((choice_51 >= 3) ? ((int)24) : ((choice_51 >= 2) ? ((int)28) : ((choice_51 >= 1) ? ((int)65) : 0)));
			t_sample choice_52 = int(sw_196);
			t_sample selector_179 = ((choice_52 >= 3) ? ((int)110) : ((choice_52 >= 2) ? ((int)80) : ((choice_52 >= 1) ? ((int)97) : 0)));
			t_sample sub_1362 = (expr_920 - ((int)0));
			t_sample scale_1359 = ((safepow((sub_1362 * ((t_sample)1)), ((int)1)) * ((int)12)) + ((int)0));
			t_sample scale_234 = scale_1359;
			t_sample phasor_156 = __m_phasor_53(scale_234, samples_to_seconds);
			__m_cycle_54.phase(phasor_156);
			t_sample cycle_186 = __m_cycle_54(__sinedata);
			t_sample cycleindex_187 = __m_cycle_54.phase();
			t_sample noise_153 = noise();
			int change_167 = __m_change_55(m_footswitch_35);
			int clamp_166 = ((change_167 <= ((int)0)) ? ((int)0) : ((change_167 >= ((int)1)) ? ((int)1) : change_167));
			int plusequals_165 = __m_pluseq_56.post(clamp_166, ((int)0), 0, 2);
			int add_164 = (plusequals_165 + ((int)1));
			int state_157 = add_164;
			t_sample sub_1366 = (expr_915 - ((int)0));
			t_sample scale_1363 = ((safepow((sub_1366 * ((t_sample)1)), ((int)1)) * ((int)12)) + ((int)0));
			t_sample scale_138 = scale_1363;
			t_sample phasor_150 = __m_phasor_57(scale_138, samples_to_seconds);
			t_sample sub_1370 = (phasor_150 - ((int)0));
			t_sample scale_1367 = ((safepow((sub_1370 * ((t_sample)1)), ((int)1)) * ((int)2)) + (-1));
			t_sample scale_135 = scale_1367;
			int gt_136 = (phasor_150 > ((t_sample)0.5));
			int sub_1374 = (gt_136 - ((int)0));
			t_sample scale_1371 = ((safepow((sub_1374 * ((t_sample)1)), ((int)1)) * ((int)2)) + (-1));
			t_sample scale_134 = scale_1371;
			t_sample mix_1375 = (m_history_6 + (((t_sample)0.0014247580910283) * (m_sw_34 - m_history_6)));
			t_sample mix_1002 = mix_1375;
			t_sample mix_1376 = (m_history_5 + (((t_sample)0.0014247580910283) * (mix_1002 - m_history_5)));
			t_sample mix_1006 = mix_1376;
			t_sample gen_217 = mix_1006;
			t_sample history_205_next_1001 = fixdenorm(mix_1002);
			t_sample history_203_next_1003 = fixdenorm(mix_1006);
			t_sample mul_216 = (gen_217 * ((int)4));
			t_sample round_215 = round(mul_216);
			t_sample clamp_133 = ((round_215 <= ((int)1)) ? ((int)1) : ((round_215 >= ((int)3)) ? ((int)3) : round_215));
			t_sample sw_152 = clamp_133;
			t_sample choice_58 = int(sw_152);
			t_sample selector_151 = ((choice_58 >= 3) ? scale_134 : ((choice_58 >= 2) ? scale_135 : ((choice_58 >= 1) ? noise_153 : 0)));
			t_sample sah_154 = __m_sah_59(selector_151, phasor_156, ((t_sample)0.5));
			int choice_60 = state_157;
			t_sample selector_155 = ((choice_60 >= 2) ? sah_154 : ((choice_60 >= 1) ? cycle_186 : 0));
			t_sample switch_159 = (gt_160 ? selector_155 : ((int)-1));
			t_sample sub_1380 = (switch_159 - (-1));
			t_sample scale_1377 = ((safepow((sub_1380 * ((t_sample)0.5)), ((int)1)) * ((int)1)) + ((int)0));
			t_sample scale_231 = scale_1377;
			t_sample mul_230 = (scale_231 * gen_225);
			t_sample add_183 = (mul_230 + mul_181);
			t_sample orange_1383 = (selector_179 - selector_180);
			t_sample sub_1384 = (add_183 - ((int)0));
			t_sample scale_1381 = ((safepow((sub_1384 * ((t_sample)1)), ((int)1)) * orange_1383) + selector_180);
			t_sample scale_185 = scale_1381;
			t_sample mtof_184 = mtof(scale_185, ((int)440));
			t_sample freq = mtof_184;
			t_sample Q = scale_162;
			t_sample q1 = safediv(((int)1), Q);
			t_sample f1 = sin(safediv((((t_sample)6.2831853071796) * freq), samplerate));
			t_sample L = (m_d_3 + (f1 * m_d_4));
			t_sample H = ((mul_194 - L) - (q1 * m_d_4));
			t_sample B = ((f1 * H) + m_d_4);
			m_d_4 = B;
			m_d_3 = L;
			t_sample expr_916 = L;
			t_sample expr_917 = H;
			t_sample expr_918 = B;
			t_sample choice_61 = int(sw_168);
			t_sample selector_161 = ((choice_61 >= 3) ? expr_918 : ((choice_61 >= 2) ? expr_917 : ((choice_61 >= 1) ? expr_916 : 0)));
			t_sample add_125 = (scale_185 + ((int)12));
			t_sample mtof_126 = mtof(add_125, ((int)440));
			t_sample freq_1009 = mtof_126;
			t_sample Q_1012 = scale_162;
			t_sample q_1017 = safediv(((int)1), Q_1012);
			t_sample f_1016 = sin(safediv((((t_sample)6.2831853071796) * freq_1009), samplerate));
			t_sample L_1015 = (m_d_1 + (f_1016 * m_d_2));
			t_sample H_1014 = ((selector_161 - L_1015) - (q_1017 * m_d_2));
			t_sample B_1010 = ((f_1016 * H_1014) + m_d_2);
			m_d_2 = B_1010;
			m_d_1 = L_1015;
			t_sample choice_62 = int(sw_168);
			t_sample selector_127 = ((choice_62 >= 3) ? B_1010 : ((choice_62 >= 2) ? H_1014 : ((choice_62 >= 1) ? L_1015 : 0)));
			t_sample dcblock_197 = __m_dcblock_63(selector_127);
			t_sample fixdenorm_199 = fixdenorm(dcblock_197);
			t_sample fixnan_198 = fixnan(fixdenorm_199);
			t_sample div_193 = (fixnan_198 * ((t_sample)0.033333333333333));
			t_sample out1 = div_193;
			m_history_42 = history_114_next_116;
			m_history_29 = history_144_next_146;
			m_history_27 = history_140_next_148;
			m_history_28 = history_142_next_147;
			m_history_26 = history_144_next_928;
			m_history_24 = history_140_next_927;
			m_history_25 = history_142_next_923;
			m_history_23 = history_144_next_941;
			m_history_21 = history_140_next_940;
			m_history_22 = history_142_next_935;
			m_history_20 = history_114_next_948;
			m_history_19 = history_144_next_958;
			m_history_17 = history_140_next_955;
			m_history_18 = history_142_next_952;
			m_history_16 = history_144_next_971;
			m_history_14 = history_140_next_968;
			m_history_15 = history_142_next_965;
			m_history_13 = history_144_next_983;
			m_history_11 = history_140_next_980;
			m_history_12 = history_142_next_978;
			m_history_10 = history_205_next_207;
			m_history_9 = history_203_next_208;
			m_history_8 = history_205_next_992;
			m_history_7 = history_203_next_997;
			m_history_6 = history_205_next_1001;
			m_history_5 = history_203_next_1003;
			// assign results to output buffer;
			(*(__out1++)) = out1;
			(*(__out2++)) = 0;
			(*(__out3++)) = out3;
			(*(__out4++)) = out4;
			(*(__out5++)) = out5;
			(*(__out6++)) = 0;
			(*(__out7++)) = 0;
			(*(__out8++)) = out8;
			(*(__out9++)) = out9;
			
		};
		return __exception;
		
	};
	inline void set_sw1(t_param _value) {
		m_sw_30 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_footswitch_1(t_param _value) {
		m_footswitch_31 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob2(t_param _value) {
		m_knob_32 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob1(t_param _value) {
		m_knob_33 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw2(t_param _value) {
		m_sw_34 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_footswitch_2(t_param _value) {
		m_footswitch_35 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob5(t_param _value) {
		m_knob_36 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob4(t_param _value) {
		m_knob_37 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_expression(t_param _value) {
		m_expression_38 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob6(t_param _value) {
		m_knob_39 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_knob3(t_param _value) {
		m_knob_40 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
	};
	inline void set_sw3(t_param _value) {
		m_sw_41 = (_value < 0 ? 0 : (_value > 1 ? 1 : _value));
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
const char *gen_kernel_outnames[] = { "out1", "out2", "led1", "led2", "relay", "out6", "out7", "led2", "relay" };

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
		case 0: *value = self->m_expression_38; break;
		case 1: *value = self->m_footswitch_31; break;
		case 2: *value = self->m_footswitch_35; break;
		case 3: *value = self->m_knob_33; break;
		case 4: *value = self->m_knob_32; break;
		case 5: *value = self->m_knob_40; break;
		case 6: *value = self->m_knob_37; break;
		case 7: *value = self->m_knob_36; break;
		case 8: *value = self->m_knob_39; break;
		case 9: *value = self->m_sw_30; break;
		case 10: *value = self->m_sw_34; break;
		case 11: *value = self->m_sw_41; break;
		
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
	// initialize parameter 0 ("m_expression_38")
	pi = self->__commonstate.params + 0;
	pi->name = "expression";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_expression_38;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 1 ("m_footswitch_31")
	pi = self->__commonstate.params + 1;
	pi->name = "footswitch_1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_footswitch_31;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 2 ("m_footswitch_35")
	pi = self->__commonstate.params + 2;
	pi->name = "footswitch_2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_footswitch_35;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 3 ("m_knob_33")
	pi = self->__commonstate.params + 3;
	pi->name = "knob1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_33;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 4 ("m_knob_32")
	pi = self->__commonstate.params + 4;
	pi->name = "knob2";
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
	// initialize parameter 5 ("m_knob_40")
	pi = self->__commonstate.params + 5;
	pi->name = "knob3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_40;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 6 ("m_knob_37")
	pi = self->__commonstate.params + 6;
	pi->name = "knob4";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_37;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 7 ("m_knob_36")
	pi = self->__commonstate.params + 7;
	pi->name = "knob5";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_knob_36;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 8 ("m_knob_39")
	pi = self->__commonstate.params + 8;
	pi->name = "knob6";
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
	// initialize parameter 9 ("m_sw_30")
	pi = self->__commonstate.params + 9;
	pi->name = "sw1";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_30;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 10 ("m_sw_34")
	pi = self->__commonstate.params + 10;
	pi->name = "sw2";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_34;
	pi->defaultref = 0;
	pi->hasinputminmax = false;
	pi->inputmin = 0;
	pi->inputmax = 1;
	pi->hasminmax = true;
	pi->outputmin = 0;
	pi->outputmax = 1;
	pi->exp = 0;
	pi->units = "";		// no units defined
	// initialize parameter 11 ("m_sw_41")
	pi = self->__commonstate.params + 11;
	pi->name = "sw3";
	pi->paramtype = GENLIB_PARAMTYPE_FLOAT;
	pi->defaultvalue = self->m_sw_41;
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
