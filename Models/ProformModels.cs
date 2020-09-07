using System.Collections.Generic;
using System.Data;
using System.Threading;
using forminfoCore.App_Code;
using System.Text.Json;

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

        public sPormModels GetSItemModels(dFormData dFormData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyformstring", "exec web.searchclimainform @formId,@inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sPormModels() { status = "nodata" };
            }
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyformstring", "exec web.searchclisubform @formId,@inoper;", dbparamlist).Rows)
            {
                dbparamlist.Clear();
                List<Dictionary<string, object>> opticonitems = new List<Dictionary<string, object>>();
                foreach (DataRow drs in new database().checkSelectSql("mssql", "flyformstring", "exec web.searchitemform;", new List<dbparam>()).Rows)
                {
                    opticonitems.Add(new Dictionary<string, object>() { { "opticonPadding", false }, { "icon", drs["icon"].ToString().TrimEnd() }, { "value", drs["value"].ToString().TrimEnd() } });
                }
                List<Dictionary<string, object>> answeritems = new List<Dictionary<string, object>>();
                switch (dr["outValue"].ToString().TrimEnd())
                {
                    case "radio":
                    case "checkbox":
                        dbparamlist.Clear();
                        dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
                        dbparamlist.Add(new dbparam("@iid", int.Parse(dr["iid"].ToString().TrimEnd())));
                        dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
                        foreach (DataRow drs in database.checkSelectSql("mssql", "flyformstring", "exec web.searchoptionform @formId,@iid,@inoper;", dbparamlist).Rows)
                        {
                            answeritems.Add(new Dictionary<string, object>() { { "id", int.Parse(drs["id"].ToString().TrimEnd()) }, { "value", drs["value"].ToString().TrimEnd() }, { "showAnswer", drs["answer"].ToString().TrimEnd() == "1" }, { "ansrDelete", false }, { "ansrModify", false }, { "ansrCreate", false } });
                        }
                        break;
                    default:
                        answeritems.Add(new Dictionary<string, object>() { { "id", 1 }, { "value", "" }, { "showAnswer", false }, { "ansrDelete", false }, { "ansrModify", false }, { "ansrCreate", true } });
                        break;
                }
                List<Dictionary<string, object>> typeitems = new List<Dictionary<string, object>>(), operationitems = new List<Dictionary<string, object>>();
                switch (dr["verified"].ToString().TrimEnd())
                {
                    case "1":
                        dbparamlist.Clear();
                        foreach (DataRow drs in database.checkSelectSql("mssql", "flyformstring", "exec web.searchtypeform;", dbparamlist).Rows)
                        {
                            typeitems.Add(new Dictionary<string, object>() { { "optionPadding", drs["optionPadding"].ToString().TrimEnd() == "1" }, { "value", drs["value"].ToString().TrimEnd() } });
                        }
                        dbparamlist.Add(new dbparam("@value", dr["type"].ToString().TrimEnd()));
                        foreach (DataRow drs in database.checkSelectSql("mssql", "flyformstring", "exec web.searchoperationform @value;", dbparamlist).Rows)
                        {
                            operationitems.Add(new Dictionary<string, object>() { { "optionPadding", drs["optionPadding"].ToString().TrimEnd() == "1" }, { "value", drs["operationValue"].ToString().TrimEnd() } });
                        }
                        break;
                }
                items.Add(new Dictionary<string, object>() { { "iid", int.Parse(dr["iid"].ToString().TrimEnd()) }, { "showLine", false }, { "title", dr["tile"].ToString().TrimEnd() }, { "showOut", false }, { "showVer", dr["verified"].ToString().TrimEnd() == "1" }, { "showDrop", false }, { "showFile", false }, { "outValue", dr["outValue"].ToString().TrimEnd() }, { "type_", dr["type"].ToString().TrimEnd() }, { "showType", false }, { "typeitems", typeitems.ToArray() }, { "operation", dr["operation"].ToString().TrimEnd() }, { "showOperation", false }, { "operationitems", operationitems.ToArray() }, { "area", dr["area"].ToString().TrimEnd() }, { "eror", dr["eror"].ToString().TrimEnd() }, { "showCheck", dr["checked"].ToString().TrimEnd() == "1" }, { "showMore", false }, { "opticonitems", opticonitems.ToArray() }, { "answeritems", answeritems.ToArray() }, { "formDelete", false }, { "formModify", false }, { "formCreate", false } });
            }
            List<Dictionary<string, object>> settitems = new List<Dictionary<string, object>>();
            settitems.Add(new Dictionary<string, object>() { { "stdate", mainRows.Rows[0]["stdate"].ToString().TrimEnd().Replace("/", "-") }, { "sttime", mainRows.Rows[0]["sttime"].ToString().TrimEnd() }, { "endate", mainRows.Rows[0]["endate"].ToString().TrimEnd().Replace("/", "-") }, { "entime", mainRows.Rows[0]["entime"].ToString().TrimEnd() }, { "showExam", mainRows.Rows[0]["examed"].ToString().TrimEnd() == "1" }, { "randOpt", mainRows.Rows[0]["randopt"].ToString().TrimEnd() == "1" }, { "randSub", mainRows.Rows[0]["randsub"].ToString().TrimEnd() == "1" }, { "showRest", mainRows.Rows[0]["restarted"].ToString().TrimEnd() == "1" }, { "showLimt", mainRows.Rows[0]["limited"].ToString().TrimEnd() == "1" }, { "number", mainRows.Rows[0]["number"].ToString().TrimEnd() } });
            return new sPormModels() { formId = mainRows.Rows[0]["formId"].ToString().TrimEnd(), tile = mainRows.Rows[0]["tile"].ToString().TrimEnd(), desc = mainRows.Rows[0]["desc"].ToString().TrimEnd(), items = items, settitems = settitems, status = "istrue" };
        }

        public sTypeModels GetSTypeModels(sRowsData sRowsData, string cuurip)
        {
            database database = new database();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", sRowsData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", sRowsData.newid.TrimEnd()));
            switch (database.checkSelectSql("mssql", "flyformstring", "exec web.searchclimainform @formId,@inoper;", dbparamlist).Rows.Count)
            {
                case 0:
                    return new sTypeModels() { status = "nodata" };
            }
            dbparamlist.Add(new dbparam("@value", sRowsData.value.TrimEnd()));
            List<Dictionary<string, object>> items = new List<Dictionary<string, object>>(); string value = "";
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyformstring", "exec web.searchoperationform @value;", dbparamlist).Rows)
            {
                value = dr["operationValue"].ToString().TrimEnd();
                items.Add(new Dictionary<string, object>() { { "optionPadding", dr["optionPadding"].ToString().TrimEnd() == "1" }, { "value", dr["operationValue"].ToString().TrimEnd() } });
            }
            return new sTypeModels() { value = value, items = items, status = "istrue" };
        }

        public sVeriModels GetSVeriModels(sRowsData sRowsData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", sRowsData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@iid", sRowsData.value.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", sRowsData.newid.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyformstring", "exec web.searchclisubdeta @formId,@iid,@inoper;", dbparamlist);
            List<Dictionary<string, object>> typeitems = new List<Dictionary<string, object>>(), operationitems = new List<Dictionary<string, object>>();
            switch (mainRows.Rows.Count)
            {
                case 0:
                    string type_ = "";
                    foreach (DataRow dr in database.checkSelectSql("mssql", "flyformstring", "exec web.searchtypeform;", dbparamlist).Rows)
                    {
                        type_ = dr["value"].ToString().TrimEnd();
                        typeitems.Add(new Dictionary<string, object>() { { "optionPadding", dr["optionPadding"].ToString().TrimEnd() == "1" }, { "value", dr["value"].ToString().TrimEnd() } });
                    }
                    string operation = "";
                    dbparamlist.Add(new dbparam("@value", type_));
                    foreach (DataRow dr in database.checkSelectSql("mssql", "flyformstring", "exec web.searchoperationform @value;", dbparamlist).Rows)
                    {
                        operation = dr["operationValue"].ToString().TrimEnd();
                        operationitems.Add(new Dictionary<string, object>() { { "optionPadding", dr["optionPadding"].ToString().TrimEnd() == "1" }, { "value", dr["operationValue"].ToString().TrimEnd() } });
                    }
                    return new sVeriModels() { type_ = type_, typeitems = typeitems, operation = operation, operationitems = operationitems, status = "istrue" };
            }
            switch (mainRows.Rows[0]["verified"].ToString().TrimEnd())
            {
                case "0":
                    return new sVeriModels() { status = "nodata" };
            }
            dbparamlist.Clear();
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyformstring", "exec web.searchtypeform;", dbparamlist).Rows)
            {
                typeitems.Add(new Dictionary<string, object>() { { "optionPadding", dr["optionPadding"].ToString().TrimEnd() == "1" }, { "value", dr["value"].ToString().TrimEnd() } });
            }
            dbparamlist.Add(new dbparam("@value", mainRows.Rows[0]["type"].ToString().TrimEnd()));
            foreach (DataRow dr in database.checkSelectSql("mssql", "flyformstring", "exec web.searchoperationform @value;", dbparamlist).Rows)
            {
                operationitems.Add(new Dictionary<string, object>() { { "optionPadding", dr["optionPadding"].ToString().TrimEnd() == "1" }, { "value", dr["operationValue"].ToString().TrimEnd() } });
            }
            return new sVeriModels() { type_ = mainRows.Rows[0]["type"].ToString().TrimEnd(), typeitems = typeitems, operation = mainRows.Rows[0]["operation"].ToString().TrimEnd(), operationitems = operationitems, status = "istrue" };
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

        public statusModels GetDeleteModels(dFormData dFormData, string cuurip)
        {
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", dFormData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", dFormData.newid.TrimEnd()));
            if (new database().checkActiveSql("mssql", "flyformstring", "exec web.deleteformdata @formId,@inoper;", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            return new statusModels() { status = "istrue" };
        }

        public statusModels GetInsertModels(uFormsData uFormsData, string cuurip)
        {
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", uFormsData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@inoper", uFormsData.newid.TrimEnd()));
            mainRows = database.checkSelectSql("mssql", "flyformstring", "exec web.searchclimainform @formId,@inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new statusModels() { status = "nodata" };
            }
            datetime datetime = new datetime();
            string date = datetime.sqldate("mssql", "flyformstring"), time = datetime.sqltime("mssql", "flyformstring");
            foreach (var item in uFormsData.items)
            {
                switch (bool.Parse(item["formCreate"].ToString().TrimEnd()))
                {
                    case true:
                        dbparamlist.Clear();
                        dbparamlist.Add(new dbparam("@formId", uFormsData.formId.TrimEnd()));
                        dbparamlist.Add(new dbparam("@iid", int.Parse(item["iid"].ToString().TrimEnd())));
                        dbparamlist.Add(new dbparam("@inoper", uFormsData.newid.TrimEnd()));
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
                        break;
                    default:
                        switch (bool.Parse(item["formDelete"].ToString().TrimEnd()))
                        {
                            case true:
                                dbparamlist.Clear();
                                dbparamlist.Add(new dbparam("@formId", uFormsData.formId.TrimEnd()));
                                dbparamlist.Add(new dbparam("@iid", int.Parse(item["iid"].ToString().TrimEnd())));
                                dbparamlist.Add(new dbparam("@inoper", uFormsData.newid.TrimEnd()));
                                if (database.checkActiveSql("mssql", "flyformstring", "exec web.deletesubdata @formId,@iid,@inoper;", dbparamlist) != "istrue")
                                {
                                    return new statusModels() { status = "error" };
                                }
                                break;
                            default:
                                switch (bool.Parse(item["formModify"].ToString().TrimEnd()))
                                {
                                    case true:
                                        dbparamlist.Clear();
                                        dbparamlist.Add(new dbparam("@tile", item["title"].ToString().TrimEnd()));
                                        dbparamlist.Add(new dbparam("@outValue", item["outValue"].ToString().TrimEnd()));
                                        dbparamlist.Add(new dbparam("@verified", bool.Parse(item["showVer"].ToString().TrimEnd()) ? "1" : "0"));
                                        dbparamlist.Add(new dbparam("@type", item["type_"].ToString().TrimEnd()));
                                        dbparamlist.Add(new dbparam("@operation", item["operation"].ToString().TrimEnd()));
                                        dbparamlist.Add(new dbparam("@area", item["area"].ToString().TrimEnd()));
                                        dbparamlist.Add(new dbparam("@eror", item["eror"].ToString().TrimEnd()));
                                        dbparamlist.Add(new dbparam("@checked", bool.Parse(item["showCheck"].ToString().TrimEnd()) ? "1" : "0"));
                                        dbparamlist.Add(new dbparam("@modate", date));
                                        dbparamlist.Add(new dbparam("@motime", time));
                                        dbparamlist.Add(new dbparam("@mooper", uFormsData.newid.TrimEnd()));
                                        dbparamlist.Add(new dbparam("@formId", uFormsData.formId.TrimEnd()));
                                        dbparamlist.Add(new dbparam("@iid", int.Parse(item["iid"].ToString().TrimEnd())));
                                        dbparamlist.Add(new dbparam("@inoper", uFormsData.newid.TrimEnd()));
                                        if (database.checkActiveSql("mssql", "flyformstring", "update web.subform set tile = @tile,outValue = @outValue,verified = @verified,type = @type,operation = @operation,area = @area,eror = @eror,checked = @checked,modate = @modate,motime = @motime,@mooper = @mooper where formId = @formId and iid = @iid and inoper = @inoper;", dbparamlist) != "istrue")
                                        {
                                            return new statusModels() { status = "error" };
                                        }
                                        break;
                                }
                                break;
                        }
                        break;
                }
                switch (bool.Parse(item["formDelete"].ToString().TrimEnd()))
                {
                    case false:
                        switch (item["outValue"].ToString().TrimEnd())
                        {
                            case "radio":
                            case "checkbox":
                                foreach (var answeritem in JsonSerializer.Deserialize<List<Dictionary<string, object>>>(item["answeritems"].ToString().TrimEnd()))
                                {
                                    switch (bool.Parse(answeritem["ansrDelete"].ToString().TrimEnd()))
                                    {
                                        case true:
                                            dbparamlist.Clear();
                                            dbparamlist.Add(new dbparam("@formId", uFormsData.formId.TrimEnd()));
                                            dbparamlist.Add(new dbparam("@iid", item["iid"].ToString().TrimEnd()));
                                            dbparamlist.Add(new dbparam("@id", answeritem["id"].ToString().TrimEnd()));
                                            dbparamlist.Add(new dbparam("@inoper", uFormsData.newid.TrimEnd()));
                                            if (database.checkActiveSql("mssql", "flyformstring", "delete from web.optionform where formId = @formId and iid = @iid and id = @id and inoper = @inoper;", dbparamlist) != "istrue")
                                            {
                                                return new statusModels() { status = "error" };
                                            }
                                            break;
                                        default:
                                            switch (bool.Parse(answeritem["ansrCreate"].ToString().TrimEnd()))
                                            {
                                                case true:
                                                    dbparamlist.Clear();
                                                    dbparamlist.Add(new dbparam("@formId", uFormsData.formId.TrimEnd()));
                                                    dbparamlist.Add(new dbparam("@iid", item["iid"].ToString().TrimEnd()));
                                                    dbparamlist.Add(new dbparam("@id", answeritem["id"].ToString().TrimEnd()));
                                                    dbparamlist.Add(new dbparam("@inoper", uFormsData.newid.TrimEnd()));
                                                    dbparamlist.Add(new dbparam("@value", answeritem["value"].ToString().TrimEnd()));
                                                    dbparamlist.Add(new dbparam("@answer", bool.Parse(answeritem["showAnswer"].ToString().TrimEnd()) ? "1" : "0"));
                                                    dbparamlist.Add(new dbparam("@indate", date));
                                                    dbparamlist.Add(new dbparam("@intime", time));
                                                    if (database.checkActiveSql("mssql", "flyformstring", "insert into web.optionform (formId,iid,id,inoper,value,answer,indate,intime) values (@formId,@iid,@id,@inoper,@value,@answer,@indate,@intime);", dbparamlist) != "istrue")
                                                    {
                                                        return new statusModels() { status = "error" };
                                                    }
                                                    break;
                                                default:
                                                    switch (bool.Parse(answeritem["ansrModify"].ToString().TrimEnd()))
                                                    {
                                                        case true:
                                                            dbparamlist.Clear();
                                                            dbparamlist.Add(new dbparam("@value", answeritem["value"].ToString().TrimEnd()));
                                                            dbparamlist.Add(new dbparam("@answer", bool.Parse(answeritem["showAnswer"].ToString().TrimEnd()) ? "1" : "0"));
                                                            dbparamlist.Add(new dbparam("@modate", date));
                                                            dbparamlist.Add(new dbparam("@motime", time));
                                                            dbparamlist.Add(new dbparam("@mooper", uFormsData.newid.TrimEnd()));
                                                            dbparamlist.Add(new dbparam("@formId", uFormsData.formId.TrimEnd()));
                                                            dbparamlist.Add(new dbparam("@iid", item["iid"].ToString().TrimEnd()));
                                                            dbparamlist.Add(new dbparam("@id", answeritem["id"].ToString().TrimEnd()));
                                                            dbparamlist.Add(new dbparam("@inoper", uFormsData.newid.TrimEnd()));
                                                            if (database.checkActiveSql("mssql", "flyformstring", "update web.optionform set value = @value,answer = @answer,modate = @modate,motime = @motime,mooper = @mooper where formId = @formId and iid = @iid and id = @id and inoper = @inoper;", dbparamlist) != "istrue")
                                                            {
                                                                return new statusModels() { status = "error" };
                                                            }
                                                            break;
                                                    }
                                                    break;
                                            }
                                            break;
                                    }
                                }
                                break;
                            default:
                                dbparamlist.Clear();
                                dbparamlist.Add(new dbparam("@formId", uFormsData.formId.TrimEnd()));
                                dbparamlist.Add(new dbparam("@iid", item["iid"].ToString().TrimEnd()));
                                dbparamlist.Add(new dbparam("@inoper", uFormsData.newid.TrimEnd()));
                                if (database.checkActiveSql("mssql", "flyformstring", "delete from web.optionform where formId = @formId and iid = @iid and inoper = @inoper;", dbparamlist) != "istrue")
                                {
                                    return new statusModels() { status = "error" };
                                }
                                break;
                        }
                        break;
                }
            }
            foreach (var settitem in uFormsData.settitems)
            {
                dbparamlist.Clear();
                dbparamlist.Add(new dbparam("@tile", uFormsData.tile.TrimEnd()));
                dbparamlist.Add(new dbparam("@desc", uFormsData.desc.TrimEnd()));
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
                dbparamlist.Add(new dbparam("@modate", date));
                dbparamlist.Add(new dbparam("@motime", time));
                dbparamlist.Add(new dbparam("@mooper", uFormsData.newid.TrimEnd()));
                dbparamlist.Add(new dbparam("@formId", uFormsData.formId.TrimEnd()));
                dbparamlist.Add(new dbparam("@inoper", uFormsData.newid.TrimEnd()));
                if (database.checkActiveSql("mssql", "flyformstring", "update web.mainform set tile = @tile,[desc] = @desc,stdate = @stdate,sttime = @sttime,endate = @endate,entime = @entime,examed = @examed,restarted = @restarted,limited = @limited,randopt = @randopt,randsub = @randsub,number = @number,modate = @modate,motime = @motime,mooper = @mooper where formId = @formId and inoper = @inoper;", dbparamlist) != "istrue")
                {
                    return new statusModels() { status = "error" };
                }
            }
            return new statusModels() { status = "istrue" };
        }
    }
}