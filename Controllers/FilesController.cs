using System.Collections.Generic;
using System.Data;
using System.IO;
using System.Threading.Tasks;
using forminfoCore.App_Code;
using forminfoCore.Models;
using Microsoft.AspNetCore.Mvc;

namespace forminfoCore.Controllers
{
    public class FilesController : Controller
    {
 [HttpPost]
        public async Task<JsonResult> uploadData()
        {
            if (Request.Form.Files.Count > 0)
            {
                string original = Request.Form.Files[0].FileName.Substring(0, Request.Form.Files[0].FileName.LastIndexOf('.')), encryption = new sha256().new256("mssql", "flyfnstring"), extension = Path.GetExtension(Request.Form.Files[0].FileName);
                database database = new database();
                DataTable mainRows = new DataTable();
                List<dbparam> dbparamlist = new List<dbparam>();
                dbparamlist.Add(new dbparam("@value", extension.Replace(".", "").Trim().ToLower()));
                dbparamlist.Add(new dbparam("@needed", "1"));
                mainRows = database.checkSelectSql("mssql", "flyfnstring", "exec web.uploadfileform @value,@needed;", dbparamlist);
                switch (mainRows.Rows.Count)
                {
                    case 0:
                        return Json(new sSiteModels() { status = "nodata" });
                }
                if (mainRows.Rows[0]["flImages"].ToString().TrimEnd() == "0" && mainRows.Rows[0]["flVideos"].ToString().TrimEnd() == "0" && mainRows.Rows[0]["flAudios"].ToString().TrimEnd() == "0")
                {
                    return Json(new sSiteModels() { status = "nodata" });
                }
                using (var fileStream = new FileStream($"{database.connectionString("formFiles")}{original}({encryption}){extension}", FileMode.Create))
                {
                    await Request.Form.Files[0].CopyToAsync(fileStream);
                    return Json(new sSiteModels() { images = mainRows.Rows[0]["flImages"].ToString().TrimEnd() == "1", videos = mainRows.Rows[0]["flVideos"].ToString().TrimEnd() == "1", audios = mainRows.Rows[0]["flAudios"].ToString().TrimEnd() == "1", src = mainRows.Rows[0]["flImages"].ToString().TrimEnd() == "1" && mainRows.Rows[0]["flShowed"].ToString().TrimEnd() == "0" ? $"{mainRows.Rows[0]["original"].ToString().TrimEnd()}({mainRows.Rows[0]["encryption"].ToString().TrimEnd()}){mainRows.Rows[0]["extension"].ToString().TrimEnd()}" : $"{original}({encryption}){extension}", imagePath = "http://221.222.222.16:4500/folderfile/", original = original, encryption = encryption, extension = extension, date = new datetime().sqldate("mssql", "flyfnstring"), status = "istrue" });
                }
            }
            return Json(new sSiteModels() { status = "nodata" });
        }

        [HttpPost]
        public JsonResult websiteData([FromBody] sRowsData sRowsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd(), userAgent = Request.Headers["user-Agent"].ToString().TrimEnd();
            return Json(new FilesClass().GetWebsiteModels(sRowsData, clientip, userAgent));
        }

        [HttpPost]
        public JsonResult downloadData([FromBody] sRowsData sRowsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd(), userAgent = Request.Headers["user-Agent"].ToString().TrimEnd();
            return Json(new FilesClass().GetDownloadModels(sRowsData, clientip, userAgent));
        }

        [HttpPost]
        public JsonResult transferData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd(), userAgent = Request.Headers["user-Agent"].ToString().TrimEnd();
            return Json(new FilesClass().GetTransferModels(otherData, clientip));
        }
    }
}