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
	//�Ƿ�ɲ���ҡ��  
	bool isCanMove;
	bool isShooting;
	//����ҡ�ˣ�ҡ��ͼƬ��ҡ�˱���ͼƬ����ʼ����  
	static HRocker* createHRocker(const char* rockerImageName, const char* rockerBGImageName, const char* shooterImageName, const char* shooterBGImageName, Point position, float scale);
	//����ҡ��  
	void startRocker(bool _isStopOther);
	//ֹͣҡ��  
	void stopRocker();
private:
	EventListenerTouchAllAtOnce* listener;
	void rockerInit(const char* rockerImageName, const char* rockerBGImageName, const char* shooterImageName, const char* shooterBGImageName, Point position, float scale);
	//�õ��뾶Ϊr��Բ���˶���һ���Ƕ�Ӧ��Ӧ��x,y����  
	Point getAnglePosition(float r, float angle);
	//�õ�ҡ�����û�������ĽǶ�  
	float getRad(Point pos1, Point pos2);
	//ҡ�˱���������  
	Point rockerBGPosition;
	Point shooterBGPosition;
	//ҡ�˱����İ뾶  
	float rockerBGR;
	float shooterBGR;

	int moveTouchID;
	int shootTouchID;
	//�����¼�  
	virtual void onTouchBegan(const std::vector<Touch*> touches, Event* event);
	virtual void onTouchMoved(const std::vector<Touch*> touches, Event* event);
	virtual void onTouchEnded(const std::vector<Touch*> touches, Event* event);
	CREATE_FUNC(HRocker);
};

#endif  