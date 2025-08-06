#pragma once

#include "GameObject/StaticMeshObject/CCharacter/CCharacter.h"
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttackManager/CBossAttackManager.h" // これがインクルードされていることを確認

// プレイヤーへの前方宣言
class CPlayer;

/***********************************************************************
*	ボスキャラクラス.
**/
class CBoss
    : public CCharacter
{
public:
    CBoss();
    ~CBoss() override;

    void Update() override;
    void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;
    void Init(); // 初期化メソッド

    void InitializeBossPosition(const D3DXVECTOR3& initialPos); // ボスの初期位置を設定するメソッド
    void RadioControl(); // 使用されていないようですが、もし今後使用するならコメントを削除
    void HandleGroundCollision(CStaticMeshObject* pGroundObject); // 地面との衝突処理

    void SetPlayer(CPlayer* player) { m_pPlayer = player; } // プレイヤーポインタの設定

protected:
    float m_TurnSpeed; // 旋回速度
    float m_MoveSpeed; // 移動速度

    enum enMoveState
    {
        stop,    // 停止
        walk,    // 歩行
        run,     // 走行
        attack,  // 攻撃 (今回はCBossAttackManagerで管理)
    };
    enMoveState m_MoveState; // 移動状態

    D3DXVECTOR3 m_vCurrentMoveVelocity; // 現在の移動速度ベクトル

    // クールタイム管理
    float deleta_time; // 現在は使われていないクールタイム用変数（残骸）
    float m_fSlashCoolTime; // 斬撃およびジャンプ攻撃のクールタイムカウンター
    const float SLASH_COOLTIME_DURATION = 2.0f; // 攻撃クールタイムの長さ（秒）

    std::unique_ptr<CBossAttackManager> m_bossAttackManager; // ボス攻撃を管理するマネージャー
    CPlayer* m_pPlayer; // プレイヤーへのポインタ（距離計算に使用）
};