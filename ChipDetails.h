#ifndef CHIPDETAILS_H
#define CHIPDETAILS_H
#include <QHash>
#include <QMetaType>

class ChipDetails
{
public:
    ChipDetails();
    ChipDetails(QString m, QList<QPair<QString, QString>> a);

    bool contains(QString) const;

    QString marking() const { return myMarking; }
    QList<QPair<QString, QString>> attributes() const { return myAttributes; }

private:
    QString myMarking;
    QList<QPair<QString, QString>> myAttributes;
};

Q_DECLARE_METATYPE(ChipDetails)

#endif // CHIPDETAILS_H
