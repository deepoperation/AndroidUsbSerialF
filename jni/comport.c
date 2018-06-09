#include <stdio.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <jni.h>

static int gFileD;

jint Java_jp_tank_deepoperation_Comport_openPort(JNIEnv* env, jobject thiz) {
    /* シリアルポートの設定を行う変数を宣言 */
    struct termios oldtio, newtio;

    gFileD = open("/dev/ttyUSB0", O_RDWR);

    /* 現在の設定を oldtio に保存 */
    tcgetattr(gFileD, &oldtio);
    /* 今回使用する設定 newtio に現在の設定 oldtio をコピー */
    newtio = oldtio;

    /* 入出力スピードの設定 */
    /* 以下の方法1または方法2で設定．どちらかでよいので方法2を有効にしている */

    /* 方法1 */
    cfsetispeed(&newtio, B57600); /* 入力スピード設定 */
    cfsetospeed(&newtio, B57600); /* 出力スピード設定 */

    /* 方法2 */
    //cfsetspeed(&newtio, B57600); /* 入出力スピード設定 */

    /* 27行目-42行目までの設定を有効にする */
    tcflush(gFileD, TCIFLUSH);
    tcsetattr(gFileD, TCSANOW, &newtio); /* 設定を有効に */

	return gFileD;
}

jint Java_jp_tank_deepoperation_Comport_closePort(JNIEnv* env, jobject thiz) {
	int ret;
    ret = close(gFileD);
	return ret;
}

jint Java_jp_tank_deepoperation_Comport_readPort(JNIEnv* env, jobject thiz) {
	char buf[1024];
	int ret;
  //  ret = read(gFileD, (void *)buf, sizeof(buf));
	return gFileD;
}

