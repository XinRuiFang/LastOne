#include "HRocker.h"
#include "math.h"
USING_NS_CC;
HRocker* HRocker::createHRocker(const char *rockerImageName, const char *rockerBGImageName, const char* shooterImageName, const char* shooterBGImageName, Point position, float scale)
{
	HRocker* layer = HRocker::create();
	if (layer)
	{
		layer->rockerInit(rockerImageName, rockerBGImageName, shooterImageName, shooterBGImageName, position, scale);
		return layer;
	}
	CC_SAFE_DELETE(layer);
	return NULL;
}
void HRocker::rockerInit(const char *rockerImageName, const char *rockerBGImageName, const char* shooterImageName, const char* shooterBGImageName, Point position, float scale)
{
	direction = 1;
	sdirection = 1;
	isCanMove = false;
	isShooting = false;
	//添加摇杆背景图  
	Sprite* spRockerBG = Sprite::create(rockerBGImageName);
	spRockerBG->setVisible(false);
	spRockerBG->setPosition(position);
	spRockerBG->setScale(scale);
	addChild(spRockerBG, 0, tag_rockerBG);
	//添加摇杆上方那个可移动的图  
	Sprite* spRocker = Sprite::create(rockerImageName);
	spRocker->setVisible(false);
	spRocker->setPosition(position);
	spRocker->setScale(scale);
	addChild(spRocker, 1, tag_rocker);

	Sprite* spShooterBG = Sprite::create(shooterBGImageName);
	spShooterBG->setVisible(false);
	spShooterBG->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - position.x, position.y));
	spShooterBG->setScale(scale);
	addChild(spShooterBG, 0, tag_shooterBG);

	Sprite* spShooter = Sprite::create(shooterImageName);
	spShooter->setVisible(false);
	spShooter->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - position.x, position.y));
	spShooter->setScale(scale);
	addChild(spShooter, 1, tag_shooter);

	spRocker->setOpacity(180);
	spShooter->setOpacity(180);
	//摇杆背景图坐标  
	rockerBGPosition = position;
	shooterBGPosition = Vec2(Director::getInstance()->getVisibleSize().width - position.x, position.y);
	//摇杆背景图半径  
	rockerBGR = spRockerBG->getContentSize().width*0.5;
	shooterBGR = spRockerBG->getContentSize().width*0.5;

	listener = EventListenerTouchAllAtOnce::create();
	// 绑定监听事件
	listener->onTouchesBegan = CC_CALLBACK_2(HRocker::onTouchBegan, this);
	listener->onTouchesMoved = CC_CALLBACK_2(HRocker::onTouchMoved, this);
	listener->onTouchesEnded = CC_CALLBACK_2(HRocker::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	moveTouchID = -1;
	shootTouchID = -1;
}
//启动摇杆  
void HRocker::startRocker(bool _isStopOther)
{
	//精灵设置可见，设置监听  
	Sprite* rocker = (Sprite*)getChildByTag(tag_rocker);
	rocker->setVisible(true);
	Sprite* rockerBG = (Sprite*)getChildByTag(tag_rockerBG);
	rockerBG->setVisible(true);
	Sprite* shooter = (Sprite*)getChildByTag(tag_shooter);
	shooter->setVisible(true);
	Sprite* shooterBG = (Sprite*)getChildByTag(tag_shooterBG);
	shooterBG->setVisible(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}
//停止摇杆  
void HRocker::stopRocker()
{
	//精灵设置不可见，取消监听  
	Sprite* rocker = (Sprite*)getChildByTag(tag_rocker);
	rocker->setVisible(false);
	Sprite* rockerBG = (Sprite*)getChildByTag(tag_rockerBG);
	rockerBG->setVisible(false);
	Sprite* shooter = (Sprite*)getChildByTag(tag_shooter);
	shooter->setVisible(false);
	Sprite* shooterBG = (Sprite*)getChildByTag(tag_shooterBG);
	shooterBG->setVisible(false);
	Director::getInstance()->getEventDispatcher()->removeEventListener(listener);
}
//得到两坐标的角度值  
float HRocker::getRad(Point pos1, Point pos2)
{
	//得到两点的坐标x,y坐标值  
	float px1 = pos1.x;
	float py1 = pos1.y;
	float px2 = pos2.x;
	float py2 = pos2.y;
	//求出两边长度  
	float x = px2 - px1;
	float y = py1 - py2;
	//开方   与  几次方 公式  
	float xie = sqrt(pow(x, 2) + pow(y, 2));
	float cos = x / xie;
	//反余弦定理，知道两边长求角度：cos = 邻边/斜边  
	float rad = acos(cos);
	//当触屏Y坐标 <摇杆的Y坐标时，取反值  
	if (py1 > py2)
	{
		rad = -rad;
	}
	return rad;
}
//得到与角度对应的半径为r的圆上一坐标点  
Point HRocker::getAnglePosition(float r, float angle)
{
	return ccp(r*cos(angle), r*sin(angle));
}
void HRocker::onTouchBegan(const std::vector<Touch*> touches, Event *event)
{
	for (auto &touch :touches)
	{
		if (moveTouchID == -1)
		{
			Sprite* sp = (Sprite*)getChildByTag(tag_rocker);
			//得到触屏点坐标  
			Point point = touch->getLocation();
			//判断是否点击到sp这个精灵：boundingBox()精灵大小之内的所有坐标  
			if (sp->boundingBox().containsPoint(point))
			{
				isCanMove = true;
				moveTouchID = touch->getID();
			}
		}
		if (shootTouchID == -1)
		{
			Sprite* st = (Sprite*)getChildByTag(tag_shooter);

			Point point = touch->getLocation();

			if (st->boundingBox().containsPoint(point))
			{
				isShooting = true;
				shootTouchID = touch->getID();			
			}
		}
	}	
}
void HRocker::onTouchMoved(const std::vector<Touch*> touches, Event *event)
{
	for (auto &touch : touches)
	{
		if (touch->getID() == moveTouchID)
		{
			if (!isCanMove)
			{
				return;
			}
			Sprite* sp = (Sprite*)getChildByTag(tag_rocker);
			Point point = touch->getLocation();
			//判断两个圆心的距离是否大于摇杆背景的半径  
			if (sqrt(pow(point.x - rockerBGPosition.x, 2) + pow(point.y - rockerBGPosition.y, 2)) >= rockerBGR)
			{
				//得到触点与摇杆背景圆心形成的角度  
				float angle = getRad(rockerBGPosition, point);
				//确保小圆运动范围在背景圆内  
				sp->setPosition(ccpAdd(getAnglePosition(rockerBGR, angle), ccp(rockerBGPosition.x, rockerBGPosition.y)));
			}
			else {
				//触点在背景圆内则跟随触点运动  
				sp->setPosition(point);
			}
			// 获取方向
			auto basePosition = ((Sprite*)getChildByTag(tag_rockerBG))->getPosition();
			this->dx = sp->getPosition().x - basePosition.x;
			this->dy = sp->getPosition().y - basePosition.y;
			float r = sqrt(dx*dx + dy*dy);
			if (dx > 0 && dy > 0 && asin(fabs(dy / r)) < 45 * PI / 180)
			{
				direction = 2;
			}
			else if (dx > 0 && dy > 0 && asin(fabs(dy / r)) > 45 * PI / 180)
			{
				direction = 3;
			}
			else if (dx > 0 && dy < 0 && asin(fabs(dy / r)) < 45 * PI / 180)
			{
				direction = 2;
			}
			else if (dx > 0 && dy < 0 && asin(fabs(dy / r)) > 45 * PI / 180)
			{
				direction = 0;
			}
			else if (dx < 0 && dy > 0 && asin(fabs(dy / r)) < 45 * PI / 180)
			{
				direction = 1;
			}
			else if (dx < 0 && dy > 0 && asin(fabs(dy / r)) > 45 * PI / 180)
			{
				direction = 3;
			}
			else if (dx < 0 && dy < 0 && asin(fabs(dy / r)) < 45 * PI / 180)
			{
				direction = 1;
			}
			else if (dx < 0 && dy < 0 && asin(fabs(dy / r)) > 45 * PI / 180)
			{
				direction = 0;
			}
			angle = asin(fabs(dy / r)) * 180 / PI;
		}
		if (touch->getID() == shootTouchID)
		{
			Sprite* sh = (Sprite*)getChildByTag(tag_shooter);
			Point point = touch->getLocation();
			//判断两个圆心的距离是否大于摇杆背景的半径  
			if (sqrt(pow(point.x - shooterBGPosition.x, 2) + pow(point.y - shooterBGPosition.y, 2)) >= shooterBGR)
			{
				//得到触点与摇杆背景圆心形成的角度  
				float angle = getRad(shooterBGPosition, point);
				//确保小圆运动范围在背景圆内  
				sh->setPosition(ccpAdd(getAnglePosition(shooterBGR, angle), ccp(shooterBGPosition.x, shooterBGPosition.y)));
			}
			else {
				//触点在背景圆内则跟随触点运动  
				sh->setPosition(point);
			}
			// 获取方向
			auto basePosition = ((Sprite*)getChildByTag(tag_shooterBG))->getPosition();
			this->sdx = sh->getPosition().x - basePosition.x;
			this->sdy = sh->getPosition().y - basePosition.y;
			float r = sqrt(sdx*sdx + sdy*sdy);
			if (sdx > 0 && sdy > 0 && asin(fabs(sdy / r)) < 45 * PI / 180)
			{
				sdirection = 2;
			}
			else if (sdx > 0 && sdy > 0 && asin(fabs(sdy / r)) > 45 * PI / 180)
			{
				sdirection = 3;
			}
			else if (sdx > 0 && sdy < 0 && asin(fabs(sdy / r)) < 45 * PI / 180)
			{
				sdirection = 2;
			}
			else if (sdx > 0 && sdy < 0 && asin(fabs(sdy / r)) > 45 * PI / 180)
			{
				sdirection = 0;
			}
			else if (sdx < 0 && sdy > 0 && asin(fabs(sdy / r)) < 45 * PI / 180)
			{
				sdirection = 1;
			}
			else if (sdx < 0 && sdy > 0 && asin(fabs(sdy / r)) > 45 * PI / 180)
			{
				sdirection = 3;
			}
			else if (sdx < 0 && sdy < 0 && asin(fabs(sdy / r)) < 45 * PI / 180)
			{
				sdirection = 1;
			}
			else if (sdx < 0 && sdy < 0 && asin(fabs(sdy / r)) > 45 * PI / 180)
			{
				sdirection = 0;
			}
			sangle = asin(fabs(sdy / r)) * 180 / PI;
		}
	}
}
void HRocker::onTouchEnded(const std::vector<Touch*> touches, Event *event)
{
	for (auto &touch : touches)
	{
		if (touch->getID() == moveTouchID)
		{
			if (!isCanMove)
			{
				return;
			}
			Sprite* rocker = (Sprite*)getChildByTag(tag_rocker);
			Sprite* rockerBG = (Sprite*)getChildByTag(tag_rockerBG);
			rocker->stopAllActions();
			rocker->runAction(MoveTo::create(0.08, rockerBG->getPosition()));
			moveTouchID = -1;
			isCanMove = false;
			dx = 0;
			dy = 0;
			angle = 0;
		}
		if (touch->getID() == shootTouchID)
		{
			Sprite* shooter = (Sprite*)getChildByTag(tag_shooter);
			Sprite* shooterBG = (Sprite*)getChildByTag(tag_shooterBG);
			shooter->stopAllActions();
			shooter->runAction(MoveTo::create(0.08, shooterBG->getPosition()));
			shootTouchID = -1;
			isShooting = false;
			sdx = 0;
			sdy = 0;
			sangle = 0;
		}
	}
}