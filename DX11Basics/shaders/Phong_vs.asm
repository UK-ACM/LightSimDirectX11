//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer CBuf
// {
//
//   float4x4 model;                    // Offset:    0 Size:    64
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
// Normal                   0   xyz         1     NONE   float   xyz 
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// Position                 0   xyz         0     NONE   float   xyz 
// Normal                   0   xyz         1     NONE   float   xyz 
// SV_POSITION              0   xyzw        2      POS   float   xyzw
//
vs_5_0
dcl_globalFlags refactoringAllowed | skipOptimization
dcl_constantbuffer CB0[8], immediateIndexed
dcl_input v0.xyz
dcl_input v1.xyz
dcl_output o0.xyz
dcl_output o1.xyz
dcl_output_siv o2.xyzw, position
dcl_temps 4
//
// Initial variable locations:
//   v0.x <- pos.x; v0.y <- pos.y; v0.z <- pos.z; 
//   v1.x <- n.x; v1.y <- n.y; v1.z <- n.z; 
//   o2.x <- <main return value>.pos.x; o2.y <- <main return value>.pos.y; o2.z <- <main return value>.pos.z; o2.w <- <main return value>.pos.w; 
//   o1.x <- <main return value>.normal.x; o1.y <- <main return value>.normal.y; o1.z <- <main return value>.normal.z; 
//   o0.x <- <main return value>.worldPos.x; o0.y <- <main return value>.worldPos.y; o0.z <- <main return value>.worldPos.z
//
#line 15 "C:\Dev\DX11Basics\DX11Basics\shaders\Phong_vs.hlsl"
mov r0.xyz, v0.xyzx
mov r0.w, l(1.000000)
dp4 r1.x, r0.xyzw, cb0[0].xyzw  // r1.x <- vso.worldPos.x
dp4 r1.y, r0.xyzw, cb0[1].xyzw  // r1.y <- vso.worldPos.y
dp4 r1.z, r0.xyzw, cb0[2].xyzw  // r1.z <- vso.worldPos.z

#line 16
dp3 r2.x, v1.xyzx, cb0[0].xyzx  // r2.x <- vso.normal.x
dp3 r2.y, v1.xyzx, cb0[1].xyzx  // r2.y <- vso.normal.y
dp3 r2.z, v1.xyzx, cb0[2].xyzx  // r2.z <- vso.normal.z

#line 17
dp4 r3.x, r0.xyzw, cb0[4].xyzw  // r3.x <- vso.pos.x
dp4 r3.y, r0.xyzw, cb0[5].xyzw  // r3.y <- vso.pos.y
dp4 r3.z, r0.xyzw, cb0[6].xyzw  // r3.z <- vso.pos.z
dp4 r3.w, r0.xyzw, cb0[7].xyzw  // r3.w <- vso.pos.w

#line 18
mov o2.xyzw, r3.xyzw
mov o0.xyz, r1.xyzx
mov o1.xyz, r2.xyzx
ret 
// Approximately 16 instruction slots used
