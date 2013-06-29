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
#include "constants.h"
#include "shrinkbandwidth.h"
#include <gnu_gama/local/gamadata.h>
#include <gnu_gama/gon2deg.h>

#include <QBrush>
#include <QFont>
#include <QMessageBox>
#include <QDebug>

typedef GNU_gama::local::LocalNetwork    LocalNetwork;

/* implementation of private structure ObsInfo - information on an Observation */
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
QString ObservationTableModel::ObsInfo::active()
{
    return observation->active() ? "1" : "0";
}
QVariant ObservationTableModel::ObsInfo::fromDh()
{
    if (double d = observation->from_dh()) return d;
    return QVariant();
}
QVariant ObservationTableModel::ObsInfo::toDh()
{
    double d1 = observation->to_dh();
    if (const Angle* angle = dynamic_cast<const Angle*>(observation))
    {
        double d2 = angle->fs_dh();
        if (d1 > 0 || d2 > 0) return QString("%1; %2").arg(d1).arg(d2);
    }
    else
    {
        if (d1 > 0) return QString("%1").arg(d1);
    }

    return QVariant();
}
QVariant ObservationTableModel::ObsInfo::Hdist()
{
    if (const H_Diff* hd = dynamic_cast<const H_Diff*>(observation))
    {
        if (double dist = hd->dist())
        {
           return QVariant(dist);
        }
    }

    return QVariant();
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
    columnCountMax = 0;

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

        obsMap.push_back(info);

        ObservationList::const_iterator i = (*ic)->observation_list.begin();
        ObservationList::const_iterator e = (*ic)->observation_list.end();
        int tmpCount = 0;
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
            else if (dynamic_cast<const GNU_gama::local::H_Diff*>(*i))
            {
                obs.observationNameIndex = indHdiff;
            }
            else if (dynamic_cast<const GNU_gama::local::S_Distance*>(*i))
            {
                obs.observationNameIndex = indSdist;
            }
            else if (dynamic_cast<const GNU_gama::local::Z_Angle*>(*i))
            {
                obs.observationNameIndex = indZangle;
                obs.angular = true;
            }
            else if (dynamic_cast<const GNU_gama::local::Xdiff*>(*i))
            {
                obs.observationNameIndex = indXdiff;
            }
            else if (dynamic_cast<const GNU_gama::local::Ydiff*>(*i))
            {
                obs.observationNameIndex = indYdiff;
            }
            else if (dynamic_cast<const GNU_gama::local::Zdiff*>(*i))
            {
                obs.observationNameIndex = indZdiff;
            }
            else if (dynamic_cast<const GNU_gama::local::X*>(*i))
            {
                obs.observationNameIndex = indX;
            }
            else if (dynamic_cast<const GNU_gama::local::Y*>(*i))
            {
                obs.observationNameIndex = indY;
            }
            else if (dynamic_cast<const GNU_gama::local::Z*>(*i))
            {
                obs.observationNameIndex = indZ;
            }

            obsMap.push_back(obs);
            tmpCount++;
        }

        if (tmpCount > columnCountMax) columnCountMax = tmpCount;

        ObsInfo tail;
        tail.rowType = clusterTail;
        obsMap.push_back(tail);
    }

    columnCountMax += indColumnCount;
}

// QAbstractTableModel functions

int ObservationTableModel::rowCount(const QModelIndex &parent) const
{
    return obsMap.size();
}

int ObservationTableModel::columnCount(const QModelIndex &parent) const
{
    return columnCountMax;
}

QVariant ObservationTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    int row = index.row();
    int col = index.column();
    ObsInfo info = obsMap[row];

    if (role == Qt::BackgroundRole)
    {        
        if (info.rowType == obsRow && col >= indColumnCount)
        {
            int r = info.clusterIndex;
            int b = col - indColumnCount;
            if (r+b > info.cluster->covariance_matrix.cols())      return GamaQ2::colorOutsideCovMat;
            if ( b  > info.cluster->covariance_matrix.bandWidth()) return GamaQ2::colorPassiveBackground;
        }

        if (info.rowType == clusterHeader) return GamaQ2::colorClusterHeader;
        if (info.observation && !info.observation->active()) return GamaQ2::colorPassiveBackground;

        return QVariant();
    }

    /*if (role == Qt::FontRole)
    {
        if (info.rowType == clusterHeader)
        {
            QFont  f;
            f.setBold(true);
            return f;
        }
    }*/

    if (role == Qt::TextAlignmentRole)
    {
        if (info.rowType == clusterHeader) return Qt::AlignCenter;

        switch (col)
        {
        case indVal:
        case indStdev:
            return (Qt::AlignVCenter + Qt::AlignRight);
        case indActive:
            return (Qt::AlignVCenter + Qt::AlignHCenter);
        }

        if (col >= indColumnCount) return (Qt::AlignVCenter + Qt::AlignRight);

        return QVariant();
    }

    if (!(role == Qt::DisplayRole || role == Qt::EditRole)) return QVariant();

    if (info.rowType == clusterHeader && col >= indColumnCount)
    {
        if (col == indColumnCount) return tr("Cov");

        int N = info.cluster->size();
        int K = col - indColumnCount;
        if (K < N) return QString("%1").arg(K);

        return QVariant();
    }

    if (info.rowType == obsRow)
    {
        switch(col)
        {
        case indFrom  : return info.from();
        case indTo    : return info.to();
        case indName  : return info.name();
        case indVal   : return info.value(lnet);
        case indStdev : return info.stdDev(lnet);
        case indActive: return info.active();
        case indFromDh: return info.fromDh();
        case indToDh  : return info.toDh();
        case indHdist : return info.Hdist();
        }

        if (col >= indColumnCount)
        {
            int i = info.clusterIndex;
            int j = i+col-indColumnCount;

            if (j <= info.cluster->covariance_matrix.cols())
            {
               double c = info.cluster->covariance_matrix(i, j);
               if (c == 0) return QVariant();

               if (lnet->degrees())
               {
                  ObsInfo inf2 = obsMap[row + col - indColumnCount];
                  if (info.angular) c *= 0.324;
                  if (inf2.angular) c *= 0.324;
               }

               return QVariant(c).toString();
               // return c; !!! results in doblespinbox editor for the item !!!
            }
            return QVariant();
        }
    }
    else if (info.rowType == clusterHeader && info.clusterName == "obs")
    {
        switch(col)
        {
        case indFrom  : return tr("From");
        case indTo    : return tr("To");
        case indName  : return tr("Obs");
        case indVal   : return lnet->gons() ? tr("Value [m|g]")   : tr("Value [m|d]");
        case indStdev : return lnet->gons() ? tr("Stdev [mm|cc]") : tr("Stdev [mm|ss]");
        case indActive: return tr("Active");
        case indFromDh: return tr("From dh");
        case indToDh  : return tr("To dh");
        case indHdist : return tr("Hdiff dist [km]");
        }
    }
    else if (info.rowType == clusterHeader && info.clusterName == "hdf")
    {
        switch(col)
        {
        case indFrom  : return tr("From");
        case indTo    : return tr("To");
        case indName  : return tr("Obs");
        case indVal   : return tr("Value [m]");
        case indStdev : return tr("Stdev [mm]");
        case indActive: return tr("Active");
        case indHdist : return tr("Hdiff dist [km]");
        }
    }
    else if (info.rowType == clusterHeader && info.clusterName == "vec")
    {
        switch(col)
        {
        case indFrom  : return tr("From");
        case indTo    : return tr("To");
        case indName  : return tr("Obs");
        case indVal   : return tr("Value [m]");
        case indStdev : return tr("Stdev [mm]");
        case indActive: return tr("Active");
        case indFromDh: return tr("From dh");
        case indToDh  : return tr("To dh");
        }
    }
    else if (info.rowType == clusterHeader && info.clusterName == "xyz")
    {
        switch(col)
        {
        case indFrom  : return tr("Id");
        case indName  : return tr("Obs");
        case indVal   : return tr("Value [m]");
        case indStdev : return tr("Stdev [mm]");
        case indActive: return tr("Active");
        }
    }

    return QVariant();
}

// implementation of header section

QVariant ObservationTableModel::headerData(int section, Qt::Orientation orientation,
           int role) const
{
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Vertical)
    {
        ObsInfo info = obsMap[section];
        switch (info.rowType)
        {
        case clusterHeader: return QVariant(info.clusterName);
        case obsRow       : return QVariant(QString("%1").arg(info.clusterIndex));
        case clusterTail  : return QVariant("");
        }
    }

   return QVariant();
}

// resizeable data

bool ObservationTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole) return false;

    int row = index.row();
    int col = index.column();
    ObsInfo info = obsMap[row];
    if (info.rowType != obsRow) return false;

    if (col == indVal)
    {
        bool ok;
        double val = value.toDouble(&ok);
        if (!ok)
        {
            ok = GNU_gama::deg2gon(value.toString().toStdString(), val);
            if (!ok)
            {
                warning(tr("Non-numeric format of value %1").arg(value.toString()));
                return false;
            }
        }

        Observation* obs = const_cast<Observation*>(info.observation);

        if (info.angular) val /= R2G;
        obs->set_value(val);

        return true;
    }

    if (col == indStdev)
    {
        bool ok;
        double std = value.toDouble(&ok);
        if (!ok)
        {
            warning(tr("Non-numeric format of StdDev %1").arg(value.toString()));
            return false;
        }

        bool angular = info.angular;
        if(angular && lnet->degrees()) std /= 0.324;

        int i = info.clusterIndex;
        Cluster* cluster = const_cast<Cluster*>(info.cluster);
        cluster->covariance_matrix(i,i) = std*std;

        return true;
    }

    if (col == indActive)
    {
        QString val = value.toString().simplified();
        if (val.isEmpty()) val = "0";

        Observation* obs = const_cast<Observation*>(info.observation);

        if      (val == "1") obs->set_active();
        else if (val == "0") obs->set_passive();
        else {
            emit warning(tr("Active values can be 1 or 0 only"));
            return false;
        }

        return true;
    }

    if (col >= indColumnCount)
    {
        int b = col - indColumnCount;
        if (b > info.cluster->covariance_matrix.bandWidth())
        {
            //emit warning("elements outside the bandwidth");
            Cluster *cluster = const_cast<Cluster*>(info.cluster);
            GNU_gama::CovMat<>& C = cluster->covariance_matrix;
            int N = C.rows();
            int B = C.bandWidth();
            GNU_gama::CovMat<> cm(N, b);
            cm.set_zero();
            for (int i=1; i<=N; i++)
                for (int j=i; j<=i+B; j++)
                {
                    cm(i,j) = C(i,j);
                }
            C = cm;
        }

        bool ok;
        double val = value.toDouble(&ok);
        if (!ok)
        {
            emit warning(tr("Bad numeric format of data"));
            return false;
        }

        ObsInfo inf2 = obsMap[row + b];

        if (lnet->degrees())
        {
            if (info.angular) val /= 0.324;
            if (inf2.angular) val /= 0.324;
        }

        int i = info.clusterIndex;
        int j = inf2.clusterIndex;
        Cluster* cluster = const_cast<Cluster*>(info.cluster);
        cluster->covariance_matrix(i,j) = val;

        if (val == 0) shrinkBandWidth(cluster->covariance_matrix);

        return true;
    }

    return false;
}

Qt::ItemFlags ObservationTableModel::ObservationTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) return Qt::NoItemFlags;

    const Qt::ItemFlags itemIsEditable = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
    int row = index.row();
    int col = index.column();
    ObsInfo info = obsMap[row];

    if (info.rowType == obsRow)
    {
        switch (col)
        {
        case indVal:
        case indStdev:
        case indActive:
            return itemIsEditable;
        }

        if (col >= indColumnCount)
        {
            int r = info.clusterIndex;
            int b = col - indColumnCount;
            if (r+b > info.cluster->covariance_matrix.cols()) return Qt::NoItemFlags;

            return itemIsEditable;
        }
    }

    if (info.rowType == clusterTail) return Qt::NoItemFlags;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
}

/*
bool ObservationTableModel::insertRows(int row, int count, const QModelIndex &parent)
{

}

bool ObservationTableModel::removeRows(int row, int count, const QModelIndex &parent)
{

}

bool ObservationTableModel::insertColumns(int column, int count, const QModelIndex &parent)
{

}

bool ObservationTableModel::removeColumns(int column, int count, const QModelIndex &parent)
{

}
*/
