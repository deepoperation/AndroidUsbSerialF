#include <stdio.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <jni.h>

static int gFileD;

jint Java_jp_tank_deepoperation_Comport_openPort(JNIEnv* env, jobject thiz) {
    /* �V���A���|�[�g�̐ݒ���s���ϐ���錾 */
    struct termios oldtio, newtio;

    gFileD = open("/dev/ttyUSB0", O_RDWR);

    /* ���݂̐ݒ�� oldtio �ɕۑ� */
    tcgetattr(gFileD, &oldtio);
    /* ����g�p����ݒ� newtio �Ɍ��݂̐ݒ� oldtio ���R�s�[ */
    newtio = oldtio;

    /* ���o�̓X�s�[�h�̐ݒ� */
    /* �ȉ��̕��@1�܂��͕��@2�Őݒ�D�ǂ��炩�ł悢�̂ŕ��@2��L���ɂ��Ă��� */

    /* ���@1 */
    cfsetispeed(&newtio, B57600); /* ���̓X�s�[�h�ݒ� */
    cfsetospeed(&newtio, B57600); /* �o�̓X�s�[�h�ݒ� */

    /* ���@2 */
    //cfsetspeed(&newtio, B57600); /* ���o�̓X�s�[�h�ݒ� */

    /* 27�s��-42�s�ڂ܂ł̐ݒ��L���ɂ��� */
    tcflush(gFileD, TCIFLUSH);
    tcsetattr(gFileD, TCSANOW, &newtio); /* �ݒ��L���� */

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

