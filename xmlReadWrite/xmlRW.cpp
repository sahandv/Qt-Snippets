#include <fstream>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <utility>

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QXmlSimpleReader>
#include <QXmlStreamReader>
#include <QtXml>
//add what header you need

bool readXML(QString path)
{
    qDebug() << "loading xml file...";
    if (path.isEmpty())
    {
        qDebug() << "oops! no xml path specified!";
        return false;
    }
    QFile file(path);
    if (file.open(QIODevice::ReadOnly))
    {
        QXmlStreamReader reader(file.readAll());
        file.close();
        while(!reader.atEnd())
        {
            reader.readNext();
            if (reader.isStartElement())
            {
                if (reader.name() == "parent")
                {
                    foreach(const QXmlStreamAttribute &attr, reader.attributes())
                    {
                        if (attr.name().toString() == QLatin1String("title"))
                        {
                            QString attribute_value = attr.value().toString();
                            qDebug() << "title : " <<   attribute_value;
                        }
                        if (attr.name().toString() == QLatin1String("something"))
                        {
                            QString attribute_value = attr.value().toString();
                            qDebug() << "something : " <<   attribute_value;
                        }
                    }

                    reader.readNextStartElement();
                    if (reader.name() == "childnest")
                    {
                        qDebug() << "- they have kids! ";
                        int attempts = 0;

                        Q_ASSERT(reader.isStartElement() && reader.name() == "childnest");
                        while(reader.readNextStartElement())
                        {
                            if(reader.name()== "child")
                            {
                                qDebug() << "-- found one child here Child " << reader.name();
                                foreach(const QXmlStreamAttribute &attr_sub, reader.attributes())
                                {
                                    if (attr_sub.name().toString() == QLatin1String("name"))
                                    {
                                        QString attribute_value = attr_sub.value().toString();
                                        qDebug() << "--- name : " << attribute_value;
                                    }
                                    if (attr_sub.name().toString() == QLatin1String("age"))
                                    {
                                        QString attribute_value = attr_sub.value().toString();
                                        qDebug() << "--- age : " << attribute_value;
                                    }
                                }
                                reader.skipCurrentElement();;
                                attempts++;
                            }
                            else
                            {
                                reader.skipCurrentElement();
                                qDebug() << "** not child " << reader.name();
                            }
//
                        }
                        qDebug() << "* that's all";
                    }

                }
            }
        }
    }
    else
    {
        qDebug() << "can not open database file!";
        return false;
    }
    qDebug() << "loading done";
    return true;
}