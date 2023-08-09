#pragma once
#include <DxLib.h>
#include <memory>

class Model;
class GraphAnimation;

class Player
{
public:
	Player();
	virtual ~Player();

	void Init();
	void End();
	void Update();
	void Draw();

	void UpdateControl();// 操作処理

	// プレイヤーの位置を取得する
	VECTOR GetPos()     const { return m_pos;     }
	// プレイヤーの当たり判定用位置を取得する
	VECTOR GetPosColl() const { return m_posColl; }
	VECTOR GetSize()    const { return m_size;    }
	// スローの加減を渡す
	int GetSlowWorld() { return static_cast<int>(m_slowSpeed); }
	// 死んでいるかどうかを渡す
	bool GetIsDead() { return m_isDead; }

	// 地面に当たっているかどうかを取得する
	void FieldCheckHit(bool hit) { m_isFieldHit = hit; }

	// 地面のy座標を取得する
	void FieldPosY(float posY) { m_fieldPosY = posY; }

	// 前のフレーム
	// 当たり判定の半径
	float GetRadius()const;

	// 動けるかどうか
	void SetMoveing(bool isMove) { m_isMove = isMove; }

	// クリア位置に到着したかどうか
	void SetClear(bool isClear) { m_isClear = isClear; }
	// クリアした場合シーンを切り替える用
	bool GetClear() { return m_isClearSceneChange; }

private:
	void JumpEffect();
	// カメラの更新
	void UpdateCamera();
	// 動き全体の更新用関数
	void UpdateRun();
	// ジャンプする用関数
	void UpdateJump();
	void Goal();
	// 移動用関数
	void UpdateMove();
	// 角度管理用関数
	void UpdateRot();
	// 重力系管理用関数
	void UpdateGravity();
	// 地面に当たった場合の処理
	void UpdateHitField();
private:
	// ジャンプエフェクト画像
	int m_hJump;
	int m_jumpImgCount;
	int m_jumpImgX = 0;
	bool m_isJumpImg = false;
	bool m_isJumpPos = false;
	// ゴール用変数
	int m_hGoal;
	int m_goalX;
	int m_goalY;

	// メンバ関数ポインタ
	void (Player::*m_updateFunc)();

	// プレイヤーのモデル
	std::shared_ptr<Model> m_pModel;
	// 画像アニメーション用クラス
	GraphAnimation* m_pGraphAnimation;
	// 画像のスクリーン位置
	VECTOR m_screenPos;
	
	// ジャンプできるかどうか
	// (true : ジャンプできる, false : ジャンプできない)
	bool m_isJumping;

	// 再生しているアニメーション番号
	int m_animNo;

	// フレームカウント
	int m_frameCount;

	// プレイヤーの位置
	VECTOR m_pos;
	// 当たり判定用位置
	VECTOR m_posColl;
	VECTOR m_size;

	// ジャンプ処理用加速度
	float m_jumpAcc;

	// ジャンプをしているかどうか
	// (true ジャンプできない : false ジャンプできる )
	bool m_isFastJumping;
	bool m_isSecondJumping;

	// 地面に当たっているかどうか
	// (true : 当たっている, false : 当たっていない)
	bool m_isFieldHit = false;
	// 地面判定用のY座標取得用
	float m_fieldPosY;

	// プレイヤーの向いている方向
	float m_angle;

	// カメラの向いている方向
	float m_cameraAngle;

	// スロー時間
	float m_slowSpeed;

	// HP
	int m_hp;
	// 無敵時間
	int m_damageFrame;

	// 死んだかどうか(true : 死んでいる,false : 死んでいない)
	bool m_isDead;

	// 回転角度を更新
	float m_rad = 0.0f;

	// 動けるかどうか
	bool m_isMove;
	// クリアしたかどうか
	bool m_isClear;
	// クリアした時に一定フレーム経ったらtrueにする
	bool m_isClearSceneChange;
	// ゴール位置に移動した場合のカメラ位置を変更する
	float m_goalCameraPos;
	// シーン切り替えようカウント
	int m_count; 
};

