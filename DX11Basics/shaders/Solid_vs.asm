//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer CBuf
// {
//
//   float4x4 model;                    // Offset:    0 Size:    64 [unused]
//   float4x4 modelViewProj;            // Offset:   64 Size:    64
//
// }
//
//
// Resource Bindings:
//
// Name                                 Type  Format         Dim      HLSL Bind  Count
// ------------------------------ ---------- ------- ----------- -------------- ------
// CBuf                              cbuffer      NA          NA            cb0      1 
//
//
//
// Input signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// Position                 0   xyz         0     NONE   float   xyz 
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_POSITION              0   xyzw        0      POS   float   xyzw
//
vs_5_0
dcl_globalFlags refactoringAllowed | skipOptimization
dcl_constantbuffer CB0[8], immediateIndexed
dcl_input v0.xyz
dcl_output_siv o0.xyzw, position
dcl_temps 1
//
// Initial variable locations:
//   v0.x <- pos.x; v0.y <- pos.y; v0.z <- pos.z; 
//   o0.x <- <main return value>.x; o0.y <- <main return value>.y; o0.z <- <main return value>.z; o0.w <- <main return value>.w
//
#line 10 "C:\Dev\DX11Basics\DX11Basics\shaders\Solid_vs.hlsl"
mov r0.xyz, v0.xyzx
mov r0.w, l(1.000000)
dp4 o0.x, r0.xyzw, cb0[4].xyzw
dp4 o0.y, r0.xyzw, cb0[5].xyzw
dp4 o0.z, r0.xyzw, cb0[6].xyzw
dp4 o0.w, r0.xyzw, cb0[7].xyzw
ret 
// Approximately 7 instruction slots used
