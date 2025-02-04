#ifndef _SKYBOX_FX_
#define _SKYBOX_FX_

#include "Params.fx"

struct VS_IN
{
    float3 localPos : POSITIONT;
    float2 uv : TEXCOORD;
};
    
struct VS_OUT
{
    float4 pos : SV_Position;
    float2 uv : TEXCOORD;
};

VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0;
    
    //Translation�� ���� �ʰ� ȸ������ ���� 
    float4 viewPos = mul(float4(input.localPos, 0.f), matView);
    float4 clipSpacePos = mul(viewPos, matProjection);
    
    //w/w =1 �̱� ������ �׻� ���� ���� 1�� ����
    output.pos = clipSpacePos.xyww;
    output.uv = input.uv;
    
    return output;

}

float4 PS_MAIN(VS_OUT input) : SV_Target
{
    float4 color = tex_0.Sample(sam_0, input.uv);
    return color;

}
#endif