#ifndef __MAP_H__
#define __MAP_H__
#define MAP_BLOCK_SIZE 64
#define MAP_BLOCK_X 25
#define MAP_BLOCK_Y 15
#define MAP_GRAPH_NUM 6
#define STAGE 6

struct Map
{
	int mapGraph[MAP_GRAPH_NUM];
};

//
//�֐��̃v���g�^�C�v�錾
//
int GetMapIndexX(float x);
int GetMapIndexY(float y);
int GetMapType(float x, float y, int stage);

void InitMap(Map& map);
void DrawMap(Map& map, int stage);

// �}�b�v�`�b�v�̎�ނ�ۑ�����f�[�^�z��.
extern const int g_mapchip_data[STAGE][MAP_BLOCK_Y][MAP_BLOCK_X];
extern const int manual_mapchip_data[MAP_BLOCK_Y][MAP_BLOCK_X];

#endif