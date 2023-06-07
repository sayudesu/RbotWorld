struct PSInput {
    float4 pos : SV_POSITION;// システムに渡す座標
    float3 color : COLOR;// 頂点カラー
    float2 uv : TEXCOORD;// UV座標
};

// テクスチャオブジェクト
Texture2D tex : register(t0);
Texture2D norm : register(t1);
SamplerState smp : register(s0);

float4 main(PSInput input) : SV_TARGET
{

    return float4(0.0f,0.0f,0.0f,0.0f);

}