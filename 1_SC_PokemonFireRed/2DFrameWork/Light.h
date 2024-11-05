#pragma once
class Light : public Singleton<Light>
{
private:
    struct PointLight
    {
        Vector2 screenPos;      //스크린좌표  //8
        float   radius;         //반지름크기  //12
        float   padding; //16
    };

    struct LightBuffer
    {
        PointLight  lights[10];
        Vector4     select;         //상수버퍼는 16바이트 배수
        Color       outColor;       //조명 밖 색
        Color       inColor;
    };

    ID3D11Buffer* lightBuffer;

public:
    LightBuffer light;

    Light();
    ~Light();

    void        Set();
};

