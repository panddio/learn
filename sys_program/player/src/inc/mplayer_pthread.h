/* ************************************************************************
 *       Filename:  mplayer_process.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月23日 18时05分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/
#ifndef __MPLAYER_PTHREAD_H__
#define __MPLAYER_PTHREAD_H__

extern SONG song;

extern void mplayer_init(MPLAYER *pm);
extern void gtk_thread_init(void);
extern void get_song_msg(MPLAYER *pm);
extern int  mplayer_process(MPLAYER *pm);
extern void create_pthread(MPLAYER *pm);
#endif