#pragma once
#include "b2d.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <math.h>
#include <vector>
#include <assert.h>
#include <map>
#include <limits.h>
#include <string>
#include <fstream>
#include <time.h>

//#define _GAME_FRAMETEST
//#define _PHICS_FRAMETEST
//�����������
const float ELIPSE=0.0000001F;

//��������Ƶ��
const float KDT = 1.f/128.f;

//˥��ϵ��
const float DAMPING = 0.6f;


const unsigned int   WINDOWS_WIDTH=1024;
const unsigned int  WINDOWS_HEIGTH=800;

const unsigned int BACK_WIDTH = 800;
const unsigned int BACK_HEIGHT = 600;


//����back2�е�λ��
const float HOLE_LEFT = 45.f;
const float HOLE_TOP =40.f;

//�򶴼�ľ���
const float HOLE_HORIZ_WIDTH = 358.f;
const float HOLE_HORIZ_HEIGHT = 520.f;