struct PSInput {
    float4 pos : SV_POSITION;// �V�X�e���ɓn�����W
    float3 color : COLOR;// ���_�J���[
    float2 uv : TEXCOORD;// UV���W
};

// �e�N�X�`���I�u�W�F�N�g
Texture2D tex : register(t0);
Texture2D norm : register(t1);
SamplerState smp : register(s0);

float4 main(PSInput input) : SV_TARGET
{

    return float4(0.0f,0.0f,0.0f,0.0f);

}