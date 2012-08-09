using System;
using System.Collections.Generic;
using System.Text;
using System.Windows.Forms;

namespace AC4Analysis
{
    public class Notes
    {
        static public Dictionary<string, string> Notelists=new Dictionary<string,string>();
        static public void load()
        {
            Ini ini = new Ini(Application.StartupPath + "\\Set.ini");
            string Num = ini.ReadValue("set", "NoteNum");
            if (string.IsNullOrEmpty(Num))
                return;
            int iNum = int.Parse(Num);
            for (int i = 0; i < iNum; i++)
            {
                string add = ini.ReadValue("Note"+i.ToString(), "Add");
                if (string.IsNullOrEmpty(add))
                    continue;
                string Note = ini.ReadValue("Note" + i.ToString(), "Note");
                if (string.IsNullOrEmpty(Note))
                    continue;
                Notelists.Add(add, Note);
            }
        }
        static public void Save()
        { 
            Ini ini = new Ini(Application.StartupPath + "\\Set.ini");
            ini.Writue("set", "NoteNum", Notelists.Keys.Count.ToString());
            int num=0;
            foreach (var key in Notelists.Keys)
            {
                ini.Writue("Note" + num.ToString(), "Add", key);
                ini.Writue("Note" + num.ToString(), "Note", Notelists[key]);
                num++;
            }
        }
        static public void Set(string key,string value)
        {
            if (!Notelists.ContainsKey(key))
                Notelists.Add(key, value);
            else
                Notelists[key] = value;
        }

        static public string Get(uint key)
        {
            string keytmp = string.Format("{0:X8}", key);
            if (!Notelists.ContainsKey(keytmp))
                return "";
            else
                return Notelists[keytmp];
        }
    }
}
