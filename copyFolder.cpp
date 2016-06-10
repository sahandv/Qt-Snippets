#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>

bool copyFolder(QString from,QString to)
{
    // copy folder from "from"
    // paste it inside folder "to"
    // folder and file names will be preserved

    QDir from_dir(from);
    QString folder_name = from_dir.dirName();
    to = to+QLatin1Char('/')+folder_name;
    if(!from_dir.mkpath(to))
        return false;

    QDirIterator directory_it(from, QDirIterator::Subdirectories);
    while (directory_it.hasNext())
    {
        QString from = directory_it.next();
        QString name = directory_it.fileName();
        QFileInfo file_info = directory_it.fileInfo();
        if(!file_info.isDir())
        {
            QString to_file = to+QLatin1Char('/')+name;
            qDebug() << "attempting to copy " << from << " to " << to_file;
            bool copy_stat = QFile::copy(from, to_file);
            if(copy_stat)
                qDebug() << "success";
            else if(!copy_stat)
                qDebug() << "fail";
        }
    }
    return true;
}