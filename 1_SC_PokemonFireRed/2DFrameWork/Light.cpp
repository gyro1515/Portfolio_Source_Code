#include "framework.h"

Light::Light()
{
    for (int i = 0; i < 10; i++)
    {
        //조명의 좌표는 스크린 좌표계
        light.lights[i].screenPos = Vector2(app.GetHalfWidth(), app.GetHalfHeight());
        light.lights[i].radius = 0.0f;
    }
    
    //조명색
    light.inColor = Color(0.5f, 0.5f, 0.5f, 0.5f); // 안에 섞을 색
    //경계밖 색
    light.outColor = Color(0.0f, 0.0f, 0.0f, 0.5f); //밖에 섞을 색
    light.select.x = 0.0f;

    //CreateConstantBuffer
    {
        D3D11_BUFFER_DESC desc = { 0 };
        desc.ByteWidth = sizeof(LightBuffer);
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; //상수버퍼
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, NULL, &lightBuffer);
        assert(SUCCEEDED(hr));
    }

    D3D->GetDC()->PSSetConstantBuffers(0, 1, &lightBuffer);
}

Light::~Light()
{
    SafeRelease(lightBuffer);
}

void Light::Set()
{
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    D3D->GetDC()->Map(lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
    memcpy_s(mappedResource.pData, sizeof(LightBuffer), &light, sizeof(LightBuffer));
    D3D->GetDC()->Unmap(lightBuffer, 0);
}