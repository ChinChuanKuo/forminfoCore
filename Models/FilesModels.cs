using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Net;
using forminfoCore.App_Code;
using Spire.Doc;
using Spire.Presentation;
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

        public sSiteModels GetTransferModels(sFileData sFileData, string cuurip)
        {
            database database = new database();
            string foldPath = new database().connectionString("folderFiles"), encryption = new sha256().new256("mssql", "flyfnstring"), extension = "pdf";
            switch (File.Exists($"{foldPath}{sFileData.original.TrimEnd()}({sFileData.encryption.TrimEnd()}){sFileData.extension.TrimEnd()}"))
            {
                case false:
                    return new sSiteModels() { status = "nodata" };
            }
            DataTable mainRows = new DataTable();
            List<dbparam> dbparamlist = new List<dbparam>();
            dbparamlist.Add(new dbparam("@value", extension));
            dbparamlist.Add(new dbparam("@needed", "1"));
            mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.uploadfileform @value,@needed;", dbparamlist);
            switch (mainRows.Rows.Count)
            {
                case 0:
                    return new sSiteModels() { status = "nodata" };
            }
            if (mainRows.Rows[0]["flImages"].ToString().TrimEnd() == "0" && mainRows.Rows[0]["flVideos"].ToString().TrimEnd() == "0" && mainRows.Rows[0]["flAudios"].ToString().TrimEnd() == "0")
            {
                return new sSiteModels() { status = "nodata" };
            }
            switch (transFileToPDF(sFileData.extension.TrimEnd(), $"{foldPath}{sFileData.original.TrimEnd()}({sFileData.encryption.TrimEnd()}){sFileData.extension.TrimEnd()}", $"{foldPath}{sFileData.original.TrimEnd()}({encryption}).{extension}"))
            {
                case false:
                    return new sSiteModels() { status = "nodata" };
            }
            return new sSiteModels() { images = mainRows.Rows[0]["flImages"].ToString().TrimEnd() == "1", videos = mainRows.Rows[0]["flVideos"].ToString().TrimEnd() == "1", audios = mainRows.Rows[0]["flAudios"].ToString().TrimEnd() == "1", src = mainRows.Rows[0]["flImages"].ToString().TrimEnd() == "1" && mainRows.Rows[0]["flShowed"].ToString().TrimEnd() == "0" ? $"{mainRows.Rows[0]["original"].ToString().TrimEnd()}({mainRows.Rows[0]["encryption"].ToString().TrimEnd()}){mainRows.Rows[0]["extension"].ToString().TrimEnd()}" : $"{sFileData.original.TrimEnd()}({encryption}).{extension}", imagePath = "http://221.222.222.16:4500/folderfile/", original = sFileData.original.TrimEnd(), encryption = encryption, extension = $".{extension}", date = new datetime().sqldate("mssql", "flyfnstring"), status = "istrue" };
        }

        public bool transFileToPDF(string extension, string originalPath, string savePath)
        {
            switch (extension)
            {
                case ".xls":
                case ".xlsx":
                    return transExcelToPDF(originalPath, savePath);
                case ".doc":
                case ".docx":
                    return transWordToPDF(originalPath, savePath);
                case ".ppt":
                case ".pptx":
                    return transPowerPointToPDF(originalPath, savePath);
            }
            return false;
        }

        public bool transExcelToPDF(string originalPath, string savePath)
        {
            Workbook workbook = new Workbook();
            workbook.LoadFromFile(originalPath, ExcelVersion.Version2010);
            workbook.SaveToFile(savePath, Spire.Xls.FileFormat.PDF);
            return File.Exists(savePath);
        }

        public bool transWordToPDF(string originalPath, string savePath)
        {
            Document document = new Document();
            document.LoadFromFile(originalPath);
            document.SaveToFile(savePath, Spire.Doc.FileFormat.PDF);
            return File.Exists(savePath);
        }

        public bool transPowerPointToPDF(string originalPath, string savePath)
        {
            Presentation presentation = new Presentation();
            presentation.LoadFromFile(originalPath);
            presentation.SaveToFile(savePath, Spire.Presentation.FileFormat.PDF);
            return File.Exists(savePath);
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