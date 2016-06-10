#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QDirIterator>

bool copyFolder(QString from,QString to)
{
    // copy folder from "from"
    // paste it inside folder "to"
    // folder and file names will be preserved
	// if parent folder has sub folders, the content of sub folders will be copied into the parent folder. ***

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
		// else copyFolder(from,to_file) // *** If you want subfolders to, call this function iteratively like this
    }
    return true;
}