using forminfoCore.Models;
using Microsoft.AspNetCore.Mvc;

namespace forminfoCore.Controllers
{
    public class ProformController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public JsonResult pollingData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ProformClass().GetPollingModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult searchData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new ProformClass().GetSearchModels(userData, clientip));
        }
    }
}