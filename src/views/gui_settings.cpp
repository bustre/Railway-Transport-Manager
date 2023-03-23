#include "gui_settings.h"

#include <QJsonArray>
#include <QJsonValue>

#include <QFile>
#include <QJsonDocument>

namespace rtm::gui
{

const unsigned int settings::max_recent_file_lenght = 5;
const QString settings::filename_config = "rtm.json";

settings::settings ()
    : app_lang (DEFAULT_EN), recent_file_open (QStringList ())
{
}

void
settings::set_lang (const langs_pack &lang)
{
  app_lang = lang;
}

void
settings::add_recent_file (const QString &file)
{
  recent_file_open.push_front (file);

  unsigned int counter = 1;
  // Skip the first I insert
  for (auto it = recent_file_open.begin () + 1; it < recent_file_open.end ();
       it++, counter++)
    {
      if ((*it) == file || counter >= max_recent_file_lenght)
        {
          it = recent_file_open.erase (it);
        }
    }
}

void
settings::clear_recent_files ()
{
  recent_file_open.clear ();
}

settings::langs_pack
settings::get_lang () const
{
  return app_lang;
}

const QStringList &
settings::get_recent_files () const
{
  return recent_file_open;
}

QJsonObject
settings::to_json_object () const
{
  QJsonObject j_obj;
  QJsonArray j_array_recent_files;

  j_obj.insert ("LANG", QJsonValue::fromVariant (app_lang));

  for (auto it = recent_file_open.begin (); it != recent_file_open.end ();
       it++)
    j_array_recent_files.append (QJsonValue::fromVariant (*it));

  j_obj.insert ("RECENT_FILES",
                QJsonValue::fromVariant (j_array_recent_files));

  return j_obj;
}

void
settings::from_json_object (const QJsonObject &j_obj)
{
  QJsonArray j_array_recent_files = j_obj.value ("RECENT_FILES").toArray ();

  switch (j_obj.value ("LANG").toVariant ().toInt ())
    {
    default:
    case DEFAULT_EN:
      set_lang (DEFAULT_EN);
      break;

    case ITALIAN:
      set_lang (ITALIAN);
      break;
    }

  for (auto it = j_array_recent_files.begin ();
       it != j_array_recent_files.end (); it++)
    add_recent_file ((*it).toString ());
}

bool
settings::write (const QString &config_path) const
{
  QFile file (config_path + "/" + filename_config);
  QJsonDocument doc;

  file.open (QFile::WriteOnly);
  if (!file.isOpen ())
    {
      file.close ();
      return false;
    }

  doc.setObject (to_json_object ());
  file.write (doc.toJson ());
  file.close ();
  return true;
}

bool
settings::read (const QString &config_path)
{
  QFile file (config_path + "/" + filename_config);
  QJsonDocument doc;

  file.open (QFile::ReadOnly);
  if (!file.isOpen ())
    {
      file.close ();
      return false;
    }

  doc = QJsonDocument::fromJson (file.readAll ());
  file.close ();

  if (doc.isEmpty ())
    return false;

  from_json_object (doc.object ());
  return true;
}

}