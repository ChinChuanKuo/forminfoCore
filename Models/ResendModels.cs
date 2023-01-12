using System;
using System.Collections.Generic;
using System.Data;
using FORMINFOCore.App_Code;

namespace FORMINFOCore.Models
{
    public class ResendClass
    {
        public statusModels GetResendUserModels(otherData otherData, string cuurip)
        {
            switch (string.IsNullOrWhiteSpace(otherData.userid))
            {
                case true:
                    return new statusModels() { status = "nousers" };
            }
            switch (string.IsNullOrWhiteSpace(otherData.values))
            {
                case true:
                    return new statusModels() { status = "errorResend" };
            }
            DataTable userRows = new DataTable();
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", otherData.userid.TrimEnd()));
            dbparamlist.Add(new dbparam("@status", "1"));
            userRows = database.checkSelectSql("mssql", "epaperstring", "exec web.resendsiteber @newid,@status;", dbparamlist);
            switch (userRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            switch (userRows.Rows[0]["isused"].ToString().TrimEnd())
            {
                case "0":
                    return new statusModels() { status = "islock" };
            }
            datetime datetime = new datetime();
            string date = datetime.sqldate("mssql", "epaperstring"), time = datetime.sqltime("mssql", "epaperstring");
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@password", new sha256().encry256(otherData.values.TrimEnd())));
            dbparamlist.Add(new dbparam("@modate", date));
            dbparamlist.Add(new dbparam("@motime", time));
            dbparamlist.Add(new dbparam("@newid", otherData.userid.TrimEnd()));
            if (database.checkActiveSql("mssql", "epaperstring", "update web.siteber set password = @password,modate = @modate,motime = @motime where newid = @newid;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            return new statusModels() { status = "istrue" };
        }
    }
}