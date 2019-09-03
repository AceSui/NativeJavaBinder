#ifndef _MY_AIDL_CALLBACK
#define _MY_AIDL_CALLBACK
#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>

using namespace android;

enum{
    ON_VALUE_CHANGE= IBinder::FIRST_CALL_TRANSACTION
};

class IMyAidlTestCallback : public IInterface{
    public:
        DECLARE_META_INTERFACE(MyAidlTestCallback );

        virtual void onValueChange(int a)=0;
};

class BnMyAidlTestCallback : public  BnInterface<IMyAidlTestCallback>{
    public:
        virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0); 

};

#endif