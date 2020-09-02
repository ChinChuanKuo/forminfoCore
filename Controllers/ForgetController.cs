using Microsoft.AspNetCore.Mvc;
using forminfoCore.Models;

namespace forminfoCore.Controllers
{
    public class ForgetController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH BTS";
            return View();
        }

        [HttpPost]
        public JsonResult forgetUserData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ForgetClass().GetForgetUserModels(otherData, clientip));
        }
    }
}
