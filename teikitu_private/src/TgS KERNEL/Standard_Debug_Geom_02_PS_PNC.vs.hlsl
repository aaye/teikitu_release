#include "Standard_Debug_Common.hlsli"

PSInput_PNC main( in STg2_KN_GPU_Vertex_Geom_02 input )
{
    PSInput_PNC result;

    result.pos_w = mul(float4(input.m_vS0.xyz, 1.0f),Debug_Model.m_vModel_Transform).xyz;
    result.pos_v = mul(float4(result.pos_w, 1.0f),Debug_Model.m_mW2C).xyz;
    result.pos_p = mul(float4(result.pos_v, 1.0f),Debug_Model.m_mC2S);
    result.normal = mul(float4(input.m_vN0.xyz, 0.0f),Debug_Model.m_vModel_Transform).xyz;
    result.colour = Debug_Model.m_uModel_Colour;

    return result;
}
