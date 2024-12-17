
//Vertex Shader In
struct VS_IN
{
    float3 pos : POSITION; //���� ��ġ
    float4 color : COLOR; // ���� ����
};

//Vertex Shader Out
struct VS_OUT
{
    float4 pos : SV_Position;   // ��ȯ�� ���� ��ġ (Ŭ�� ����)
    float4 color : COLOR;       // ���� ����
};

//Vertex Shader Main
VS_OUT VS_Main(VS_IN input)
{
    VS_OUT output = (VS_OUT) 0; // ��� ����ü �ʱ�ȭ
    //�Է� ���� ��ġ�� float4�� ��ȯ(w=1.0f)
    output.pos = float4(input.pos, 1.f);
    //�Է� ���� ������ �״�� ����
    output.color = input.color;
    
    return output; // ��� ����ü ��ȯ
    
}

//Pixel Shader Main
float4 PS_Main(VS_OUT input) : SV_Target
{
    //�Է� ���� ������ �״�� ��ȯ
    return input.color;
}