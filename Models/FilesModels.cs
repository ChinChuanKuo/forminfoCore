using System.Collections.Generic;
using System.Data;
using folderCore.App_Code;

namespace folderCore.Models
{
    public class FilesClass
    {
        public string GetFileType(string extension)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@value", extension.Replace(".", "").ToLower()));
            dbparamlist.Add(new dbparam("@needed", "1"));
            mainRows = new database().checkSelectSql("mssql", "flytrainstring", "exec web.searchfiletype @value,@needed;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return "OTHER";
            }
            return mainRows.Rows[0]["flTitle"].ToString().TrimEnd();
        }

        public long GetFileCapacity(string filename)
        {
            return new System.IO.FileInfo(new database().connectionString("folderFiles") + filename).Length;
        }
    }
}