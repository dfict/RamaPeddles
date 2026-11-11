{
	"patcher" : 	{
		"fileversion" : 1,
		"appversion" : 		{
			"major" : 8,
			"minor" : 6,
			"revision" : 4,
			"architecture" : "x64",
			"modernui" : 1
		}
,
		"classnamespace" : "box",
		"rect" : [ 34.0, 100.0, 1306.0, 812.0 ],
		"bglocked" : 0,
		"openinpresentation" : 0,
		"default_fontsize" : 12.0,
		"default_fontface" : 0,
		"default_fontname" : "Arial",
		"gridonopen" : 1,
		"gridsize" : [ 15.0, 15.0 ],
		"gridsnaponopen" : 1,
		"objectsnaponopen" : 1,
		"statusbarvisible" : 2,
		"toolbarvisible" : 1,
		"lefttoolbarpinned" : 0,
		"toptoolbarpinned" : 0,
		"righttoolbarpinned" : 0,
		"bottomtoolbarpinned" : 0,
		"toolbars_unpinned_last_save" : 0,
		"tallnewobj" : 0,
		"boxanimatetime" : 200,
		"enablehscroll" : 1,
		"enablevscroll" : 1,
		"devicewidth" : 0.0,
		"description" : "",
		"digest" : "",
		"tags" : "",
		"style" : "",
		"subpatcher_template" : "",
		"assistshowspatchername" : 0,
		"boxes" : [ 			{
				"box" : 				{
					"id" : "obj-6",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 466.400006949901581, 297.600004434585571, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-9",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 466.400006949901581, 332.800004959106445, 47.0, 22.0 ],
					"text" : "sw8 $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-10",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 372.000005543231964, 348.00000536441803, 58.0, 22.0 ],
					"text" : "knob3 $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-7",
					"maxclass" : "live.dial",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 388.800005793571472, 280.800004363059998, 41.0, 48.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "knob3_harmonics",
							"parameter_mmax" : 1.0,
							"parameter_modmode" : 3,
							"parameter_shortname" : "Harmonics",
							"parameter_type" : 0,
							"parameter_unitstyle" : 0
						}

					}
,
					"varname" : "live.dial"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-2",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "bang" ],
					"patching_rect" : [ 487.200007259845734, 12.800000190734863, 58.0, 22.0 ],
					"text" : "loadbang"
				}

			}
, 			{
				"box" : 				{
					"hidden" : 1,
					"id" : "obj-4",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 487.200007259845734, 42.400000631809235, 213.0, 22.0 ],
					"text" : "target FunBox.json, samplerate 48kHz"
				}

			}
, 			{
				"box" : 				{
					"args" : [ "FunBox.json" ],
					"bgmode" : 0,
					"border" : 0,
					"clickthrough" : 0,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-83",
					"lockeddragscroll" : 0,
					"lockedsize" : 0,
					"maxclass" : "bpatcher",
					"name" : "oopsy.maxpat",
					"numinlets" : 1,
					"numoutlets" : 0,
					"offset" : [ 0.0, 0.0 ],
					"patching_rect" : [ 487.200007259845734, 77.600001156330109, 215.0, 135.0 ],
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"bgmode" : 0,
					"border" : 0,
					"clickthrough" : 0,
					"enablehscroll" : 0,
					"enablevscroll" : 0,
					"id" : "obj-8",
					"lockeddragscroll" : 0,
					"lockedsize" : 0,
					"maxclass" : "bpatcher",
					"name" : "testinput_bpatch.maxpat",
					"numinlets" : 0,
					"numoutlets" : 1,
					"offset" : [ 0.0, 0.0 ],
					"outlettype" : [ "signal" ],
					"patching_rect" : [ 47.200000703334808, 12.800000190734863, 360.0, 260.0 ],
					"viewvisibility" : 1
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-24",
					"maxclass" : "toggle",
					"numinlets" : 1,
					"numoutlets" : 1,
					"outlettype" : [ "int" ],
					"parameter_enable" : 0,
					"patching_rect" : [ 107.20000159740448, 292.800004363059998, 24.0, 24.0 ]
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-25",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 107.20000159740448, 328.000004887580872, 47.0, 22.0 ],
					"text" : "sw7 $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-3",
					"maxclass" : "live.dial",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 172.000002562999725, 292.800004363059998, 41.0, 48.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "knob1_mix",
							"parameter_mmax" : 1.0,
							"parameter_modmode" : 3,
							"parameter_shortname" : "Mix",
							"parameter_type" : 0,
							"parameter_unitstyle" : 1
						}

					}
,
					"varname" : "live.dial[1]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-12",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 172.000002562999725, 352.800005257129669, 81.0, 22.0 ],
					"text" : "knob1 $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-5",
					"maxclass" : "live.dial",
					"numinlets" : 1,
					"numoutlets" : 2,
					"outlettype" : [ "", "float" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 267.200003981590271, 292.800004363059998, 41.0, 48.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "knob2_density",
							"parameter_mmax" : 1.0,
							"parameter_modmode" : 3,
							"parameter_shortname" : "Rate",
							"parameter_type" : 0,
							"parameter_unitstyle" : 1
						}

					}
,
					"varname" : "live.dial[2]"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-17",
					"maxclass" : "message",
					"numinlets" : 2,
					"numoutlets" : 1,
					"outlettype" : [ "" ],
					"patching_rect" : [ 267.200003981590271, 352.800005257129669, 81.0, 22.0 ],
					"text" : "knob2 $1"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-1",
					"maxclass" : "newobj",
					"numinlets" : 1,
					"numoutlets" : 4,
					"outlettype" : [ "signal", "signal", "signal", "signal" ],
					"patcher" : 					{
						"fileversion" : 1,
						"appversion" : 						{
							"major" : 8,
							"minor" : 6,
							"revision" : 4,
							"architecture" : "x64",
							"modernui" : 1
						}
,
						"classnamespace" : "dsp.gen",
						"rect" : [ 187.0, 100.0, 1180.0, 812.0 ],
						"bglocked" : 0,
						"openinpresentation" : 0,
						"default_fontsize" : 12.0,
						"default_fontface" : 0,
						"default_fontname" : "Arial",
						"gridonopen" : 1,
						"gridsize" : [ 15.0, 15.0 ],
						"gridsnaponopen" : 1,
						"objectsnaponopen" : 1,
						"statusbarvisible" : 2,
						"toolbarvisible" : 1,
						"lefttoolbarpinned" : 0,
						"toptoolbarpinned" : 0,
						"righttoolbarpinned" : 0,
						"bottomtoolbarpinned" : 0,
						"toolbars_unpinned_last_save" : 0,
						"tallnewobj" : 0,
						"boxanimatetime" : 200,
						"enablehscroll" : 1,
						"enablevscroll" : 1,
						"devicewidth" : 0.0,
						"description" : "",
						"digest" : "",
						"tags" : "",
						"style" : "",
						"subpatcher_template" : "",
						"assistshowspatchername" : 0,
						"boxes" : [ 							{
								"box" : 								{
									"id" : "obj-7",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 545.132787227630615, 8.849558234214783, 67.0, 22.0 ],
									"text" : "param sw7"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-1",
									"maxclass" : "newobj",
									"numinlets" : 0,
									"numoutlets" : 1,
									"outlettype" : [ "" ],
									"patching_rect" : [ 276.0, 44.0, 28.0, 22.0 ],
									"text" : "in 1"
								}

							}
, 							{
								"box" : 								{
									"code" : "// 2-second buffer at 48kHz\nData buf(96000);\nHistory wptr(0);\nHistory timer(4800);\nHistory hold_timer(0);\nHistory hold_total(24000);\nHistory is_holding(0);\nHistory grain_len_samps(24000);\nHistory step_idx(0);\nHistory anchor(0);\n\n// Multi-voice Phase and Pitch speeds\nHistory phase0(0);\nHistory phase1(0);\nHistory phase2(0);\nHistory speed1(1.5);\nHistory speed2(2.0);\n\n// Hardware controls\nParam knob1(0.7, min=0, max=1); // Base Wet Mix\nParam knob2(0.5, min=0, max=1); // Capture Rate / Frequency\nParam knob3(0.5, min=0, max=1); // Choral Harmonics Mix\nParam sw8(0, min=0, max=1);     // Toggle Switch 1\nParam sw7(0, min=0, max=1);     // Footswitch 1\n\n// Footswitch software latching\nHistory prev_foot(0);\nHistory is_active(1); // Defaults to ON\n\nfoot_trig = (sw7 > 0.5);\nif (foot_trig && !prev_foot) {\n    is_active = 1 - is_active;\n}\nprev_foot = foot_trig;\nactive = is_active || (sw8 > 0.5);\n\n// Continuous Dry Audio Buffer Write\ndry = in1;\npoke(buf, in1, wptr);\nwptr = wrap(wptr + 1, 0, dim(buf));\n\nsr = samplerate;\nmin_hold = floor(sr * 0.40); // 400ms minimum hold\nmax_hold = floor(sr * 2.00); // 2.0s maximum hold\n\n// --- Trigger & Choral Interval Selection ---\nif (is_holding == 0) {\n    timer = timer - 1;\n    if (timer <= 0) {\n        is_holding = 1;\n        anchor = wptr;\n        \n        // Random hold duration\n        rnd = abs(noise());\n        hold_total = min_hold + floor(rnd * (max_hold - min_hold));\n        hold_timer = hold_total;\n        \n        // Longer grain slice sizes: 400ms to 1200ms\n        step_idx = wrap(step_idx + 1, 0, 5);\n        grain_ms = 400.0 + (step_idx * 200.0);\n        grain_len_samps = max(100, floor(grain_ms * 0.001 * sr));\n        \n        phase0 = 0;\n        phase1 = 0;\n        phase2 = 0;\n        \n        // Pick random musical cluster interval for Voice 1\n        r1 = abs(noise());\n        detune1 = (abs(noise()) * 0.016) - 0.008; // Subtle tape flutter\n        if (r1 < 0.20)      { speed1 = 0.5000 + detune1; } // Sub-octave (-12st)\n        else if (r1 < 0.40) { speed1 = 1.2599 + detune1; } // Major 3rd (+4st)\n        else if (r1 < 0.60) { speed1 = 1.3348 + detune1; } // Perfect 4th (+5st)\n        else if (r1 < 0.80) { speed1 = 1.4983 + detune1; } // Perfect 5th (+7st)\n        else                { speed1 = 2.0000 + detune1; } // Octave up (+12st)\n        \n        // Pick random musical cluster interval for Voice 2\n        r2 = abs(noise());\n        detune2 = (abs(noise()) * 0.016) - 0.008;\n        if (r2 < 0.25)      { speed2 = 1.4983 + detune2; } // Perfect 5th (+7st)\n        else if (r2 < 0.50) { speed2 = 1.7818 + detune2; } // Minor 7th (+10st)\n        else if (r2 < 0.75) { speed2 = 2.0000 + detune2; } // Octave up (+12st)\n        else                { speed2 = 2.9966 + detune2; } // Octave + 5th (+19st)\n    }\n} else {\n    hold_timer = hold_timer - 1;\n    if (hold_timer <= 0) {\n        is_holding = 0;\n        rnd_wait = abs(noise());\n        wait_sec = 0.08 + (rnd_wait * 2.5 * pow(1.0 - knob2, 2));\n        timer = max(500, floor(wait_sec * sr));\n    }\n}\n\n// --- Granular Playback with Interpolation ---\nwet_base = 0;\nwet_v1 = 0;\nwet_v2 = 0;\n\nif (is_holding == 1) {\n    buf_len = dim(buf);\n    \n    // Hold fade envelope to avoid clicks at start/finish\n    hold_env = 1.0;\n    fade_samps = floor(0.015 * sr);\n    elapsed = hold_total - hold_timer;\n    if (elapsed < fade_samps) {\n        hold_env = elapsed / fade_samps;\n    } else if (hold_timer < fade_samps) {\n        hold_env = hold_timer / fade_samps;\n    }\n\n    // --- Voice 0: Root Pitch (1.0x) ---\n    norm0 = phase0 / grain_len_samps;\n    win0 = 0.5 * (1.0 - cos(6.28318530718 * norm0));\n    pos0 = wrap(anchor - grain_len_samps + phase0, 0, buf_len);\n    wet_base = peek(buf, floor(pos0), 0) * win0 * hold_env;\n    phase0 = wrap(phase0 + 1, 0, grain_len_samps);\n\n    // --- Voice 1: Cluster Harmonic 1 (Linear Interpolation) ---\n    norm1 = phase1 / grain_len_samps;\n    win1 = 0.5 * (1.0 - cos(6.28318530718 * norm1));\n    pos1 = wrap(anchor - grain_len_samps + (phase1 * speed1), 0, buf_len);\n    i1 = floor(pos1);\n    f1 = pos1 - i1;\n    s1_a = peek(buf, i1, 0);\n    s1_b = peek(buf, wrap(i1 + 1, 0, buf_len), 0);\n    wet_v1 = (s1_a + f1 * (s1_b - s1_a)) * win1 * hold_env;\n    phase1 = wrap(phase1 + 1, 0, grain_len_samps);\n\n    // --- Voice 2: Cluster Harmonic 2 (Linear Interpolation) ---\n    norm2 = phase2 / grain_len_samps;\n    win2 = 0.5 * (1.0 - cos(6.28318530718 * norm2));\n    pos2 = wrap(anchor - grain_len_samps + (phase2 * speed2), 0, buf_len);\n    i2 = floor(pos2);\n    f2 = pos2 - i2;\n    s2_a = peek(buf, i2, 0);\n    s2_b = peek(buf, wrap(i2 + 1, 0, buf_len), 0);\n    wet_v2 = (s2_a + f2 * (s2_b - s2_a)) * win2 * hold_env;\n    phase2 = wrap(phase2 + 1, 0, grain_len_samps);\n}\n\n// Combine signals: knob1 = base grain level, knob3 = choral harmonics level\nwet_harmonics_L = (wet_v1 * 0.8 + wet_v2 * 0.3) * knob3;\nwet_harmonics_R = (wet_v1 * 0.3 + wet_v2 * 0.8) * knob3;\n\nout_L = dry + (active ? (wet_base * knob1 + wet_harmonics_L) : 0);\nout_R = dry + (active ? (wet_base * knob1 + wet_harmonics_R) : 0);\n\nout1 = out_L;\nout2 = out_R;\nout3 = is_holding; // LED 1: active capture\nout4 = active;     // LED 2: effect on/off",
									"fontface" : 0,
									"fontname" : "<Monospaced>",
									"fontsize" : 12.0,
									"id" : "obj-2",
									"maxclass" : "codebox",
									"numinlets" : 1,
									"numoutlets" : 4,
									"outlettype" : [ "", "", "", "" ],
									"patching_rect" : [ 276.0, 94.0, 654.867309331893921, 482.300923764705658 ]
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-3",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 276.0, 604.0, 110.619477927684784, 22.0 ],
									"text" : "out 1"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-4",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 463.0, 604.0, 110.619477927684784, 22.0 ],
									"text" : "out 2"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-5",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 650.0, 604.0, 136.283196806907654, 22.0 ],
									"text" : "out 3 led1"
								}

							}
, 							{
								"box" : 								{
									"id" : "obj-6",
									"maxclass" : "newobj",
									"numinlets" : 1,
									"numoutlets" : 0,
									"patching_rect" : [ 837.0, 604.0, 136.283196806907654, 22.0 ],
									"text" : "out 4 led2"
								}

							}
 ],
						"lines" : [ 							{
								"patchline" : 								{
									"destination" : [ "obj-2", 0 ],
									"source" : [ "obj-1", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-3", 0 ],
									"source" : [ "obj-2", 0 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-4", 0 ],
									"source" : [ "obj-2", 1 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-5", 0 ],
									"source" : [ "obj-2", 2 ]
								}

							}
, 							{
								"patchline" : 								{
									"destination" : [ "obj-6", 0 ],
									"source" : [ "obj-2", 3 ]
								}

							}
 ]
					}
,
					"patching_rect" : [ 107.20000159740448, 412.800006151199341, 180.0, 22.0 ],
					"saved_object_attributes" : 					{
						"exportfolder" : "Macintosh HD:/Users/danielfishkin/Downloads/",
						"exportname" : "GranularHold"
					}
,
					"text" : "gen~ @title GranularHold",
					"varname" : "GranularHold"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-14",
					"lastchannelcount" : 0,
					"maxclass" : "live.gain~",
					"numinlets" : 2,
					"numoutlets" : 5,
					"outlettype" : [ "signal", "signal", "", "float", "list" ],
					"parameter_enable" : 1,
					"patching_rect" : [ 107.20000159740448, 462.400006890296936, 48.0, 120.0 ],
					"saved_attribute_attributes" : 					{
						"valueof" : 						{
							"parameter_longname" : "live.gain~",
							"parameter_mmax" : 6.0,
							"parameter_mmin" : -70.0,
							"parameter_modmode" : 3,
							"parameter_shortname" : "live.gain~",
							"parameter_type" : 0,
							"parameter_unitstyle" : 4
						}

					}
,
					"varname" : "live.gain~"
				}

			}
, 			{
				"box" : 				{
					"id" : "obj-28",
					"maxclass" : "ezdac~",
					"numinlets" : 2,
					"numoutlets" : 0,
					"patching_rect" : [ 107.20000159740448, 602.400008976459503, 45.0, 45.0 ]
				}

			}
 ],
		"lines" : [ 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 1 ],
					"source" : [ "obj-1", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-14", 0 ],
					"source" : [ "obj-1", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-10", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-12", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-28", 1 ],
					"source" : [ "obj-14", 1 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-28", 0 ],
					"source" : [ "obj-14", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-17", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-4", 0 ],
					"hidden" : 1,
					"source" : [ "obj-2", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-25", 0 ],
					"source" : [ "obj-24", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-25", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-12", 0 ],
					"source" : [ "obj-3", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-83", 0 ],
					"hidden" : 1,
					"source" : [ "obj-4", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-17", 0 ],
					"source" : [ "obj-5", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-9", 0 ],
					"source" : [ "obj-6", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-10", 0 ],
					"source" : [ "obj-7", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-8", 0 ]
				}

			}
, 			{
				"patchline" : 				{
					"destination" : [ "obj-1", 0 ],
					"source" : [ "obj-9", 0 ]
				}

			}
 ],
		"parameters" : 		{
			"obj-14" : [ "live.gain~", "live.gain~", 0 ],
			"obj-3" : [ "knob1_mix", "Mix", 0 ],
			"obj-5" : [ "knob2_density", "Rate", 0 ],
			"obj-7" : [ "knob3_harmonics", "Harmonics", 0 ],
			"obj-83::obj-32" : [ "live.text[2]", "FILTER", 0 ],
			"obj-83::obj-33" : [ "live.text[1]", "FILTER", 0 ],
			"obj-83::obj-34" : [ "live.text[3]", "FILTER", 0 ],
			"parameterbanks" : 			{
				"0" : 				{
					"index" : 0,
					"name" : "",
					"parameters" : [ "-", "-", "-", "-", "-", "-", "-", "-" ]
				}

			}
,
			"inherited_shortname" : 1
		}
,
		"dependency_cache" : [ 			{
				"name" : "oopsy.maxpat",
				"bootpath" : "~/Documents/Max 8/Packages/oopsy/patchers",
				"patcherrelativepath" : "../Documents/Max 8/Packages/oopsy/patchers",
				"type" : "JSON",
				"implicit" : 1
			}
, 			{
				"name" : "oopsy.node4max.js",
				"bootpath" : "~/Documents/Max 8/Packages/oopsy/javascript",
				"patcherrelativepath" : "../Documents/Max 8/Packages/oopsy/javascript",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "oopsy.snoop.js",
				"bootpath" : "~/Documents/Max 8/Packages/oopsy/javascript",
				"patcherrelativepath" : "../Documents/Max 8/Packages/oopsy/javascript",
				"type" : "TEXT",
				"implicit" : 1
			}
, 			{
				"name" : "testinput_bpatch.maxpat",
				"bootpath" : "~/gitprojects/RamaPeddles/pedals",
				"patcherrelativepath" : "../gitprojects/RamaPeddles/pedals",
				"type" : "JSON",
				"implicit" : 1
			}
 ],
		"autosave" : 0
	}

}
