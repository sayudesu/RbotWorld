#include "EffekseerDrawer.h"
#include <DxLib.h>
#include <EffekseerForDXLib.h>
#include <cassert>

EffekseerDrawer::EffekseerDrawer():
	m_hEff(-1),
	m_hPlayEff(-1),
	m_hBg(-1),
	m_time(0)
{
}

EffekseerDrawer::~EffekseerDrawer()
{
}

int EffekseerDrawer::Init()
{
	// エフェクトリソースを読み込む。
	m_hEff = LoadEffekseerEffect("goal.efkefc",80.0f);
	assert(m_hEff != -1);
	m_hBg = LoadGraph("Background.png");
	assert(m_hBg != -1);
	return 0;
}

void EffekseerDrawer::End()
{
	// エフェクトリソースを削除する。(Effekseer終了時に破棄されるので削除しなくてもいい)
	DeleteEffekseerEffect(m_hEff);
}

void EffekseerDrawer::Update()
{
	// DXライブラリのカメラとEffekseerのカメラを同期する。
	Effekseer_Sync3DSetting();
	// Effekseerにより再生中のエフェクトを更新する。
	UpdateEffekseer3D();
}

void EffekseerDrawer::Draw(VECTOR pos)
{
	// 定期的にエフェクトを再生する
	if (m_time % 60 == 0)
	{
		// エフェクトを再生する。
		m_hPlayEff = PlayEffekseer3DEffect(m_hEff);
	}
	m_time++;

	// 再生中のエフェクトを移動する。
	SetPosPlayingEffekseer3DEffect(m_hPlayEff, pos.x, pos.y , pos.z);

	// Effekseerにより再生中のエフェクトを描画する。
	DrawEffekseer3D();
}
