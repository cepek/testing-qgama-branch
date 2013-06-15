/*
  GNU Gama Qt based GUI
  Copyright (C) 2013 Ales Cepek <cepek@gnu.org>

  This file is part of GNU Gama.

  GNU Gama is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  GNU Gama is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with GNU Gama.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "observationtablemodel.h"
#include <gnu_gama/local/gamadata.h>
#include <gnu_gama/gon2deg.h>

#include <QBrush>
#include <QDebug>

typedef GNU_gama::local::LocalNetwork    LocalNetwork;

/* implementation of private structure ObsInfo */
// -------------------------------------------------------------------------------
QStringList ObservationTableModel::ObsInfo::obsNames;

ObservationTableModel::ObsInfo::ObsInfo()
    : cluster(0), observation(0), angle(0), angular(false)
{
    if (obsNames.size() == 0)
    {
        obsNames << "dist." << "dir." << "angle" << "h dif"
                 << "x dif" << "y dif" << "z dif" << "x" << "y" << "z"
                 << "slope" << "zangle";
    }
}

QString  ObservationTableModel::ObsInfo::from()
{
    return QString::fromUtf8(observation->from().str().c_str());
}
QString  ObservationTableModel::ObsInfo::to()
{
    QString to = QString::fromUtf8(observation->to().str().c_str());

    if (angle)
    {
        to += "; ";
        to += QString::fromUtf8(angle->fs().str().c_str());
    }
    return to;
}
QString  ObservationTableModel::ObsInfo::name()
{
    return obsNames.at(observationNameIndex);
}
QVariant ObservationTableModel::ObsInfo::value(LocalNetwork* lnet)
{
    double val = observation->value();
    if (!angular)        return QString::number(val,'f',5);
    val *= R2G;
    if (lnet->degrees()) return GNU_gama::gon2deg(val, 0, 2).c_str();
    return  QString::number(val,'f',6);

}
QVariant ObservationTableModel::ObsInfo::stdDev(LocalNetwork* lnet)
{
    double stdev = observation->stdDev();
    if(angular && lnet->degrees()) stdev *= 0.324;
    return QString::number(stdev, 'g', 3);
}
// -------------------------------------------------------------------------------

ObservationTableModel::ObservationTableModel(GNU_gama::local::LocalNetwork *localNetwork,
                                             QObject *parent) :
    lnet(localNetwork),
    obsData(lnet->OD),
    QAbstractTableModel(parent)
{
    initObsMap();
}

void ObservationTableModel::initObsMap()
{
    obsMap.clear();
    ClusterList::const_iterator ic = obsData.clusters.begin();
    ClusterList::const_iterator ec = obsData.clusters.end();
    for ( ; ic!=ec; ++ic)
    {
        ObsInfo info;
        info.rowType = clusterHeader;
        info.cluster = *ic;

        if (dynamic_cast<const GNU_gama::local::StandPoint*>(*ic))
        {
             info.clusterName = "obs";
        }
        else if (dynamic_cast<const GNU_gama::local::Coordinates*>(*ic))
        {
             info.clusterName = "xyz";
        }
        else if (dynamic_cast<const GNU_gama::local::HeightDifferences*>(*ic))
        {
             info.clusterName = "hdf";
        }
        else  if (dynamic_cast<const GNU_gama::local::Vectors*>(*ic))
        {
             info.clusterName = "vec";
        }
        else
        {
            // ....
        }
        //obsMap.push_back(info);

        ObservationList::const_iterator i = (*ic)->observation_list.begin();
        ObservationList::const_iterator e = (*ic)->observation_list.end();
        int clusterIndex = 1;
        for ( ; i!=e; ++i)
        {
            ObsInfo obs      = info;
            info.clusterName = "";
            obs.observation  = *i;
            obs.clusterIndex = clusterIndex++;
            obs.rowType      = obsRow;

            if (dynamic_cast<const GNU_gama::local::Distance*>(*i))
            {
                obs.observationNameIndex = indDist;
            }
            else if (dynamic_cast<const GNU_gama::local::Direction*>(*i))
            {
                obs.observationNameIndex = indDir;
                obs.angular = true;
            }
            else if (const GNU_gama::local::Angle *a
                     = dynamic_cast<const GNU_gama::local::Angle*>(*i))
            {
                obs.observationNameIndex = indAngle;
                obs.angle = a;
                obs.angular = true;
            }

            obsMap.push_back(obs);
        }

        ObsInfo tail;
        tail.rowType = clusterTail;
        obsMap.push_back(tail);
    }
}

// QAbstractTableModel functions

int ObservationTableModel::rowCount(const QModelIndex &parent) const
{
    return obsMap.size();
}

int ObservationTableModel::columnCount(const QModelIndex &parent) const
{
    return indColumnCount;
}

QVariant ObservationTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    int r = index.row();
    int c = index.column();
    ObsInfo info = obsMap[r];

    if (role == Qt::BackgroundRole)
    {        
        if (info.observation && !info.observation->active())
        {
            QBrush passiveBackground(QColor(240,240,240));// Qt::lightGray is too dark
            return passiveBackground;
        }
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole)
    {
        switch (c)
        {
        case indVal:
        case indStdev:
            return Qt::AlignRight;
        }
        return QVariant();
    }

    if (!(role == Qt::DisplayRole || role == Qt::EditRole)) return QVariant();

    if (info.rowType == obsRow)
    {
        switch(c)
        {
        case indAdj  : return QVariant();
        case indFrom : return info.from();
        case indTo   : return info.to();
        case indName : return info.name();
        case indVal  : return info.value(lnet);
        case indStdev: return info.stdDev(lnet);
        }
    }

    return QVariant("");
}

// implementation of header section
QVariant ObservationTableModel::headerData(int section, Qt::Orientation orientation,
           int role) const
{
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section)
        {
        case indAdj  : return QString("i");
        case indFrom : return QString("From");
        case indTo   : return QString("To");
        case indVal  : return lnet->gons() ? QString("Value [m|g]")   : QString("Value [m|d]");
        case indStdev: return lnet->gons() ? QString("Stdev [mm|cc]") : QString("Stdev [mm|ss]");
        }
    }
    else if (orientation == Qt::Vertical)
    {
        ObsInfo info = obsMap[section];
        if (info.rowType == clusterTail) return QVariant("");

        QString vh = "%2 %1";
        return QVariant(vh.arg(info.clusterName).arg(info.clusterIndex));
    }

   return QVariant("");
}

