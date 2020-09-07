using System.Collections.Generic;
using System.Data;
using forminfoCore.App_Code;
using System.Text.Json;

namespace forminfoCore.Models
{
    public class FormorClass
    {
        public sFoorModels GetSearchModels(userData userData, string cuurip)
        {
            List<Dictionary<string, object>> opticonitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flyformstring", "exec web.searchitemform;", new List<dbparam>()).Rows)
            {
                opticonitems.Add(new Dictionary<string, object>() { { "opticonPadding", false }, { "icon", dr["icon"].ToString().TrimEnd() }, { "value", dr["value"].ToString().TrimEnd() } });
            }
            List<Dictionary<string, object>> answeritems = new List<Dictionary<string, object>>();
            answeritems.Add(new Dictionary<string, object>() { { "id", 1 }, { "value", "" }, { "showAnswer", false }, { "ansrDelete", false } });
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            items.Add(new Dictionary<string, object>() { { "iid", 1 }, { "showLine", false }, { "title", "" }, { "showOut", false }, { "showVer", false }, { "showDrop", false }, { "showFile", false }, { "outValue", "text" }, { "type_", "" }, { "showType", false }, { "typeitems", new List<Dictionary<string, object>>().ToArray() }, { "operation", "" }, { "showOperation", false }, { "operationitems", new List<Dictionary<string, object>>().ToArray() }, { "area", "" }, { "eror", "" }, { "showCheck", false }, { "showMore", false }, { "opticonitems", opticonitems.ToArray() }, { "answeritems", answeritems.ToArray() }, { "itemDelete", false } });
            List<Dictionary<string, object>> settitems = new List<Dictionary<string, object>>();
            settitems.Add(new Dictionary<string, object>() { { "stdate", "" }, { "sttime", "" }, { "endate", "" }, { "entime", "" }, { "showExam", false }, { "randOpt", false }, { "randSub", false }, { "showRest", false }, { "showLimt", false }, { "number", "" } });
            return new sFoorModels() { items = items, settitems = settitems };
        }

        public sTypeModels GetSTypeModels(otherData otherData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@value", otherData.values.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>(); string value = "";
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyformstring", "exec web.searchoperationform @value;", dbparamlist).Rows)
            {
                value = dr["operationValue"].ToString().TrimEnd();
                items.Add(new Dictionary<string, object>() { { "optionPadding", dr["optionPadding"].ToString().TrimEnd() == "1" }, { "value", dr["operationValue"].ToString().TrimEnd() } });
            }
            return new sTypeModels() { value = value, items = items, status = "istrue" };
        }

        public sVeriModels GetSVeriModels(userData userData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            string type_ = "";
            List<Dictionary<string, object>> typeitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyformstring", "exec web.searchtypeform;", dbparamlist).Rows)
            {
                type_ = dr["value"].ToString().TrimEnd();
                typeitems.Add(new Dictionary<string, object>() { { "optionPadding", dr["optionPadding"].ToString().TrimEnd() == "1" }, { "value", dr["value"].ToString().TrimEnd() } });
            }
            string operation = "";
            dbparamlist.Add(new dbparam("@value", type_));
            List<Dictionary<string, object>> operationitems = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyformstring", "exec web.searchoperationform @value;", dbparamlist).Rows)
            {
                operation = dr["operationValue"].ToString().TrimEnd();
                operationitems.Add(new Dictionary<string, object>() { { "optionPadding", dr["optionPadding"].ToString().TrimEnd() == "1" }, { "value", dr["operationValue"].ToString().TrimEnd() } });
            }
            return new sVeriModels() { type_ = type_, typeitems = typeitems, operation = operation, operationitems = operationitems, status = "istrue" };
        }

        public sOptonModels GetAddModels(userData userData, string cuurip)
        {
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in new database().checkSelectSql("mssql", "flyformstring", "exec web.searchitemform;", new List<dbparam>()).Rows)
            {
                items.Add(new Dictionary<string, object>() { { "opticonPadding", false }, { "icon", dr["icon"].ToString().TrimEnd() }, { "value", dr["value"].ToString().TrimEnd() } });
            }
            return new sOptonModels() { items = items };
        }

        public statusModels GetInsertModels(iFormsData iFormsData, string cuurip)
        {
            database database = new database();
            datetime datetime = new datetime();
            string formId = new sha256().new256("mssql", "flyformstring"), date = datetime.sqldate("mssql", "flyformstring"), time = datetime.sqltime("mssql", "flyformstring");
            foreach (var item in iFormsData.items)
            {
                List<dbparam> dbparamlist = new List<dbparam>();
                dbparamlist.Add(new dbparam("@formId", formId));
                dbparamlist.Add(new dbparam("@iid", item["iid"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@inoper", iFormsData.newid.TrimEnd()));
                dbparamlist.Add(new dbparam("@tile", item["title"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@outValue", item["outValue"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@verified", bool.Parse(item["showVer"].ToString().TrimEnd()) ? "1" : "0"));
                dbparamlist.Add(new dbparam("@type", item["type_"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@operation", item["operation"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@area", item["area"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@eror", item["eror"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@checked", bool.Parse(item["showCheck"].ToString().TrimEnd()) ? "1" : "0"));
                dbparamlist.Add(new dbparam("@indate", date));
                dbparamlist.Add(new dbparam("@intime", time));
                if (database.checkActiveSql("mssql", "flyformstring", "insert into web.subform (formId,iid,inoper,tile,outValue,verified,type,operation,area,eror,checked,indate,intime) values (@formId,@iid,@inoper,@tile,@outValue,@verified,@type,@operation,@area,@eror,@checked,@indate,@intime);", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
                switch (item["outValue"].ToString().TrimEnd())
                {
                    case "radio":
                    case "checkbox":
                        foreach (var answeritem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["answeritems"].ToString().TrimEnd()))
                        {
                            switch (bool.Parse(answeritem["ansrDelete"].ToString().TrimEnd()))
                            {
                                case false:
                                    dbparamlist.Clear();
                                    dbparamlist.Add(new dbparam("@formId", formId));
                                    dbparamlist.Add(new dbparam("@iid", item["iid"].ToString().TrimEnd()));
                                    dbparamlist.Add(new dbparam("@id", answeritem["id"].ToString().TrimEnd()));
                                    dbparamlist.Add(new dbparam("@inoper", iFormsData.newid.TrimEnd()));
                                    dbparamlist.Add(new dbparam("@value", answeritem["value"].ToString().TrimEnd()));
                                    dbparamlist.Add(new dbparam("@answer", bool.Parse(answeritem["showAnswer"].ToString().TrimEnd()) ? "1" : "0"));
                                    dbparamlist.Add(new dbparam("@indate", date));
                                    dbparamlist.Add(new dbparam("@intime", time));
                                    if (database.checkActiveSql("mssql", "flyformstring", "insert into web.optionform (formId,iid,id,inoper,value,answer,indate,intime) values (@formId,@iid,@id,@inoper,@value,@answer,@indate,@intime);", dbparamlist) != "istrue")
                                    {
                                        return new statusModels() { status = "error" };
                                    }
                                    break;
                            }
                        }
                        break;
                }
            }
            foreach (var settitem in iFormsData.settitems)
            {
                List<dbparam> dbparamlist = new List<dbparam>();
                dbparamlist.Add(new dbparam("@formId", formId));
                dbparamlist.Add(new dbparam("@inoper", iFormsData.newid.TrimEnd()));
                dbparamlist.Add(new dbparam("@tile", iFormsData.tile.TrimEnd()));
                dbparamlist.Add(new dbparam("@desc", iFormsData.desc.TrimEnd()));
                dbparamlist.Add(new dbparam("@stdate", settitem["stdate"].ToString().TrimEnd().Replace("-", "/")));
                dbparamlist.Add(new dbparam("@sttime", settitem["sttime"].ToString().TrimEnd().Replace("-", "/")));
                dbparamlist.Add(new dbparam("@endate", settitem["endate"].ToString().TrimEnd().Replace("-", "/")));
                dbparamlist.Add(new dbparam("@entime", settitem["entime"].ToString().TrimEnd().Replace("-", "/")));
                dbparamlist.Add(new dbparam("@examed", bool.Parse(settitem["showExam"].ToString().TrimEnd()) ? "1" : "0"));
                dbparamlist.Add(new dbparam("@restarted", bool.Parse(settitem["showRest"].ToString().TrimEnd()) ? "1" : "0"));
                dbparamlist.Add(new dbparam("@limited", bool.Parse(settitem["showLimt"].ToString().TrimEnd()) ? "1" : "0"));
                dbparamlist.Add(new dbparam("@randopt", bool.Parse(settitem["randOpt"].ToString().TrimEnd()) ? "1" : "0"));
                dbparamlist.Add(new dbparam("@randsub", bool.Parse(settitem["randSub"].ToString().TrimEnd()) ? "1" : "0"));
                dbparamlist.Add(new dbparam("@number", settitem["number"].ToString().TrimEnd()));
                dbparamlist.Add(new dbparam("@indate", date));
                dbparamlist.Add(new dbparam("@intime", time));
                if (database.checkActiveSql("mssql", "flyformstring", "insert into web.mainform (formId,inoper,tile,[desc],stdate,sttime,endate,entime,examed,restarted,limited,randopt,randsub,number,indate,intime) values (@formId,@inoper,@tile,@desc,@stdate,@sttime,@endate,@entime,@examed,@restarted,@limited,@randopt,@randsub,@number,@indate,@intime);", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            return new statusModels() { status = "istrue" };
        }
    }
}