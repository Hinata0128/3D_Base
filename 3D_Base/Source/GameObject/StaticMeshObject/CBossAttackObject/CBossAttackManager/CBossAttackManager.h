#pragma once
#include <vector>
#include <memory>
// CBossAttackObject/CBossAttackObject.h は直接使用しないなら削除
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttack/CBossAttack.h"
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttack/CBossAttackSlash/CBossAttackSlash.h"
// ★追加: Jump Attackのヘッダをインクルード
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttack/CBossAttackJump/CBossAttackJump.h"
// ★追加: CBossAttackSlashChargeのヘッダーをインクルード
#include "..//CBossAttack/CBossAttackSlashCharge/CBossAttackSlashCharge.h"

#include "..//CBossAttack/CBossAttackSpecial/CBossAttackSpecial.h"

#include "..//CBossAttack/CBossAttackShout/CBossAttackShout.h"

class CPlayer; // 前方宣言

/***********************************************************************
*	ボスマネージャークラス.
**/

class CBossAttackManager
{
public:
	//列挙型を作成(BossList用)
	enum class BossAttackList
	{
		Slash,
		Jump, // ★追加: ジャンプ攻撃
		Charge, // ★追加: チャージ攻撃
		Special,
		Shout, // ★追加: 叫び攻撃

		max,
	};

public:
	CBossAttackManager();
	~CBossAttackManager();

	void Update();
	void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera);

	// ボスアタックの生成と設定を行う関数
	// Parameters:
	//    attackType: 攻撃の種類
	//    bossCurrentPos: 攻撃開始時のボスの現在のワールド座標
	// ★修正: playerTargetPosを引数に追加し、CPlayer*も追加
	void CreateBossAttack(BossAttackList attackType, const D3DXVECTOR3& bossCurrentPos, const D3DXVECTOR3& playerTargetPos, CPlayer* player);

	// 現在アクティブなボスアタックが存在するかどうかをチェックする
	bool HasActiveAttack() const { return m_pAttack != nullptr && m_pAttack->IsAttackActive(); }

	// 現在アクティブなボスアタックオブジェクトへのポインタを取得（読み取り専用）
	// CBossクラスが攻撃の状態や位置を取得するために使用
	CBossAttack* GetActiveAttack() const { return m_pAttack.get(); }

	// 現在のボスアタックを強制的に終了させる（必要であれば）
	void ResetCurrentAttack();

private:
	std::unique_ptr<CBossAttack> m_pAttack; // 現在アクティブなボスアタックを保持
};