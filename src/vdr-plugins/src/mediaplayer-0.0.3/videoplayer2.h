/***************************************************************************
 *   Copyright (C) 2005 by Reel Multimedia                                 *
 *                                                                         *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *********tr******************************************************************/

//videoplayer.h
 
#ifndef P__VIDEOPLAYER2_H
#define P__VIDEOPLAYER2_H

#include <string>
#include <vdr/plugin.h>
#include <vdr/status.h>

static const char *DESCRIPTION = trNOOP("Video Library");
const char *const MOUNT_SH = "/usr/sbin/mount.sh";


class cPluginVideoPlayer2 : public cPlugin
{
public:
    cPluginVideoPlayer2();
    virtual ~cPluginVideoPlayer2();

    /*override*/ const char *Version();
    /*override*/ const char *Description();
    /*override*/ bool Initialize();
    /*override*/ const char *MainMenuEntry(void) { return I18nTranslate("Movie & media player", "vdr-mediaplayer"); }
    /*override*/ cOsdObject *MainMenuAction(void);
    /*override*/ cMenuSetupPage *SetupMenu();
    /*override*/ bool SetupParse(const char *Name, const char *Value);
    /*override*/ bool HasSetupOptions(void) { return false; }
    /*override*/ bool Service(char const *id, void *data);  
    /*override*/ const char **SVDRPHelpPages(void);
    /*override*/ cString SVDRPCommand(const char *Command, const char *Option, int &ReplyCode);

private:

    // No assigning or copying
    cPluginVideoPlayer2(const cPluginVideoPlayer2 &plugin);
    cPluginVideoPlayer2 &operator=(const cPluginVideoPlayer2 &plugin);
    cOsdObject *PlayVideo();
    cOsdObject *CallXine();
};

#endif // P__MEDIAPLAYER_H

