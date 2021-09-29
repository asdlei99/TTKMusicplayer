#include "musicstringutils.h"
#include "musicsettingmanager.h"

#include <QColor>
#include <QTextDocument>

QString MusicUtils::String::lrcPrefix()
{
    QString path = G_SETTING_PTR->value(MusicSettingManager::DownloadLrcDirPath).toString();
    if(path.isEmpty())
    {
        path = QDir(LRC_DIR_FULL).canonicalPath();
    }
    else
    {
        if(!QDir(path).exists())
        {
            QDir().mkpath(path);
        }
    }
    return path;
}

QString MusicUtils::String::musicPrefix()
{
    QString path = G_SETTING_PTR->value(MusicSettingManager::DownloadMusicDirPath).toString();
    if(path.isEmpty())
    {
        path = QDir(MUSIC_DIR_FULL).canonicalPath();
    }
    else
    {
        if(!QDir(path).exists())
        {
            QDir().mkpath(path);
        }
    }
    return path;
}

QString MusicUtils::String::stringPrefix(const QString &name)
{
    return stringPrefix(name, ".");
}

QString MusicUtils::String::stringPrefix(const QString &name, const QString &prefix)
{
    return name.left(name.indexOf(prefix));
}

QString MusicUtils::String::stringSuffix(const QString &name)
{
    return stringSuffix(name, ".");
}

QString MusicUtils::String::stringSuffix(const QString &name, const QString &suffix)
{
    return name.right(name.length() - name.lastIndexOf(suffix) - suffix.length());
}

QString MusicUtils::String::stringSplitToken(const QString &name)
{
    return stringSplitToken(name, ".", "?");
}

QString MusicUtils::String::stringSplitToken(const QString &name, const QString &prefix, const QString &suffix, bool revert)
{
    if(revert)
    {
        const QString &data = stringSuffix(name, prefix);
        return stringPrefix(data, suffix);
    }
    else
    {
        const QString &data = stringPrefix(name, prefix);
        return stringSuffix(data, suffix);
    }
}

QStringList MusicUtils::String::stringSplit(const QString &value, const QString &key)
{
    QStringList strings = value.split(QString(" %1 ").arg(key));
    if(strings.isEmpty() || strings.count() == 1)
    {
        strings = value.split(key);
    }
    return strings;
}

QString MusicUtils::String::removeStringToken(const QString &value, const QString &key)
{
    QString s = value;
    s.remove(key);
    if(s.contains(key))
    {
        s = removeStringToken(key);
    }
    return s;
}

QString MusicUtils::String::newlines()
{
#ifdef Q_OS_WIN
    return "\r\n";
#else
    return "\n";
#endif
}

bool MusicUtils::String::isChinese(const QChar &c)
{
#ifdef Q_CC_MSVC
    return '\xa9\x96' == c || (c.unicode() >= 0x4e00 && c.unicode() <= 0x9fa5);
#else
    return L'〇' == c || (c.unicode() >= 0x4e00 && c.unicode() <= 0x9fa5);
#endif
}

QString MusicUtils::String::artistName(const QString &value, const QString &key)
{
    const QStringList &s = stringSplit(value);
    if(s.count() >= 2)
    {
        const int index = value.indexOf(key);
        return value.left(index).trimmed();
    }
    return value;
}

QString MusicUtils::String::songName(const QString &value, const QString &key)
{
    const QStringList &s = stringSplit(value);
    if(s.count() >= 2)
    {
        const int index = value.indexOf(key) + 1;
        return value.right(value.length() - index).trimmed();
    }
    return value;
}

QString MusicUtils::String::convertHtmlToPlain(const QString &value)
{
    QTextDocument text;
    text.setHtml(value);
    return text.toPlainText();
}

QStringList MusicUtils::String::illegalCharacters()
{
    QStringList acs;
    acs << "\\" << "/" << "?"  << "*" << "\"" << ":" << "<" << ">" << "|";
    return acs;
}

bool MusicUtils::String::isCharacterValid(const QString &value)
{
    const QStringList acs(illegalCharacters());
    for(const QString &ac : qAsConst(acs))
    {
        if(value.contains(ac))
        {
            return true;
        }
    }

    return false;
}

QString MusicUtils::String::charactersReplaced(const QString &value)
{
    QString s(convertHtmlToPlain(value));
    const QStringList acs(illegalCharacters());

    for(const QString &ac : qAsConst(acs))
    {
        if(s.contains(ac))
        {
            s.replace(ac, " ");
        }
    }

    return s;
}
