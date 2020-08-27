using System.Collections.Generic;
using folderCore.App_Code;

namespace folderCore.Models
{
    public class IconClass
    {
        public statusModels GetSearchModels(userData userData, string cuurip)
        {
            /*database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            mainRows = database.checkSelectSql("mssql", "flytrainstring", "select value,icon from web.qaitemform where inoper = @inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sItemsModels() { status = "nodata" };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in mainRows.Rows)
            {
                items.Add(new Dictionary<string, object>() { { "icon", dr["icon"].ToString().TrimEnd() }, { "value", dr["value"].ToString().TrimEnd() } });
            }*/
            return new statusModels() { status = "istrue" };
        }

        public statusModels GetInsertModels(iIconData iIconData, string cuurip)
        {
            database database = new database();
            datetime datetime = new datetime();
            string date = datetime.sqldate("mssql", "flytrainstring"), time = datetime.sqltime("mssql", "flytrainstring");
            for (int i = 0; i < iIconData.items.Count; i++)
            {
                List<dbparam> dbparamlist = new List<dbparam>();
                dbparamlist.Add(new dbparam("@value", iIconData.items[i]["value"].ToString().TrimEnd()));
                switch (database.checkSelectSql("mssql", "flytrainstring", "select value,icon from web.iconform where value = @value;", dbparamlist).Rows.Count)
                {
                    case 0:
                        dbparamlist.Add(new dbparam("@icon", iIconData.items[i]["icon"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@indate", date));
                        dbparamlist.Add(new dbparam("@intime", time));
                        dbparamlist.Add(new dbparam("@inoper", iIconData.newid.TrimEnd()));
                        if (database.checkActiveSql("mssql", "flytrainstring", "insert into web.iconform (value,icon,indate,intime,inoper) values (@value,@icon,@indate,@intime,@inoper);", dbparamlist) != "istrue")
                        {
                            return new statusModels() { status = "error" };
                        }
                        break;
                }
            }
            for (int i = 0; i < iIconData.qaitems.Count; i++)
            {
                List<dbparam> dbparamlist = new List<dbparam>();
                dbparamlist.Add(new dbparam("@padding", "0"));
                dbparamlist.Add(new dbparam("@value", iIconData.qaitems[i]["value"].ToString().TrimEnd()));
                switch (database.checkSelectSql("mssql", "flytrainstring", "select value,icon from web.itemform where value = @value;", dbparamlist).Rows.Count)
                {
                    case 0:
                        dbparamlist.Add(new dbparam("@icon", iIconData.qaitems[i]["icon"].ToString().TrimEnd()));
                        dbparamlist.Add(new dbparam("@indate", date));
                        dbparamlist.Add(new dbparam("@intime", time));
                        dbparamlist.Add(new dbparam("@inoper", iIconData.newid.TrimEnd()));
                        if (database.checkActiveSql("mssql", "flytrainstring", "insert into web.itemform (padding,value,icon,indate,intime,inoper) values (@padding,@value,@icon,@indate,@intime,@inoper);", dbparamlist) != "istrue")
                        {
                            return new statusModels() { status = "error" };
                        }
                        break;
                }
            }
            return new statusModels() { status = "saveSuccess" };
        }
    }
}