#ifndef GUI_SETTINGS_H
#define GUI_SETTINGS_H

#include <QJsonObject>
#include <QStringList>

namespace rtm::gui
{

class settings
{
public:
  enum langs_pack
  {
    DEFAULT_EN,
    ITALIAN
  };

  static const unsigned int max_recent_file_lenght;
  static const QString filename_config;

private:
  langs_pack app_lang;
  QStringList recent_file_open;

  QJsonObject to_json_object () const;
  void from_json_object (const QJsonObject &j_objs);

public:
  settings ();

  void set_lang (const langs_pack &lang);
  void add_recent_file (const QString &file);
  void clear_recent_files ();

  langs_pack get_lang () const;
  const QStringList &get_recent_files () const;

  bool write (const QString &config_path) const;
  bool read (const QString &config_path);
};
}

#endif