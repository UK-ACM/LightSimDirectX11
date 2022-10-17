//
// Generated by Microsoft (R) HLSL Shader Compiler 10.1
//
//
// Buffer Definitions: 
//
// cbuffer CBuf
// {
//
//   float4 face_colors[6];             // Offset:    0 Size:    96
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
// SV_PrimitiveID           0   x           0   PRIMID    uint   x   
//
//
// Output signature:
//
// Name                 Index   Mask Register SysValue  Format   Used
// -------------------- ----- ------ -------- -------- ------- ------
// SV_Target                0   xyzw        0   TARGET   float   xyzw
//
ps_5_0
dcl_globalFlags refactoringAllowed | skipOptimization
dcl_constantbuffer CB0[6], dynamicIndexed
dcl_input_ps_sgv constant v0.x, primitive_id
dcl_output o0.xyzw
dcl_temps 1
//
// Initial variable locations:
//   v0.x <- tid; 
//   o0.x <- <main return value>.x; o0.y <- <main return value>.y; o0.z <- <main return value>.z; o0.w <- <main return value>.w
//
#line 8 "C:\Dev\DX11Basics\DX11Basics\shaders\PixelShader_ps.hlsl"
mov r0.x, l(2)
udiv r0.x, null, v0.x, r0.x
mov o0.xyzw, cb0[r0.x + 0].xyzw
ret 
// Approximately 4 instruction slots used
