using Microsoft.AspNetCore.Mvc;
using FORMINFOCore.Models;

namespace FORMINFOCore.Controllers
{
    public class SignupController : Controller
    {
        public IActionResult Index()
        {
            ViewBag.Title = "FLYTECH BTS";
            return View();
        }

        [HttpPost]
        public JsonResult signupUserData([FromBody] signupData signupData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new SignupClass().GetSignupUserModels(signupData, clientip));
        }
    }
}
