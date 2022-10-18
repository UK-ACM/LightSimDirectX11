//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// splr                              sampler      NA          NA             s0      1 
// tex                               texture  float4          2d             t0      1 
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// TexCoord                 0   xy          0     NONE   float   xy  
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_TARGET                0   xyzw        0   TARGET   float   xyzw
//
ps_5_0
dcl_globalFlags refactoringAllowed | skipOptimization
dcl_sampler s0, mode_default
dcl_resource_texture2d (float,float,float,float) t0
dcl_input_ps linear v0.xy
dcl_output o0.xyzw
//
// Initial variable locations:
//   v0.x <- tc.x; v0.y <- tc.y; 
//   o0.x <- <main return value>.x; o0.y <- <main return value>.y; o0.z <- <main return value>.z; o0.w <- <main return value>.w
//
#line 5 "C:\Users\mrwha\Documents\DX11Basics\DX11Basics\shaders\Texture_ps.hlsl"
sample_indexable(texture2d)(float,float,float,float) o0.xyzw, v0.xyxx, t0.xyzw, s0
ret 
// Approximately 2 instruction slots used