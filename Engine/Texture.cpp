#include "pch.h"
#include "Texture.h"
#include "GameEngine.h"

void Texture::Init(const wstring& path)
{
	//�ؽ�ó ����
	CreateTexture(path);

	//�ؽ�ó �� ����
	CreateView();
}

void Texture::CreateTexture(const wstring& path)
{
	//���� Ȯ���� ���
	wstring ext = filesystem::path(path).extension();

	//���� Ȯ���ڿ� ���� ������ �ε� �Լ� ȣ��
	if (ext == L".dds" || ext == L".DDS")
		LoadFromDDSFile(path.c_str(), DDS_FLAGS_NONE, nullptr, image);
	else if (ext == L".tga" || ext == L".TGA")
		LoadFromTGAFile(path.c_str(), nullptr, image);
	else // png, jpg, jpeg, bmp
		LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, image);

	//�ؽ�ó ����
	HRESULT hr = DirectX::CreateTexture(GameEngine::Get().GetDevice()->GetDevice().Get(), image.GetMetadata(), &texture2D);

	//�ؽ�ó ���� ���ϸ� ũ����
	if (FAILED(hr))
		assert(nullptr);

	//���� ���ҽ� ������ ����
	vector<D3D12_SUBRESOURCE_DATA> subResource;

	//���ε� �غ�
	hr = PrepareUpload(GameEngine::Get().GetDevice()->GetDevice().Get(),
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		subResource);

	//���ε� �غ� ���ϸ� ũ����
	if (FAILED(hr))
		assert(nullptr);

	//�߰� ������ ũ�� ���
	const UINT64 bufferSize = GetRequiredIntermediateSize(texture2D.Get(), 0, static_cast<UINT32>(subResource.size()));

	//�� �Ӽ� ����(���ε� ��)
	D3D12_HEAP_PROPERTIES heapProperty = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);

	//���ҽ� ������ ����(���� ������)
	D3D12_RESOURCE_DESC desc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

	//�ؽ�ó ���ε� �� ���ҽ� ����
	ComPtr<ID3D12Resource> textureUploadHeap;
	hr = GameEngine::Get().GetDevice()->GetDevice()->CreateCommittedResource(
		&heapProperty,
		D3D12_HEAP_FLAG_NONE,
		&desc,
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(textureUploadHeap.GetAddressOf()));

	//���ϸ� ũ����
	if (FAILED(hr))
		assert(nullptr);

	//���� ���ҽ� �ؽ�ó�� ����
	UpdateSubresources(GameEngine::Get().GetCmdQueue()->GetResourceCmdList().Get(),
		texture2D.Get(),
		textureUploadHeap.Get(),
		NULL, NULL,
		static_cast<UINT32>(subResource.size()),
		subResource.data());


	//���ҽ� ��� ��⿭ ����
	GameEngine::Get().GetCmdQueue()->SubmitResourceCommandQueue();
}

void Texture::CreateView()
{
	//SRV ��ũ���� �� ������ �ʱ�ȭ
	D3D12_DESCRIPTOR_HEAP_DESC srvHeapDesc = {};
	srvHeapDesc.NumDescriptors = 1; // ��ũ���� ���� 1��
	srvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV; // �� Ÿ���� CBV/SRV/UAV
	srvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE; // �÷��� ����

	//��ũ���� �� ����
	GameEngine::Get().GetDevice()->GetDevice()->CreateDescriptorHeap(&srvHeapDesc, IID_PPV_ARGS(&srvHeap));

	//SRV�� CPU ��ũ���� �ڵ� ��������
	srvHandle = srvHeap->GetCPUDescriptorHandleForHeapStart();

	//���̴� ���ҽ� ��(SRV) ������ �ʱ�ȭ
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
	srvDesc.Format = image.GetMetadata().format; // �̹��� ���˼���
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D; // 2D �ؽ�ó �� ����
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING; //�⺻ ���̴� 4 ������Ʈ ����
	srvDesc.Texture2D.MipLevels = 1; //Mip ������ ����

	GameEngine::Get().GetDevice()->GetDevice()->CreateShaderResourceView(texture2D.Get(), &srvDesc, srvHandle); // SRV ����
}
