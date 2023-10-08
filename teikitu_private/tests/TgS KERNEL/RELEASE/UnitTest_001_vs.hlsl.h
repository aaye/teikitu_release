#if 0
;
; Input signature:
;
; Name                 Index   Mask Register SysValue  Format   Used
; -------------------- ----- ------ -------- -------- ------- ------
; SV_Position              0   xyzw        0      POS   float       
; COLOR                    0   xyzw        1     NONE   float   xyz 
;
;
; Output signature:
;
; Name                 Index   Mask Register SysValue  Format   Used
; -------------------- ----- ------ -------- -------- ------- ------
; SV_Target                0   xyzw        0   TARGET   float   xyzw
;
; shader debug name: D:\development\teikitu\build\msvc17_msvc_c17_x64_win_win_desktop_dx12_none\teikitu\bin\Release\UnitTest_001.ps.debug
; shader hash: 2f7d9e9e965cc60e11f95147786d8777
;
; Pipeline Runtime Information: 
;
; Pixel Shader
; DepthOutput=0
; SampleFrequency=0
;
;
; Input signature:
;
; Name                 Index             InterpMode DynIdx
; -------------------- ----- ---------------------- ------
; SV_Position              0          noperspective       
; COLOR                    0                 linear       
;
; Output signature:
;
; Name                 Index             InterpMode DynIdx
; -------------------- ----- ---------------------- ------
; SV_Target                0                              
;
; Buffer Definitions:
;
; cbuffer SceneConstantBufferInstance
; {
;
;   struct hostlayout.SceneConstantBufferInstance
;   {
;
;       column_major float4x4 view;                   ; Offset:    0
;       column_major float4x4 projection;             ; Offset:   64
;       float4 scene_light_ambient;                   ; Offset:  128
;       float scene_standard_nits;                    ; Offset:  144
;       uint hdr_scanout_transform;                   ; Offset:  148
;       uint scene_num_lights;                        ; Offset:  152
;       float perceptual_exponent;                    ; Offset:  156
;       struct struct.Light_Data
;       {
;
;           float4 origin_and_range;                  ; Offset:  160
;           float4 colour;                            ; Offset:  176
;       
;       } scene_lights[8];;                           ; Offset:  160
;
;   
;   } SceneConstantBufferInstance;                    ; Offset:    0 Size:   416
;
; }
;
;
; Resource Bindings:
;
; Name                                 Type  Format         Dim      ID      HLSL Bind  Count
; ------------------------------ ---------- ------- ----------- ------- -------------- ------
; SceneConstantBufferInstance       cbuffer      NA          NA     CB0            cb0     1
;
;
; ViewId state:
;
; Number of inputs: 8, outputs: 4
; Outputs dependent on ViewId: {  }
; Inputs contributing to computation of Outputs:
;   output 0 depends on inputs: { 4 }
;   output 1 depends on inputs: { 5 }
;   output 2 depends on inputs: { 6 }
;
target datalayout = "e-m:e-p:32:32-i1:32-i8:32-i16:32-i32:32-i64:64-f16:32-f32:32-f64:64-n8:16:32:64"
target triple = "dxil-ms-dx"

%dx.types.Handle = type { i8* }
%dx.types.CBufRet.f32 = type { float, float, float, float }
%hostlayout.SceneConstantBufferInstance = type { [4 x <4 x float>], [4 x <4 x float>], <4 x float>, float, i32, i32, float, [8 x %struct.Light_Data] }
%struct.Light_Data = type { <4 x float>, <4 x float> }

define void @main() {
  %1 = call %dx.types.Handle @dx.op.createHandle(i32 57, i8 2, i32 0, i32 0, i1 false)  ; CreateHandle(resourceClass,rangeId,index,nonUniformIndex)
  %2 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 0, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %3 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 1, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %4 = call float @dx.op.loadInput.f32(i32 4, i32 1, i32 0, i8 2, i32 undef)  ; LoadInput(inputSigId,rowIndex,colIndex,gsVertexAxis)
  %5 = call %dx.types.CBufRet.f32 @dx.op.cbufferLoadLegacy.f32(i32 59, %dx.types.Handle %1, i32 9)  ; CBufferLoadLegacy(handle,regIndex)
  %6 = extractvalue %dx.types.CBufRet.f32 %5, 3
  %7 = call float @dx.op.unary.f32(i32 6, float %2)  ; FAbs(value)
  %8 = call float @dx.op.unary.f32(i32 6, float %3)  ; FAbs(value)
  %9 = call float @dx.op.unary.f32(i32 6, float %4)  ; FAbs(value)
  %10 = call float @dx.op.unary.f32(i32 23, float %7)  ; Log(value)
  %11 = call float @dx.op.unary.f32(i32 23, float %8)  ; Log(value)
  %12 = call float @dx.op.unary.f32(i32 23, float %9)  ; Log(value)
  %13 = fmul fast float %10, %6
  %14 = fmul fast float %11, %6
  %15 = fmul fast float %12, %6
  %16 = call float @dx.op.unary.f32(i32 21, float %13)  ; Exp(value)
  %17 = call float @dx.op.unary.f32(i32 21, float %14)  ; Exp(value)
  %18 = call float @dx.op.unary.f32(i32 21, float %15)  ; Exp(value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 0, float %16)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 1, float %17)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 2, float %18)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  call void @dx.op.storeOutput.f32(i32 5, i32 0, i32 0, i8 3, float 1.000000e+00)  ; StoreOutput(outputSigId,rowIndex,colIndex,value)
  ret void
}

; Function Attrs: nounwind readnone
declare float @dx.op.loadInput.f32(i32, i32, i32, i8, i32) #0

; Function Attrs: nounwind
declare void @dx.op.storeOutput.f32(i32, i32, i32, i8, float) #1

; Function Attrs: nounwind readnone
declare float @dx.op.unary.f32(i32, float) #0

; Function Attrs: nounwind readonly
declare %dx.types.CBufRet.f32 @dx.op.cbufferLoadLegacy.f32(i32, %dx.types.Handle, i32) #2

; Function Attrs: nounwind readonly
declare %dx.types.Handle @dx.op.createHandle(i32, i8, i32, i32, i1) #2

attributes #0 = { nounwind readnone }
attributes #1 = { nounwind }
attributes #2 = { nounwind readonly }

!llvm.ident = !{!0}
!dx.version = !{!1}
!dx.valver = !{!2}
!dx.shaderModel = !{!3}
!dx.resources = !{!4}
!dx.viewIdState = !{!7}
!dx.entryPoints = !{!8}

!0 = !{!"clang version 3.7 (tags/RELEASE_370/final)"}
!1 = !{i32 1, i32 2}
!2 = !{i32 1, i32 6}
!3 = !{!"ps", i32 6, i32 2}
!4 = !{null, null, !5, null}
!5 = !{!6}
!6 = !{i32 0, %hostlayout.SceneConstantBufferInstance* undef, !"", i32 0, i32 0, i32 1, i32 416, null}
!7 = !{[10 x i32] [i32 8, i32 4, i32 0, i32 0, i32 0, i32 0, i32 1, i32 2, i32 4, i32 0]}
!8 = !{void ()* @main, !"main", !9, !4, null}
!9 = !{!10, !15, null}
!10 = !{!11, !13}
!11 = !{i32 0, !"SV_Position", i8 9, i8 3, !12, i8 4, i32 1, i8 4, i32 0, i8 0, null}
!12 = !{i32 0}
!13 = !{i32 1, !"COLOR", i8 9, i8 0, !12, i8 2, i32 1, i8 4, i32 1, i8 0, !14}
!14 = !{i32 3, i32 7}
!15 = !{!16}
!16 = !{i32 0, !"SV_Target", i8 9, i8 16, !12, i8 0, i32 1, i8 4, i32 0, i8 0, !17}
!17 = !{i32 3, i32 15}

#endif

const unsigned char g_uiUnitTest_001_PS_Compiled[] = {
  0x44, 0x58, 0x42, 0x43, 0x7d, 0x50, 0x75, 0x17, 0x58, 0x61, 0x7d, 0x8b,
  0x17, 0xdc, 0x4c, 0x6d, 0x02, 0xe1, 0x7a, 0x6a, 0x01, 0x00, 0x00, 0x00,
  0x94, 0x10, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,
  0x50, 0x00, 0x00, 0x00, 0xb2, 0x00, 0x00, 0x00, 0xec, 0x00, 0x00, 0x00,
  0xb0, 0x01, 0x00, 0x00, 0x44, 0x09, 0x00, 0x00, 0xc8, 0x09, 0x00, 0x00,
  0xe4, 0x09, 0x00, 0x00, 0x53, 0x46, 0x49, 0x30, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x53, 0x47, 0x31,
  0x5a, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x03, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x07, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x53, 0x56, 0x5f, 0x50, 0x6f, 0x73, 0x69, 0x74,
  0x69, 0x6f, 0x6e, 0x00, 0x43, 0x4f, 0x4c, 0x4f, 0x52, 0x00, 0x4f, 0x53,
  0x47, 0x31, 0x32, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x56,
  0x5f, 0x54, 0x61, 0x72, 0x67, 0x65, 0x74, 0x00, 0x50, 0x53, 0x56, 0x30,
  0xbc, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
  0x02, 0x01, 0x00, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x18, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0d, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x43, 0x4f, 0x4c,
  0x4f, 0x52, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x00, 0x44, 0x03, 0x03, 0x04, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x44, 0x00, 0x03, 0x02, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x44, 0x10,
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x53, 0x54, 0x41, 0x54, 0x8c, 0x07, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00,
  0xe3, 0x01, 0x00, 0x00, 0x44, 0x58, 0x49, 0x4c, 0x02, 0x01, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x74, 0x07, 0x00, 0x00, 0x42, 0x43, 0xc0, 0xde,
  0x21, 0x0c, 0x00, 0x00, 0xda, 0x01, 0x00, 0x00, 0x0b, 0x82, 0x20, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x07, 0x81, 0x23, 0x91,
  0x41, 0xc8, 0x04, 0x49, 0x06, 0x10, 0x32, 0x39, 0x92, 0x01, 0x84, 0x0c,
  0x25, 0x05, 0x08, 0x19, 0x1e, 0x04, 0x8b, 0x62, 0x80, 0x14, 0x45, 0x02,
  0x42, 0x92, 0x0b, 0x42, 0xa4, 0x10, 0x32, 0x14, 0x38, 0x08, 0x18, 0x4b,
  0x0a, 0x32, 0x52, 0x88, 0x48, 0x90, 0x14, 0x20, 0x43, 0x46, 0x88, 0xa5,
  0x00, 0x19, 0x32, 0x42, 0xe4, 0x48, 0x0e, 0x90, 0x91, 0x22, 0xc4, 0x50,
  0x41, 0x51, 0x81, 0x8c, 0xe1, 0x83, 0xe5, 0x8a, 0x04, 0x29, 0x46, 0x06,
  0x51, 0x18, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x1b, 0x8c, 0xe0, 0xff,
  0xff, 0xff, 0xff, 0x07, 0x40, 0x02, 0xa8, 0x0d, 0x84, 0xf0, 0xff, 0xff,
  0xff, 0xff, 0x03, 0x20, 0x6d, 0x30, 0x86, 0xff, 0xff, 0xff, 0xff, 0x1f,
  0x00, 0x09, 0xa8, 0x00, 0x49, 0x18, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x13, 0x82, 0x60, 0x42, 0x20, 0x4c, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00,
  0x89, 0x20, 0x00, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x32, 0x22, 0x48, 0x09,
  0x20, 0x64, 0x85, 0x04, 0x93, 0x22, 0xa4, 0x84, 0x04, 0x93, 0x22, 0xe3,
  0x84, 0xa1, 0x90, 0x14, 0x12, 0x4c, 0x8a, 0x8c, 0x0b, 0x84, 0xa4, 0x4c,
  0x10, 0x70, 0x23, 0x00, 0x25, 0x00, 0x14, 0x66, 0x00, 0xe6, 0x08, 0xc0,
  0x60, 0x8e, 0x00, 0x29, 0xc6, 0x20, 0x84, 0x14, 0x42, 0xa6, 0x18, 0x80,
  0x10, 0x52, 0x06, 0xa1, 0x32, 0x0c, 0x32, 0x48, 0x1d, 0x35, 0x5c, 0xfe,
  0x84, 0x3d, 0x84, 0xe4, 0x73, 0x1b, 0x55, 0xac, 0xc4, 0xe4, 0x17, 0xb7,
  0x8d, 0x88, 0x31, 0xc6, 0xa0, 0x72, 0xcf, 0x70, 0xf9, 0x13, 0xf6, 0x10,
  0x92, 0x1f, 0x02, 0xcd, 0xb0, 0x10, 0x28, 0x68, 0x85, 0x60, 0xc4, 0x11,
  0x7a, 0x73, 0x04, 0x41, 0x31, 0x1c, 0x29, 0x84, 0x44, 0x92, 0x03, 0x01,
  0xc3, 0x08, 0xc4, 0x90, 0x04, 0xf5, 0x22, 0x69, 0x8a, 0x28, 0x61, 0xf2,
  0x4b, 0xc4, 0x38, 0xa6, 0xbf, 0x03, 0x26, 0x00, 0x09, 0xb5, 0x26, 0xc2,
  0x3d, 0x33, 0x38, 0x1c, 0x69, 0x5a, 0x00, 0xcc, 0xa1, 0x26, 0x9f, 0x15,
  0x88, 0x86, 0xe0, 0x9c, 0x46, 0x9a, 0x80, 0x66, 0xda, 0xa8, 0xa2, 0x20,
  0x22, 0xb1, 0x91, 0x26, 0xa0, 0x11, 0x08, 0x84, 0x58, 0x5b, 0x07, 0x21,
  0x03, 0x53, 0x4e, 0x05, 0x02, 0x00, 0x00, 0x00, 0x13, 0x14, 0x72, 0xc0,
  0x87, 0x74, 0x60, 0x87, 0x36, 0x68, 0x87, 0x79, 0x68, 0x03, 0x72, 0xc0,
  0x87, 0x0d, 0xaf, 0x50, 0x0e, 0x6d, 0xd0, 0x0e, 0x7a, 0x50, 0x0e, 0x6d,
  0x00, 0x0f, 0x7a, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d,
  0x90, 0x0e, 0x71, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e, 0x78,
  0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e, 0x71, 0x60, 0x07, 0x7a,
  0x30, 0x07, 0x72, 0xd0, 0x06, 0xe9, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x73,
  0x20, 0x07, 0x6d, 0x90, 0x0e, 0x76, 0x40, 0x07, 0x7a, 0x60, 0x07, 0x74,
  0xd0, 0x06, 0xe6, 0x10, 0x07, 0x76, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d,
  0x60, 0x0e, 0x73, 0x20, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06, 0xe6,
  0x60, 0x07, 0x74, 0xa0, 0x07, 0x76, 0x40, 0x07, 0x6d, 0xe0, 0x0e, 0x78,
  0xa0, 0x07, 0x71, 0x60, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x76,
  0x40, 0x07, 0x43, 0x9e, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x86, 0x3c, 0x06, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x79, 0x10, 0x20, 0x00, 0x04, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0xf2, 0x28, 0x40, 0x00, 0x04, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xe4, 0x79, 0x80, 0x00, 0x18,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xc8, 0x23, 0x01, 0x01,
  0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x16, 0x08, 0x00,
  0x17, 0x00, 0x00, 0x00, 0x32, 0x1e, 0x98, 0x18, 0x19, 0x11, 0x4c, 0x90,
  0x8c, 0x09, 0x26, 0x47, 0xc6, 0x04, 0x43, 0x22, 0x25, 0x50, 0x04, 0x23,
  0x00, 0xc5, 0x50, 0xc0, 0x06, 0x05, 0x54, 0x06, 0xe5, 0x50, 0x12, 0x05,
  0x52, 0x08, 0x05, 0x18, 0x50, 0x80, 0x02, 0x05, 0x2a, 0x50, 0xa8, 0x02,
  0xa5, 0x50, 0xb0, 0x02, 0x85, 0x2b, 0x50, 0xc0, 0x02, 0xe5, 0x51, 0x18,
  0xe5, 0x42, 0xa5, 0x24, 0xca, 0xa0, 0x10, 0x46, 0x00, 0x8a, 0xa0, 0x40,
  0x28, 0xd6, 0x00, 0xdd, 0x19, 0x00, 0xca, 0x33, 0x00, 0xa4, 0x67, 0x00,
  0x68, 0x8f, 0xa5, 0x20, 0x04, 0x00, 0x00, 0x40, 0x20, 0x10, 0x00, 0x00,
  0x79, 0x18, 0x00, 0x00, 0xcd, 0x00, 0x00, 0x00, 0x1a, 0x03, 0x4c, 0x90,
  0x46, 0x02, 0x13, 0x44, 0x35, 0x18, 0x63, 0x0b, 0x73, 0x3b, 0x03, 0xb1,
  0x2b, 0x93, 0x9b, 0x4b, 0x7b, 0x73, 0x03, 0x99, 0x71, 0xb9, 0x01, 0x41,
  0xa1, 0x0b, 0x3b, 0x9b, 0x7b, 0x91, 0x2a, 0x62, 0x2a, 0x0a, 0x9a, 0x2a,
  0xfa, 0x9a, 0xb9, 0x81, 0x79, 0x31, 0x4b, 0x73, 0x0b, 0x63, 0x4b, 0xd9,
  0x10, 0x04, 0x13, 0x04, 0xc2, 0x98, 0x20, 0x10, 0xc7, 0x06, 0x61, 0x20,
  0x26, 0x08, 0x04, 0xb2, 0x41, 0x30, 0x0c, 0x0a, 0x70, 0x73, 0x13, 0x04,
  0x22, 0xd9, 0x30, 0x20, 0x09, 0x31, 0x41, 0xd0, 0xca, 0x80, 0xdb, 0xd4,
  0x58, 0x99, 0x5b, 0xd9, 0xd0, 0x9b, 0xdb, 0x1c, 0x5d, 0x98, 0x1b, 0x9d,
  0x50, 0x9d, 0x99, 0x59, 0x99, 0x5c, 0x92, 0xdb, 0x1c, 0x5d, 0x98, 0xdb,
  0x58, 0xd9, 0x04, 0x81, 0x50, 0x36, 0x20, 0xc6, 0xc2, 0x18, 0xc6, 0xd0,
  0x00, 0x1b, 0x02, 0x67, 0x03, 0x01, 0x00, 0x0f, 0x30, 0x41, 0xb8, 0xc6,
  0x60, 0x82, 0x40, 0x2c, 0x84, 0xde, 0xe4, 0xd2, 0xce, 0xd2, 0xdc, 0xbe,
  0xc2, 0xdc, 0xc8, 0xbe, 0xe4, 0xc2, 0xdc, 0xce, 0xca, 0x26, 0x08, 0x04,
  0x33, 0x41, 0x20, 0x9a, 0x09, 0x02, 0xe1, 0x6c, 0x30, 0x92, 0x89, 0x32,
  0x2a, 0x8b, 0xc6, 0xd8, 0x1b, 0xdb, 0x5b, 0x9d, 0xdc, 0x04, 0x81, 0x78,
  0x36, 0x18, 0x09, 0x46, 0x65, 0x95, 0xb5, 0x61, 0x90, 0x2e, 0x6d, 0x82,
  0x90, 0x91, 0x01, 0x09, 0xbb, 0xb4, 0xb2, 0xbb, 0x09, 0x02, 0x01, 0x6d,
  0x18, 0x3c, 0x8f, 0xd8, 0x80, 0x24, 0x1d, 0xf1, 0x51, 0x46, 0x65, 0x51,
  0x81, 0x93, 0x7b, 0x53, 0x2b, 0x1b, 0xa3, 0x4b, 0x7b, 0x73, 0x9b, 0x20,
  0x10, 0xd1, 0x06, 0x24, 0x09, 0x03, 0xe2, 0xa3, 0xc4, 0xa0, 0xb2, 0x38,
  0xcd, 0x8d, 0x95, 0xb9, 0x95, 0x7d, 0xb1, 0xa5, 0x9d, 0xa1, 0xd1, 0x7d,
  0x85, 0xb5, 0x89, 0xa5, 0x95, 0xb9, 0xd1, 0x4d, 0x10, 0x08, 0x69, 0x83,
  0x91, 0x90, 0x01, 0x55, 0x06, 0x95, 0xc5, 0x69, 0x6e, 0xac, 0xcc, 0xad,
  0xec, 0x6b, 0x8e, 0x2e, 0xcc, 0x8d, 0x2c, 0x4c, 0x8e, 0xec, 0xcb, 0x2d,
  0x8d, 0x6e, 0x6e, 0x82, 0x40, 0x4c, 0x1b, 0x8c, 0xe4, 0x0c, 0x28, 0x34,
  0xa8, 0x2c, 0x56, 0x68, 0x64, 0x72, 0x5f, 0x73, 0x63, 0x61, 0x6e, 0x6f,
  0x75, 0x74, 0x5f, 0x74, 0x72, 0x61, 0x6e, 0x73, 0x66, 0x6f, 0x72, 0x6d,
  0x13, 0x04, 0x82, 0x9a, 0x20, 0x10, 0xd5, 0x06, 0x23, 0x51, 0x03, 0x6a,
  0x0d, 0x2a, 0x36, 0x20, 0x34, 0x37, 0x56, 0xe6, 0x56, 0xf6, 0xe5, 0x56,
  0xd7, 0xf6, 0xc5, 0x96, 0x76, 0x86, 0x46, 0x37, 0x37, 0x41, 0x20, 0xac,
  0x0d, 0x46, 0xe2, 0x06, 0xd4, 0x1b, 0x54, 0x6c, 0xc0, 0x09, 0xae, 0x4c,
  0x6e, 0xac, 0x0c, 0x8e, 0xae, 0x2e, 0x8c, 0xed, 0xab, 0x0c, 0x0f, 0xee,
  0xcd, 0xad, 0xcc, 0x8d, 0x6e, 0x82, 0x40, 0x5c, 0x13, 0x84, 0x48, 0x0c,
  0x36, 0x20, 0x49, 0x1c, 0x50, 0x72, 0x50, 0x59, 0xd6, 0x1c, 0x90, 0x99,
  0x1b, 0x2b, 0x73, 0x2b, 0xfb, 0x62, 0x4b, 0x3b, 0x43, 0xa3, 0x9b, 0x9b,
  0x20, 0x10, 0xd8, 0x06, 0x22, 0xa9, 0x03, 0xca, 0x0e, 0x36, 0x24, 0x0d,
  0x18, 0x8c, 0x81, 0x19, 0xa4, 0x41, 0x1b, 0xc0, 0x01, 0x1d, 0xdc, 0xc1,
  0x86, 0xc2, 0x88, 0x36, 0x0e, 0x0f, 0x26, 0x08, 0x02, 0xb0, 0x01, 0xd8,
  0x30, 0x18, 0x7b, 0xb0, 0x07, 0x1b, 0x02, 0x3e, 0xd8, 0x30, 0x0c, 0x7a,
  0xd0, 0x07, 0x13, 0x84, 0xcd, 0x0c, 0x36, 0x04, 0x7f, 0x40, 0xa2, 0x2d,
  0x2c, 0xcd, 0x8d, 0xcb, 0x94, 0xd5, 0x17, 0xd4, 0xdb, 0x5c, 0x1a, 0x5d,
  0xda, 0x9b, 0xdb, 0x04, 0xa1, 0xe0, 0x26, 0x08, 0x45, 0xb7, 0x21, 0x30,
  0x26, 0x08, 0x85, 0x37, 0x41, 0x28, 0xbe, 0x0d, 0x8b, 0x21, 0x0a, 0xa3,
  0x40, 0x0a, 0xa5, 0x60, 0x0a, 0x83, 0x29, 0x18, 0xa7, 0x00, 0xb0, 0x18,
  0x7a, 0x62, 0x7a, 0x92, 0x9a, 0x20, 0x14, 0x60, 0xb0, 0x41, 0xa0, 0xaa,
  0x0d, 0xcb, 0x90, 0x0a, 0xa3, 0x70, 0x0a, 0xa5, 0xa0, 0x0a, 0x83, 0x29,
  0x0c, 0xa7, 0xb0, 0x0a, 0x1b, 0x04, 0x54, 0x60, 0x05, 0x26, 0x53, 0x56,
  0x5f, 0x54, 0x61, 0x72, 0x67, 0x65, 0x74, 0x13, 0x84, 0x22, 0x0c, 0x26,
  0x08, 0x44, 0xb6, 0x41, 0xa0, 0x60, 0x61, 0xc3, 0x62, 0xb8, 0xc2, 0x28,
  0xbc, 0x42, 0x29, 0x9c, 0xc2, 0x60, 0x0a, 0xc6, 0x29, 0xc4, 0xc2, 0x86,
  0x40, 0x16, 0x36, 0x0c, 0xad, 0x30, 0x0b, 0xc0, 0x86, 0x42, 0x0f, 0x42,
  0x81, 0x16, 0x20, 0x80, 0x86, 0x19, 0xdb, 0x5b, 0x18, 0xdd, 0xdc, 0x04,
  0x81, 0xd0, 0x58, 0xa4, 0xb9, 0xcd, 0xd1, 0xcd, 0x4d, 0x10, 0x88, 0x8d,
  0xc6, 0x5c, 0xda, 0xd9, 0x17, 0x1b, 0x19, 0x8d, 0xb9, 0xb4, 0xb3, 0xaf,
  0x39, 0xba, 0x0d, 0x88, 0x2d, 0xdc, 0x02, 0x2e, 0xe4, 0x82, 0x2e, 0x50,
  0xbb, 0xe0, 0x55, 0x61, 0x63, 0xb3, 0x6b, 0x73, 0x49, 0x23, 0x2b, 0x73,
  0xa3, 0x9b, 0x12, 0x04, 0x55, 0xc8, 0xf0, 0x5c, 0xec, 0xca, 0xe4, 0xe6,
  0xd2, 0xde, 0xdc, 0xa6, 0x04, 0x44, 0x13, 0x32, 0x3c, 0x17, 0xbb, 0x30,
  0x36, 0xbb, 0x32, 0xb9, 0x29, 0x81, 0x51, 0x87, 0x0c, 0xcf, 0x65, 0x0e,
  0x2d, 0x8c, 0xac, 0x4c, 0xae, 0xe9, 0x8d, 0xac, 0x8c, 0x6d, 0x4a, 0x90,
  0x94, 0x21, 0xc3, 0x73, 0x91, 0x2b, 0x9b, 0x7b, 0xab, 0x93, 0x1b, 0x2b,
  0x9b, 0x9b, 0x12, 0x3c, 0x95, 0xc8, 0xf0, 0x5c, 0xe8, 0xf2, 0xe0, 0xca,
  0x82, 0xdc, 0xdc, 0xde, 0xe8, 0xc2, 0xe8, 0xd2, 0xde, 0xdc, 0xe6, 0xa6,
  0x08, 0x78, 0xd0, 0x07, 0x75, 0xc8, 0xf0, 0x5c, 0xec, 0xd2, 0xca, 0xee,
  0x92, 0xc8, 0xa6, 0xe8, 0xc2, 0xe8, 0xca, 0xa6, 0x04, 0x7f, 0x50, 0x87,
  0x0c, 0xcf, 0xa5, 0xcc, 0x8d, 0x4e, 0x2e, 0x0f, 0xea, 0x2d, 0xcd, 0x8d,
  0x6e, 0x6e, 0x4a, 0x40, 0x0b, 0x5d, 0xc8, 0xf0, 0x5c, 0xc6, 0xde, 0xea,
  0xdc, 0xe8, 0xca, 0xe4, 0xe6, 0xa6, 0x04, 0xbb, 0x00, 0x00, 0x00, 0x00,
  0x79, 0x18, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x33, 0x08, 0x80, 0x1c,
  0xc4, 0xe1, 0x1c, 0x66, 0x14, 0x01, 0x3d, 0x88, 0x43, 0x38, 0x84, 0xc3,
  0x8c, 0x42, 0x80, 0x07, 0x79, 0x78, 0x07, 0x73, 0x98, 0x71, 0x0c, 0xe6,
  0x00, 0x0f, 0xed, 0x10, 0x0e, 0xf4, 0x80, 0x0e, 0x33, 0x0c, 0x42, 0x1e,
  0xc2, 0xc1, 0x1d, 0xce, 0xa1, 0x1c, 0x66, 0x30, 0x05, 0x3d, 0x88, 0x43,
  0x38, 0x84, 0x83, 0x1b, 0xcc, 0x03, 0x3d, 0xc8, 0x43, 0x3d, 0x8c, 0x03,
  0x3d, 0xcc, 0x78, 0x8c, 0x74, 0x70, 0x07, 0x7b, 0x08, 0x07, 0x79, 0x48,
  0x87, 0x70, 0x70, 0x07, 0x7a, 0x70, 0x03, 0x76, 0x78, 0x87, 0x70, 0x20,
  0x87, 0x19, 0xcc, 0x11, 0x0e, 0xec, 0x90, 0x0e, 0xe1, 0x30, 0x0f, 0x6e,
  0x30, 0x0f, 0xe3, 0xf0, 0x0e, 0xf0, 0x50, 0x0e, 0x33, 0x10, 0xc4, 0x1d,
  0xde, 0x21, 0x1c, 0xd8, 0x21, 0x1d, 0xc2, 0x61, 0x1e, 0x66, 0x30, 0x89,
  0x3b, 0xbc, 0x83, 0x3b, 0xd0, 0x43, 0x39, 0xb4, 0x03, 0x3c, 0xbc, 0x83,
  0x3c, 0x84, 0x03, 0x3b, 0xcc, 0xf0, 0x14, 0x76, 0x60, 0x07, 0x7b, 0x68,
  0x07, 0x37, 0x68, 0x87, 0x72, 0x68, 0x07, 0x37, 0x80, 0x87, 0x70, 0x90,
  0x87, 0x70, 0x60, 0x07, 0x76, 0x28, 0x07, 0x76, 0xf8, 0x05, 0x76, 0x78,
  0x87, 0x77, 0x80, 0x87, 0x5f, 0x08, 0x87, 0x71, 0x18, 0x87, 0x72, 0x98,
  0x87, 0x79, 0x98, 0x81, 0x2c, 0xee, 0xf0, 0x0e, 0xee, 0xe0, 0x0e, 0xf5,
  0xc0, 0x0e, 0xec, 0x30, 0x03, 0x62, 0xc8, 0xa1, 0x1c, 0xe4, 0xa1, 0x1c,
  0xcc, 0xa1, 0x1c, 0xe4, 0xa1, 0x1c, 0xdc, 0x61, 0x1c, 0xca, 0x21, 0x1c,
  0xc4, 0x81, 0x1d, 0xca, 0x61, 0x06, 0xd6, 0x90, 0x43, 0x39, 0xc8, 0x43,
  0x39, 0x98, 0x43, 0x39, 0xc8, 0x43, 0x39, 0xb8, 0xc3, 0x38, 0x94, 0x43,
  0x38, 0x88, 0x03, 0x3b, 0x94, 0xc3, 0x2f, 0xbc, 0x83, 0x3c, 0xfc, 0x82,
  0x3b, 0xd4, 0x03, 0x3b, 0xb0, 0xc3, 0x0c, 0xc4, 0x21, 0x07, 0x7c, 0x70,
  0x03, 0x7a, 0x28, 0x87, 0x76, 0x80, 0x87, 0x19, 0xd1, 0x43, 0x0e, 0xf8,
  0xe0, 0x06, 0xe4, 0x20, 0x0e, 0xe7, 0xe0, 0x06, 0xf6, 0x10, 0x0e, 0xf2,
  0xc0, 0x0e, 0xe1, 0x90, 0x0f, 0xef, 0x50, 0x0f, 0xf4, 0x00, 0x00, 0x00,
  0x71, 0x20, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x46, 0xb0, 0x0d, 0x97,
  0xef, 0x3c, 0xbe, 0x10, 0x50, 0x45, 0x41, 0x44, 0xa5, 0x03, 0x0c, 0x25,
  0x61, 0x00, 0x02, 0xe6, 0x17, 0xb7, 0x6d, 0x05, 0xd2, 0x70, 0xf9, 0xce,
  0xe3, 0x0b, 0x11, 0x01, 0x4c, 0x44, 0x08, 0x34, 0xc3, 0x42, 0x58, 0xc0,
  0x34, 0x5c, 0xbe, 0xf3, 0xf8, 0x8b, 0x03, 0x0c, 0x62, 0xf3, 0x50, 0x93,
  0x5f, 0xdc, 0xb6, 0x09, 0x54, 0xc3, 0xe5, 0x3b, 0x8f, 0x2f, 0x4d, 0x4e,
  0x44, 0xa0, 0xd4, 0xf4, 0x50, 0x93, 0x5f, 0xdc, 0xb6, 0x0d, 0x3c, 0xc3,
  0xe5, 0x3b, 0x8f, 0x4f, 0x35, 0x40, 0x84, 0xf9, 0xc5, 0x6d, 0x1b, 0x00,
  0xc1, 0x00, 0x48, 0x03, 0x00, 0x00, 0x00, 0x00, 0x49, 0x4c, 0x44, 0x4e,
  0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x74, 0x00, 0x44, 0x3a, 0x5c, 0x64,
  0x65, 0x76, 0x65, 0x6c, 0x6f, 0x70, 0x6d, 0x65, 0x6e, 0x74, 0x5c, 0x74,
  0x65, 0x69, 0x6b, 0x69, 0x74, 0x75, 0x5c, 0x62, 0x75, 0x69, 0x6c, 0x64,
  0x5c, 0x6d, 0x73, 0x76, 0x63, 0x31, 0x37, 0x5f, 0x6d, 0x73, 0x76, 0x63,
  0x5f, 0x63, 0x31, 0x37, 0x5f, 0x78, 0x36, 0x34, 0x5f, 0x77, 0x69, 0x6e,
  0x5f, 0x77, 0x69, 0x6e, 0x5f, 0x64, 0x65, 0x73, 0x6b, 0x74, 0x6f, 0x70,
  0x5f, 0x64, 0x78, 0x31, 0x32, 0x5f, 0x6e, 0x6f, 0x6e, 0x65, 0x5c, 0x74,
  0x65, 0x69, 0x6b, 0x69, 0x74, 0x75, 0x5c, 0x62, 0x69, 0x6e, 0x5c, 0x52,
  0x65, 0x6c, 0x65, 0x61, 0x73, 0x65, 0x5c, 0x55, 0x6e, 0x69, 0x74, 0x54,
  0x65, 0x73, 0x74, 0x5f, 0x30, 0x30, 0x31, 0x2e, 0x70, 0x73, 0x2e, 0x64,
  0x65, 0x62, 0x75, 0x67, 0x00, 0x00, 0x00, 0x00, 0x48, 0x41, 0x53, 0x48,
  0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2f, 0x7d, 0x9e, 0x9e,
  0x96, 0x5c, 0xc6, 0x0e, 0x11, 0xf9, 0x51, 0x47, 0x78, 0x6d, 0x87, 0x77,
  0x44, 0x58, 0x49, 0x4c, 0xa8, 0x06, 0x00, 0x00, 0x62, 0x00, 0x00, 0x00,
  0xaa, 0x01, 0x00, 0x00, 0x44, 0x58, 0x49, 0x4c, 0x02, 0x01, 0x00, 0x00,
  0x10, 0x00, 0x00, 0x00, 0x90, 0x06, 0x00, 0x00, 0x42, 0x43, 0xc0, 0xde,
  0x21, 0x0c, 0x00, 0x00, 0xa1, 0x01, 0x00, 0x00, 0x0b, 0x82, 0x20, 0x00,
  0x02, 0x00, 0x00, 0x00, 0x13, 0x00, 0x00, 0x00, 0x07, 0x81, 0x23, 0x91,
  0x41, 0xc8, 0x04, 0x49, 0x06, 0x10, 0x32, 0x39, 0x92, 0x01, 0x84, 0x0c,
  0x25, 0x05, 0x08, 0x19, 0x1e, 0x04, 0x8b, 0x62, 0x80, 0x14, 0x45, 0x02,
  0x42, 0x92, 0x0b, 0x42, 0xa4, 0x10, 0x32, 0x14, 0x38, 0x08, 0x18, 0x4b,
  0x0a, 0x32, 0x52, 0x88, 0x48, 0x90, 0x14, 0x20, 0x43, 0x46, 0x88, 0xa5,
  0x00, 0x19, 0x32, 0x42, 0xe4, 0x48, 0x0e, 0x90, 0x91, 0x22, 0xc4, 0x50,
  0x41, 0x51, 0x81, 0x8c, 0xe1, 0x83, 0xe5, 0x8a, 0x04, 0x29, 0x46, 0x06,
  0x51, 0x18, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x1b, 0x8c, 0xe0, 0xff,
  0xff, 0xff, 0xff, 0x07, 0x40, 0x02, 0xa8, 0x0d, 0x84, 0xf0, 0xff, 0xff,
  0xff, 0xff, 0x03, 0x20, 0x6d, 0x30, 0x86, 0xff, 0xff, 0xff, 0xff, 0x1f,
  0x00, 0x09, 0xa8, 0x00, 0x49, 0x18, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
  0x13, 0x82, 0x60, 0x42, 0x20, 0x4c, 0x08, 0x06, 0x00, 0x00, 0x00, 0x00,
  0x89, 0x20, 0x00, 0x00, 0x2d, 0x00, 0x00, 0x00, 0x32, 0x22, 0x48, 0x09,
  0x20, 0x64, 0x85, 0x04, 0x93, 0x22, 0xa4, 0x84, 0x04, 0x93, 0x22, 0xe3,
  0x84, 0xa1, 0x90, 0x14, 0x12, 0x4c, 0x8a, 0x8c, 0x0b, 0x84, 0xa4, 0x4c,
  0x10, 0x70, 0x23, 0x00, 0x25, 0x00, 0x14, 0x66, 0x00, 0xe6, 0x08, 0xc0,
  0x60, 0x8e, 0x00, 0x29, 0xc6, 0x20, 0x84, 0x14, 0x42, 0xa6, 0x18, 0x80,
  0x10, 0x52, 0x06, 0xa1, 0x32, 0x0c, 0x32, 0x48, 0x1d, 0x35, 0x5c, 0xfe,
  0x84, 0x3d, 0x84, 0xe4, 0x73, 0x1b, 0x55, 0xac, 0xc4, 0xe4, 0x17, 0xb7,
  0x8d, 0x88, 0x31, 0xc6, 0xa0, 0x72, 0xcf, 0x70, 0xf9, 0x13, 0xf6, 0x10,
  0x92, 0x1f, 0x02, 0xcd, 0xb0, 0x10, 0x28, 0x68, 0x85, 0x60, 0xc4, 0x11,
  0x7a, 0x73, 0x04, 0x41, 0x31, 0x1c, 0x29, 0x84, 0x44, 0x92, 0x03, 0x01,
  0xc3, 0x08, 0xc4, 0x90, 0x04, 0xf5, 0x22, 0x69, 0x8a, 0x28, 0x61, 0xf2,
  0x4b, 0xc4, 0x38, 0xa6, 0xbf, 0x03, 0x26, 0x00, 0x09, 0xb5, 0x26, 0xc2,
  0x3d, 0x33, 0x38, 0x1c, 0x69, 0x5a, 0x00, 0xcc, 0xa1, 0x26, 0x9f, 0x15,
  0x88, 0x86, 0xe0, 0x9c, 0x46, 0x9a, 0x80, 0x66, 0xda, 0xa8, 0xa2, 0x20,
  0x22, 0xb1, 0x91, 0x26, 0xa0, 0x11, 0x08, 0x84, 0x58, 0x5b, 0x07, 0x21,
  0x03, 0x53, 0x4e, 0x05, 0x02, 0x00, 0x00, 0x00, 0x13, 0x14, 0x72, 0xc0,
  0x87, 0x74, 0x60, 0x87, 0x36, 0x68, 0x87, 0x79, 0x68, 0x03, 0x72, 0xc0,
  0x87, 0x0d, 0xaf, 0x50, 0x0e, 0x6d, 0xd0, 0x0e, 0x7a, 0x50, 0x0e, 0x6d,
  0x00, 0x0f, 0x7a, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d,
  0x90, 0x0e, 0x71, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e, 0x78,
  0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d, 0x90, 0x0e, 0x71, 0x60, 0x07, 0x7a,
  0x30, 0x07, 0x72, 0xd0, 0x06, 0xe9, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x73,
  0x20, 0x07, 0x6d, 0x90, 0x0e, 0x76, 0x40, 0x07, 0x7a, 0x60, 0x07, 0x74,
  0xd0, 0x06, 0xe6, 0x10, 0x07, 0x76, 0xa0, 0x07, 0x73, 0x20, 0x07, 0x6d,
  0x60, 0x0e, 0x73, 0x20, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xd0, 0x06, 0xe6,
  0x60, 0x07, 0x74, 0xa0, 0x07, 0x76, 0x40, 0x07, 0x6d, 0xe0, 0x0e, 0x78,
  0xa0, 0x07, 0x71, 0x60, 0x07, 0x7a, 0x30, 0x07, 0x72, 0xa0, 0x07, 0x76,
  0x40, 0x07, 0x43, 0x9e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x86, 0x3c, 0x06, 0x10, 0x00, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x79, 0x10, 0x20, 0x00, 0x04, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0xf2, 0x28, 0x40, 0x00, 0x04, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0xe4, 0x79, 0x80, 0x00, 0x18,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0xc8, 0x23, 0x01, 0x01,
  0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x16, 0x08, 0x00,
  0x0e, 0x00, 0x00, 0x00, 0x32, 0x1e, 0x98, 0x14, 0x19, 0x11, 0x4c, 0x90,
  0x8c, 0x09, 0x26, 0x47, 0xc6, 0x04, 0x43, 0x22, 0x25, 0x50, 0x04, 0xc5,
  0x30, 0x02, 0x50, 0xc0, 0x06, 0x65, 0x50, 0x0e, 0xe5, 0x41, 0xa5, 0x24,
  0xca, 0xa0, 0x10, 0x46, 0x00, 0x8a, 0xa0, 0x40, 0x48, 0xcf, 0x00, 0xd0,
  0x1e, 0x4b, 0x41, 0x08, 0x00, 0x00, 0x80, 0x40, 0x20, 0x00, 0x00, 0x00,
  0x79, 0x18, 0x00, 0x00, 0x58, 0x00, 0x00, 0x00, 0x1a, 0x03, 0x4c, 0x90,
  0x46, 0x02, 0x13, 0x44, 0x35, 0x18, 0x63, 0x0b, 0x73, 0x3b, 0x03, 0xb1,
  0x2b, 0x93, 0x9b, 0x4b, 0x7b, 0x73, 0x03, 0x99, 0x71, 0xb9, 0x01, 0x41,
  0xa1, 0x0b, 0x3b, 0x9b, 0x7b, 0x91, 0x2a, 0x62, 0x2a, 0x0a, 0x9a, 0x2a,
  0xfa, 0x9a, 0xb9, 0x81, 0x79, 0x31, 0x4b, 0x73, 0x0b, 0x63, 0x4b, 0xd9,
  0x10, 0x04, 0x13, 0x04, 0xc2, 0x98, 0x20, 0x10, 0xc7, 0x06, 0x61, 0x20,
  0x26, 0x08, 0x04, 0xb2, 0x41, 0x18, 0x0c, 0x0a, 0x70, 0x73, 0x1b, 0x06,
  0xc4, 0x20, 0x26, 0x08, 0x44, 0x32, 0x41, 0xd0, 0x28, 0x02, 0x13, 0x04,
  0x42, 0xd9, 0x80, 0x28, 0x0b, 0xa3, 0x28, 0x43, 0x03, 0x6c, 0x08, 0x9c,
  0x0d, 0x04, 0x00, 0x3c, 0xc0, 0x04, 0x61, 0xab, 0x36, 0x04, 0xd1, 0x04,
  0x41, 0x00, 0x48, 0xb4, 0x85, 0xa5, 0xb9, 0x71, 0x99, 0xb2, 0xfa, 0x82,
  0x7a, 0x9b, 0x4b, 0xa3, 0x4b, 0x7b, 0x73, 0x9b, 0x20, 0x14, 0xce, 0x04,
  0xa1, 0x78, 0x36, 0x04, 0xca, 0x04, 0xa1, 0x80, 0x26, 0x08, 0x45, 0xb4,
  0x61, 0x51, 0x2a, 0xeb, 0xc2, 0xb2, 0x21, 0x53, 0x34, 0x80, 0xc5, 0xd0,
  0x13, 0xd3, 0x93, 0xd4, 0x04, 0xa1, 0x90, 0x26, 0x08, 0xc4, 0x32, 0x41,
  0x20, 0x98, 0x0d, 0x82, 0xf7, 0x6d, 0x58, 0x06, 0xce, 0xd2, 0xb0, 0x6e,
  0xc8, 0x06, 0x0d, 0x0c, 0x36, 0x08, 0x5b, 0x18, 0x30, 0x99, 0xb2, 0xfa,
  0xa2, 0x0a, 0x93, 0x3b, 0x2b, 0xa3, 0x9b, 0x20, 0x14, 0xd3, 0x04, 0x81,
  0x68, 0x36, 0x08, 0x5e, 0x19, 0x6c, 0x58, 0x94, 0x31, 0xb0, 0xc8, 0x00,
  0xd3, 0x86, 0x4c, 0xd1, 0xcc, 0x60, 0x43, 0x70, 0x06, 0x1b, 0x06, 0x31,
  0x40, 0x03, 0x60, 0x43, 0x31, 0x51, 0x69, 0x00, 0x01, 0x55, 0xd8, 0xd8,
  0xec, 0xda, 0x5c, 0xd2, 0xc8, 0xca, 0xdc, 0xe8, 0xa6, 0x04, 0x41, 0x15,
  0x32, 0x3c, 0x17, 0xbb, 0x32, 0xb9, 0xb9, 0xb4, 0x37, 0xb7, 0x29, 0x01,
  0xd1, 0x84, 0x0c, 0xcf, 0xc5, 0x2e, 0x8c, 0xcd, 0xae, 0x4c, 0x6e, 0x4a,
  0x60, 0xd4, 0x21, 0xc3, 0x73, 0x99, 0x43, 0x0b, 0x23, 0x2b, 0x93, 0x6b,
  0x7a, 0x23, 0x2b, 0x63, 0x9b, 0x12, 0x20, 0x65, 0xc8, 0xf0, 0x5c, 0xe4,
  0xca, 0xe6, 0xde, 0xea, 0xe4, 0xc6, 0xca, 0xe6, 0xa6, 0x04, 0x4f, 0x1d,
  0x32, 0x3c, 0x17, 0xbb, 0xb4, 0xb2, 0xbb, 0x24, 0xb2, 0x29, 0xba, 0x30,
  0xba, 0xb2, 0x29, 0x41, 0x54, 0x87, 0x0c, 0xcf, 0xa5, 0xcc, 0x8d, 0x4e,
  0x2e, 0x0f, 0xea, 0x2d, 0xcd, 0x8d, 0x6e, 0x6e, 0x4a, 0x90, 0x06, 0x00,
  0x79, 0x18, 0x00, 0x00, 0x4c, 0x00, 0x00, 0x00, 0x33, 0x08, 0x80, 0x1c,
  0xc4, 0xe1, 0x1c, 0x66, 0x14, 0x01, 0x3d, 0x88, 0x43, 0x38, 0x84, 0xc3,
  0x8c, 0x42, 0x80, 0x07, 0x79, 0x78, 0x07, 0x73, 0x98, 0x71, 0x0c, 0xe6,
  0x00, 0x0f, 0xed, 0x10, 0x0e, 0xf4, 0x80, 0x0e, 0x33, 0x0c, 0x42, 0x1e,
  0xc2, 0xc1, 0x1d, 0xce, 0xa1, 0x1c, 0x66, 0x30, 0x05, 0x3d, 0x88, 0x43,
  0x38, 0x84, 0x83, 0x1b, 0xcc, 0x03, 0x3d, 0xc8, 0x43, 0x3d, 0x8c, 0x03,
  0x3d, 0xcc, 0x78, 0x8c, 0x74, 0x70, 0x07, 0x7b, 0x08, 0x07, 0x79, 0x48,
  0x87, 0x70, 0x70, 0x07, 0x7a, 0x70, 0x03, 0x76, 0x78, 0x87, 0x70, 0x20,
  0x87, 0x19, 0xcc, 0x11, 0x0e, 0xec, 0x90, 0x0e, 0xe1, 0x30, 0x0f, 0x6e,
  0x30, 0x0f, 0xe3, 0xf0, 0x0e, 0xf0, 0x50, 0x0e, 0x33, 0x10, 0xc4, 0x1d,
  0xde, 0x21, 0x1c, 0xd8, 0x21, 0x1d, 0xc2, 0x61, 0x1e, 0x66, 0x30, 0x89,
  0x3b, 0xbc, 0x83, 0x3b, 0xd0, 0x43, 0x39, 0xb4, 0x03, 0x3c, 0xbc, 0x83,
  0x3c, 0x84, 0x03, 0x3b, 0xcc, 0xf0, 0x14, 0x76, 0x60, 0x07, 0x7b, 0x68,
  0x07, 0x37, 0x68, 0x87, 0x72, 0x68, 0x07, 0x37, 0x80, 0x87, 0x70, 0x90,
  0x87, 0x70, 0x60, 0x07, 0x76, 0x28, 0x07, 0x76, 0xf8, 0x05, 0x76, 0x78,
  0x87, 0x77, 0x80, 0x87, 0x5f, 0x08, 0x87, 0x71, 0x18, 0x87, 0x72, 0x98,
  0x87, 0x79, 0x98, 0x81, 0x2c, 0xee, 0xf0, 0x0e, 0xee, 0xe0, 0x0e, 0xf5,
  0xc0, 0x0e, 0xec, 0x30, 0x03, 0x62, 0xc8, 0xa1, 0x1c, 0xe4, 0xa1, 0x1c,
  0xcc, 0xa1, 0x1c, 0xe4, 0xa1, 0x1c, 0xdc, 0x61, 0x1c, 0xca, 0x21, 0x1c,
  0xc4, 0x81, 0x1d, 0xca, 0x61, 0x06, 0xd6, 0x90, 0x43, 0x39, 0xc8, 0x43,
  0x39, 0x98, 0x43, 0x39, 0xc8, 0x43, 0x39, 0xb8, 0xc3, 0x38, 0x94, 0x43,
  0x38, 0x88, 0x03, 0x3b, 0x94, 0xc3, 0x2f, 0xbc, 0x83, 0x3c, 0xfc, 0x82,
  0x3b, 0xd4, 0x03, 0x3b, 0xb0, 0xc3, 0x0c, 0xc4, 0x21, 0x07, 0x7c, 0x70,
  0x03, 0x7a, 0x28, 0x87, 0x76, 0x80, 0x87, 0x19, 0xd1, 0x43, 0x0e, 0xf8,
  0xe0, 0x06, 0xe4, 0x20, 0x0e, 0xe7, 0xe0, 0x06, 0xf6, 0x10, 0x0e, 0xf2,
  0xc0, 0x0e, 0xe1, 0x90, 0x0f, 0xef, 0x50, 0x0f, 0xf4, 0x00, 0x00, 0x00,
  0x71, 0x20, 0x00, 0x00, 0x17, 0x00, 0x00, 0x00, 0x46, 0xb0, 0x0d, 0x97,
  0xef, 0x3c, 0xbe, 0x10, 0x50, 0x45, 0x41, 0x44, 0xa5, 0x03, 0x0c, 0x25,
  0x61, 0x00, 0x02, 0xe6, 0x17, 0xb7, 0x6d, 0x05, 0xd2, 0x70, 0xf9, 0xce,
  0xe3, 0x0b, 0x11, 0x01, 0x4c, 0x44, 0x08, 0x34, 0xc3, 0x42, 0x58, 0xc0,
  0x34, 0x5c, 0xbe, 0xf3, 0xf8, 0x8b, 0x03, 0x0c, 0x62, 0xf3, 0x50, 0x93,
  0x5f, 0xdc, 0xb6, 0x09, 0x54, 0xc3, 0xe5, 0x3b, 0x8f, 0x2f, 0x4d, 0x4e,
  0x44, 0xa0, 0xd4, 0xf4, 0x50, 0x93, 0x5f, 0xdc, 0xb6, 0x0d, 0x3c, 0xc3,
  0xe5, 0x3b, 0x8f, 0x4f, 0x35, 0x40, 0x84, 0xf9, 0xc5, 0x6d, 0x1b, 0x00,
  0xc1, 0x00, 0x48, 0x03, 0x61, 0x20, 0x00, 0x00, 0x43, 0x00, 0x00, 0x00,
  0x13, 0x04, 0x41, 0x2c, 0x10, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00,
  0x14, 0x47, 0x00, 0x88, 0x94, 0x42, 0x21, 0xcc, 0x00, 0x94, 0x4b, 0xa9,
  0x94, 0x5c, 0xd9, 0x95, 0x04, 0x95, 0x12, 0xa0, 0x31, 0x46, 0x00, 0x82,
  0x20, 0x88, 0x7f, 0x00, 0x23, 0x06, 0x09, 0x00, 0x82, 0x60, 0x20, 0x71,
  0xc5, 0x83, 0x61, 0xcb, 0x88, 0x41, 0x02, 0x80, 0x20, 0x18, 0x18, 0x61,
  0xa0, 0x70, 0x59, 0x94, 0x8c, 0x18, 0x24, 0x00, 0x08, 0x82, 0x81, 0x21,
  0x06, 0x4b, 0xa7, 0x11, 0xca, 0x88, 0x41, 0x02, 0x80, 0x20, 0x18, 0x18,
  0x63, 0xc0, 0x78, 0x9b, 0xb4, 0x8c, 0x18, 0x1c, 0x00, 0x08, 0x82, 0xc1,
  0x13, 0x06, 0x08, 0x71, 0x8c, 0x26, 0x04, 0xc3, 0x88, 0x81, 0x01, 0x80,
  0x20, 0x18, 0x28, 0x64, 0xf0, 0x15, 0x23, 0x06, 0x06, 0x00, 0x82, 0x60,
  0xa0, 0x94, 0x01, 0x18, 0x14, 0x23, 0x06, 0x06, 0x00, 0x82, 0x60, 0xa0,
  0x98, 0x41, 0x18, 0x14, 0x23, 0x06, 0x06, 0x00, 0x82, 0x60, 0xa0, 0x9c,
  0x01, 0x34, 0x8c, 0x18, 0x18, 0x00, 0x08, 0x82, 0x81, 0x82, 0x06, 0xd1,
  0x30, 0x62, 0x60, 0x00, 0x20, 0x08, 0x06, 0x4a, 0x1a, 0x48, 0x83, 0x0d,
  0x87, 0x7c, 0x6c, 0x40, 0xe4, 0x63, 0x43, 0x22, 0x9f, 0x11, 0x03, 0x03,
  0x00, 0x41, 0x30, 0x50, 0xda, 0xa0, 0x1a, 0x46, 0x0c, 0x0c, 0x00, 0x04,
  0xc1, 0x40, 0x71, 0x03, 0x6b, 0x18, 0x31, 0x30, 0x00, 0x10, 0x04, 0x03,
  0xe5, 0x0d, 0xae, 0x61, 0xc4, 0x20, 0x01, 0x40, 0x10, 0x0c, 0x90, 0x38,
  0xe0, 0xd4, 0x40, 0x0d, 0xc4, 0x60, 0x18, 0x31, 0x48, 0x00, 0x10, 0x04,
  0x03, 0x24, 0x0e, 0x38, 0x35, 0x50, 0x03, 0x4a, 0x18, 0x31, 0x48, 0x00,
  0x10, 0x04, 0x03, 0x24, 0x0e, 0x38, 0x35, 0x50, 0x83, 0x30, 0x08, 0x46,
  0x0c, 0x12, 0x00, 0x04, 0xc1, 0x00, 0x89, 0x03, 0x4e, 0x0d, 0xd4, 0x80,
  0x0c, 0x26, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00
};
