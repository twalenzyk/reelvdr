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
 ***************************************************************************/

#ifndef P__FILECACHE_H
#define P__FILECACHE_H

#include <vector>
#include <string>

typedef unsigned int uint;

//----------cFileCache-----------------------

class cFileCache 
{
public:
    cFileCache(){}; 
    virtual ~cFileCache(){};
    bool Open(const std::string &cacheDir, uint maxCacheSize);
    bool PutInCache(const std::string &item, const std::vector<unsigned char> &buffer, std::string ending = "", bool keyless = false);
    bool FetchFromCache(const std::string &item, std::vector<unsigned char> &buffer, std::string ending = "", bool keyless = false) const;
    bool FetchFromCache(const std::string &item, std::string &file, std::string ending = "", bool keyless = false) const;
    void RemoveFromCache(std::string item, std::string ending = "", bool keyless = false);
    void ClearCache(); 
    bool InCache(const std::string &item, std::string ending = "", bool keyless = false) const;

protected:
    uint maxCacheSize_;
    std::string cacheDir_; 
    virtual std::string BuildKey(const std::string &item, std::string ending = "", bool keyless = false) const; 
    bool LimitCacheSize();
};

class cTempFileCache : public cFileCache
{
public: 
    bool PutInCache(const std:: string &item, int size, const std::vector<unsigned char> &buffer, std::string ending = "");
    bool FetchFromCache(const std::string &item, std::string &file, int filesize, std::string ending = "") const;
    void RemoveFromCache(std::string item, int filesize, std::string ending = "");
    bool InCache(const std::string &item, int filesize, std::string ending = "") const;
    std::string BuildKey(const std::string &item, int filesize, std::string ending = "") const; 

protected:
    /*override*/std::string BuildKey(const std::string &item, std::string ending = "", bool keyless = false) const; 
};

#endif //P__FILECACHE_H
