#include <iostream>

#include "views/main_window.h"
#include <QApplication>

#include "views/gui_settings.h"
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QStandardPaths>
#include <QTranslator>

void translate_error ();

int
main (int argc, char *argv[])
{
  int exit_status = 0;
  QApplication app (argc, argv);
  QTranslator translator;
  rtm::gui::settings app_settings;
  const QString &config_dir
      = QStandardPaths::writableLocation (QStandardPaths::ConfigLocation);

  // Try to load settings
  if (!app_settings.read (config_dir))
    std::cerr << "Error: Unable to open or read settings file at: \""
              << config_dir.toStdString () << "/"
              << rtm::gui::settings::filename_config.toStdString ()
              << "\". Default "
                 "settings will be loaded.\n";

  // Load lang
  switch (app_settings.get_lang ())
    {
    case rtm::gui::settings::ITALIAN:
      if (!translator.load (":languages/it_lang_pack"))
        translate_error ();
      break;

    case rtm::gui::settings::DEFAULT_EN:
      // Empty translator
      break;

    default:
      translate_error ();
      // Empty translator
      break;
    }

  if (!translator.isEmpty ())
    app.installTranslator (&translator);

  auto mv = new rtm::gui::main_window (app_settings);
  // app.setWindowIcon (QIcon (":assets/icons/rtm.svg"));

  mv->show ();
  exit_status = app.exec ();

  delete mv;

  if (!app_settings.write (config_dir))
    std::cerr << "Error: Unable write settings file at this path: \""
              << config_dir.toStdString () << "/"
              << rtm::gui::settings::filename_config.toStdString ()
              << "\". Settings will be lost.\n";

  return exit_status;
}

void
translate_error ()
{
  std::cerr << "Error: Unable to load language package. Default package will "
               "be set.\n";
}