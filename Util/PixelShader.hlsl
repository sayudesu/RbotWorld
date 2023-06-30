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
    // ���C�g�x�N�g���̍쐬(�E�A���A��)
    float3 light = float3(1,-1,1);

    light = normalize(light);// ���K��

    // �@���}�b�v�̒l������Ă���
    float3 n = norm.Sample(smp,input.uv).rgb;
    // ���Ƃ̖@���x�N�g���̒l�𕜌����Ă���
    n.xy *= 2.0;// 2�{
    n.xy -= 1.0;// -1 = -1�`1
    // z��x��y����v�Z�ł���B�Ȃ��A�x�N�g����
    // �������Ɍ����Ă���O��Ȃ̂ŁA����n
    // �}�C�i�X�������Ă����܂�
    n.z = -sqrt(1 - n.x * n.x - n.y * n.y);

    float4 color = tex.Sample(smp, input.uv);
    if (color.a == 0.0) {
        discard;// �s�N�Z���V�F�[�_�[�̓�����j������
    }

    const float ambient = 0.2;

    // �f�B�t���[�Y���v�Z����
    float diffuse = saturate(dot(n, -light));
  
    color.rgb *= max(diffuse, ambient);

    // �X�y�L�������v�Z����
    light = reflect(light, n);
    float3 eyeRay = float3(0, 0, 1);
    float spec = pow(dot(light, -eyeRay), 5);

    return color;

    return float4(input.uv, 1.0f, 1.0f);
}