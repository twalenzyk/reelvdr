#!/bin/sh
# $Id: check_paranoia.sh.in,v 1.10 2005/04/11 02:36:36 rocky Exp $
# Compare our cd-paranoia with an installed cdparanoia

if test "X$srcdir" = "X" ; then
  srcdir=`pwd`
fi

if test "X$top_builddir" = "X" ; then
  top_builddir=`pwd`/..
fi

if test "X$top_srcdir" = "X" ; then
  top_srcdir=`pwd`/..
fi

if test "/usr/bin/cmp" != no -a "#"X = X ; then
  $top_srcdir/src/cd-paranoia/cd-paranoia -d $srcdir/cdda.cue -v -r -- "1-"
  if test $? -ne 0 ; then
    exit 6
  fi
  dd bs=16 skip=17 if=cdda.raw of=cdda-1.raw
  dd bs=16 if=cdda.bin of=cdda-2.raw count=44377
  if /usr/bin/cmp cdda-1.raw cdda-2.raw ; then
    echo "** Raw cdda.bin extraction okay"
  else
    echo "** Raw cdda.bin extraction differ"
    exit 3
  fi
  mv cdda.raw cdda-good.raw
  $top_builddir/src/cd-paranoia/cd-paranoia -d $srcdir/cdda.cue -x 64 -v -r -- "1-"
  mv cdda.raw cdda-underrun.raw
  $top_builddir/src/cd-paranoia/cd-paranoia -d $srcdir/cdda.cue -r -- "1-"
  if test $? -ne 0 ; then
    exit 6
  fi
  if /usr/bin/cmp cdda-underrun.raw cdda-good.raw ; then
    echo "** Under-run correction okay"
  else
    echo "** Under-run correction problem"
    exit 3
  fi
  # Start out with small jitter
  $top_builddir/src/cd-paranoia/cd-paranoia -d $srcdir/cdda.cue -x 5 -v -r -- "1-"
  if test $? -ne 0 ; then
    exit 6
  fi
  mv cdda.raw cdda-jitter.raw
  if /usr/bin/cmp cdda-jitter.raw cdda-good.raw ; then
    echo "** Small jitter correction okay"
  else
    echo "** Small jitter correction problem"
    exit 3
  fi
  # A more massive set of failures: underrun + medium jitter
  $top_builddir/src/cd-paranoia/cd-paranoia -d $srcdir/cdda.cue -x 70 -v -r -- "1-"
  if test $? -ne 0 ; then
    exit 6
  fi
  mv cdda.raw cdda-jitter.raw
  if /usr/bin/cmp cdda-jitter.raw cdda-good.raw ; then
    echo "** under-run + jitter correction okay"
  else
    echo "** under-run + jitter correction problem"
    exit 3
  fi
  ### FIXME: large jitter is known to fail. Investigate.
  exit 0
else 
  echo "Don't see libcdio cd-paranoia program. Test skipped."
  exit 77
fi
fi
#;;; Local Variables: ***
#;;; mode:shell-script ***
#;;; eval: (sh-set-shell "bash") ***
#;;; End: ***

