package jp.tank.deepoperation;

import android.app.Activity;
import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;

public class Comport extends Activity implements View.OnClickListener {
    /** Called when the activity is first created. */
	EditText textEdit;
	private final static int FP = LinearLayout.LayoutParams.FILL_PARENT;
	private final static int WC = LinearLayout.LayoutParams.WRAP_CONTENT;
	
	public native int openPort();
	public native int closePort();
	public native int readPort();
	static {
		System.loadLibrary("comport");  
	}
	@Override
    public void onCreate(Bundle savedInstanceState) {
    	super.onCreate(savedInstanceState);

		// レイアウトの生成 (1)
		LinearLayout layout = new LinearLayout(this);
		layout.setBackgroundColor(Color.rgb(255, 255, 255));
		layout.setOrientation(LinearLayout.VERTICAL);
		setContentView(layout);

		textEdit =new EditText(this);
		textEdit.setTextSize(16.0f);
		textEdit.setTextColor(Color.rgb(0,0,0));
		// コンポーネントのサイズの指定 (3)
		textEdit.setLayoutParams(new LinearLayout.LayoutParams(FP, WC));

		layout.addView(textEdit);
		openPort();
		textEdit.append("open result:" + Integer.toString(openPort()));
		// ボタンの生成
		layout.addView(makeButton("読み取り","0"));
		layout.addView(makeButton("終了","1"));

	}
	
	@Override
	public void onDestroy() {
		closePort();
		super.onDestroy();
	}
	//ボタンの生成(1)
	private Button makeButton(String text, String tag) {
		Button button = new Button(this);
		button.setText(text);
		button.setTag(tag);
		button.setOnClickListener(this);	//ボタンクリックイベントの処理 (2)
		button.setLayoutParams(new LinearLayout.LayoutParams(WC,WC));
		return button;
	}
	
	@Override
	public void onClick(View arg0) {
		int tag = Integer.parseInt((String)arg0.getTag());
		if(tag == 0) {
			int num;
			num = readPort();
			textEdit.append("¥nread:" + Integer.toString(num));	
		} else {
			finish();
		}
	}
}