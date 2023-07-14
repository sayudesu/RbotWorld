#include "DrawTitleModel.h"
#include "Model.h"

namespace
{
	// ファイル名
	const char* const kFileName = "Data/Model/Player/Robot.mv1";
	constexpr float kModelSpeed = 30.0f;
}

TitleDrawModeler::TitleDrawModeler():
	m_posY(-1000.0f),
	m_pModel(nullptr),
	m_isMoveSelect(false),
	m_isSceneChange(false)

{
	m_pModel = new Model(kFileName);
	m_pModel->SetAnimation(6, true, true);

	// モデルの状態初期設定
	m_pModel->SetPos(VGet(-1000.0f, 0.0f, 0.0f));
	m_pModel->SetRot(VGet(0.0f, -90 * DX_PI_F / 180.0f, 0.0f));

	// カメラの設定
	// near,far
	SetCameraNearFar(5.0f, 2800.0f);
	// カメラの視野角（60）を設定（ラジアン）
	SetupCamera_Perspective(60.0f * DX_PI_F / 180.0f);
	// カメラの位置、どこを見ているかを設定する
	SetCameraPositionAndTarget_UpVecY(
		VGet(0.0f,400.0f,-1300.0f),
		VGet(0.0f,200.0f, 0.0f)
		 );

}

TitleDrawModeler::~TitleDrawModeler()
{
	// メモリ解放
	delete m_pModel;
}

void TitleDrawModeler::Update()
{
	// モデルの更新処理
	m_pModel->Update();
	m_pModel->SetPos(VGet(m_posY, 0.0f, 0.0f));

	// -1000左
	// 0　　中
	// 1000右
	// 画面真ん中位まで移動する
	if(m_posY < 0.0f)m_posY += kModelSpeed;

	// 決定ボタンが押させてらより右に移動始める
	if (m_isMoveSelect)m_posY += kModelSpeed;
	// 画面右まで移動しかたどうか
	if (m_posY > 1000.0f)m_isSceneChange = true;
}

void TitleDrawModeler::Draw()
{
	// モデル描画
	m_pModel->Draw();
}
