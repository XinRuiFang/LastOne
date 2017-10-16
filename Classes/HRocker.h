#ifndef __HROCKER_H__
#define __HROCKER_H__
#include "cocos2d.h"  
using namespace cocos2d;
#define PI 3.1415926
typedef enum{
	tag_rocker,
	tag_rockerBG,
	tag_shooter,
	tag_shooterBG
}tagForHRocker;
class HRocker : public Layer
{
public:
	float dx;
	float dy;
	int direction;
	float angle;
	float sdx;
	float sdy;
	int sdirection;
	float sangle;
	//是否可操作摇杆  
	bool isCanMove;
	bool isShooting;
	//创建摇杆，摇杆图片，摇杆背景图片，起始坐标  
	static HRocker* createHRocker(const char* rockerImageName, const char* rockerBGImageName, const char* shooterImageName, const char* shooterBGImageName, Point position, float scale);
	//启动摇杆  
	void startRocker(bool _isStopOther);
	//停止摇杆  
	void stopRocker();
private:
	EventListenerTouchAllAtOnce* listener;
	void rockerInit(const char* rockerImageName, const char* rockerBGImageName, const char* shooterImageName, const char* shooterBGImageName, Point position, float scale);
	//得到半径为r的圆周运动上一个角度应对应的x,y坐标  
	Point getAnglePosition(float r, float angle);
	//得到摇杆与用户触屏点的角度  
	float getRad(Point pos1, Point pos2);
	//摇杆背景的坐标  
	Point rockerBGPosition;
	Point shooterBGPosition;
	//摇杆背景的半径  
	float rockerBGR;
	float shooterBGR;

	int moveTouchID;
	int shootTouchID;
	//触屏事件  
	virtual void onTouchBegan(const std::vector<Touch*> touches, Event* event);
	virtual void onTouchMoved(const std::vector<Touch*> touches, Event* event);
	virtual void onTouchEnded(const std::vector<Touch*> touches, Event* event);
	CREATE_FUNC(HRocker);
};

#endif  