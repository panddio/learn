/* ************************************************************************
 *       Filename:  mplayer_control.h
 *    Description:  
 *        Version:  1.0
 *        Created:  2015年08月24日 10时05分21秒
 *       Revision:  none
 *       Compiler:  gcc
 *         Author:  YOUR NAME (), 
 *        Company:  
 * ************************************************************************/

#ifndef __MPLAYER_CONTROL_H__
#define __MPLAYER_CONTROL_H__

extern void send_cmd(char cmd[],MPLAYER *pm);
extern void mplayer_show_musiclist(MPLAYER *pm, SONG *ps);
//extern void mplayer_show_musiclist(MPLAYER *pm);
extern void playing_song(MPLAYER *pm, int new_song);
extern void set_playing_song(MPLAYER *pm, int step);
extern void set_lable(GtkLabel *label, char *src);
extern void set_keyflag(KEY_STATUS status);
extern void set_songname(int song_num);
extern void set_lrc_lable(MPLAYER *pm, char *pbuf[]);
extern void clear_lrc_lable(MPLAYER *pm);

#endif


