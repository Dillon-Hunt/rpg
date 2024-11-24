#ifndef CONFIG_H
#define CONFIG_H

// Setup

#define WIDTH 800
#define HEIGHT 600
#define CELL_SIZE 24
#define SCALE 2.0f
#define BASE_FPS 120
#define FPS 120
#define SPEED 0.75f * BASE_FPS / FPS

// HUD

#define TEXT_SEPARATION 20
#define CURSOR_TEXTURE_PATH "resources/cursor.png"

// Pallet

#define PALLET_BORDER 4

// Chunks

#define CHUNK_SIZE 16

// Tiles

#define GRASS 0
#define DIRT 1
#define WATER 2
#define GARDEN 3

#define GRASS_DIRT 0
#define GRASS_WATER 1
#define GRASS_GARDEN 2
#define DIRT_WATER 3

#define GRASS_DIRT_TEXTURE_PATH "resources/grass-dirt.png"
#define GRASS_WATER_TEXTURE_PATH "resources/grass-water.png"
#define GRASS_GARDEN_TEXTURE_PATH "resources/grass-grass.png"

#define DIRT_WATER_TEXTURE_PATH "resources/dirt-water.png"

#define PLAYER_TEXTURE_PATH "resources/player.png"

// Game Objects

#define NONE -1
#define FENCE 0

// NPC

#define NPC_SPEED 0.5f * BASE_FPS / FPS
#define NPC_1_TEXTURE_PATH "resources/npc1.png"

// Enemy

#define NO_SPAWN_RADIUS 1
#define SPAWN_RADIUS 3
#define ENTITY_MAXIMUM_WANDER_RADIUS 20
#define ENEMY_IDLE_SPEED 0.4f
#define ENEMY_TARGET_SPEED 0.6f
#define ENEMY_DETECTION_RADIUS 4
#define ENEMY_ESCAPE_RADIUS 6

// Game Objects
#define TREE_1_TEXTURE_PATH "resources/tree1.png"
#define TREE_2_TEXTURE_PATH "resources/tree2.png"

#define FENCE_TEXTURE_PATH "resources/fence.png"

#define LARGE_SHADOW_TEXTURE_PATH "resources/tree-shadow.png"
#define SMALL_SHADOW_TEXTURE_PATH "resources/npc-shadow.png"

// Map

#define MAP_PATH "resources/map.txt"

// Debug

#define SHOW_COLLISION_SHAPE true
#define SHOW_ENEMY_TARGETING false

#endif // CONFIG_H
