#ifndef _MY_AIDL_INTERFACE
#define _MY_AIDL_INTERFACE
#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <hao/sui/nativebinder/IMyAidlTestCallback.h>

using namespace android;

enum {
    SET_VALUE = IBinder::FIRST_CALL_TRANSACTION,
    GET_VALUE,
    SET_CALLBACK
};

class IMyAidlTestInterface : public IInterface
{
public:
    DECLARE_META_INTERFACE(MyAidlTestInterface);
    int mValue=-1;
    virtual void setValue(int a) = 0;
    virtual int getValue() = 0;
    virtual void setCallBack(const sp<IMyAidlTestCallback>& callback)=0;
};


class BnMyAidlTestInterface : public BnInterface<IMyAidlTestInterface>
{
public:
    virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0); 
};

#endif