#ifndef __TEST_BINDER_SERVICE_H__
#define __TEST_BINDER_SERVICE_H__

#include "hao/sui/nativebinder/IMyAidlTestInterface.h"


class TestBinderService : public BnMyAidlTestInterface
{
public:
    void setValue(int a);
    int getValue();
    void setCallBack(const sp<IMyAidlTestCallback>& callback);
    static void instance()
    {
        defaultServiceManager()->addService(String16("BINDERTEST"), new TestBinderService());
    };

protected:
    int mValue=-1;
    sp<IMyAidlTestCallback> mCallback;
};


#endif /* __TEST_BINDER_SERVICE_H__ */