package danxx.ndk;

import android.Manifest;
import android.content.pm.PackageManager;
import android.support.annotation.NonNull;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;

/**
 * http://blog.csdn.net/cloverjf/article/details/78654366
 */
public class MainActivity extends AppCompatActivity {

    public String name = "danxx";

    public String getName() {
        return name;
    }

    private int[] arrays = {20, 35, 2, 98, 4};


    protected String[] needPermissions = {
            Manifest.permission.WRITE_EXTERNAL_STORAGE,//存储卡写入权限
            Manifest.permission.READ_EXTERNAL_STORAGE,//存储卡读取权限
    };

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());

        TextView tvJni = findViewById(R.id.jni_text);
        tvJni.setText(getHelloJni());

        TextView tvJniH = findViewById(R.id.jni_h_text);
        tvJniH.setText(getStringH("NMNMNMNMMNNM"));

        TextView stringFJni = findViewById(R.id.jni_h_text01);
        stringFJni.setText(getStringNativeFormJava());

        TextView stringFJni2 = findViewById(R.id.jni_h_text02);
        stringFJni2.setText(getStringNativeFormJavaMethod());

        findViewById(R.id.btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                int permission_write = ContextCompat.checkSelfPermission(MainActivity.this,
                        Manifest.permission.WRITE_EXTERNAL_STORAGE);
                int permission_read = ContextCompat.checkSelfPermission(MainActivity.this,
                        Manifest.permission.READ_EXTERNAL_STORAGE);
                if (permission_write != PackageManager.PERMISSION_GRANTED
                        || permission_read != PackageManager.PERMISSION_GRANTED) {
                    Toast.makeText(MainActivity.this, "正在请求权限", Toast.LENGTH_SHORT).show();
                    //申请权限，特征码自定义为1，可在回调时进行相关判断
                    ActivityCompat.requestPermissions(MainActivity.this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.READ_EXTERNAL_STORAGE}, 1);
                } else {
                    doNdkReadFile();
                }
            }
        });

        getArray(arrays);

        for (int i : arrays) {
            Log.d("danxx", "i----> " + i);
        }

        try {
            jniExceptionTest();
        } catch (Exception e) {
            Log.d("exception", "exception msg------------> " + e.getMessage());
            e.printStackTrace();
        }

        if (1 != 1) {
            //java中抛出异常
            throw new IllegalArgumentException("参数异常了233");
        }

        Log.d("danxx", "Exception------------> ");

    }

    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        switch (requestCode) {
            case 1:
                if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    //权限已成功申请
                    doNdkReadFile();

                } else {
                    //用户拒绝授权
                    Toast.makeText(this, "无法获取SD卡读写权限", Toast.LENGTH_SHORT).show();
                }
                break;
            default:
                super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        }
    }

    private void doNdkReadFile() {
        // /data/data/com.xxx.ooo.filetestdemo/cache
        String cachePath = MainActivity.this.getCacheDir().getAbsolutePath();
        Log.e("DXX", "cachePath:" + cachePath);
        String filePath = cachePath + File.separator + "infile.txt";
        Log.e("DXX", "filePath:" + filePath);
        File file = new File(filePath);
        if (file.exists()) {
            Log.e("DXX", "file exists");
        } else {
            Log.e("DXX", "file is not exists");
        }
        ndkReadFile(filePath);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native String getHelloJni();

    public native String getStringH(String str);

    public native String getStringNativeFormJava();

    public native String getStringNativeFormJavaMethod();

    public native void getArray(int[] arrays);

    public native void jniExceptionTest();

    public native String ndkReadFile(String filePath);

}
