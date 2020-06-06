/**
  Created by Weng Y on 2020/05/25.
  Copyright © 2020 Weng Y. Under GNU General Public License v2.0.
*/
#include "VtuberFrameWork.hpp"
#include"VtuberDelegate.hpp"

namespace {
    static bool isLoad;

    static bool isInit;

    static int initCount = 0;
}

void VtuberFrameWork::InitVtuber(int id)
{
    initCount++;
    if (initCount == 0) {
	isInit = false;
    }
    isLoad = VtuberDelegate::GetInstance()->LoadResource(id);
}

void VtuberFrameWork::ReanderVtuber(int targatid, char *data, int bufferWidth,
				    int bufferheight)
{
    if (isLoad) {
    
    if (initCount>0 && !isInit) {
	    isInit = true;
	    VtuberDelegate::GetInstance()->Initialize(targatid);
    }

    if (isInit)
	VtuberDelegate::GetInstance()->Reader(targatid, data, bufferWidth,bufferheight);

    }
}

void VtuberFrameWork::UinitVtuber(int id)
{   
    initCount--;
    if (id==1)
	    VtuberDelegate::GetInstance()->ReleaseResource(id);
    if (initCount == 0 && isInit) {
	    isInit = false;
	    VtuberDelegate::GetInstance()->Release();
    }
}

void VtuberFrameWork::UpData(int id,double _x, double _y, int width, int height,
			     double sc,double _delayTime, bool _randomMotion,bool _break,
			     bool _eyeBlink,const char *modelPath,bool _tarck,
			     const char *mode,bool _live2d)
{

	VtuberDelegate::GetInstance()->UpdataViewWindow(_x,_y,width, height,sc, id);
	VtuberDelegate::GetInstance()->updataModelSetting(
		_randomMotion, _delayTime, _break, _eyeBlink, _tarck,id );
	VtuberDelegate::GetInstance()->ChangeModel(modelPath,id);
	VtuberDelegate::GetInstance()->ChangeMode(mode, _live2d, id);
}

int VtuberFrameWork::GetWidth(int id)
{
	return VtuberDelegate::GetInstance()->getBufferWidth(id);
}

int VtuberFrameWork::GetHeight(int id)
{
	return VtuberDelegate::GetInstance()->getBufferHeight(id);
}







