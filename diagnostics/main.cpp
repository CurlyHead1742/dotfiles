#include <QApplication>
#include <QDir>
#include <QFont>
#include <QIcon>
#include <QPalette>
#include <QProcessEnvironment>
#include <QProxyStyle>
#include <QSettings>
#include <QStandardPaths>
#include <QStyle>
#include <QStyleFactory>
#include <QTextStream>

namespace {

QString color(const QPalette &palette, QPalette::ColorRole role)
{
    return palette.color(QPalette::Active, role).name(QColor::HexArgb);
}

void printEnvironment(QTextStream &out)
{
    const auto environment = QProcessEnvironment::systemEnvironment();
    for (const QString &name : {QStringLiteral("QT_QPA_PLATFORMTHEME"),
                                QStringLiteral("QT_STYLE_OVERRIDE"),
                                QStringLiteral("QT_QPA_PLATFORM"),
                                QStringLiteral("XDG_CURRENT_DESKTOP"),
                                QStringLiteral("XDG_CONFIG_HOME")}) {
        out << "env." << name << "=" << environment.value(name) << Qt::endl;
    }
}

void printKdeSettings(QTextStream &out)
{
    const QString configHome = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    QSettings kdeGlobals(QDir(configHome).filePath(QStringLiteral("kdeglobals")), QSettings::IniFormat);
    out << "kde.color_scheme=" << kdeGlobals.value(QStringLiteral("General/ColorScheme")).toString() << Qt::endl;
    out << "kde.icon_theme=" << kdeGlobals.value(QStringLiteral("Icons/Theme")).toString() << Qt::endl;
    out << "kde.widget_style=" << kdeGlobals.value(QStringLiteral("KDE/widgetStyle")).toString() << Qt::endl;
}

}

int main(int argc, char **argv)
{
    QApplication application(argc, argv);
    QTextStream out(stdout);
    const QPalette palette = application.palette();

    out << "qt.version=" << qVersion() << Qt::endl;
    out << "qt.platform=" << application.platformName() << Qt::endl;
    out << "qt.style=" << application.style()->objectName() << Qt::endl;
    out << "qt.style_class=" << application.style()->metaObject()->className() << Qt::endl;
    if (const auto *proxy = qobject_cast<const QProxyStyle *>(application.style())) {
        out << "qt.style_base=" << proxy->baseStyle()->objectName() << Qt::endl;
        out << "qt.style_base_class=" << proxy->baseStyle()->metaObject()->className() << Qt::endl;
    }
    out << "qt.style_keys=" << QStyleFactory::keys().join(",") << Qt::endl;
    out << "qt.hypr_style_available="
        << (QStyleFactory::create(QStringLiteral("hypr-style")) != nullptr ? "true" : "false")
        << Qt::endl;
    out << "qt.hyprqt6engine_style_available="
        << (QStyleFactory::create(QStringLiteral("hyprqt6engine")) != nullptr ? "true" : "false")
        << Qt::endl;
    out << "qt.application_font=" << application.font().toString() << Qt::endl;
    out << "qt.icon_theme=" << QIcon::themeName() << Qt::endl;
    out << "palette.window=" << color(palette, QPalette::Window) << Qt::endl;
    out << "palette.base=" << color(palette, QPalette::Base) << Qt::endl;
    out << "palette.button=" << color(palette, QPalette::Button) << Qt::endl;
    out << "palette.text=" << color(palette, QPalette::Text) << Qt::endl;
    out << "palette.highlight=" << color(palette, QPalette::Highlight) << Qt::endl;
    out << "palette.highlighted_text=" << color(palette, QPalette::HighlightedText) << Qt::endl;
    printEnvironment(out);
    printKdeSettings(out);
    return 0;
}
