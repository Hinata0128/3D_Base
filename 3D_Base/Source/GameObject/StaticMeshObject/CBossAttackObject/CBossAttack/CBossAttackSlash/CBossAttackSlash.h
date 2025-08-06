#pragma once
#include "GameObject/StaticMeshObject/CBossAttackObject/CBossAttack/CBossAttack.h"

class CBossAttackSlash
    : public CBossAttack
{
public:
    CBossAttackSlash();
    ~CBossAttackSlash() override;

    void Update() override;
    void Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera) override;

    //斬撃攻撃を開始するメソッド
    //Parameters:
    //  bossCurrentPos: 攻撃開始時のボスの現在のワールド座標
    void StartBossSlash(const D3DXVECTOR3& bossCurrentPos);

    //現在斬撃中であるかを返すメソッド
    bool IsSlashing() const { return m_bIsSlashing; }

    //斬撃動作中のボスのワールド行列を取得するメソッド
    //ボスの描画や位置更新にこれを使用します
    const D3DXMATRIX& GetAttackWorldMatrix() const { return m_mAttackWorld; }

    //CBossAttackの純粋仮想関数をオーバーライド
    bool IsAttackActive() const override { return m_bIsSlashing; }
    const D3DXVECTOR3& GetCalculatedAttackPosition() const override { return m_vCurrentAttackPos; }

private:
    bool        m_bIsSlashing;              //斬撃中かどうかを管理するフラグ
    float       m_fCurrentSlashTime;        //現在の斬撃経過時間 (秒)
    float       m_fSlashDuration;           //斬撃の持続時間 (秒)
    float       m_fZMoveDistance;           //Z軸方向への移動距離 (今回は-2.0f)
    D3DXVECTOR3 m_vInitialBossPos;          //斬撃開始時のボスの初期位置
    D3DXVECTOR3 m_vCurrentAttackPos;        //斬撃中のボスの現在位置 (攻撃によって計算される位置)
    D3DXMATRIX  m_mAttackWorld;             //斬撃動作中のボスのワールド行列
};