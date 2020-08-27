using System.Collections.Generic;
using System.Data;
using folderCore.App_Code;

namespace folderCore.Models
{
    public class FormClass
    {
        public statusModels GetCheckNewModels(userData userData, string cuurip)
        {
            switch (string.IsNullOrWhiteSpace(userData.userid))
            {
                case true:
                    return new statusModels() { status = "nodata" };
            }
            DataTable checkRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", userData.userid.TrimEnd()));
            dbparamlist.Add(new dbparam("@status", "1"));
            checkRows = new database().checkSelectSql("mssql", "flytrainstring", "exec web.checkformnewid @newid,@status;", dbparamlist);
            switch (checkRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            switch (checkRows.Rows[0]["isused"].ToString().TrimEnd())
            {
                case "1":
                    return new statusModels() { status = "istrue" };
            }
            return new statusModels() { status = "islock" };
        }

        public loginModels GetLoginFormModels(userData userData, string cuurip, string userAgent)
        {
            switch (string.IsNullOrWhiteSpace(userData.userid))
            {
                case true:
                    return new loginModels() { status = "errorFormLogin" };
            }
            database database = new database();
            DataTable loginRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", userData.userid.TrimEnd()));
            dbparamlist.Add(new dbparam("@externip", cuurip));
            dbparamlist.Add(new dbparam("@status", "1"));
            loginRows = database.checkSelectSql("mssql", "flytrainstring", "exec web.checkformlogin @newid,@externip,@status;", dbparamlist);
            switch (loginRows.Rows.Count)
            {
                case 0:
                    return new loginModels() { status = "nodata" };
            }
            if (loginRows.Rows[0]["isused"].ToString().TrimEnd() == "1" && loginRows.Rows[0]["islogin"].ToString().TrimEnd() == "1")
            {
                datetime datetime = new datetime();
                information information = new information();
                string date = datetime.sqldate("mssql", "flytrainstring"), time = datetime.sqltime("mssql", "flytrainstring");
                dbparamlist.Add(new dbparam("@cpu", ""));
                dbparamlist.Add(new dbparam("@os", information.osystem(userAgent)));
                dbparamlist.Add(new dbparam("@internip", ""));
                dbparamlist.Add(new dbparam("@indate", date));
                dbparamlist.Add(new dbparam("@intime", time));
                switch (database.checkActiveSql("mssql", "flytrainstring", "update web.sitelog set cpu = @cpu,os = @os,internip = @internip,indate = @indate,intime = @intime where newid = @newid and externip = @externip and islogin = @status;", dbparamlist))
                {
                    case "istrue":
                        return new loginModels() { newid = loginRows.Rows[0]["newid"].ToString().TrimEnd(), name = loginRows.Rows[0]["username"].ToString().TrimEnd().Substring(0, 1), allname = loginRows.Rows[0]["username"].ToString().TrimEnd(), status = "istrue" };
                }
                return new loginModels() { status = "error" };
            }
            return new loginModels() { status = "islock" };
        }

        public statusModels GetBadgeFormModels(userData userData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", userData.userid.TrimEnd()));
            dbparamlist.Add(new dbparam("@status", "0"));
            return new statusModels() { status = new database().checkSelectSql("mssql", "flytrainstring", "exec web.countnoticeform @newid,@status;", dbparamlist).Rows[0]["counts"].ToString().TrimEnd() };
        }

        public permissModels GetPermissModels(userData userData, string cuurip)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", userData.userid.TrimEnd()));
            mainRows = new database().checkSelectSql("mssql", "flytrainstring", "exec web.searchallmissform @newid;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new permissModels() { insert = false, update = false, delete = false, export = false };
            }
            return new permissModels() { insert = mainRows.Rows[0]["isinsert"].ToString().TrimEnd() == "1", update = mainRows.Rows[0]["ismodify"].ToString().TrimEnd() == "1", delete = mainRows.Rows[0]["isdelete"].ToString().TrimEnd() == "1", export = mainRows.Rows[0]["isexport"].ToString().TrimEnd() == "1" };
        }

        public itemsModels GetRecordModels(userData userData, string cuurip)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", userData.userid.TrimEnd()));
            mainRows = new database().checkSelectSql("mssql", "flytrainstring", "exec web.searchrecordform @newid;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new itemsModels() { itemShow = false };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in mainRows.Rows)
            {
                items.Add(new Dictionary<string, object>() { { "link", dr["link"].ToString().TrimEnd() }, { "icon", dr["icon"].ToString().TrimEnd() }, { "value", dr["value"].ToString().TrimEnd() } });
            }
            return new itemsModels() { itemShow = true, items = items };
        }

        public itemsModels GetBadgeModels(userData userData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@status", "1"));
            dbparamlist.Add(new dbparam("@mooper", userData.userid.TrimEnd()));
            dbparamlist.Add(new dbparam("@newid", userData.userid.TrimEnd()));
            dbparamlist.Add(new dbparam("@changestatus", "0"));
            if (database.checkActiveSql("mssql", "flytrainstring", "update web.noticeform set status = @status,mooper = @mooper where newid = @newid and status = @changestatus;", dbparamlist) != "istrue")
            {
                return new itemsModels() { itemShow = false };
            }
            dbparamlist.Clear();
            DataTable mainRows = new DataTable();
            dbparamlist.Add(new dbparam("@newid", userData.userid.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flytrainstring", "exec web.searchnoticeform @newid;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new itemsModels() { itemShow = false };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in mainRows.Rows)
            {
                items.Add(new Dictionary<string, object>() { { "link", dr["link"].ToString().TrimEnd() }, { "name", dr["username"].ToString().TrimEnd().Substring(0, 1) }, { "value", dr["value"].ToString().TrimEnd() }, { "datetime", $"{dr["indate"].ToString().TrimEnd()} {dr["intime"].ToString().TrimEnd()}" } });
            }
            return new itemsModels() { itemShow = true, items = items };
        }
    }
}