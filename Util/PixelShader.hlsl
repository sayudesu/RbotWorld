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
    // ライトベクトルの作成(右、下、奥)
    float3 light = float3(1,-1,1);

    light = normalize(light);// 正規化

    // 法線マップの値を取ってくる
    float3 n = norm.Sample(smp,input.uv).rgb;
    // もとの法線ベクトルの値を復元している
    n.xy *= 2.0;// 2倍
    n.xy -= 1.0;// -1 = -1～1
    // zはxとyから計算できる。なお、ベクトルは
    // こっちに向いている前提なので、左手系
    // マイナスをかけておきます
    n.z = -sqrt(1 - n.x * n.x - n.y * n.y);

    float4 color = tex.Sample(smp, input.uv);
    if (color.a == 0.0) {
        discard;// ピクセルシェーダーの内部を破棄する
    }

    const float ambient = 0.2;

    // ディフューズを計算する
    float diffuse = saturate(dot(n, -light));
  
    color.rgb *= max(diffuse, ambient);

    // スペキュラを計算する
    light = reflect(light, n);
    float3 eyeRay = float3(0, 0, 1);
    float spec = pow(dot(light, -eyeRay), 5);

    return color;

    return float4(input.uv, 1.0f, 1.0f);
}