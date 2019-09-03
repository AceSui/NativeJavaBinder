
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>  
#include "hao/sui/nativebinder/IMyAidlTestCallback.h"  
#include "TestBinderService.h"

#define LOG_NDEBUG 0
#define LOG_TAG "TestBinderService"  
  
#include <utils/Log.h>  


void TestBinderService::setValue(int a)
{
    mValue=a;
    ALOGD("TestBinderService setValue a:%d", a);
    if (!mCallback.get()) {
         ALOGD("TestBinderService mCallback is null!");
       return;
    }
     mCallback->onValueChange(a);
}

int TestBinderService::getValue()
{
    ALOGD("TestBinderService getValue a:%d", mValue);
    return mValue;
}

void TestBinderService::setCallBack(const sp<IMyAidlTestCallback>& callback){
    mCallback=callback;
}

int main(int argc, char** argv)  
{  
    TestBinderService::instance();  

    ProcessState::self()->startThreadPool();  
    IPCThreadState::self()->joinThreadPool();  
  
    return 0;  
} 


































