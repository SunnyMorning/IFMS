#ifndef QPSTPRODUCT_H
#define QPSTPRODUCT_H

#include <QObject>

#include <qagentapp.h>

class QPSTProduct : public QObject
{
    Q_OBJECT
public:
    explicit QPSTProduct(QObject *parent = 0);

    void init_pstObjects();
signals:

public slots:

private:
    QAgentApp       *_agent;
};

#endif // QPSTPRODUCT_H
