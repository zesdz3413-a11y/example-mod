#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <cocos2d.h>
#include "ui/CocosGUI.h" 

using namespace geode::prelude;
using namespace cocos2d::ui;

class $modify(MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // 1. An hinh nen mac dinh cua game
        if (auto background = this->getChildByID("main-menu-bg")) {
            background->setVisible(false);
        } else if (this->getChildrenCount() > 0) {
            auto firstChild = typeinfo_cast<CCSprite*>(this->getChildren()->objectAtIndex(0));
            if (firstChild) firstChild->setVisible(false);
        }

        // 2. Lay kich thuoc man hinh
        auto winSize = CCDirector::sharedDirector()->getWinSize();

        // 3. Tao Trinh phat Video
        auto videoPlayer = VideoPlayer::create();
        videoPlayer->setContentSize(winSize);
        videoPlayer->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        videoPlayer->setAnchorPoint(ccp(0.5f, 0.5f));

        // 4. Goi file video da khai bao trong mod.json
        videoPlayer->setFileName("menu_bg.mp4");

        // 5. Cau hinh phat va lap lai (Loop)
        videoPlayer->setKeepAspectRatioEnabled(true);
        videoPlayer->setFullScreenEnabled(false);
        
        videoPlayer->addEventListener([videoPlayer](CCObject* sender, VideoPlayer::EventType eventType) {
            if (eventType == VideoPlayer::EventType::COMPLETED) {
                videoPlayer->play(); 
            }
        });

        // 6. Dua video ra sau cung (Z-order = -1) va phat
        this->addChild(videoPlayer, -1);
        videoPlayer->play();

        return true;
    }
};
