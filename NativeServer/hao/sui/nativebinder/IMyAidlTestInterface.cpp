#include <utils/Log.h> 

#include "IMyAidlTestInterface.h"

using namespace android;

class BpMyAidlTestInterface : public BpInterface<IMyAidlTestInterface>{
    public:
        BpMyAidlTestInterface(const sp<IBinder>& impl) : BpInterface<IMyAidlTestInterface>(impl){

        };

        void setValue(int a){
            Parcel data;
            data.writeInterfaceToken(BpMyAidlTestInterface::getInterfaceDescriptor());  
            data.writeInt32(a);
            Parcel reply; 
            remote()->transact(SET_VALUE, data, &reply);
            int32_t exception = reply.readExceptionCode();
            ALOGD("BpMyAidlTestInterface setValue a:%d\n", a);
        }

        int getValue(){
            Parcel data;
            data.writeInterfaceToken(BpMyAidlTestInterface::getInterfaceDescriptor());  
            Parcel reply; 
            remote()->transact(GET_VALUE, data, &reply);
            int32_t exception = reply.readExceptionCode();
            ALOGD("BpMyAidlTestInterface getValue");
            return reply.readInt32();
        }

        virtual void setCallBack(const sp<IMyAidlTestCallback>& callback){
             Parcel data;
            data.writeInterfaceToken(BpMyAidlTestInterface::getInterfaceDescriptor());  
            data.writeStrongBinder(callback->asBinder());
            Parcel reply; 
            remote()->transact(SET_CALLBACK, data, &reply);
            int32_t exception = reply.readExceptionCode();
            ALOGD("BpMyAidlTestInterface setCallBack");
        }
};

IMPLEMENT_META_INTERFACE(MyAidlTestInterface, "hao.sui.nativebinder.IMyAidlTestInterface");

status_t BnMyAidlTestInterface::onTransact(uint32_t code,const Parcel & data,Parcel * reply, uint32_t flags)
{
    switch(code)
    {
        case SET_VALUE:
        {
            CHECK_INTERFACE(IMyAidlTestInterface, data, reply);
            int32_t value=data.readInt32();
            setValue(value);
            ALOGD("BnMyAidlTestInterface SET_VALUE value:%d\n", value);
            reply->writeNoException();
            reply->writeInt32(0);
            return NO_ERROR;
        }
        case GET_VALUE:
        {
            CHECK_INTERFACE(IMyAidlTestInterface, data, reply);
           
            ALOGD("BnMyAidlTestInterface GET_VALUE");
            reply->writeNoException();
            reply->writeInt32( getValue());
            return NO_ERROR;
        }
         case SET_CALLBACK:
        {
            CHECK_INTERFACE(IMyAidlTestInterface, data, reply);
            sp<IMyAidlTestCallback> callback = interface_cast<IMyAidlTestCallback>(data.readStrongBinder());
            setCallBack(callback);
            ALOGD("BnMyAidlTestInterface SET_CALLBACK");
            reply->writeNoException();
            reply->writeInt32(0);
            return NO_ERROR;
        }
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
}

