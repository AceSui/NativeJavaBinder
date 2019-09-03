// IMyAidlTestInterface.aidl
package hao.sui.nativebinder;

import hao.sui.nativebinder.IMyAidlTestCallback;

// Declare any non-default types here with import statements

interface IMyAidlTestInterface {

    void setValue(int value);
    int getValue();
    void setCallBack(IMyAidlTestCallback callback);
}
