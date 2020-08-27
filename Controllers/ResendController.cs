using Microsoft.AspNetCore.Mvc;
using folderCore.Models;

namespace folderCore.Controllers
{
    public class ResendController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH BTS";
            return View();
        }

        [HttpPost]
        public JsonResult resendUserData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ResendClass().GetResendUserModels(otherData, clientip));
        }
    }
}
