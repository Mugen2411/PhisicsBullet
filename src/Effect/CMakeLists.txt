cmake_minimum_required(VERSION 3.11)
add_library(Effect STATIC
 CEffect.h CEffect.cpp CEffectParent.h CEffectParent.cpp CEffect_Bat_Swing.h CEffect_Bat_Swing.cpp
 CEffect_Bright.h CEffect_Bright.cpp 
 CEffect_BulletDelete.h CEffect_BulletDelete.cpp CEffect_CoinDelete.h CEffect_CoinDelete.cpp
 CEffect_DamageNumber.h CEffect_DamageNumber.cpp CEffect_EnemyDelete.h CEffect_EnemyDelete.cpp
 CEffect_MoneyNumber.h CEffect_MoneyNumber.cpp CEffect_Wind.h CEffect_Wind.cpp 
)