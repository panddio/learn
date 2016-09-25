/* ************************************************************************
 *       Filename:  main.c
 *    Description:
 *        Version:  1.0
 *        Created:  2015 �� 08�� 22��
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (),
 *        Company:
 * ************************************************************************/
#include "common.h"
#include "mplayer_ui.h"
#include "mplayer_control.h"
#include "mplayer_pthread.h"



int main(int argc, char *argv[])
{
	MPLAYER mplayer;

	//bzero(&mplayer, sizeof(&mplayer));
	gtk_thread_init();
	gtk_init(&argc, &argv);

	mplayer_init(&mplayer);
	window_init(&mplayer);

	mplayer_show_musiclist(&mplayer, &song);
	mplayer_process(&mplayer);
	create_pthread(&mplayer);

	gdk_threads_enter();// ������̻߳�������
	gtk_main();
	gdk_threads_leave();// �˳����̻߳�������

	return 0;
}

