
//조명 색상 저장
struct LightColor
{
    float4 diffuse; //확산광 색상
    float4 ambient; //주변광 색상
    float4 specular;//반사광 색상
};

//조명 정보를 저장
struct LightInfo
{
    LightColor color;   //조명 색상 48byte 16*3
    float4 position;    //조명 위치 +16byte
    float4 direction;   //조명 방향 +16byte
    int lightType;      //(0:Directional, 1:Point, 2:Spot 3:..)// +4byte
    float range;        //조명 범위(Point 조명, Spot 조명이 해당)// +4byte
    float angle;        //조명 각도(Spot 조명이 해당)            // +4byte
    int padding;        //패딩(메모리 정렬을 위해)               // +4byte
};

//전역 파라미터 버퍼: b0 레지스터에 바인딩
cbuffer GLOBAL_PARAMS : register(b0)
{
    int lightCount;     //조명갯수                  // 4byte
    float3 padding;     //패딩(메모리 정렬을 위해)   // + 12byte
    LightInfo light[50];//최대 50개의 조명 정보
}

//Transform 파라미터는 b1에 바인딩
cbuffer TRANSFORM_PARAMS : register(b1)
{
    row_major matrix matWorld;      //월드 행렬
    row_major matrix matview;       //뷰 행렬
    row_major matrix matProjection; //투영 행렬
    row_major matrix matWV;         //월드-뷰 행렬
    row_major matrix matWVP;        //월드-뷰-투영 행렬
}

//Material 파라미터는 b2에 바인딩
cbuffer MATERIAL_PARAMS : register(b2)
{
    int int_0;
    int int_1;
    int int_2;
    int int_3;
    int int_4;
    
    float float_0;
    float float_1;
    float float_2;
    float float_3;
    float float_4;
}

Texture2D tex_0 : register(t0);
Texture2D tex_1 : register(t1);
Texture2D tex_2 : register(t2);
Texture2D tex_3 : register(t3);
Texture2D tex_4 : register(t4);


SamplerState sam_0 : register(s0);


struct VS_IN
{
    float3 pos : POSITION; 
    float2 uv : TEXCOORD;
    float3 normal : NORMAL; // Normal 벡터
};

struct VS_OUT
{
    float4 pos : SV_Position;   
    float2 uv : TEXCOORD; 
    float3 viewPos : POSITION; // 뷰 공간 정점 위치
    float3 viewNormal : NORMAL;// 뷰 공간 Normal 벡터
};


VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0; 

    //정점 위치를 변환하여 클립 공간 좌표를 계산
    output.pos = mul(float4(input.pos, 1.f), matWVP);
    output.uv = input.uv; 
    
    //뷰 공간 정점 위치와 normal 벡터를 계산
    output.viewPos = mul(float4(input.pos, 1.f), matWV).xyz;
    output.viewNormal = normalize(mul(float4(input.normal, 0.f), matWV).xyz);
    return output;
    
}

