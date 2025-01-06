#pragma once

class Shader;
class Texture;

//Material �Ű������� �ִ� ������ ����
enum 
{
	MATERIAL_INT_COUNT = 5,		//���� �Ű������� �ִ� ����
	MATERIAL_FLOAT_COUNT = 5,	//�Ǽ� �Ű������� �ִ� ����
	MATERIAL_TEXTURE_COUNT = 5,	//�ؽ�ó �Ű������� �ִ� ����

};

//Material �Ű������� �����ϴ� ����ü
struct MaterialParams
{
	//���� �Ű������� �����ϴ� �迭
	array<INT32, MATERIAL_INT_COUNT> intParams;		//[4][4][4][4][4]
	//�Ǽ� �Ű������� �����ϴ� �迭
	array<float, MATERIAL_FLOAT_COUNT> floatParams;	//[4][4][4][4][4]

	//index :0~4
	//���� �Ű������� �����ϴ� Set �Լ�
	void SetInt(UINT8 index, INT32 value) { intParams[index] = value; }

	//�Ǽ� �Ű������� �����ϴ� Set �Լ�
	void SetFloat(UINT8 index, float value) { floatParams[index] = value; }

};

class Material
{
private:
	shared_ptr<Shader> shader;	// ���̴� ��ü
	MaterialParams params;		//Material �Ű�����
	array<shared_ptr<Texture>, MATERIAL_TEXTURE_COUNT> textures; // �ؽ�ó �迭

public:
	//���̴� ��ȯ�ϴ� Get�Լ�
	shared_ptr<Shader> GetShader() { return shader; }

public:
	//���̴� Set�ϴ� �Լ�
	void SetShader(shared_ptr<Shader> _shader) { shader = _shader; }

	//���� �Ű������� �����ϴ� Set �Լ�
	void SetInt(UINT8 index, INT32 value) { params.SetInt(index, value); }

	//�Ǽ� �Ű������� �����ϴ� Set �Լ�
	void SetFloat(UINT8 index, float value) { params.SetFloat(index, value); }
	//�ؽ�ó �Ű������� �����ϴ� Set �Լ�
	void SetTexture(UINT8 index, shared_ptr<Texture> value) { textures[index] = value; }
public:
	//Material ������Ʈ �����ִ� �Լ�
	void Update();
};

