#ifndef __VGAME_RAND_H__
#define __VGAME_RAND_H__

//#include "FrameWorkDefine.h"
class /*G_FRAME_WORK_DLL*/ GRand
{
public:
	//�����������
	void setRandSeed(double m);
	//��ȡ�����
	double getRand();
private:
	double getRand2();
	double g_seed;
	double g_last;
};



#endif // __VGAME_RAND_H__