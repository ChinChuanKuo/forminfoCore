using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Net;
using System.Threading.Tasks;
using forminfoCore.App_Code;
using forminfoCore.Models;
using Microsoft.AspNetCore.Mvc;
using NPOI.HSSF.UserModel;
using NPOI.SS.UserModel;
using NPOI.XSSF.UserModel;

namespace forminfoCore.Controllers
{
    public class ExcelController : Controller
    {
        public ActionResult exampleData(string newid)
        {
            string filename = "", clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            XSSFWorkbook workbook = new XSSFWorkbook();
            XSSFSheet sheet = (XSSFSheet)workbook.CreateSheet("Information");
            XSSFRow row = (XSSFRow)sheet.CreateRow(0);
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@newid", newid));
            mainRows = database.checkSelectSql("mssql", "epaperstring", "exec web.checksitename @newid;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    row.CreateCell(0).SetCellValue("NOT YOUR INFORMATION ABOUT THIS FORM DATABASE");
                    filename = "沒資料呈現";
                    break;
                default:
                    datetime datetime = new datetime();
                    string stdate = datetime.sqldate("mssql", "epaperstring"), sttime = datetime.sqltime("mssql", "epaperstring");
                    XSSFCellStyle xs = (XSSFCellStyle)workbook.CreateCellStyle();
                    xs.Alignment = HorizontalAlignment.Center;
                    row.CreateCell(0).SetCellValue("表單上傳範例");
                    sheet.AddMergedRegion(new NPOI.SS.Util.CellRangeAddress(0, 0, 0, 19));
                    row.GetCell(0).CellStyle = xs;
                    row = (XSSFRow)sheet.CreateRow(1);
                    row.CreateCell(0).SetCellValue("表單代碼");
                    row.CreateCell(1).SetCellValue("57ae8a28-5b48-4e61-97af-e50431a9c65b");
                    row.CreateCell(2).SetCellValue("表單題目");
                    row.CreateCell(3).SetCellValue("測試表單");
                    row.CreateCell(4).SetCellValue("表單備註");
                    row.CreateCell(5).SetCellValue("測試備註");
                    row = (XSSFRow)sheet.CreateRow(2);
                    row.CreateCell(0).SetCellValue("開始日期");
                    row.CreateCell(1).SetCellValue("2020/09/08");
                    row.CreateCell(2).SetCellValue("開始時間");
                    row.CreateCell(3).SetCellValue("11:17");
                    row.CreateCell(4).SetCellValue("截止日期");
                    row.CreateCell(5).SetCellValue("2020/09/08");
                    row.CreateCell(6).SetCellValue("截止時間");
                    row.CreateCell(7).SetCellValue("12:00");
                    row.CreateCell(8).SetCellValue("是否考試？（0:否 ,1:是）");
                    row.CreateCell(9).SetCellValue("1");
                    row.CreateCell(10).SetCellValue("重新開始？（0:否 ,1:是）");
                    row.CreateCell(11).SetCellValue("1");
                    row.CreateCell(12).SetCellValue("限制人員？（0:否 ,1:是）");
                    row.CreateCell(13).SetCellValue("1");
                    row.CreateCell(14).SetCellValue("選項隨機？（0:否 ,1:是）");
                    row.CreateCell(15).SetCellValue("1");
                    row.CreateCell(16).SetCellValue("題目隨機？（0:否 ,1:是）");
                    row.CreateCell(17).SetCellValue("1");
                    row.CreateCell(18).SetCellValue("顯示題數（若要全數，請輸入0或空白）");
                    row.CreateCell(19).SetCellValue("0");
                    row = (XSSFRow)sheet.CreateRow(4);
                    row.CreateCell(0).SetCellValue("題目編號");
                    row.CreateCell(1).SetCellValue("選項編號");
                    row.CreateCell(2).SetCellValue("題目 / 選項內容");
                    row.CreateCell(3).SetCellValue("類型（radio:單選 / checkbox:複選 / text:短句 / textarea:長句 / image:圖片）");
                    row.CreateCell(4).SetCellValue("是否需要檢查（0:不需要 / 1:需要）");
                    row.CreateCell(5).SetCellValue("是否為答案（0:否 / 1:是）");
                    row = (XSSFRow)sheet.CreateRow(5);
                    row.CreateCell(0).SetCellValue("1");
                    row.CreateCell(2).SetCellValue("測試第一題");
                    row.CreateCell(3).SetCellValue("radio");
                    row.CreateCell(4).SetCellValue("1");
                    row = (XSSFRow)sheet.CreateRow(6);
                    row.CreateCell(1).SetCellValue("1");
                    row.CreateCell(2).SetCellValue("是");
                    row.CreateCell(5).SetCellValue("1");
                    dbparamlist.Clear();
                    string date = datetime.sqldate("mssql", "epaperstring"), time = datetime.sqltime("mssql", "epaperstring"), cuname = Dns.GetHostEntry(clientip).HostName.IndexOf('.') == -1 ? Dns.GetHostEntry(clientip).HostName : Dns.GetHostEntry(clientip).HostName.Split('.')[0];
                    dbparamlist.Add(new dbparam("@externip", clientip));
                    dbparamlist.Add(new dbparam("@hostname", cuname));
                    dbparamlist.Add(new dbparam("@stdate", stdate));
                    dbparamlist.Add(new dbparam("@sttime", sttime));
                    dbparamlist.Add(new dbparam("@endate", date));
                    dbparamlist.Add(new dbparam("@entime", time));
                    dbparamlist.Add(new dbparam("@indate", date));
                    dbparamlist.Add(new dbparam("@intime", time));
                    dbparamlist.Add(new dbparam("@inoper", newid));
                    database.checkActiveSql("mssql", "flyformstring", "insert into web.examplelog (externip,hostname,stdate,sttime,endate,entime,indate,intime,inoper) values (@externip,@hostname,@stdate,@sttime,@endate,@entime,@indate,@intime,@inoper);", dbparamlist);
                    filename = $"{mainRows.Rows[0]["username"].ToString().TrimEnd()}匯入表單範本";
                    break;
            }
            MemoryStream ms = new MemoryStream();
            workbook.Write(ms);
            byte[] bytes = ms.ToArray();
            return File(bytes, "application/vnd.ms-excel", $"FLYTECH{filename}.xlsx");
        }

        [HttpPost]
        public async Task<JsonResult> uploadData()
        {
            if (Request.Form.Files.Count > 0)
            {
                ISheet sheet;
                database database = new database();
                string original = Request.Form.Files[0].FileName.Substring(0, Request.Form.Files[0].FileName.LastIndexOf('.')), extension = Path.GetExtension(Request.Form.Files[0].FileName).ToLower();
                using (var fileStream = new FileStream(database.connectionString("formFiles") + original + extension, FileMode.Create))
                {
                    await Request.Form.Files[0].CopyToAsync(fileStream);
                    fileStream.Position = 0;
                    switch (extension)
                    {
                        case ".xls":
                            HSSFWorkbook hSSFWorkbook = new HSSFWorkbook(fileStream);
                            sheet = (XSSFSheet)hSSFWorkbook.GetSheetAt(0);
                            break;
                        case ".xlsx":
                            XSSFWorkbook xSSFWorkbook = new XSSFWorkbook(fileStream);
                            sheet = (XSSFSheet)xSSFWorkbook.GetSheetAt(0);
                            break;
                        default:
                            return Json(new sExcelModels() { status = "nodata" });
                    }
                    IRow row = sheet.GetRow(1);
                    datetime datetime = new datetime();
                    List<dbparam> dbparamlist = new List<dbparam>();
                    dbparamlist.Add(new dbparam("@formId", checkNullObject(row.GetCell(1))));
                    bool showSafe = database.checkSelectSql("mssql", "flyformstring", "exec web.checkmainformId @formId;", dbparamlist).Rows.Count > 0;
                    string formId = showSafe ? checkNullObject(row.GetCell(1)) : new sha256().new256("mssql", "flyformstring"), tile = checkNullObject(row.GetCell(3)) == "" ? "noTitle" : checkNullObject(row.GetCell(3)), desc = checkNullObject(row.GetCell(5)), date = datetime.sqldate("mssql", "flyformstring"), time = datetime.sqltime("mssql", "flyformstring");
                    switch (showSafe)
                    {
                        case true:
                            if (database.checkActiveSql("mssql", "flyformstring", "exec web.deleteformdeta @formId;", dbparamlist) != "istrue")
                            {
                                return Json(new sExcelModels() { status = "error" });
                            }
                            break;
                    }
                    string iid = "";
                    int i = 5, number = 0;
                    while (i <= sheet.LastRowNum)
                    {
                        row = sheet.GetRow(i);
                        switch (checkNullObject(row.GetCell(0)))
                        {
                            case "":
                                switch (iid)
                                {
                                    case "":
                                        return Json(new sExcelModels() { status = "error" });
                                }
                                if (checkNullObject(row.GetCell(1)) != "")
                                {
                                    dbparamlist.Clear();
                                    dbparamlist.Add(new dbparam("@formId", formId));
                                    dbparamlist.Add(new dbparam("@iid", iid));
                                    dbparamlist.Add(new dbparam("@id", checkNullObject(row.GetCell(1))));
                                    dbparamlist.Add(new dbparam("@value", checkNullObject(row.GetCell(2))));
                                    dbparamlist.Add(new dbparam("@answer", checkBoolObject(row.GetCell(5))));
                                    dbparamlist.Add(new dbparam("@indate", date));
                                    dbparamlist.Add(new dbparam("@intime", time));
                                    if (database.checkActiveSql("mssql", "flyformstring", "insert into web.optionform (formId,iid,id,value,answer,indate,intime) values (@formId,@iid,@id,@value,@answer,@indate,@intime);", dbparamlist) != "istrue")
                                    {
                                        return Json(new sExcelModels() { status = "error" });
                                    }
                                }
                                break;
                            default:
                                iid = checkNullObject(row.GetCell(0));
                                dbparamlist.Clear();
                                dbparamlist.Add(new dbparam("@formId", formId));
                                dbparamlist.Add(new dbparam("@iid", iid));
                                dbparamlist.Add(new dbparam("@tile", checkNullObject(row.GetCell(2))));
                                dbparamlist.Add(new dbparam("@outValue", checkNullObject(row.GetCell(3))));
                                dbparamlist.Add(new dbparam("@checked", checkBoolObject(row.GetCell(4))));
                                dbparamlist.Add(new dbparam("@indate", date));
                                dbparamlist.Add(new dbparam("@intime", time));
                                if (database.checkActiveSql("mssql", "flyformstring", "insert into web.subform (formId,iid,tile,outValue,checked,indate,intime) values (@formId,@iid,@tile,@outValue,@checked,@indate,@intime);", dbparamlist) != "istrue")
                                {
                                    return Json(new sExcelModels() { status = "error" });
                                }
                                number++;
                                break;
                        }
                        i++;
                    }
                    row = sheet.GetRow(2);
                    dbparamlist.Clear();
                    dbparamlist.Add(new dbparam("@formId", formId));
                    dbparamlist.Add(new dbparam("@tile", tile));
                    dbparamlist.Add(new dbparam("@desc", desc));
                    dbparamlist.Add(new dbparam("@stdate", checkNullObject(row.GetCell(1))));
                    dbparamlist.Add(new dbparam("@sttime", checkNullObject(row.GetCell(3))));
                    dbparamlist.Add(new dbparam("@endate", checkNullObject(row.GetCell(5))));
                    dbparamlist.Add(new dbparam("@entime", checkNullObject(row.GetCell(7))));
                    dbparamlist.Add(new dbparam("@examed", checkBoolObject(row.GetCell(9))));
                    dbparamlist.Add(new dbparam("@restarted", checkBoolObject(row.GetCell(11))));
                    dbparamlist.Add(new dbparam("@limited", checkBoolObject(row.GetCell(13))));
                    dbparamlist.Add(new dbparam("@randopt", checkBoolObject(row.GetCell(15))));
                    dbparamlist.Add(new dbparam("@randsub", checkBoolObject(row.GetCell(17))));
                    dbparamlist.Add(new dbparam("@number", checkNullObject(row.GetCell(19)) == "" || checkNullObject(row.GetCell(19)) == "0" ? number.ToString().TrimEnd() : checkNullObject(row.GetCell(19))));
                    dbparamlist.Add(new dbparam("@indate", date));
                    dbparamlist.Add(new dbparam("@intime", time));
                    if (database.checkActiveSql("mssql", "flyformstring", "insert into web.mainform (formId,tile,[desc],stdate,sttime,endate,entime,examed,restarted,limited,randopt,randsub,number,indate,intime) values (@formId,@tile,@desc,@stdate,@sttime,@endate,@entime,@examed,@restarted,@limited,@randopt,@randsub,@number,@indate,@intime);", dbparamlist) != "istrue")
                    {
                        return Json(new sExcelModels() { status = "error" });
                    }
                    return Json(new sExcelModels() { formId = formId, status = "istrue" });
                }
            }
            return Json(new sExcelModels() { status = "nodata" });
        }

        public string checkNullObject(object value)
        {
            switch (value)
            {
                case null:
                    return "";
            }
            return value.ToString().TrimEnd();
        }

        public string checkBoolObject(object value)
        {
            switch (value)
            {
                case null:
                    return "1";
            }
            switch (value.ToString().TrimEnd())
            {
                case "1":
                    return "1";
            }
            return "0";
        }

        public ActionResult excelData(string formid, string newid)
        {
            string filename = "", clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            XSSFWorkbook workbook = new XSSFWorkbook();
            XSSFSheet sheet = (XSSFSheet)workbook.CreateSheet("填寫分數");
            XSSFRow row = (XSSFRow)sheet.CreateRow(0);
            database database = new database();
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formid", formid));
            dbparamlist.Add(new dbparam("@inoper", newid));
            mainRows = database.checkSelectSql("mssql", "flyformstring", "select tile from web.mainform where formId = @formid and inoper = @inoper;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    row.CreateCell(0).SetCellValue("NOT YOUR INFORMATION ABOUT THIS FORM DATABASE");
                    filename = "沒資料呈現";
                    break;
                default:
                    int i = 1;
                    foreach (DataRow dr in database.checkSelectSql("mssql", "flyformstring", "exec web.showscoreitems @formid,@inoper;", dbparamlist).Rows)
                    {
                        dbparamlist.Clear();
                        row = (XSSFRow)sheet.CreateRow(i);
                        dbparamlist.Add(new dbparam("@newid", dr["inoper"].ToString().TrimEnd()));
                        row.CreateCell(0).SetCellValue(database.checkSelectSql("mssql", "epaperstring", "exec web.checksitename @newid;", dbparamlist).Rows[0]["username"].ToString().TrimEnd());
                        row.CreateCell(1).SetCellValue($"{dr["score"].ToString().TrimEnd()}分");
                    }
                    filename = mainRows.Rows[0]["tile"].ToString().TrimEnd();
                    break;
            }
            MemoryStream ms = new MemoryStream();
            workbook.Write(ms);
            byte[] bytes = ms.ToArray();
            return File(bytes, "application/vnd.ms-excel", $"FLYTECH{filename}.xlsx");
        }
    }
}