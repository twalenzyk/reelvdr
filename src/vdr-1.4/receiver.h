/*
 * receiver.h: The basic receiver interface
 *
 * See the main source file 'vdr.c' for copyright information and
 * how to reach the author.
 *
 * $Id: receiver.h 1.4 2006/05/27 09:04:22 kls Exp $
 */

#ifndef __RECEIVER_H
#define __RECEIVER_H

#include "device.h"

#define MAXRECEIVEPIDS  64 // the maximum number of PIDs per receiver

class cReceiver {
  friend class cDevice;
private:
  cDevice *device;
  int ca;
  int priority;
  int pids[MAXRECEIVEPIDS];
  int numPids;
  bool WantsPid(int Pid);
protected:
  void Detach(void);
  virtual void Activate(bool On) {}
               ///< This function is called just before the cReceiver gets attached to
               ///< (On == true) or detached from (On == false) a cDevice. It can be used
               ///< to do things like starting/stopping a thread.
               ///< It is guaranteed that Receive() will not be called before Activate(true).
  virtual void Receive(uchar *Data, int Length) = 0;
               ///< This function is called from the cDevice we are attached to, and
               ///< delivers one TS packet from the set of PIDs the cReceiver has requested.
               ///< The data packet must be accepted immediately, and the call must return
               ///< as soon as possible, without any unnecessary delay. Each TS packet
               ///< will be delivered only ONCE, so the cReceiver must make sure that
               ///< it will be able to buffer the data if necessary.
public:
  cReceiver(int Ca, int Priority, int Pid1, int Pid2 = 0, const int *Pids1 = NULL, const int *Pids2 = NULL, const int *Pids3 = NULL);
               ///< Creates a new receiver that requires conditional access Ca and has
               ///< the given Priority. Pid1 and Pid2 are single PIDs (typically the video and pcr PIDs), 
               ///< while Pids1...Pids3 are pointers to zero terminated lists of PIDs.
               ///< If any of these PIDs are 0, they will be silently ignored.
               ///< The total number of non-zero PIDs must not exceed MAXRECEIVEPIDS.
               ///< Priority may be any value in the range -99..99. Negative values indicate
               ///< that this cReceiver may be detached at any time (without blocking the
               ///< cDevice it is attached to).
  virtual ~cReceiver();
  };

#endif //__RECEIVER_H
