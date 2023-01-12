using FORMINFOCore.Models;
using Microsoft.AspNetCore.Mvc;

namespace FORMINFOCore.Controllers
{
    public class FormorController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public JsonResult searchData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new FormorClass().GetSearchModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult sTypeData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new FormorClass().GetSTypeModels(otherData, clientip));
        }

        [HttpPost]
        public JsonResult sVeriData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new FormorClass().GetSVeriModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult addData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new FormorClass().GetAddModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult insertData([FromBody] iFormsData iFormsData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new FormorClass().GetInsertModels(iFormsData, clientip));
        }

        [HttpPost]
        public JsonResult sLimitData([FromBody] userData userData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new FormorClass().GetSlimitModels(userData, clientip));
        }

        [HttpPost]
        public JsonResult sOperData([FromBody] otherData otherData)
        {
            string clientip = Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd() == "::1" ? "127.0.0.1" : Request.HttpContext.Connection.RemoteIpAddress.ToString().TrimEnd();
            return Json(new FormorClass().GetSoperModels(otherData, clientip));
        }
    }
}