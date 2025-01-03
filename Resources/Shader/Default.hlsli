
cbuffer TEST_B0 : register(b0)
{
    float4 offset0; 
}

cbuffer TEST_B1 : register(b1)
{
    float4 offset1;
}

//텍스처 2D, 레지스터 t0에 바인딩
Texture2D tex_0 : register(t0);

//샘플러 상태, 레지스터 s0에 바인딩
SamplerState sam_0 : register(s0);


struct VS_IN
{
    float3 pos : POSITION; 
    float4 color : COLOR;
    float2 uv : TEXCOORD; // 텍스처 좌표
};

struct VS_OUT
{
    float4 pos : SV_Position;   
    float4 color : COLOR;      
    float2 uv : TEXCOORD; // 텍스처 좌표
};


VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0; 
    output.pos = float4(input.pos, 1.f);
    output.pos += offset0; // 위치값 변경
    output.color = input.color;
    
    output.uv = input.uv; 
   
    return output;
    
}


float4 PS_Main(VS_OUT input) : SV_Target
{
    float4 color = tex_0.Sample(sam_0, input.uv);
    
    return color;
}