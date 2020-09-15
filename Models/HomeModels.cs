using System.Collections.Generic;
using System.Data;
using System.Threading;
using forminfoCore.App_Code;
using System.Text.Json;
using System;

namespace forminfoCore.Models
{
    public class HomeClass
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
                int itemCount = int.Parse(database.checkSelectSql("mssql", "flyformstring", "exec web.countmainform;", dbparamlist).Rows[0]["itemCount"].ToString().TrimEnd()), values = int.Parse(otherData.values.TrimEnd());
                if (itemCount > values)
                {
                    dbparamlist.Clear();
                    dbparamlist.Add(new dbparam("@length", itemCount - values));
                    dbparamlist.Add(new dbparam("@inoper", otherData.userid.TrimEnd()));
                    foreach (DataRow dr in new database().checkSelectSql("mssql", "flyformstring", "exec web.searchmaining @length,@inoper;", dbparamlist).Rows)
                    {
                        items.Add(new Dictionary<string, object>() { { "id", dr["formId"].ToString().TrimEnd() }, { "tile", dr["tile"].ToString().TrimEnd() }, { "datetime", dr["indate"].ToString().TrimEnd() }, { "showOther", false }, { "showFinish", dr["finish"].ToString().TrimEnd() == "1" } });
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
            int itemCount = int.Parse(database.checkSelectSql("mssql", "flyformstring", "exec web.countmainform;", dbparamlist).Rows[0]["itemcount"].ToString().TrimEnd());
            DataTable mainRows = new DataTable();
            dbparamlist.Add(new dbparam("@inoper", userData.userid.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyformstring", "exec web.searchmainform @inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new itemModels() { status = "nodata" };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in mainRows.Rows)
            {
                items.Add(new Dictionary<string, object>() { { "id", dr["formId"].ToString().TrimEnd() }, { "tile", dr["tile"].ToString().TrimEnd() }, { "datetime", dr["indate"].ToString().TrimEnd() }, { "showOther", false }, { "showFinish", dr["finish"].ToString().TrimEnd() == "1" } });
            }
            return new itemModels() { itemCount = itemCount, items = items, status = "istrue" };
        }

        public sFormModels GetSItemModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyformstring", "exec web.searchmaindeta @formId,@inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sFormModels() { status = "nodata" };
            }
            int i = 1;
            dbparamlist.Add(new dbparam("@random", mainRows.Rows[0]["randsub"].ToString().TrimEnd()));
            dbparamlist.Add(new dbparam("@number", mainRows.Rows[0]["number"].ToString().TrimEnd()));
            dbparamlist.Add(new dbparam("@finish", mainRows.Rows[0]["finish"].ToString().TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyformstring", "exec web.searchsubdeta @formId,@inoper,@random,@number,@finish;", dbparamlist).Rows)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
                dbparamlist.Add(new dbparam("@iid", int.Parse(dr["iid"].ToString().TrimEnd())));
                dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
                dbparamlist.Add(new dbparam("@random", mainRows.Rows[0]["randopt"].ToString().TrimEnd()));
                List<Dictionary<string, object>> answeritems = new List<Dictionary<string, object>>();
                foreach (DataRow drs in database.checkSelectSql("mssql", "flyformstring", "exec web.searchoptiondeta @formId,@iid,@inoper,@random;", dbparamlist).Rows)
                {
                    answeritems.Add(new Dictionary<string, object>() { { "id", drs["id"].ToString().TrimEnd() }, { "values", drs["value"].ToString().TrimEnd() }, { "showAnswer", drs["answer"].ToString().TrimEnd() == "1" }, { "showRight", drs["right"].ToString().TrimEnd() == "1" } });
                }
                items.Add(new Dictionary<string, object>() { { "iid", dr["iid"].ToString().TrimEnd() }, { "title", $"{i}.{dr["tile"].ToString().TrimEnd()}" }, { "showVeri", dr["verified"].ToString().TrimEnd() == "1" }, { "showDrop", false }, { "showFile", false }, { "outValue", dr["outValue"].ToString().TrimEnd() }, { "value", dr["value"].ToString().TrimEnd() }, { "showMenu", false }, { "type_", dr["type"].ToString().TrimEnd() }, { "operation", dr["operation"].ToString().TrimEnd() }, { "area", dr["area"].ToString().TrimEnd() }, { "eror", dr["eror"].ToString().TrimEnd() }, { "showCheck", dr["checked"].ToString().TrimEnd() == "1" }, { "answeritems", answeritems.ToArray() } });
                i++;
            }
            return new sFormModels() { formId = mainRows.Rows[0]["formId"].ToString().TrimEnd(), tile = mainRows.Rows[0]["tile"].ToString().TrimEnd(), desc = mainRows.Rows[0]["desc"].ToString().TrimEnd(), exam = mainRows.Rows[0]["examed"].ToString().TrimEnd() == "1", restart = mainRows.Rows[0]["restarted"].ToString().TrimEnd() == "1", finish = mainRows.Rows[0]["finish"].ToString().TrimEnd() == "1", score = $"{mainRows.Rows[0]["score"].ToString().TrimEnd()}分", items = items, status = "istrue" };
        }

        public sFormModels GetRestartModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyformstring", "exec web.deletefilldeta @formId,@inoper;", dbparamlist) != "istrue")
            {
                return new sFormModels() { status = "error" };
            }
            DataTable mainRows = new DataTable();
            mainRows = database.checkSelectSql("mssql", "flyformstring", "exec web.searchmaindeta @formId,@inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sFormModels() { status = "nodata" };
            }
            int i = 1;
            dbparamlist.Add(new dbparam("@random", mainRows.Rows[0]["randsub"].ToString().TrimEnd()));
            dbparamlist.Add(new dbparam("@number", mainRows.Rows[0]["number"].ToString().TrimEnd()));
            dbparamlist.Add(new dbparam("@finish", mainRows.Rows[0]["finish"].ToString().TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyformstring", "exec web.searchsubdeta @formId,@inoper,@random,@number,@finish;", dbparamlist).Rows)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
                dbparamlist.Add(new dbparam("@iid", int.Parse(dr["iid"].ToString().TrimEnd())));
                dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
                dbparamlist.Add(new dbparam("@random", mainRows.Rows[0]["randopt"].ToString().TrimEnd()));
                List<Dictionary<string, object>> answeritems = new List<Dictionary<string, object>>();
                foreach (DataRow drs in database.checkSelectSql("mssql", "flyformstring", "exec web.searchoptiondeta @formId,@iid,@inoper,@random;", dbparamlist).Rows)
                {
                    answeritems.Add(new Dictionary<string, object>() { { "id", drs["id"].ToString().TrimEnd() }, { "values", drs["value"].ToString().TrimEnd() }, { "showAnswer", drs["answer"].ToString().TrimEnd() == "1" }, { "showRight", drs["right"].ToString().TrimEnd() == "1" } });
                }
                items.Add(new Dictionary<string, object>() { { "iid", dr["iid"].ToString().TrimEnd() }, { "title", $"{i}.{dr["tile"].ToString().TrimEnd()}" }, { "showVeri", dr["verified"].ToString().TrimEnd() == "1" }, { "showDrop", false }, { "showFile", false }, { "outValue", dr["outValue"].ToString().TrimEnd() }, { "value", dr["value"].ToString().TrimEnd() }, { "showMenu", false }, { "type_", dr["type"].ToString().TrimEnd() }, { "operation", dr["operation"].ToString().TrimEnd() }, { "area", dr["area"].ToString().TrimEnd() }, { "eror", dr["eror"].ToString().TrimEnd() }, { "showCheck", dr["checked"].ToString().TrimEnd() == "1" }, { "answeritems", answeritems.ToArray() } });
                i++;
            }
            return new sFormModels() { formId = mainRows.Rows[0]["formId"].ToString().TrimEnd(), tile = mainRows.Rows[0]["tile"].ToString().TrimEnd(), desc = mainRows.Rows[0]["desc"].ToString().TrimEnd(), exam = mainRows.Rows[0]["examed"].ToString().TrimEnd() == "1", restart = mainRows.Rows[0]["restarted"].ToString().TrimEnd() == "1", finish = mainRows.Rows[0]["finish"].ToString().TrimEnd() == "1", score = $"{mainRows.Rows[0]["score"].ToString().TrimEnd()}分", items = items, status = "istrue" };
        }

        public sFormModels GetInsertModels(iFormData iFormData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", iFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", iFormData.newid.TrimEnd()));
            switch (database.checkSelectSql("mssql", "flyformstring", "exec web.searchmaindeta @formId,@inoper;", dbparamlist).Rows.Count)
            {
                case 0:
                    return new sFormModels() { status = "nodata" };
            }
            foreach (var item in iFormData.items)
            {
                switch (bool.Parse(item["showCheck"].ToString().TrimEnd()))
                {
                    case true:
                        switch (item["outValue"].ToString().TrimEnd())
                        {
                            case "radio":
                            case "checkbox":
                                bool showAnswer = false;
                                foreach (var answeritem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["answeritems"].ToString().TrimEnd()))
                                {
                                    if (bool.Parse(answeritem["showAnswer"].ToString().TrimEnd())) showAnswer = true;
                                }
                                switch (showAnswer)
                                {
                                    case false:
                                        return new sFormModels() { status = $"{item["title"].ToString().TrimEnd()} is not choose" };
                                }
                                break;
                            case "image":
                                switch (item["value"].ToString().TrimEnd())
                                {
                                    case "":
                                        return new sFormModels() { status = $"{item["title"].ToString().TrimEnd()} is not upload" };
                                }
                                break;
                            default:
                                switch (item["value"].ToString().TrimEnd())
                                {
                                    case "":
                                        return new sFormModels() { status = $"{item["title"].ToString().TrimEnd()} is not write" };
                                }
                                break;
                        }
                        break;
                }
            }
            if (database.checkActiveSql("mssql", "flyformstring", "exec web.deletesuboption @formId,@inoper;", dbparamlist) != "istrue")
            {
                return new sFormModels() { status = "error" };
            }
            datetime datetime = new datetime();
            double total = 0, right = 0;
            string date = datetime.sqldate("mssql", "flyformstring"), time = datetime.sqltime("mssql", "flyformstring");
            foreach (var item in iFormData.items)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", iFormData.formId.TrimEnd()));
                dbparamlist.Add(new dbparam("@iid", int.Parse(item["iid"].ToString().TrimEnd())));
                dbparamlist.Add(new dbparam("@inoper", iFormData.newid.TrimEnd()));
                dbparamlist.Add(new dbparam("@value", item["value"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@indate", date));
                dbparamlist.Add(new dbparam("@intime", time));
                if (database.checkActiveSql("mssql", "flyformstring", "insert into web.sillform (formId,iid,inoper,value,indate,intime) values (@formId,@iid,@inoper,@value,@indate,@intime);", dbparamlist) != "istrue")
                {
                    return new sFormModels() { status = "error" };
                }
                switch (item["outValue"].ToString().TrimEnd())
                {
                    case "radio":
                    case "checkbox":
                        bool showRight = true;
                        foreach (var answeritem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["answeritems"].ToString().TrimEnd()))
                        {
                            dbparamlist.Clear();
                            dbparamlist.Add(new dbparam("@formId", iFormData.formId.TrimEnd()));
                            dbparamlist.Add(new dbparam("@iid", int.Parse(item["iid"].ToString().TrimEnd())));
                            dbparamlist.Add(new dbparam("@id", int.Parse(answeritem["id"].ToString().TrimEnd())));
                            bool answer = database.checkSelectSql("mssql", "flyformstring", "exec web.searchoptioninfo @formId,@iid,@id;", dbparamlist).Rows[0]["answer"].ToString().TrimEnd() == "1";
                            dbparamlist.Add(new dbparam("@inoper", iFormData.newid.TrimEnd()));
                            dbparamlist.Add(new dbparam("@answer", bool.Parse(answeritem["showAnswer"].ToString().TrimEnd()) ? "1" : "0"));
                            dbparamlist.Add(new dbparam("@right", bool.Parse(answeritem["showAnswer"].ToString().TrimEnd()) == answer ? "1" : "0"));
                            dbparamlist.Add(new dbparam("@indate", date));
                            dbparamlist.Add(new dbparam("@intime", time));
                            if (database.checkActiveSql("mssql", "flyformstring", "insert into web.oillform (formId,iid,id,inoper,answer,[right],indate,intime) values (@formId,@iid,@id,@inoper,@answer,@right,@indate,@intime);", dbparamlist) != "istrue")
                            {
                                return new sFormModels() { status = "error" };
                            }
                            if (bool.Parse(answeritem["showAnswer"].ToString().TrimEnd()) != answer) showRight = false;
                        }
                        if (showRight) right++;
                        total++;
                        break;
                }
            }
            dbparamlist.Clear();
            dbparamlist.Add(new dbparam("@formId", iFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@score", total == 0 ? 100 : Math.Round((right / total) * 100, 1)));
            dbparamlist.Add(new dbparam("@inoper", iFormData.newid.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyformstring", "exec web.searchmaininfo @formId,@score,@inoper;", dbparamlist) != "istrue")
            {
                return new sFormModels() { status = "error" };
            }
            dbparamlist.Clear();
            DataTable mainRows = new DataTable();
            dbparamlist.Add(new dbparam("@formId", iFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", iFormData.newid.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyformstring", "exec web.searchmaindeta @formId,@inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sFormModels() { status = "nodata" };
            }
            int i = 1;
            dbparamlist.Add(new dbparam("@random", mainRows.Rows[0]["randsub"].ToString().TrimEnd()));
            dbparamlist.Add(new dbparam("@number", mainRows.Rows[0]["number"].ToString().TrimEnd()));
            dbparamlist.Add(new dbparam("@finish", mainRows.Rows[0]["finish"].ToString().TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyformstring", "exec web.searchsubdeta @formId,@inoper,@random,@number,@finish;", dbparamlist).Rows)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@formId", iFormData.formId.TrimEnd()));
                dbparamlist.Add(new dbparam("@iid", int.Parse(dr["iid"].ToString().TrimEnd())));
                dbparamlist.Add(new dbparam("@inoper", iFormData.newid.TrimEnd()));
                dbparamlist.Add(new dbparam("@random", mainRows.Rows[0]["randopt"].ToString().TrimEnd()));
                List<Dictionary<string, object>> answeritems = new List<Dictionary<string, object>>();
                foreach (DataRow drs in database.checkSelectSql("mssql", "flyformstring", "exec web.searchoptiondeta @formId,@iid,@inoper,@random;", dbparamlist).Rows)
                {
                    answeritems.Add(new Dictionary<string, object>() { { "id", drs["id"].ToString().TrimEnd() }, { "values", drs["value"].ToString().TrimEnd() }, { "showAnswer", drs["answer"].ToString().TrimEnd() == "1" }, { "showRight", drs["right"].ToString().TrimEnd() == "1" } });
                }
                items.Add(new Dictionary<string, object>() { { "iid", dr["iid"].ToString().TrimEnd() }, { "title", $"{i}.{dr["tile"].ToString().TrimEnd()}" }, { "showVeri", dr["verified"].ToString().TrimEnd() == "1" }, { "showDrop", false }, { "showFile", false }, { "outValue", dr["outValue"].ToString().TrimEnd() }, { "value", dr["value"].ToString().TrimEnd() }, { "showMenu", false }, { "type_", dr["type"].ToString().TrimEnd() }, { "operation", dr["operation"].ToString().TrimEnd() }, { "area", dr["area"].ToString().TrimEnd() }, { "eror", dr["eror"].ToString().TrimEnd() }, { "showCheck", dr["checked"].ToString().TrimEnd() == "1" }, { "answeritems", answeritems.ToArray() } });
                i++;
            }
            return new sFormModels() { formId = mainRows.Rows[0]["formId"].ToString().TrimEnd(), tile = mainRows.Rows[0]["tile"].ToString().TrimEnd(), desc = mainRows.Rows[0]["desc"].ToString().TrimEnd(), exam = mainRows.Rows[0]["examed"].ToString().TrimEnd() == "1", restart = mainRows.Rows[0]["restarted"].ToString().TrimEnd() == "1", finish = mainRows.Rows[0]["finish"].ToString().TrimEnd() == "1", score = $"{mainRows.Rows[0]["score"].ToString().TrimEnd()}分", items = items, status = "istrue" };
        }
    }
}