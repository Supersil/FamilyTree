#ifndef TREESTRUCTURE_H
#define TREESTRUCTURE_H

#include <QObject>

//class contains pointers to all treeleafs
// stores their levels in tree and

class TreeStructure : public QObject
{
	Q_OBJECT
public:
	explicit TreeStructure(QObject *parent = 0);

signals:

public slots:
};

#endif // TREESTRUCTURE_H
