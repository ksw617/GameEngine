
struct LightColor
{
    float4 diffuse; 
    float4 ambient; 
    float4 specular;
};


struct LightInfo
{
    LightColor color;   
    float4 position;    
    float4 direction;   
    int lightType;      
    float range;        
    float angle;        
    int padding;        
};

cbuffer GLOBAL_PARAMS : register(b0)
{
    int lightCount;     
    float3 padding;     
    LightInfo light[50];
}


cbuffer TRANSFORM_PARAMS : register(b1)
{
    row_major matrix matWorld;      
    row_major matrix matview;       
    row_major matrix matProjection; 
    row_major matrix matWV;         
    row_major matrix matWVP;        
}


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
    float3 normal : NORMAL;
};

struct VS_OUT
{
    float4 pos : SV_Position;   
    float2 uv : TEXCOORD; 
    float3 viewPos : POSITION;
    float3 viewNormal : NORMAL;
};


VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0; 

    output.pos = mul(float4(input.pos, 1.f), matWVP);
    output.uv = input.uv; 
    
    output.viewPos = mul(float4(input.pos, 1.f), matWV).xyz;
    output.viewNormal = normalize(mul(float4(input.normal, 0.f), matWV).xyz);
    return output;
    
}


LightColor CalculateLightColor(int lightIndex, float3 viewNormal, float3 viewPos)
{
    LightColor color = (LightColor) 0.f;    //초기 조명 색상 초기화
    
    float3 viewLightDir = (float3) 0.f;     //뷰 공간에서의 조명 방향 초기화
    float diffuseRatio = 0.f;               //확산광 비율 초기화
    float specularRatio = 0.f;              //반사광 비율 초기화
    float distanceRatio = 0.f;              //거리 비율 초기화
    
    //Directional Light(다이렉트 조명) 라면
    if (light[lightIndex].lightType == 0)
    {
        //조명 방향을 뷰 공간으로 변환
        viewLightDir = normalize(mul(float4(light[lightIndex].direction.xyz, 0f), matview).xyz);

        //벡터의 내적 dot 외적 cross
        //확산광 비율 계산(조명 방향 벡터와 normal 벡터와의 내적)
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));

    }
    //Point Light(포인트 조명)이라면
    else if (light[lightIndex].lightType == 1)
    {
        //조명 위치를 뷰 공간으로 변환
        float3 viewLightPos = mul(float4(light[lightIndex].position.xyz, 1f), matview).xyz;

        //조명 방향 벡터 계산(정점 위치와 조명 위치의 차이)
        viewLightDir = normalize(viewPos - viewLightPos);
        
        //확산광 비율 계산(조명 방향 벡터와 normal 벡터와의 내적)
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));
        
        //정점 위치과 조명 위치간의 거리 계산
        float dist = distance(viewPos, viewLightPos);
        
        //거리 비율 계산(조명 범위에 따른 감쇠)
        distanceRatio = light[lightIndex].range == 0.f ? 0.f : saturate(1.f - pow(dist / light[lightIndex].range, 2));

    }
    //Spot Light(스포트라이트) 라면
    else
    {
        //조명 위치를 뷰 공간으로 변환
        float3 viewLightPos = mul(float4(light[lightIndex].position.xyz, 1f), matview).xyz;
        
        //조명 방향 벡터 계산(정점 위치와 조명 위치의 차이)의 정규화
        viewLightDir = normalize(viewPos - viewLightPos);
        
        //확산광 비율 계산(방향벡터와 normal 벡터와의 내적)
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));

        if (light[lightIndex].range == 0.f)
        {
            distanceRatio = 0.f;
        }
        else
        {
            //스포트라이트의 절반 각도 계산
            float halfAngle = light[lightIndex].angle / 2;
            
            //뷰 공간에서의 조명 벡터 계산
            float3 viewLightVec = viewPos - viewLightPos;
            //뷰 공간에서의 조명중심의 방향 벡터 계산
            float3 viewCenterLightDir = normalize(mul(float4(light[lightIndex].direction.xyz, 0.f), matview).xyz);

            //중심 거리 계산(정점 위치와 조명 방향 벡터의 내적)
            float centerDist = dot(viewLightVec, viewCenterLightDir);
            
            //거리 비율 계산(조명 범위에 따른 감쇠)
            distanceRatio = saturate(1.f - centerDist / light[lightIndex].range);

            //조명 각도 계산(정점 위치와 중심 조명 방향 벡터간의 각도)
            float lightAngle = acos(dot(normalize(viewLightVec), viewCenterLightDir));

            if (centerDist < 0.f || centerDist > light[lightIndex].range || lightAngle > halfAngle)
                distanceRatio = 0.f;
            else
                distanceRatio = saturate(1.f - pow(centerDist / light[lightIndex].range, 2));

        }

    }
    
    //스펙큘러 반사 방향 벡터 계산
    float3 reflectionDir = normalize(viewLightDir + 2 * (saturate(dot(-viewLightDir, viewNormal)) * viewNormal));

    //카메라 방향 벡터 계산
    float3 eyeDir = normalize(viewPos);
    
    //스펙큘러 반사 비율 계산
    specularRatio = pow(saturate(dot(-eyeDir, reflectionDir)), 2);
    
    //최종 조명 색상 계산
    color.diffuse = light[lightIndex].color.diffuse * diffuseRatio * distanceRatio;
    color.ambient = light[lightIndex].color.ambient * distanceRatio;
    color.specular = light[lightIndex].color.specular * specularRatio * distanceRatio;
    
    return color;
}


//픽셀 쉐이더 메인 함수
float4 PS_Main(VS_OUT input) : SV_Target
{
    //기본 색상 설정(흰색)
    float4 color = float4(1.f, 1.f, 1.f, 1.f);

    //전체 조명 색상 초기화
    LightColor totalColor = (LightColor) 0.f;
    
    //각 조명에 대한 색상 계산
    for (int i = 0; i < lightCount; i++)
    {
        LightColor color = CalculateLightColor(i, input.viewNormal, input.viewPos);
        totalColor.diffuse += color.diffuse;
        totalColor.ambient += color.ambient;
        totalColor.specular += color.specular;

    }

    //계산된 조명 색상을 적용하여 최종 색상 결정
    color.xyz = (totalColor.diffuse.xyz * color.xyz)
    + (totalColor.ambient.xyz * color.xyz)
    + totalColor.specular.xyz;

    return color;
}

