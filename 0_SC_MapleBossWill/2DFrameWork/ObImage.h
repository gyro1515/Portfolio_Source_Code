#pragma once

class ObImage : public GameObject
{
private:
    static ID3D11Buffer*        vertexBuffer;
    static ID3D11Buffer*        uvBuffer;

public:
    static void CreateStaticMember();
    static void DeleteStaticMember();

private:
    ID3D11ShaderResourceView*   SRV;
    ID3D11SamplerState*         sampler;
    D3D11_SAMPLER_DESC	        samplerDesc;

    float                       animTime; //재생시킬 때 필요한 변수
    bool                        animXAxis; //가로재생?

public:
    float                       animInterval; //재생간격
    Vector4                     uv;
    Int2                        maxFrame;
    Int2                        frame;
    bool                        reverseLR;
    Int2                        imageSize;

private:

public:
    ObImage(wstring file);
    ~ObImage();

    void Render()override;
    void ChangeSampler(D3D11_FILTER filter = D3D11_FILTER_MIN_MAG_MIP_POINT,
        D3D11_TEXTURE_ADDRESS_MODE addressU = D3D11_TEXTURE_ADDRESS_WRAP,
        D3D11_TEXTURE_ADDRESS_MODE addressV = D3D11_TEXTURE_ADDRESS_WRAP);
};

