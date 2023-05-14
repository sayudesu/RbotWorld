#include "Animation.h"
#include <cassert>

Animation::Animation(const char* modelName, Vec3 pos) :
	m_modelHandle(-1),
	m_playTime(0.0f),
	m_attachIndex(0), m_totalTime(0),
	m_saveAnimNo(2),
	m_isAnimTime(false)
{
	m_modelHandle = MV1LoadModel(modelName);
	assert(m_modelHandle != -1);

	VECTOR DxPos = { pos.x, pos.y, pos.z };
	MV1SetPosition(m_modelHandle, DxPos);
}

Animation::Animation(const char* modelName):
	m_modelHandle(-1),
	m_playTime(0.0f),
	m_attachIndex(0), m_totalTime(0),
	m_saveAnimNo(2),
	m_isAnimTime(false)
{
	m_modelHandle = MV1LoadModel(modelName);
	assert(m_modelHandle != -1);
}

Animation::~Animation()
{
}

void Animation::Init()
{
	// ３Ｄモデルの０番目のアニメーションをアタッチする
	m_attachIndex = MV1AttachAnim(m_modelHandle, m_saveAnimNo, -1, FALSE);

	// アタッチしたアニメーションの総再生時間を取得する
	m_totalTime = static_cast<int>(MV1GetAttachAnimTotalTime(m_modelHandle, m_attachIndex));

	// 標準ライトを無効にする
	SetLightEnable(true);
}

void Animation::End()
{
	MV1DeleteModel(m_modelHandle);
}

void Animation::Update(float angleX,float angleY, float angleZ,float animTime)
{
	// 再生時間を進める
	m_playTime += animTime;

	// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
	if (m_playTime > m_totalTime)
	{
		m_playTime = 0.0f;
		m_isAnimTime = true;
	}
	else
	{
		m_isAnimTime = false;
	}

	// 再生時間をセットする
	MV1SetAttachAnimTime(m_modelHandle, m_attachIndex, m_playTime);
	// モデルの向きをセットする
	MV1SetRotationXYZ(m_modelHandle, VGet(angleX, angleY * DX_PI_F / 180.0f, angleZ));
}

void Animation::Draw()
{
	MV1DrawModel(m_modelHandle);
}

void Animation::SetAnimation(int animNo)
{
//	if (m_isAnimTime) return;

	// 前回とは違うアニメーションだったら
	if (m_saveAnimNo != animNo)
	{
		// アニメーション情報を削除
		MV1DetachAnim(m_modelHandle, m_attachIndex);
		// アニメーション再生時間を初期化
		m_playTime = 0.0f;
		// 新しいアニメーション情報
		MV1SetAttachAnimTime(m_modelHandle, animNo, m_playTime);
		// ３ＤモデルのanimNo番目のアニメーションをアタッチする
		m_attachIndex = MV1AttachAnim(m_modelHandle, animNo, -1, FALSE);
		// アタッチしたアニメーションの総再生時間を取得する
		m_totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_attachIndex);
		// アニメーション記録
		m_saveAnimNo = animNo;
	}
}

void Animation::ChangeAnimation(int animNo, bool isLoop)
{
	// アニメーション情報を削除
	MV1DetachAnim(m_modelHandle, m_attachIndex);
	// アニメーション再生時間を初期化
	m_playTime = 0.0f;
	// アニメーション記録
	m_saveAnimNo = animNo;
	// 新しいアニメーション情報
	MV1SetAttachAnimTime(m_modelHandle, m_saveAnimNo, m_playTime);
	// ３ＤモデルのanimNo番目のアニメーションをアタッチする
	m_attachIndex = MV1AttachAnim(m_modelHandle, m_saveAnimNo, -1, FALSE);
	// アタッチしたアニメーションの総再生時間を取得する
	m_totalTime = MV1GetAttachAnimTotalTime(m_modelHandle, m_attachIndex);

}

void Animation::SetPos(Vec3 pos)
{
	// 位置を取得する
	VECTOR DxPos = { pos.x, pos.y, pos.z };
	MV1SetPosition(m_modelHandle, DxPos);
}

void Animation::SetSize(VECTOR size)
{
	// ３Ｄモデルのスケールをx軸方向に２倍にする
	MV1SetScale(m_modelHandle, size);
}
