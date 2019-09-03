package hao.sui.nativebinder;

import android.os.IBinder;
import android.os.RemoteException;
import android.support.v7.app.AppCompatActivity;
import android.os.ServiceManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private static final String TAG=MainActivity.class.getSimpleName();
    private static final String DESCRIPTOR="BINDERTEST";

    public IMyAidlTestInterface iMyAidlTestInterface;

    private IMyAidlTestCallback iMyAidlTestCallback=new IMyAidlTestCallback.Stub() {
        @Override
        public void onValueChange(final int value) throws RemoteException {
            runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    Toast.makeText(getApplicationContext(),"设置数据:"+value,Toast.LENGTH_SHORT);
                    Log.e(TAG, "callback: "+value );
                }
            });
        }
    };
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initData();
    }

    public void initData() {
        IBinder iBinder = ServiceManager.getService(DESCRIPTOR);
        if (iBinder == null) {
            Log.e(TAG, "biner get is null");
            return;
        }
        iMyAidlTestInterface=IMyAidlTestInterface.Stub.asInterface(iBinder);
        Log.e(TAG, "initData: "+(iMyAidlTestInterface==null));
        try {
            iMyAidlTestInterface.setCallBack(iMyAidlTestCallback);
        } catch (RemoteException e) {
            e.printStackTrace();
        }
        //iMyAidlTestCallback=IMyAidlTestCallback.Stub.asInterface(iBinder);
    }

    public void setData(View view){
        if(iMyAidlTestInterface!=null){
            try {
                int data=(int)System.currentTimeMillis();
                iMyAidlTestInterface.setValue(data);
                Log.e(TAG, "setData: "+data );
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
    }

    public void getData(View view){
        if(iMyAidlTestInterface!=null){
            try {
                int data=iMyAidlTestInterface.getValue();
                Log.e(TAG, "getData: "+data );
                Toast.makeText(getApplicationContext(),"获取数据:"+data,Toast.LENGTH_SHORT);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
    }

    public void testCallBack(View view){
        if(iMyAidlTestCallback!=null){
            try {
                Log.e(TAG, "testCallBack: " );
                iMyAidlTestCallback.onValueChange(3);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
    }
}
