#include <utils/Log.h> 

#include "IMyAidlTestCallback.h"

using namespace android;

class BpMyAidlTestCallback : public BpInterface<IMyAidlTestCallback>{
    public:
        BpMyAidlTestCallback(const sp<IBinder>& impl) : BpInterface<IMyAidlTestCallback>(impl){

        };

        virtual void onValueChange(int a){
            Parcel data;
            data.writeInterfaceToken(IMyAidlTestCallback::getInterfaceDescriptor());  
            data.writeInt32(a);
            Parcel reply; 
            remote()->transact(ON_VALUE_CHANGE, data, &reply);
            int32_t exception = reply.readExceptionCode();
            ALOGD("BpMyAidlTestCallback onValueChange a:%d\n", a);
        }
};
IMPLEMENT_META_INTERFACE(MyAidlTestCallback, "hao.sui.nativebinder.IMyAidlTestCallback");
status_t BnMyAidlTestCallback::onTransact(uint32_t code,const Parcel & data,Parcel * reply, uint32_t flags)
{
    switch(code)
    {
        case ON_VALUE_CHANGE:
        {
            CHECK_INTERFACE(IMyAidlTestCallback, data, reply);
            int32_t value=data.readInt32();
            onValueChange(value);
            ALOGD("BnMyAidlTestCallback ON_VALUE_CHANGE value:%d\n", value);
            reply->writeNoException();
            reply->writeInt32(0);
            return NO_ERROR;
        }
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

