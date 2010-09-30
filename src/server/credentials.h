/***************************************************************************
**                                                                        **
**   Copyright (C) 2010 Nokia Corporation.                                **
**                                                                        **
**   Author: Simo Piiroinen <simo.piiroinen@nokia.com>                    **
**                                                                        **
**     This file is part of Timed                                         **
**                                                                        **
**     Timed is free software; you can redistribute it and/or modify      **
**     it under the terms of the GNU Lesser General Public License        **
**     version 2.1 as published by the Free Software Foundation.          **
**                                                                        **
**     Timed is distributed in the hope that it will be useful, but       **
**     WITHOUT ANY WARRANTY;  without even the implied warranty  of       **
**     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.               **
**     See the GNU Lesser General Public License  for more details.       **
**                                                                        **
**   You should have received a copy of the GNU  Lesser General Public    **
**   License along with Timed. If not, see http://www.gnu.org/licenses/   **
**                                                                        **
***************************************************************************/

#ifndef CREDENTIALS_H
#define CREDENTIALS_H

# ifndef __cplusplus
#  error This is a C++ only header
# endif

#include <string>
#include <set>
using namespace std ;

#include <sys/types.h>
#include <sys/creds.h>
#include <QDBusMessage>
#include <QDBusConnection>

#include <iodata/iodata>

uint32_t get_name_owner_from_dbus_sync(const QDBusConnection &bus, const QString &name) ;

struct credentials_t
{
  string uid, gid ;
  set<string> tokens ;

  // TODO: make nobody/nogroup run-time option: /etc/timed.rc
  credentials_t() : uid("nobody"), gid("nogroup") { }

  bool apply() const ; // set the credentials for the current process
  bool apply_and_compare() ; // set the credentials and check if they are really set

  static credentials_t from_current_process() ; // get the credentials of the current process
  static credentials_t from_dbus_connection(const QDBusMessage &msg) ; // get from dbus client

  iodata::record *save() const ;
  void load(const iodata::record *r) ;
} ;

#endif // CREDENTIALS_H
