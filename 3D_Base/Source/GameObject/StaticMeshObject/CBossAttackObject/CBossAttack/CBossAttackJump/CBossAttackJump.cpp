#include "CBossAttackJump.h"

#include <cmath>       //fmaxf を使うために必要



CBossAttackJump::CBossAttackJump()
	: m_bIsJumping(false)

	, m_fCurrentJumpTime(0.0f)
	, m_fJumpDuration(0.5f)
	, m_fJumpHeight(5.0f)
	, m_vInitialBossPos(0.0f, 0.0f, 0.0f)
	, m_vCurrentAttackPos(0.0f, 0.0f, 0.0f)
	, m_vJumpVelocity(0.0f, 0.0f, 0.0f)
	, m_JumpPower(0.5f)
	, m_Gravity(0.02f)
{

}



CBossAttackJump::~CBossAttackJump()
{

}



void CBossAttackJump::StartJump(const D3DXVECTOR3& bossCurrentPos)
{
	if (m_bIsJumping)
	{
		return;
	}

	m_bIsJumping = true;

	m_fCurrentJumpTime = 0.0f;//経過時間をリセット

	m_vInitialBossPos = bossCurrentPos; //ジャンプ開始時のボスのワールド位置を保存

	//ジャンプ開始時のY速度にジャンプ力を与える
	m_vJumpVelocity.y = m_JumpPower;



	//現在位置も初期位置で初期化
	m_vCurrentAttackPos = bossCurrentPos;


	//CStaticMeshObjectの基底クラスの位置も更新
	SetPosition(m_vInitialBossPos);

}



void CBossAttackJump::Update()
{
	//ジャンプ中でなければ何もしない
	if (!m_bIsJumping)
	{
		return;
	}

	float delta_time = 1.0f; //プレイヤーのUpdateと同じく、ここで固定値を使うか、実際のデルタタイムを渡すか検討

	//重力の影響を受ける
	m_vJumpVelocity.y -= m_Gravity * delta_time; //Y軸速度から重力を引く (Y軸上が正の場合)

	//現在のY座標を速度で更新
	m_vCurrentAttackPos.y += m_vJumpVelocity.y * delta_time;



	//地面 (Y=0.0f) に到達したかどうかの判定
	//プレイヤーの HandleGroundCollision に似た着地処理
	if (m_vCurrentAttackPos.y <= 0.0f)
	{
		m_vCurrentAttackPos.y = 0.0f; //地面にめり込まないように Y=0.0f にクランプ

		//Y速度が下向き（負）またはゼロであれば、速度をリセットして着地判定
		//厳密にはプレイヤーのように衝突判定はしないが、Y速度が負になったら着地とみなす
		if (m_vJumpVelocity.y <= 0.0f)
		{
			m_vJumpVelocity.y = 0.0f; //Y方向の速度をゼロにする

			//ジャンプ終了
			m_bIsJumping = false;
		}
	}





	//CStaticMeshObjectの内部位置も更新
	//ジャンプ開始時のX, Z座標は維持
	//Y座標のみ物理計算された値を使う
	SetPosition(m_vCurrentAttackPos); //m_vCurrentAttackPos は既にX, Zが初期位置

	CStaticMeshObject::Update(); //基底クラスのUpdateを呼び出し (ワールド行列の更新など)

}



void CBossAttackJump::Draw(D3DXMATRIX& View, D3DXMATRIX& Proj, LIGHT& Light, CAMERA& Camera)
{
	//ジャンプ中であれば、攻撃オブジェクト自身 (もしメッシュがあれば) を描画
	if (m_bIsJumping)
	{
		CStaticMeshObject::Draw(View, Proj, Light, Camera); //基底クラスの描画を呼び出し
	}
}