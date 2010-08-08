/* This file is part of Clementine.

   Clementine is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Clementine is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Clementine.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef AFCDEVICE_H
#define AFCDEVICE_H

#include "gpoddevice.h"

#include <QMutex>
#include <QWaitCondition>

#include <gpod/itdb.h>

class AfcTransfer;
class GPodLoader;

class AfcDevice : public GPodDevice {
  Q_OBJECT

public:
  Q_INVOKABLE AfcDevice(const QUrl& url, DeviceLister* lister,
                        const QString& unique_id, DeviceManager* manager,
                        int database_id, bool first_time);
  ~AfcDevice();

  void Init();

  static QStringList url_schemes() { return QStringList() << "afc"; }

  bool CopyToStorage(const QString &source, const QString &destination,
                     const Song &metadata, bool overwrite, bool remove_original);
  void FinishCopy();

  bool DeleteFromStorage(const Song &metadata);

protected:
  void FinaliseDatabase();

private slots:
  void CopyFinished();

private:
  void RemoveRecursive(const QString& path);

private:
  AfcTransfer* transfer_;

  QString local_path_;
};

#endif // AFCDEVICE_H
