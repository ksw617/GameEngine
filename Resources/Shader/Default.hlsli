
//���� ���� ����
struct LightColor
{
    float4 diffuse; //Ȯ�걤 ����
    float4 ambient; //�ֺ��� ����
    float4 specular;//�ݻ籤 ����
};

//���� ������ ����
struct LightInfo
{
    LightColor color;   //���� ���� 48byte 16*3
    float4 position;    //���� ��ġ +16byte
    float4 direction;   //���� ���� +16byte
    int lightType;      //(0:Directional, 1:Point, 2:Spot 3:..)// +4byte
    float range;        //���� ����(Point ����, Spot ������ �ش�)// +4byte
    float angle;        //���� ����(Spot ������ �ش�)            // +4byte
    int padding;        //�е�(�޸� ������ ����)               // +4byte
};

//���� �Ķ���� ����: b0 �������Ϳ� ���ε�
cbuffer GLOBAL_PARAMS : register(b0)
{
    int lightCount;     //������                  // 4byte
    float3 padding;     //�е�(�޸� ������ ����)   // + 12byte
    LightInfo light[50];//�ִ� 50���� ���� ����
}

//Transform �Ķ���ʹ� b1�� ���ε�
cbuffer TRANSFORM_PARAMS : register(b1)
{
    row_major matrix matWorld;      //���� ���
    row_major matrix matview;       //�� ���
    row_major matrix matProjection; //���� ���
    row_major matrix matWV;         //����-�� ���
    row_major matrix matWVP;        //����-��-���� ���
}

//Material �Ķ���ʹ� b2�� ���ε�
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
    float3 normal : NORMAL; // Normal ����
};

struct VS_OUT
{
    float4 pos : SV_Position;   
    float2 uv : TEXCOORD; 
    float3 viewPos : POSITION; // �� ���� ���� ��ġ
    float3 viewNormal : NORMAL;// �� ���� Normal ����
};


VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0; 

    //���� ��ġ�� ��ȯ�Ͽ� Ŭ�� ���� ��ǥ�� ���
    output.pos = mul(float4(input.pos, 1.f), matWVP);
    output.uv = input.uv; 
    
    //�� ���� ���� ��ġ�� normal ���͸� ���
    output.viewPos = mul(float4(input.pos, 1.f), matWV).xyz;
    output.viewNormal = normalize(mul(float4(input.normal, 0.f), matWV).xyz);
    return output;
    
}

