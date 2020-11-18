using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Net;
using forminfoCore.App_Code;
using Spire.Xls;

namespace forminfoCore.Models
{
    public class FilesClass
    {
        public sSiteModels GetWebsiteModels(sRowsData sRowsData, string cuurip, string userAgent)
        {
            database database = new database();
            datetime datetime = new datetime();
            string stdate = datetime.sqldate("mssql", "flyformstring"), sttime = datetime.sqltime("mssql", "flyformstring"), original = "", encryption = new sha256().new256("mssql", "flyformstring"), extension = ".jpg";
            new WebClient().DownloadFile(sRowsData.value.TrimEnd(), $"{database.connectionString("formFiles")}{original}({encryption}){extension}");
            List<dbparam> dbparamlist = new List<dbparam>();
            string date = datetime.sqldate("mssql", "flyformstring"), time = datetime.sqltime("mssql", "flyformstring"), cuname = Dns.GetHostEntry(cuurip).HostName.IndexOf('.') == -1 ? Dns.GetHostEntry(cuurip).HostName : Dns.GetHostEntry(cuurip).HostName.Split('.')[0];
            dbparamlist.Add(new dbparam("@formId", sRowsData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@website", sRowsData.value.TrimEnd()));
            dbparamlist.Add(new dbparam("@externip", cuurip));
            dbparamlist.Add(new dbparam("@hostname", cuname));
            dbparamlist.Add(new dbparam("@browser", new information().browser(userAgent)));
            dbparamlist.Add(new dbparam("@stdate", stdate));
            dbparamlist.Add(new dbparam("@sttime", sttime));
            dbparamlist.Add(new dbparam("@eddate", date));
            dbparamlist.Add(new dbparam("@edtime", time));
            dbparamlist.Add(new dbparam("@indate", date));
            dbparamlist.Add(new dbparam("@intime", time));
            dbparamlist.Add(new dbparam("@inoper", sRowsData.newid.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyformstring", "insert into web.websitelog (formId,website,externip,hostname,browser,stdate,sttime,eddate,edtime,indate,intime,inoper) values (@formId,@website,@externip,@hostname,@browser,@stdate,@sttime,@eddate,@edtime,@indate,@intime,@inoper);", dbparamlist) != "istrue")
            {
                return new sSiteModels() { status = "error" };
            }
            switch (File.Exists($"{database.connectionString("formFiles")}{original}({encryption}){extension}"))
            {
                case false:
                    return new sSiteModels() { status = "nodata" };
            }
            return new sSiteModels() { images = true, videos = false, audios = false, src = $"{original}({encryption}){extension}", imagePath = "http://221.222.222.16:4500/bugimage/", original = original, encryption = encryption, extension = extension, status = "istrue" };
        }

        public statusModels GetDownloadModels(sRowsData sRowsData, string cuurip, string userAgent)
        {
            database database = new database();
            datetime datetime = new datetime();
            string stdate = datetime.sqldate("mssql", "flyformstring"), sttime = datetime.sqltime("mssql", "flyformstring");
            switch (File.Exists(database.connectionString("formFiles") + sRowsData.value.TrimEnd()))
            {
                case false:
                    return new statusModels() { status = "nodata" };
            }
            string date = datetime.sqldate("mssql", "flyformstring"), time = datetime.sqltime("mssql", "flyformstring"), cuname = Dns.GetHostEntry(cuurip).HostName.IndexOf('.') == -1 ? Dns.GetHostEntry(cuurip).HostName : Dns.GetHostEntry(cuurip).HostName.Split('.')[0];
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@formId", sRowsData.formId.TrimEnd()));
            dbparamlist.Add(new dbparam("@files", sRowsData.value.TrimEnd()));
            dbparamlist.Add(new dbparam("@externip", cuurip));
            dbparamlist.Add(new dbparam("@hostname", cuname));
            dbparamlist.Add(new dbparam("@browser", new information().browser(userAgent)));
            dbparamlist.Add(new dbparam("@stdate", stdate));
            dbparamlist.Add(new dbparam("@sttime", sttime));
            dbparamlist.Add(new dbparam("@eddate", date));
            dbparamlist.Add(new dbparam("@edtime", time));
            dbparamlist.Add(new dbparam("@indate", date));
            dbparamlist.Add(new dbparam("@intime", time));
            dbparamlist.Add(new dbparam("@inoper", sRowsData.newid.TrimEnd()));
            if (database.checkActiveSql("mssql", "flyformstring", "insert into web.downloadlog (formId,files,externip,hostname,browser,stdate,sttime,eddate,edtime,indate,intime,inoper) values (@formId,@files,@externip,@hostname,@browser,@stdate,@sttime,@eddate,@edtime,@indate,@intime,@inoper);", dbparamlist) != "istrue")
            {
                return new statusModels() { status = "error" };
            }
            return new statusModels() { status = "istrue" };
        }

        public sSiteModels GetTransferModels(otherData otherData, string cuurip)
        {
            switch (string.IsNullOrWhiteSpace(otherData.values))
            {
                case true:
                    return new sSiteModels() { status = "nodata" };
            }
            Workbook workbook = new Workbook();
            workbook.LoadFromFile(new database().connectionString("formFiles") + otherData.values.TrimEnd(), ExcelVersion.Version2010);
            workbook.SaveToFile(@"..\..\result.pdf", Spire.Xls.FileFormat.PDF);
            return new sSiteModels() { status = "istrue" };
        }

        public string GetFileType(string extension)
        {
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@value", extension.Replace(".", "").ToLower()));
            dbparamlist.Add(new dbparam("@needed", "1"));
            mainRows = new database().checkSelectSql("mssql", "epaperstring", "exec web.searchfiletype @value,@needed;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return "OTHER";
            }
            return mainRows.Rows[0]["flTitle"].ToString().TrimEnd();
        }

        public long GetFileCapacity(string filename)
        {
            return new System.IO.FileInfo(new database().connectionString("formFiles") + filename).Length;
        }
    }
}