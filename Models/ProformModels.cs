using System.Collections.Generic;
using System.Data;
using System.Threading;
using forminfoCore.App_Code;

namespace forminfoCore.Models
{
    public class ProformClass
    {
        public sOptonModels GetPollingModels(otherData otherData, string cuurip)
        {
            bool isbreak = true;
            database database = new database();
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            while (isbreak)
            {
                Thread.Sleep(5000);
                List<dbparam> dbparamlist = new List<dbparam>();
                dbparamlist.Add(new dbparam("@inoper", otherData.userid.TrimEnd()));
                int itemCount = int.Parse(database.checkSelectSql("mssql", "flyformstring", "exec web.countclientform @inoper;", dbparamlist).Rows[0]["itemCount"].ToString().TrimEnd()), values = int.Parse(otherData.values.TrimEnd());
                if (itemCount > values)
                {
                    dbparamlist.Add(new dbparam("@length", itemCount - values));
                    foreach (DataRow dr in new database().checkSelectSql("mssql", "flyformstring", "exec web.searchclienting @length,@inoper;", dbparamlist).Rows)
                    {
                        items.Add(new Dictionary<string, object>() { { "id", dr["formId"].ToString().TrimEnd() }, { "tile", dr["tile"].ToString().TrimEnd() }, { "datetime", dr["indate"].ToString().TrimEnd() }, { "showOther", false } });
                    }
                    isbreak = false;
                }
            }
            return new sOptonModels() { items = items };
        }
        public itemModels GetSearchModels(userData userData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@inoper", userData.userid.TrimEnd()));
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyformstring", "exec web.countclientform @inoper;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd());
            DataTable mainRows = new DataTable();
            mainRows = database.checkSelectSql("mssql", "flyformstring", "exec web.searchclientform @inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new itemModels() { status = "nodata" };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in mainRows.Rows)
            {
                items.Add(new Dictionary<string, object>() { { "id", dr["formId"].ToString().TrimEnd() }, { "tile", dr["tile"].ToString().TrimEnd() }, { "datetime", dr["indate"].ToString().TrimEnd() }, { "showOther", false } });
            }
            return new itemModels() { itemCount = itemCount, items = items, status = "istrue" };
        }
    }
}