#pragma once
#include<cstdint>

const uint32_t kCollisionAttributePlayer         = 0b00001;
const uint32_t kCollisionAttributeEnemy          = 0b00010;
const uint32_t kCollisionAttributeEnemy2         = 0b00100;
const uint32_t kCollisionAttributeGoal           = 0b01001;
const uint32_t kCollisionAttributeInvertionSwich = 0b10110;

const uint32_t kCollisionMaskPlayer         = 0b11110;
const uint32_t kCollisionMaskEnemy          = 0b11101;
const uint32_t kCollisionMaskEnemy2         = 0b11011;
const uint32_t kCollisionMaskGoal           = 0b10110;
const uint32_t kCollisionMaskInvertionSwich = 0b00111;
