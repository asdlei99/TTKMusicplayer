#include "musicqualitywidget.h"
#include "musicqualitywidgetuiobject.h"
#include "musicnumberutils.h"

#include <qmmp/soundcore.h>

MusicQualityWidget::MusicQualityWidget(QWidget *parent)
    : QLabel(parent)
{
    setToolTip(tr("Quality"));
    setFixedSize(48, 20);
    setStyleSheet(TTK::UI::LabelQuality + "margin-left:-48px;");
}

void MusicQualityWidget::updateQuality()
{
    QString style;
    switch(TTK::Number::bitrateToLevel(SoundCore::instance()->bitrate()))
    {
        case TTK::QueryQuality::Standard:
        {
            style = "margin-left:-48px;";
            break;
        }
        case TTK::QueryQuality::High:
        {
            style = "margin-left:-96px;";
            break;
        }
        case TTK::QueryQuality::Super:
        {
            style = "margin-left:-144px;";
            break;
        }
        case TTK::QueryQuality::Lossless:
        {
            style = "margin-left:-192px;";
            break;
        }
        default: break;
    }

    setStyleSheet(styleSheet() + style);
}
