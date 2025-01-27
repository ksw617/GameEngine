
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
    LightColor color = (LightColor) 0.f;    //�ʱ� ���� ���� �ʱ�ȭ
    
    float3 viewLightDir = (float3) 0.f;     //�� ���������� ���� ���� �ʱ�ȭ
    float diffuseRatio = 0.f;               //Ȯ�걤 ���� �ʱ�ȭ
    float specularRatio = 0.f;              //�ݻ籤 ���� �ʱ�ȭ
    float distanceRatio = 0.f;              //�Ÿ� ���� �ʱ�ȭ
    
    //Directional Light(���̷�Ʈ ����) ���
    if (light[lightIndex].lightType == 0)
    {
        //���� ������ �� �������� ��ȯ
        viewLightDir = normalize(mul(float4(light[lightIndex].direction.xyz, 0f), matview).xyz);

        //������ ���� dot ���� cross
        //Ȯ�걤 ���� ���(���� ���� ���Ϳ� normal ���Ϳ��� ����)
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));

    }
    //Point Light(����Ʈ ����)�̶��
    else if (light[lightIndex].lightType == 1)
    {
        //���� ��ġ�� �� �������� ��ȯ
        float3 viewLightPos = mul(float4(light[lightIndex].position.xyz, 1f), matview).xyz;

        //���� ���� ���� ���(���� ��ġ�� ���� ��ġ�� ����)
        viewLightDir = normalize(viewPos - viewLightPos);
        
        //Ȯ�걤 ���� ���(���� ���� ���Ϳ� normal ���Ϳ��� ����)
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));
        
        //���� ��ġ�� ���� ��ġ���� �Ÿ� ���
        float dist = distance(viewPos, viewLightPos);
        
        //�Ÿ� ���� ���(���� ������ ���� ����)
        distanceRatio = light[lightIndex].range == 0.f ? 0.f : saturate(1.f - pow(dist / light[lightIndex].range, 2));

    }
    //Spot Light(����Ʈ����Ʈ) ���
    else
    {
        //���� ��ġ�� �� �������� ��ȯ
        float3 viewLightPos = mul(float4(light[lightIndex].position.xyz, 1f), matview).xyz;
        
        //���� ���� ���� ���(���� ��ġ�� ���� ��ġ�� ����)�� ����ȭ
        viewLightDir = normalize(viewPos - viewLightPos);
        
        //Ȯ�걤 ���� ���(���⺤�Ϳ� normal ���Ϳ��� ����)
        diffuseRatio = saturate(dot(-viewLightDir, viewNormal));

        if (light[lightIndex].range == 0.f)
        {
            distanceRatio = 0.f;
        }
        else
        {
            //����Ʈ����Ʈ�� ���� ���� ���
            float halfAngle = light[lightIndex].angle / 2;
            
            //�� ���������� ���� ���� ���
            float3 viewLightVec = viewPos - viewLightPos;
            //�� ���������� �����߽��� ���� ���� ���
            float3 viewCenterLightDir = normalize(mul(float4(light[lightIndex].direction.xyz, 0.f), matview).xyz);

            //�߽� �Ÿ� ���(���� ��ġ�� ���� ���� ������ ����)
            float centerDist = dot(viewLightVec, viewCenterLightDir);
            
            //�Ÿ� ���� ���(���� ������ ���� ����)
            distanceRatio = saturate(1.f - centerDist / light[lightIndex].range);

            //���� ���� ���(���� ��ġ�� �߽� ���� ���� ���Ͱ��� ����)
            float lightAngle = acos(dot(normalize(viewLightVec), viewCenterLightDir));

            if (centerDist < 0.f || centerDist > light[lightIndex].range || lightAngle > halfAngle)
                distanceRatio = 0.f;
            else
                distanceRatio = saturate(1.f - pow(centerDist / light[lightIndex].range, 2));

        }

    }
    
    //����ŧ�� �ݻ� ���� ���� ���
    float3 reflectionDir = normalize(viewLightDir + 2 * (saturate(dot(-viewLightDir, viewNormal)) * viewNormal));

    //ī�޶� ���� ���� ���
    float3 eyeDir = normalize(viewPos);
    
    //����ŧ�� �ݻ� ���� ���
    specularRatio = pow(saturate(dot(-eyeDir, reflectionDir)), 2);
    
    //���� ���� ���� ���
    color.diffuse = light[lightIndex].color.diffuse * diffuseRatio * distanceRatio;
    color.ambient = light[lightIndex].color.ambient * distanceRatio;
    color.specular = light[lightIndex].color.specular * specularRatio * distanceRatio;
    
    return color;
}


//�ȼ� ���̴� ���� �Լ�
float4 PS_Main(VS_OUT input) : SV_Target
{
    //�⺻ ���� ����(���)
    float4 color = float4(1.f, 1.f, 1.f, 1.f);

    //��ü ���� ���� �ʱ�ȭ
    LightColor totalColor = (LightColor) 0.f;
    
    //�� ���� ���� ���� ���
    for (int i = 0; i < lightCount; i++)
    {
        LightColor color = CalculateLightColor(i, input.viewNormal, input.viewPos);
        totalColor.diffuse += color.diffuse;
        totalColor.ambient += color.ambient;
        totalColor.specular += color.specular;

    }

    //���� ���� ������ �����Ͽ� ���� ���� ����
    color.xyz = (totalColor.diffuse.xyz * color.xyz)
    + (totalColor.ambient.xyz * color.xyz)
    + totalColor.specular.xyz;

    return color;
}

