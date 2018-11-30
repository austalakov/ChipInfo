#include "ChipDetails.h"

ChipDetails::ChipDetails(QString m, QList<QPair<QString, QString>> a)
    : myMarking(m), myAttributes(a)
{
}
ChipDetails::ChipDetails()
{
}

bool ChipDetails::contains(QString string) const
{
    foreach(auto pair, myAttributes)
    {
        if(pair.second.contains(string, Qt::CaseInsensitive))
            return true;
    }
    return false;
}
