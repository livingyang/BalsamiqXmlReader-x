#include "HelloWorldScene.h"
#include "AppMacros.h"
USING_NS_CC;

//#include "BalsamiqFileManager.h"
#include "BalsamiqFileParser.h"
#include "BalsamiqControlData.h"
#include "BalsamiqBmmlData.h"
#include "CCBalsamiqLayer.h"

#include "curl/curl.h"
#include <locale>

#include <iconv.h>

using std::string;

int ahextoi( const char* hex_str)
{
    int r =0;
    if(hex_str)
        sscanf(hex_str,"%x",&r);
    return r;
}

wchar_t convertAnsiToUnicode(const char *ansiStr)
{
    return ahextoi(ansiStr);
}

std::string convertAnsiToUTF8(const char *ansiStr)
{
    {
        iconv_t conv = iconv_open("UTF-8", "UTF-16LE");
        
        wchar_t wc[] = {convertAnsiToUnicode(ansiStr), 0};
        
        char outPut[10] = {};
        char *in = (char *)wc;
        char *out = outPut;
        
        size_t inSize = sizeof(wc);
        size_t outSize = 10;
        
        iconv(conv, &in, &inSize, &out, &outSize);
        
        iconv_close(conv);
        
        return outPut;
    }
    
    char *origLocale = setlocale(LC_CTYPE, "UTF-8");
    
    wchar_t wc = convertAnsiToUnicode(ansiStr);
    
    char mb[4] = {};
    wctomb(mb, wc);
    
    setlocale(LC_CTYPE, origLocale);
    
    return std::string(mb);
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    
    {
        string filePath = CCFileUtils::sharedFileUtils()->fullPathFromRelativePath("alert-loading.bmml");
        
        BalsamiqBmmlData *data = BalsamiqFileParser::sharedBalsamiqFileParser()->parseBmmlFile(filePath);
        
        CCLOG("bmml data = %s", data->description().c_str());
        
        CCBalsamiqLayer *layer = CCBalsamiqLayerCreator::sharedBalsamiqLayerCreator()->createBalsamiqLayer(data);
        addChild(layer);
        
        titleLabel = CCBalsamiqLayerCreator::sharedBalsamiqLayerCreator()->getLabelFromLayer(layer, "Title");
        CCBalsamiqLayerCreator::sharedBalsamiqLayerCreator()->getButtonFromLayer(layer, "Cancle")->setTarget(this, menu_selector(HelloWorld::buttonCallback));
        
        for (int i = 0; i < data->getControlDataArray()->count(); ++i)
        {
            BalsamiqControlData *controlData = static_cast<BalsamiqControlData *>(data->getControlDataArray()->objectAtIndex(i));
            
            std::string text = controlData->getText();
            
            std::string str = "Please%20waiting";
            if (text == str)
            {
                int a;
                a = 1;
            }
        }
    }
    
    std::string a = "124";
    std::cout << a;
    a[0] = '2';
    
    std::cout << a;
    {
//        class Test
//        {
//            
//        public:
//            void
//        };
        
        std::string str = "test%20%u4E2D%u6587%20%21%21%21%3F%21@%20test";
        std::string eStr = curl_unescape(str.c_str(), str.length());
        std::cout << "src = " << eStr << std::endl;
        
//        std::string utf8Str(eStr.size(), '\0');
        
        bool isEnterUtf16 = false;
        std::stringstream ss;
        for (std::string::iterator iter = str.begin(); iter != str.end(); ++iter)
        {
            if (*iter == '%' && *(iter + 1) == 'u')
            {
                isEnterUtf16 = true;
                
                std::string encodeStr(iter + 2, iter + 6);
                iter += 5;
                
                ss << convertAnsiToUTF8(encodeStr.c_str());
            }
            else
            {
                ss << *iter;
            }
        }
        
        std::cout << "ss = " << ss.str() << std::endl;
        std::cout << "ss url = " << curl_unescape(ss.str().c_str(), ss.str().length()) << std::endl;
    }
    {
    }
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::buttonCallback(CCObject* pSender)
{
    titleLabel->setString("Changed!!");
}
