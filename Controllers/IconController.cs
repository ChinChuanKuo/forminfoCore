using folderCore.Models;
using Microsoft.AspNetCore.Mvc;

namespace folderCore.Controllers
{
    public class IconController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH BTS";
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IconClass().GetSearchModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult insertData([FromBody] iIconData iIconData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new IconClass().GetInsertModels(iIconData, clientip));
        }
    }
}