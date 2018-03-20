package danxx.ndk;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.IllegalFormatException;

/**
 * http://blog.csdn.net/cloverjf/article/details/78654366
 */
public class MainActivity extends AppCompatActivity {

  public String name = "danxx";

  public String getName(){
    return name;
  }

  private int[] arrays = {20,35,2,98,4};

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

    getArray(arrays);

    for(int i : arrays){
      Log.d("danxx","i----> "+i);
    }

    try {
      jniExceptionTest();
    }catch (Exception e){
      Log.d("exception","exception msg------------> "+e.getMessage());
      e.printStackTrace();
    }

    if(1 != 1){
      //java中抛出异常
      throw new IllegalArgumentException("参数异常了233");
    }

    Log.d("danxx","Exception------------> ");

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

}
