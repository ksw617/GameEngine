
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
    
    //texture ����
    int tex_on_0;
    int tex_on_1;
    int tex_on_2;
    int tex_on_3;
    int tex_on_4;
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
    //tangent�� �߰�
    float3 tangent : TANGENT;
   
};

struct VS_OUT
{
    float4 pos : SV_Position;   
    float2 uv : TEXCOORD; 
    float3 viewPos : POSITION;
    float3 viewNormal : NORMAL;
    
    //viewTangent�� �߰�
    float3 viewTangent : TANGENT;
    //viewBinormal�� �߰�
    float3 viewBinormal : BINORMAL;
};


VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0; 

    output.pos = mul(float4(input.pos, 1.f), matWVP);
    output.uv = input.uv; 
    
    output.viewPos = mul(float4(input.pos, 1.f), matWV).xyz;
    output.viewNormal = normalize(mul(float4(input.normal, 0.f), matWV).xyz);
    
    //input.tangent������ viewTangent ����
    output.viewTangent = normalize(mul(float4(input.tangent, 0.f), matWV).xyz);
    //viewTangent�� viewNormal�� ������ ���� viewBinormal�� �־���
    output.viewBinormal = normalize(cross(output.viewTangent, output.viewNormal));
    return output;
    
}


LightColor CalculateLightColor(int lightIndex, float3 viewNormal, float3 viewPos)
{
    LightColor color = (LightColor) 0;   
    
    float3 viewLightDir = (float3) 0.f;    
    float diffuseRatio = 0.f;              
    float specularRatio = 0.f;             
    float distanceRatio = 1.f;            
    
            
    
    if (light[lightIndex].lightType == 0)
    {
        viewLightDir = normalize(mul(float4(light[lightIndex].direction.xyz, 0.f), matview).xyz);
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));
    
    }
    else if (light[lightIndex].lightType == 1)
    {
        float3 viewLightPos = mul(float4(light[lightIndex].position.xyz, 1.f), matview).xyz;
        viewLightDir = normalize(viewPos - viewLightPos);
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));
        float dist = distance(viewPos, viewLightPos);
       
        distanceRatio = light[lightIndex].range == 0.f ? 0.f : saturate(1.f - pow(dist / light[lightIndex].range, 2));

    }
    else
    {
        float3 viewLightPos = mul(float4(light[lightIndex].position.xyz, 1.f), matview).xyz;
        viewLightDir = normalize(viewPos - viewLightPos);
        
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));

        if (light[lightIndex].range == 0.f)
        {
            distanceRatio = 0.f;
        }
        else
        {
            float halfAngle = light[lightIndex].angle / 2;      
            float3 viewLightVec = viewPos - viewLightPos;
            float3 viewCenterLightDir = normalize(mul(float4(light[lightIndex].direction.xyz, 0.f), matview).xyz);
            float centerDist = dot(viewLightVec, viewCenterLightDir);
            
            distanceRatio = saturate(1.f - centerDist / light[lightIndex].range);

            float lightAngle = acos(dot(normalize(viewLightVec), viewCenterLightDir));

            if (centerDist < 0.f || centerDist > light[lightIndex].range || lightAngle > halfAngle)
                distanceRatio = 0.f;
            else
                distanceRatio = saturate(1.f - pow(centerDist / light[lightIndex].range, 2));

        }

    }
    
    float3 reflectionDir = normalize(viewLightDir + 2 * (saturate(dot(-viewLightDir, viewNormal)) * viewNormal));
    float3 eyeDir = normalize(viewPos);
    specularRatio = pow(saturate(dot(-eyeDir, reflectionDir)), 2);
    
    color.diffuse = light[lightIndex].color.diffuse * diffuseRatio * distanceRatio;
    color.ambient = light[lightIndex].color.ambient * distanceRatio;
    color.specular = light[lightIndex].color.specular * specularRatio * distanceRatio;

    return color;
}


float4 PS_Main(VS_OUT input) : SV_Target
{
    float4 color = float4(1.f, 1.f, 1.f, 1.f);
    
    //�⺻ texture���� true�� ��� �ؽ�ó�� ���ø��Ͽ� ������ ����
    if(tex_on_0)
        color = tex_0.Sample(sam_0, input.uv);

    //�ʱ� viewNormal�� ����
    float3 viewNormal = input.viewNormal;
    
    //NormalMap���� true�� ��� �ι�° �ؽ�ó�� ����Ͽ� Normal Map ���ø�
    if(tex_on_1)
    {
        //[0~255] ������ �ؽ�ó ���� [0,1] ������ ��ȯ
        float3 tangentSpaceNormal = tex_1.Sample(sam_0, input.uv).xyz;
        
        //[0~1]qjadnlfmf [-1, 1] ������ ��ȯ
        tangentSpaceNormal = (tangentSpaceNormal - 0.5f) * 2.f;
        
        //TBN ��Ʈ������ ����Ͽ� �׽�ó ������ Normal�� �� ������ Normal�� ��ȯ
        float3x3 matTBN = { input.viewTangent, input.viewBinormal, input.viewNormal };
        viewNormal = normalize(mul(tangentSpaceNormal, matTBN));

    }
    
    LightColor totalColor = (LightColor) 0.f;
    
    for (int i = 0; i < lightCount; i++)
    {
        //���� ���� viewNormal ����
        LightColor lightColor = CalculateLightColor(i, viewNormal, input.viewPos);
        totalColor.diffuse += lightColor.diffuse;
        totalColor.ambient += lightColor.ambient;
        totalColor.specular += lightColor.specular;

    }

    color.xyz = (totalColor.diffuse.xyz * color.xyz)
    + (totalColor.ambient.xyz * color.xyz)
    + totalColor.specular.xyz;

    return color;
}

