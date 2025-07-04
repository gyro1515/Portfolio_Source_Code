#pragma once
class Texture :public Singleton<Texture>
{
private:
    struct TextureNode
    {
        ID3D11ShaderResourceView*   srv;
        Int2                        textureSize;
    };

    map<wstring, TextureNode> textureList;

public:
    ~Texture();
    ID3D11ShaderResourceView* LoadTexture(wstring file);
    bool DeleteTexture(wstring file);
    Int2 GetTextureSize(wstring file);
};

