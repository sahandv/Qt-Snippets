#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QDirIterator>

bool copyFolder(QString from,QString to)
{
    // Copy folder from "from"
    // Paste it inside folder "to"
    // Folder and file names will be preserved
    // If parent folder has sub folders, the content of sub folders will be copied into the parent folder. ***

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
		QString to_file = to+QLatin1Char('/')+name;
        if(!file_info.isDir())
        {
            qDebug() << "attempting to copy " << from << " to " << to_file;
            bool copy_stat = QFile::copy(from, to_file);
            if(copy_stat)
                qDebug() << "success";
            else if(!copy_stat)
                qDebug() << "fail";
        }
	    // To enable iterative nested folder copy, enable this:
	/*else if(file_info.isDir())
        {
            qDebug() << from << "is dir";
            copyFolder(from,to); // If you want subfolders too, call this function iteratively like this
        }*/
    }
    return true;
}
