#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A)
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B)
// B実装 HW16A005 有村 泉弥
// TODO: 砲台を青い壁に沿って上下に動かす。(C)
// C実装 HW16A005 有村 泉弥
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D)　HW16A075 小梶　希望
// TODO: スコアのサイズを大きくする。(E)　HW16A075 小梶　希望
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F)　HW16A075 小梶　希望
// TODO: PlayBGM()関数を使って、BGMを再生する。(G)
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H)


Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
int     score;          //!< スコア
float   vx_cloud = 30;
float   vy_cannon = 3;



// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-300, -150);//位置の変更（実装：HW16A076 小谷　将豊）
    targetRect = Rect(270, -140, 40, 40);
    bulletPos.x = -999;
    score = 0;
    // PlayBGM（実装：HW16A076 小谷　将豊）
    PlayBGM("bgm_maoudamashii_8bit07.mp3");

}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);
        //弾の発射音（実装：HW16A076 小谷　将豊）
        PlaySound("se_maoudamashii_system20.mp3");
    }

    // 弾の移動
    if (bulletPos.x > -999) {
        bulletPos.x += 150 * Time::deltaTime;

        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            score += 100;         // スコアの加算
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
            //ヒット音（実装：HW16A076 小谷　将豊）
            PlaySound("se_maoudamashii_explosion06.mp3");
        }
        else if (bulletPos.x > 300){
            bulletPos.x = -999;
        }
    }

    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);

    // 雲の描画
    DrawImage("cloud1.png", cloudPos);
    cloudPos.x += vx_cloud;
    if ( cloudPos.x > 320 ) {
        cloudPos.x = -540;
    }
    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }

    // 砲台の描画
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    DrawImage("cannon.png", cannonPos);
    cannonPos.y += vy_cannon;
    if ( cannonPos.y > -60 ) {
        cannonPos.y = -60;
        vy_cannon *= -1;
    }
    if ( cannonPos.y < -150 ) {
        cannonPos.y = -150;
        vy_cannon *= -1;
    }
        

    // ターゲットの描画
    FillRect(targetRect, Color::red);

    // スコアの描画
    SetFont("nicoca_v1.ttf", 55.0f);
    DrawText(FormatString("%05d", score), Vector2(-310, 180), Color::black);
    DrawText(FormatString("%05d", score), Vector2(-319, 189), Color::white);
}

